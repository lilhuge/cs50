from cs50 import SQL
import csv
from sys import argv

db = SQL("sqlite:///students.db")

if len(argv) != 2:
    
    print("INPUT ERROR - Single argument required")
    exit(1)
    
roster = db.execute("SELECT * FROM students where house == ? ORDER BY last, first", argv[1])

for row in roster:
    
    if row["middle"] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
        