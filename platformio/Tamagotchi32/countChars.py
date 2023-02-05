import os
from os.path import join

num_chars = 0


# Python implementation to compute
# number of characters, words, spaces
# and lines in a file
 
# Function to count number
# of characters, words, spaces
# and lines in a file
def counter(fname):
     
    # variable to store total word count
    num_words = 0
     
    # variable to store total line count
    num_lines = 0
     
    # variable to store total character count
    num_charc = 0
     
    # variable to store total space count
    num_spaces = 0
     
    # opening file using with() method
    # so that file gets closed
    # after completion of work
    with open(fname, 'r') as f:
         
        # loop to iterate file
        # line by line
        for line in f:
             
            # separating a line
            # from \n character
            # and storing again in line
            # variable for further operations
            line = line.strip(os.linesep)
             
            # splitting the line
            # to make a list of
            # all the words present
            # in that line and storing
            # that list in
            # wordlist variable
            wordslist = line.split()
             
            # incrementing value of
            # num_lines with each
            # iteration of loop to
            # store total line count
            num_lines = num_lines + 1
             
            # incrementing value of
            # num_words by the
            # number of items in the
            # list wordlist
            num_words = num_words + len(wordslist)
             
            # incrementing value of
            # num_charc by 1 whenever
            # value of variable c is other
            # than white space in the separated line
            num_charc = num_charc + sum(1 for c in line
                        if c not in (os.linesep, ' '))
             
            # incrementing value of
            # num_spaces by 1 whenever
            # value of variable s is
            # white space in the separated line
            num_spaces = num_spaces + sum(1 for s in line
                                if s in (os.linesep, ' '))
     
    # printing total word count
    print("Number of words in text file: ",
          num_words)
     
    # printing total line count
    print("Number of lines in text file: ",
          num_lines)
     
    # printing total character count
    print("Number of characters in text file: ",
          num_charc)
     
    # printing total space count
    print("Number of spaces in text file: ",
          num_spaces)
     


for root, dirs, files in os.walk('./lib'):
    # print(root)
    # print(sum(getsize(join(root, name)) for name in files), end=" ")
    for name in files:
        counter(join(root, name))
        with open(join(root, name), "r") as file:
            filename = file.read()
            num_chars += sum(len(word) for word in filename)

    if 'CVS' in dirs:
        dirs.remove('CVS')  # don't visit CVS directories
        
print(num_chars)