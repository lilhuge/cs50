from cs50 import get_int

n = get_int("Number: ")         #Declare variables used
i = 0
total = 0

while n > 0:            #While loop identifies and sums each digit of number
    
    i += 1              #Counter i identifies digit and counts total No digits
    digit = n % 10
    #print(n,i,digit)       Testing
    if i % 2 == 0:
        
        digit *= 2          #Starting with penultimate digit, every other digit is *2
        
        if digit > 9:
            
            digit = 1 + (digit % 10)
            
    total = total + digit
    
    if (n > 9 and n < 100):
        
        n_2 = n
        
    n = int(n / 10) 
#print(total)               Testing

if (total % 10 == 0):
    
    if i == 15 and (n_2 == 34 or n_2 == 37):
        
        print("AMEX")
        
    elif i == 16 and (n_2 == 51 or n_2 == 52 or n_2 == 53 or n_2 == 54 or n_2 == 55):
        
        print("MASTERCARD")
        
    elif (i == 13 or i == 16) and n_2 / 10 == 4:
        
        print("VISA")
        
else:
        
    print("INVALID")
        
        
    
         
    
    
