
#sets
print("sets\n")

x = set([1,2,3])
print(x)
x = set((1,2,3))
print(x)

somethink_text = "wooah"

print(list(somethink_text))
print(set(somethink_text))

x = {"one","two","three",54,(21,3,4)}
print(type(x))

print(bool(x))
print("four" in x)

print(len(x))

b = set([1,2,3])
c = set([4,5,3])
print(b | c)
# or with methods .union
print(b.union(c))

#intersection of sets
print(b & c)
# or
print(b.intersection(c))

#difference of sets (everyelements which are in first set but no in other)
print(b - c)
# or
print(b.difference(c))

#symetric_difference (everyelements are in two sets but not repeat)
print(b ^ c)
#or
print(b.symmetric_difference(c))

#add element to set
b.add(6)
print(b)
#delete 6 from set
b.remove(6)
print(b)
#delete 6 element but no exception
b.discard(6)
print(b)
#remove random element from set
b.pop()
print(b)
#clear sets
b.clear()
print(b)

print()

#lists

print("\n\n")

print("lists")

simple_list = ['a','b']
element = simple_list.append(123)
element2 = simple_list.extend([1,2,3])
simple_list.insert(2,'c')
print(element)
print(simple_list)

#remove delete element raise error if no exist
simple_list.remove('a')
#simple_list.remove('a')

#remove element from the list by index default -1 also raise error if no exist
#simple_list.clear()
simple_list.pop()
print(simple_list)


#tuples
print("\n\n")

print("tuples")

simple_tuple = ('first','second','third')
print(simple_tuple[0])
print(simple_tuple[-1])
print(simple_tuple[1::1])
print(simple_tuple[::-1])

(el1,el2,el3) = simple_tuple
print(el1)
print(el2)
print(el3)


