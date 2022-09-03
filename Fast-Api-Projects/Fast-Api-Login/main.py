from datetime import datetime, timedelta
import json

from fastapi import FastAPI,Request ,Form , Body , Response
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from fastapi.responses import HTMLResponse , RedirectResponse
from pydantic import BaseModel , ValidationError
from passlib.context import CryptContext
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from jose import jwt, JWTError

fake_user = {
    "username" : "",
    "password" : "",
    "email" : ""
}

SECRET_KEY = "e33967b2d9fc29a904cb0cc6ff48e4ddf0169344b6417b32edc54313319bea52"
ALGORITHM = "HS256"
ACCESS_TOKEN_EXPIRE_MINUTES = 1

class LoginReg(BaseModel):
    username: str
    password: str
    email: str

class LoginLog(BaseModel):
    username: str
    password: str

app = FastAPI()

app.mount("/static", StaticFiles(directory="static"),name="static")
templates = Jinja2Templates(directory="templates")

crypt_context = CryptContext(schemes=["sha256_crypt", "md5_crypt"])

def get_hash_pwd(password):
    return crypt_context.hash(password)

def verify_pwd(password,hashed_password):
    return crypt_context.verify(password,hashed_password)

def create_access_token(data: dict,expires_delta: timedelta):
    to_encode = data.copy()
    expire = datetime.utcnow() + expires_delta
    to_encode.update({"exp": expire})
    encoded_jwt = jwt.encode(to_encode,SECRET_KEY,algorithm=ALGORITHM)
    return encoded_jwt

oauth2_scheme = OAuth2PasswordBearer(tokenUrl="token")

def get_current_user(token): 
    try:
        if token is None:
            return {"this is none" : "this is none"}
        payload = jwt.decode(token,SECRET_KEY,algorithms=[ALGORITHM])
        username: str = payload.get("sub")
    except JWTError:
        #return this if token expires 
        return {"JWT error" : "No username"}
    return username

@app.get("/",response_class="HTMLResponse")
async def register(request: Request):
    return templates.TemplateResponse("register.html",{"request": request})

@app.post("/")
async def register(request: Request):
    u = await request.form()
    try:
        new_user = LoginReg(**u)
        fake_user["username"],fake_user["password"],fake_user["email"] = \
        new_user.username,get_hash_pwd(new_user.password),new_user.email
        access_token = create_access_token({"sub":new_user.username},expires_delta=timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES))
        response = RedirectResponse(request.url_for("private"),status_code=302)
        response.set_cookie("Authorization",value=access_token)
        return response
    except ValidationError as e:
        message = json.loads(e.json())
        return message[0]["msg"]
    

@app.get("/login",response_class="HTMLResponse")
async def login(request: Request):
    return templates.TemplateResponse("login.html",{"request": request})

@app.post("/login")
async def login(request: Request):
    u = await request.form()
    try:
        new_user = LoginLog(**u)
        if fake_user["username"] != new_user.username or verify_pwd(new_user.password,fake_user["password"]) == False:
            return {"Incorrect login data"}
        access_token = create_access_token({"sub":new_user.username},expires_delta=timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES))
        response = RedirectResponse(url='/private')
        response.set_cookie("Authorization",value=access_token)
        return response
    except ValidationError as e:
        message = json.loads(e.json())
        return message[0]["msg"]

@app.get("/private")
async def private(request: Request):
    cookie_auth: str = request.cookies.get("Authorization")
    return {"score" : get_current_user(cookie_auth)}

   

