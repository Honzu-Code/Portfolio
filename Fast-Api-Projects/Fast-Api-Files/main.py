from inspect import getfile
from select import select
from typing import List, Union
from unicodedata import name
import aiofiles
from fastapi import FastAPI, File, UploadFile , Request
from fastapi.templating import Jinja2Templates
from fastapi.staticfiles import StaticFiles
from fastapi.responses import RedirectResponse , FileResponse
import os
from pydantic import BaseModel, ValidationError
import json
import glob

from requests import Response
from database import account,database
import base64
import random

from generate import generate

class AccountIn(BaseModel):
    user: str


app = FastAPI()

app.mount("/static", StaticFiles(directory="static"),name="static")

templates = Jinja2Templates(directory="templates")

@app.on_event("startup")
async def startup():
    await database.connect()

@app.on_event("shutdown")
async def shutdown():
    await database.disconnect()

@app.get("/show/{id}")
async def show(request: Request,id: int):
    select_query = account.select().where(account.c.id == id)
    result = await database.fetch_one(select_query)
    if result is None:
        return {"result" : "is none"}
    return templates.TemplateResponse("show.html",{"request":request,"result": result})

@app.get("/create")
async def get_form(request: Request):
    return templates.TemplateResponse("file.html",{"request":request})

@app.post("/create", status_code=200)
async def send_form(request: Request,file: Union[UploadFile, None] = None):
    data = await request.form()
    try:
        validate = AccountIn(user=data["user"])
    except ValidationError as e:
        return {"no work": data["user"]}
    
    hash_f = generate()
    while hash_f + ".png" in os.listdir(os.path.join("static","files")):
        hash_f = generate()
    
    path_to_file = os.path.join("static","files",hash_f + ".png")
    with open(path_to_file,"w+") as fi:
        pass
    
    async with aiofiles.open(path_to_file,'wb') as out_file:
        content = await file.read()
        await out_file.write(content)

    insert_account = account.insert().values(user=validate.user,photo = hash_f + ".png")
    await database.execute(insert_account)
    
    return RedirectResponse(request.url_for("show",id=1),status_code=302)
    
