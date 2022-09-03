
#for passwords example using bcrypt
from passlib.context import CryptContext
from passlib.hash import bcrypt


hash = bcrypt.hash("martin")
print(hash)
print("Verify hash",bcrypt.verify("martin",hash))
print("Verify hash",bcrypt.verify("martidn",hash))

#for tokens example using cryptography
from cryptography.fernet import Fernet

key = Fernet.generate_key()
print("key",key)
f = Fernet(key)
token = f.encrypt(b"Welcome my friend")
print(token)
print(f.decrypt(token))

from jose import jws
signed = jws.sign({'a': 'b'},key,algorithm='HS256')
print(signed)
print(jws.verify(signed,key,algorithms=["HS256"]))