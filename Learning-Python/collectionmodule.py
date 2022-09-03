from collections import namedtuple,deque,defaultdict,OrderedDict,Counter,UserString,UserList,UserDict

#namedtuple

#we can use . operator instead index like in normal tuple

regularTuple = (1,2)
print(f"Regular Tuple: {regularTuple[0]}")
CollectionsTuple = namedtuple("CollectionsTuple",["x","y"])
noRegularTuple = CollectionsTuple(1,2)
print(f"{noRegularTuple}")

#also we can use default argument for namedtuple (this set default to the most of right argument so its job in this case)
#or other method like convert tuple to dict or replace the value of field
Person = namedtuple("Person", "name job", defaults=["Python Developer"])
person = Person("Martin")
print(person)
print("Convert to dict ",person._asdict())
person = person._replace(job="Web Developer")
print(person)

#deque
#this work fast in adding item in two direction . Python have slow adding item to the begin of the list
#this datatype work in two direction

tickets = deque()
print(f"\nTickets {tickets}")

#adding values
tickets.append("John")
tickets.append("Jack")
print(f"Tickets after append {tickets}")

#pop values (cause indexerror if deque is empty)
tickets.popleft()
print(f"Tickets after popleft {tickets}")

#adding values to the left side
tickets.appendleft("James")
print(f"Tickets after appendleft {tickets}")

#also we can add more than one value by using extend method
tickets.extend(["Katy","Mike"])
print(f"Tickets after extend {tickets}")

#after count method
print(f"Tickets how much mikes {tickets.count('Mike')}")

#after rotate method
tickets.rotate(2)
print(f"Tickets after rotate {tickets}")

#also we can use other method like extendleft,clearmcopy,remove


#defaultdict
#this work like normal dict but no cause error if we want to ge access to index which doesn't exist

exampleCounter = defaultdict(int)
print(f"\nexampleCounter: {exampleCounter}")
exampleCounter["first"]
print(f"exampleCounter: {exampleCounter}")
exampleCounter["first"] += 1
exampleCounter["first"] += 1
exampleCounter["second"] += 1
exampleCounter["third"]
print(f"exampleCounter ['first']: {exampleCounter['first']}")

#orderedDict
#this datype work the same like regular ordered dictionairy (In new python dictionairy also is ordered) but have also good methods to example moving elementss
#also regular dict doesn't care about order elements, but if elements are the same return true in both dict. OrderedDict return only true when elements are the same and are in the same order.
#- in 2 dicts

life_stages = OrderedDict()

life_stages["childhood"] = "0-9"
life_stages["adolescence"] = "9-18"
life_stages["adulthood"] = "18-65"
life_stages["old"] = "+65"

print("\nOrderedDict: ")
for stage, years in life_stages.items():
    print(stage, "->", years)


#Counter
#this is very good object which counter how much elements are in list,str (only with hashable objects)

print(f"\nCounter elements {Counter('Programming')}")
print(f"Counter elements {Counter([1,1,1,2,2,3,3,3,4])}")

#and goood example to use Counter to check adopt dogs,cats,pythons

inventory = Counter(dogs=23, cats=14, pythons=7)
print(f"\nInventory: {inventory}")

inventory.subtract(Counter(dogs=2,cats=5,pythons=3))
print(f"Inventory after subtract: {inventory}")

inventory.update({"boas": 5,"pythons": 2})
print(f"Inventory after update(add 5 boas,2 pythons): {inventory}")

#we can also use +,- operator to operator on counter object

#chainmap
#its special data type in python that you have first dict that you can operate on this and if you try to delete index from second dict you will get error (even exist!)
#example (first chain is parents, second is childs)

from collections import ChainMap

dad = {"name": "John", "age": 35}
mom = {"name": "Jane", "age": 31}
family = ChainMap(mom, dad)
print(f"\nFamily: {family}")

son = {"name": "Mike", "age": 0}
family = family.new_child(son)

print("After add child")
for person in family.maps:
    print(person)

#if we want to modify standard dict,string or list; UserString,UserList,UserDict can help us to do this

print("\nExample with Dict if we want to make all keys lower even if we give big letters: ")

class LowerDict(UserDict):
    def __setitem__(self, key, value):
        key = key.lower()
        super().__setitem__(key, value)

ordinals = LowerDict({"FIRST": 1, "SECOND": 2})
print(f"Ordinals: {ordinals}")
