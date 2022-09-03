from dataclasses import dataclass


def inputText(id="text"):
    return f"""
<div class='form-group'> \n\
    <label for='exampleInputPassword1'>{id}</label> \n \
    <input type='text' class='form-control' id='{id}' placeholder='enter {id}'> \n \
</div> """

def inputPassword(id="text"):
    return f"""
<div class='form-group'> \n \
    <label for='exampleInputPassword1'>{id}</label> \n \
    <input type='password' class='form-control' id='{id}' placeholder='enter {id}'> \n\
</div> """

def generate(html_name,*inputs):
    with open(html_name,"w+",encoding = 'utf-8',) as f:
        for i in inputs:
            f.write(i)
