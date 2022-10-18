from cs50 import SQL
import csv
from sys import argv

db = SQL("sqlite:///students.db")

if len(argv) != 2:
    
    print("INPUT ERROR - Single argument required")
    exit(1)
    
with open(argv[1], "r") as file:
    reader = csv.DictReader(file)
    
    for row in reader:
        
        
        name = row["name"] 
        names = name.split()
        house = row["house"]
        birth = row["birth"]
        
        if len(names) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?)", names[0], names[1], names[2], house, birth)
        
        elif len(names) == 2:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES (?,?,?,?)", names[0], names[1], house, birth)
        

