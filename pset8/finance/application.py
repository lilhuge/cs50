import os       #export API_KEY=pk_419a2a2ee0d54ddaa5fae18b0eb04ec1

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():

    rows = db.execute("SELECT * FROM shares"+str(session['user_id'])+"")
    cash = db.execute("SELECT * FROM users WHERE id = :user_id", user_id = session["user_id"])
    
    if len(rows) > 0:   #if user owns any shares
 
        for row in rows:        #for each row add columns price and value
    
            symbol = row['symbol']
    
            result = lookup(symbol)
            row['price'] = (result['price'])
            row['value'] = (row['shares']*row['price'])
            row['fvalue'] = usd(row['value'])
    
    
        
        grand_total = sum(row['value'] for row in rows) + cash[0]['cash']
    
        return render_template("index.html", rows = rows, grand_total = usd(grand_total), cash = usd(cash[0]['cash']))

    else:   #return only cash
        
        return render_template("index.html", cash = usd(cash[0]['cash']), grand_total = usd(cash[0]['cash']))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        #Check symbol and shares input exists
        if not symbol:
            return apology("must provide symbol", 403)

        elif not shares:
            return apology("must provide positive iteger number of shares", 403)

        else:
            try:    #Check if integer greater than 0
                shares = int(shares)
                if shares <=0:
                   return apology("must provide positive iteger number of shares", 403)

            except ValueError:
                return apology("must provide positive iteger number of shares", 403)

            result = lookup(symbol)     #Lookup symbol

            if result == None:
                return apology("symbol not found", 402)

            else:
                cost = shares * result["price"]
                rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])
                cash = rows[0]["cash"]

                if cash < cost:
                    return apology("insufficient funds", 405)

                else:
                    db.execute("INSERT INTO transactions (user_id, type, symbol, company, shares, price, value, date_time) VALUES (?,?,?,?,?,?,?,?)",
                    session["user_id"], "Purchase", symbol, result["name"], shares, result["price"], -cost, datetime.datetime.now());
                    new_cash = cash - cost
                    db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id", new_cash = new_cash, user_id = session["user_id"])

                    existing_shares = db.execute("SELECT shares FROM shares"+str(session['user_id'])+" WHERE symbol = :symbol", symbol = symbol)

                    if len(existing_shares) != 1:

                        db.execute("CREATE TABLE IF NOT EXISTS 'shares"+str(session['user_id'])+"' ('user_id' INTEGER NOT NULL, 'symbol' TEXT NOT NULL, 'company' TEXT NOT NULL, 'shares' INTEGER DEFAULT 0)")
                        db.execute("INSERT INTO shares"+str(session['user_id'])+" (user_id, symbol, company, shares) VALUES (?,?,?,?)",
                        session["user_id"], symbol, result['name'], shares)

                    else:
                        db.execute("UPDATE shares"+str(session['user_id'])+" SET shares = :new_shares WHERE symbol = :symbol", new_shares = existing_shares[0]['shares'] + shares, symbol = symbol)


                    return render_template("buy.html")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():

    rows = db.execute("SELECT * FROM transactions WHERE user_id = :user_id", user_id = session["user_id"])

    for row in rows:

        row['fvalue'] = usd(row['value'])   #add formatted versions of value and price
        row['fprice'] = usd(row['price'])

    return render_template("history.html", rows = rows)




@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == "POST":

        #Save lookup results
        result = lookup(request.form.get("symbol"))
        if result == None:
            return apology("symbol not found", 402)
        else:

            #Return quote template with variables
            return render_template("quoted.html", name = result["name"], price = result["price"], symbol = result["symbol"])

    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        #Create variables for simplicity
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        #Check username, password and password match
        if not username:
            return apology("must provide username", 403)

        elif not password:
            return apology("must provide password", 403)

        elif password != confirmation:
            return apology("passwords do not match", 403)

        else:
            #Query database for username
            rows = db.execute("SELECT * FROM users WHERE username = :username",
                                username = username)
            if len(rows) > 0:
                return apology("username already exists")

            else:
                hashval = generate_password_hash(password)

                #Insert new user into database
                db.execute("INSERT INTO users (username, hash) VALUES (?,?)", username, hashval)
                new_id = db.execute("SELECT id FROM users WHERE username = :username", username = username)
                db.execute("CREATE TABLE IF NOT EXISTS 'shares"+str(new_id[0]['id'])+"' ('user_id' INTEGER NOT NULL, 'symbol' TEXT NOT NULL, 'company' TEXT NOT NULL, 'shares' INTEGER DEFAULT 0)")
                return render_template("login.html")

    else:
        return render_template("register.html")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    
    if request.method == "POST":
        
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        
        if not symbol:
            return apology("must provide symbol", 403)

        elif not shares:
            return apology("must provide positive iteger number of shares", 403)

        else:
            try:    #Check if integer greater than 0
                shares = int(shares)
                if shares <=0:
                   return apology("must provide positive iteger number of shares", 403)

            except ValueError:
                return apology("must provide positive iteger number of shares", 403)

        
            rows = db.execute("SELECT * FROM shares"+str(session['user_id'])+" WHERE symbol = :symbol", symbol = symbol)
            
            if len(rows) != 1:
                return apology("Shares not owned", 403)
                
            elif rows[0]['shares'] < int(shares):
                return apology("You do only have "+rows[0]['shares']+" available to sell", 403)
                
            else:
                
                result = lookup(symbol)
                profit = shares * result["price"]
                cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])
                new_cash = cash[0]['cash'] + profit
                new_shares = rows[0]['shares'] - shares
                
                #update transaction table
                db.execute("INSERT INTO transactions (user_id, type, symbol, company, shares, price, value, date_time) VALUES (?,?,?,?,?,?,?,?)",
                session["user_id"], "Sale", symbol, result["name"], shares, result["price"], profit, datetime.datetime.now());
                
                #update user cash
                db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id", new_cash = new_cash, user_id = session["user_id"])
                
                if new_shares == 0:
                    db.execute("DELETE FROM shares"+str(session['user_id'])+" WHERE symbol = :symbol", symbol = symbol);
                    
                else:
                    #update user's share table
                    db.execute("UPDATE shares"+str(session['user_id'])+" SET shares = :new_shares WHERE symbol = :symbol", new_shares = new_shares, symbol = symbol)
                
               #TOTAL CASH NOT UPDATING NEED TO FIX
                
                return render_template("sell.html")
                
    
    if request.method == "GET":
        rows = db.execute("SELECT * FROM shares"+str(session['user_id'])+"")
    
        return  render_template("sell.html", rows = rows)
    


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
