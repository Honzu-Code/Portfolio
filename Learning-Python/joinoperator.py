import random
import string

example = ["1","2","3","4","5"]

print("-".join(example))
print("".join(random.choices(string.punctuation,k=5)))

def specific_string(length):
    sample_string = "abc"
    print("".join((random.choice(sample_string)) for x in range(length)))

specific_string(4)
