print(dir())


#import two

#after import this changing caller table
#print(dir())

#print(two.text)

#we can import specific elements from module
#from two import function,Object

#print(dir())
#print(function(5))

#if we import like this we will use all elements but this method can cause problem with names of elements
#from two import *

#print(dir())
#print(exampleList)

#other method is make alias for name of importing elements:
#from two import exampleList as numbers

#print(dir())

#print(numbers)

#import two



#import packages:
#we can also import like as this module or from package import module
#import pkg.third, pkg.fourth
#print(pkg.third.foo())

#we can't import like this because we don't have __init__
#import pkg
#will doesn't work print(pkg.third.foo())

#from package import * will doesn't work if we will don't have __all__ in __init__ or in module
#from pkg import *
#print(third.foo())

