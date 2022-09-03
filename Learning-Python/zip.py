letters = ['a','b','c']
numbers = [0,1,2]

#example using zip
print("#1 ",list(zip(letters,numbers)))

#we can also use zip for packing one list
print("#2 ",list(zip(letters)))

#and also for more than 2 lists if we have 3 3 2 lists zip will package this to 3 3 and skip last
words = ["first","second","third"]
print("#3 ",list(zip(letters,numbers,words)))

for i,(elem1,elem2) in enumerate(zip(letters,numbers),start=1):
    print(f"iteration = {i}")
    print(f"element1 = {elem1}")
    print(f"element2 = {elem2}")

#good example of using zip with loop

before_sales = [120,540,230]
after_sales = [90,400,200]

for i,(elem1,elem2) in enumerate(zip(before_sales,after_sales),start=1):
    cheaper = elem1 - elem2
    print(f"#{i} is cheaper {cheaper} money")

#conversion 2 lists to dict example
print(dict(zip(letters,numbers)))
