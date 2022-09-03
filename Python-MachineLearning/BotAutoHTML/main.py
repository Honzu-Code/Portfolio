from Generate import inputText,inputPassword,generate

class Example():
    def __init__(self):
        self.first = inputText(id="username")
        self.second = inputPassword(id="password")

e = Example()
generate("example.html",e.first,e.second)
