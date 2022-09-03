
datas = list()

#with open("hello.txt") as f:
#    for line in f:
#        datas.append(line[:-1])

#print(f"{datas}")

#new_data = str(input("Give me data to save to file: "))

#with open("hello.txt","a") as f:
#    f.write(new_data)

with open("hello.txt","r+") as f:
    f.seek(14,0)
    for line in f:
        datas.append(line[:-1])

print(f"{datas}")
