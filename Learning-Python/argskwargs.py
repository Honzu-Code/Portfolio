def add_somethink(*args,**kwargs):
    print(f"args {args}")
    print(f"kwargs {kwargs}")

add_somethink(1,2,first=3,second=4,third=2)
