text = "onetwothree"
exampleList = [1,2,3]

def function(arg):
    print(f"arg = {arg}")

class Object:
    pass

#if we use without __main__ print statements this can cause problem with printing in other modules after importing this module
#print("Two")

if __name__ == "__main__":
    print("Two")
