import random
import os 

ALPHABET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
def generate():
    chars=[random.choice(ALPHABET) for i in range(22)]
    return "".join(chars)

if "text3" + ".txt" in os.listdir(os.path.join("static","files")):
    print("This file exist")
else: 
    print("This file does not exist")