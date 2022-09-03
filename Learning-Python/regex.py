import re

example1 = "Ffa125fart+ "

if "123" in example1:
    print("Yes in example1")

print("123 in string example1:",example1.find("123"))

print("Research for any number 3*[0-9]: ",re.search("[0-9][0-9][0-9]",example1))
print("Research for number from 1 to 5 with . operator: ",re.search("1.5",example1))
print("Research for any operator: ",re.search("[+]",example1))
print("Research for string if last character pass: ",re.search("far[z,g,h,t]",example1))
print("First small letter: ",re.search("[a-z]",example1))
print("Any alphanumeric word character: ",re.search("\w",example1))
print("Any special word character: ",re.search("\W",example1))
print("Any digital number: ",re.search("\d",example1))
print("Any no digital number: ",re.search("\D",example1))
print("Any space from word: ",re.search("\s",example1))
print("Any no space from word: ",re.search("\S",example1))


print("if backslash is in string: ",re.search(r"\\",r"  \\ "))
print("if word is on begining string: ",re.search("^ard","arduino"))
print("if word is on end of string: ",re.search("ino$","arduino"))
print("if word is begin or end of string: ",re.search(r"\bard","arduino"))
print("if word is no begin and end of string: ",re.search(r"\Bdu\B","arduino"))


print("if word have 0 or more symbol -",re.search("one-*two","onetwo"))
print("if word have 0 or more symbol -",re.search("one-*two","one-two"))
print("if word have 0 or more symbol -",re.search("one-*two","one--two"))

print("if word have 1 or more symbol -",re.search("one-+two","onetwo"))
print("if word have 1 or more symbol -",re.search("one-+two","one-two"))
print("if word have 1 or more symbol -",re.search("one-+two","one--two"))

print("if word have 0 or 1 symbol -",re.search("one-?two","onetwo"))
print("if word have 0 or 1 symbol -",re.search("one-?two","one-two"))
print("if word have 0 or 1 symbol -",re.search("one-?two","one--two"))

print(r"this operator {} have a much combination example {m,n} {m,} {,n} {,}")
print("If symbol is in word 4 times - ",re.search("z-{4}z","z----z"))

print("groups of searching: ")
print("if word exist one or more this in string: ",re.search("(one)+"," two oneone two"))

print("return of searching: ","(\w+),(\w+) like,word,programming")
value = re.search("(\w+),(\w+)","like,word,programming")
print(value.groups())
print(value.group(1))
print(value.group(2))
print(value.group(2,1))
print((value.group(2),value.group(1)))
