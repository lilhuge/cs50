from cs50 import get_string


def main():
    
    text = get_string("Text: ")
    text = text.lower()
    
    print(text)
    words, ltrs, sents = count(text)

    L = (ltrs / words) * 100
    S = (sents / words) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    
    result(index)


def count(n):
    
    words = 1
    ltrs = 0
    sents = 0
    
    for i in n:
        
        if i.isalpha() == True:
            
            ltrs += 1
            
        if i == " ":

            words += 1
            
        if i in ["!","?","."]:
            
            sents += 1
            
    return words, ltrs, sents

def result(y):
    
    if y < 1:
        
        print("Before Grade 1")
        
    elif y > 1 and y < 16:
        
        print(f"Grade {y}")
        
    else:
        
        print("Grade 16+")
        
 
main()