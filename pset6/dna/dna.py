from cs50 import get_int, get_string
import csv
from dataclasses import dataclass
from sys import argv


def main():
    
    if len(argv) != 3:                      #check for 2 arguments
    
        print("2 arguments required!")      #return error if not 2 arguments
    
    with open(argv[1], "r") as file:        #open database csv
    
        datab = list(csv.reader(file))      #save CSV data into memory as list
    
    STR = datab[0]                          #define STRs from first row of database list
    STR.remove('name')                      #remove 'name' from list
    
    with open(argv[2], "r") as file:        #open sequence CSV
    
        sample = file.read().replace('\n', '')           #save sequence into memory as string 'sample'
    longest = []
    
    for STR_i in STR:                   #for each STR in the list of STRs
        maxi = 0                            #define max count
        
        for j in range(len(sample)):        #using each char in the sample as a starting point
            
            count = check(sample, STR_i, j, 0)  #run check function, return count
        
            if count > maxi:                    #if count greater than current max, update
                maxi = count
     
        longest.append(maxi)                   #add to longest list

    compare = [0]*len(STR)                      #initialize compare list
                                                        
    for i in range(1, len(datab)):                      #for each row ignoring tow row of STR names
        
        for j in range(len(STR)):                       #for each element of compare list
            
            compare[j] = int(datab[i][j + 1])           #set compare
            
        if compare == longest:       #checks to see if data base matches longest list
                
            name = datab[i][0]
            print(f"match with {name}'s DNA")           #if match print name
                
            exit (0)
            
    print("No matches found")                           #if not return no matches
    
    exit(1)
            


def check(sample, STR_i, y, count):
    
    #print(sample[y : y + len(STR_i)])
    if sample[y : y + len(STR_i)] == STR_i:

        count += 1
        #print(count)
        return check(sample, STR_i, y + len(STR_i), count)
        
    else:
        
        return count
        


main()








# substring string[i:j]