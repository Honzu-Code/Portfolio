#mode w = write

with open("hello.txt", mode="r") as file:
    print(file.read())


#we can read a file and in the same block of code save to file
#with open("input.txt") as in_file, open("output.txt", "w") as out_file:
#this with have methods which we calls as __enter__() and __exit__()
#enter is execute in the start
#exit is execute on the end of with and return also state of this block if error raises or like this
#always after with we can't write again to file because with have almost safe closing files
#we can use with with threading, with async, and also we can write sample class based on this context manager :

class HelloContextManager:
    def __enter__(self):
        print("Entering the context...")
        return "Hello, World!"
    def __exit__(self, exc_type, exc_value, exc_tb):
        print("Leaving the context...")
        print(exc_type, exc_value, exc_tb, sep="\n")

with HelloContextManager() as hello:
    print(hello)

#if we want to get access to index out of range this exc_type,_exc_value,_exc_tb will return not None value:

#with HelloContextManager() as hello:
#    print(hello)
#    hello[100]

#<class 'IndexError'>
#string index out of range
#<traceback object at 0x7fe417af79c0>
