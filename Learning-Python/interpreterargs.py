import sys

add = 0.0
for i in range(1,len(sys.argv)):
    add += float(sys.argv[i])
print(f"sum is = {add}")
