class Persons:
    def __init__(self,person):
        self.persons = list(person)

    def __len__(self):
        return len(self.persons)

    #def __str__(self):
    #    return f"list of persons {self.persons}"

    def __repr__(self):
        return f"list of persons {self.persons}"

    def __bool__(self):
        return len(self.persons) > 0

    def __add__(self,argument):
        new_list = self.persons.copy()
        new_list.append(argument)
        return Persons(new_list)

    def __iadd__(self,argument):
        self.persons.append(argument)
        return self

    def __getitem__(self,key):
        return self.persons[key]

    def __setitem__(self,key,value):
        self.persons[key] = value

    def __radd__(self,argument):
        new_list = self.persons.copy()
        new_list.insert(0,argument)
        return Persons(new_list)

    def __eq__(self,argument):
        return (self.persons == argument.persons)

    def __ne__(self,argument):
        return (self.persons != argument.persons)

listPersons = Persons(["first","Second"])
print("Length of listPersons",len(listPersons))

#this is the same and show our object
print(listPersons)
print(str(listPersons))

#this show all methods build in class
#print(dir(listPersons))

repr(listPersons)
print(type(listPersons))

listPersons2 = Persons([])
print("If full list: {listPersons2}",bool(listPersons2))
print("If full list: {listPersons}",bool(listPersons))

#Operators (we can define more operators depends of class)

#[+,+=]
print((listPersons + "Third"))
listPersons = listPersons + "Four"
listPersons2 = "ten" + listPersons
listPersons += "Fifth"
print("List persons: ",listPersons)
print("List persons2: ",listPersons2)

#[],[] = val
print(listPersons[0])
listPersons[2] = "Third"
print(listPersons)

#[==,!=]
print(listPersons == listPersons2)
print(listPersons != listPersons2)




