from cs50 import get_int

while True:
    height = get_int("Input pyramid height (between 1-8): ")
    if (height > 0 and height < 9):
        break
for i in range(height):
    print(" " * (height - (i + 1) ), "#" * (i + 1), "  ", "#" * (i + 1))
    
    
