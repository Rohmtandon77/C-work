#                                        string formatting

num = 50
print(f"Is this number even? {True if num%2==0 else False}")

from string import Template

a1 = 'where'
a2 = 'what'

n = Template("Hello, can you figure out $n1 you are, and $n2 this is?")
print(n.substitute(n1=a1, n2=a2))

#                                           Conditionals

age = 20
message = "Legal" if age>= 21 else "Not legal yet"
print (message)


#                                           File handling

import pandas as pd
csvfile= pd.read_csv('/Users/rohmtandon/Downloads/train.csv')
#print(csvfile)

rand=[]
with open('/Users/rohmtandon/Desktop/file1.txt', "r") as reader:
    for line in reader.readlines():
        rand.append(line)
    for line in reader.readlines():
        print(line)
print(rand)
reader.close()

with open('/Users/rohmtandon/Desktop/file1.txt', "w") as writer:
    writer.write("Hello, lets see if this works\n")
    for n in range(0,len(rand)):
        writer.write(rand[n])

#                                           Regex

import re
pattern = "[a-zA-Z0-9]+@[a-zA-Z0-9]+\.(com|edu|net)"
user_inp=input("enter email address")
if re.search(pattern, user_inp):
    print("Valid email")
else:
    print("invalid email")

while True:  #this program is useless but I just wanted to practice a couple different regex things
    inp=input("phone number: ")
    if "-" in inp:
        numb_patt="(\d\d\d)-(\d\d\d)-(\d\d\d\d)"
        new_patt= r"\1\2\3"
        new_inp= re.sub(numb_patt, new_patt, inp)
        print(new_inp)
        break
    else:
        numb_patt="[0-9]{10}"
        if re.search(numb_patt,inp):
            print("Please type the number using - after area code")
