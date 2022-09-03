import re

#check only if value exist on the begining of a string
print(re.match(r'\d+','123abc'))

#check if value exist in the next line (we can use flag MULTILINE)
print(re.search("^123","abc\n123\n321",re.MULTILINE))

#check if value is only like in this case digits
print(re.fullmatch(r'\d+',"123"))

#check all value and skip all symbols to check if value exist in string
print(re.findall(r'\w+',".;'abc.[;';[]abc"))

#check if value exist and return iterator (similar to findall but return iterator to elements)
it = re.finditer(r"\w+",".'..abc...''abc")
print(next(it))
print(next(it))

#return a modified string and insert string into passes places
s = "abc.123.abc.321"
print(re.sub(r"\d+","#",s))

#if we want also return how much this word is in string we can use subn
print(re.subn(r"\d+","#",s,count=1))

#we can split a string into substrings
print(re.split('\s*[,;/]\s*', 'foo,bar  ;  baz / qux'))

#if we want to no adding \ to searching we can use escape
print(re.match(re.escape('foo^bar(baz)|qux'), 'foo^bar(baz)|qux'))

#we can compile regex object to use this later
s1, s2, s3, s4 = 'foo.bar', 'foo123bar', 'baz99', 'qux & grault'
re_obj = re.compile('\d+')

print(re_obj.search(s1))
print(re_obj.search(s2))
