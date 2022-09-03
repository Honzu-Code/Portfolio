from click import option
from fastapi import Depends, FastAPI, Request
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from requests import request
from enums import cars
from pydantic import BaseModel

app = FastAPI()
app.mount("/static", StaticFiles(directory="static"),name="static")
templates = Jinja2Templates(directory="templates")

class Validate(BaseModel):
    cars : str

async def add_somethink(value : int = 0):
    return value + 3


@app.get("/", response_class="HTMLResponse")
async def show(request: Request):
    return templates.TemplateResponse("form.html",{"request": request,"options" : cars})

@app.post("/")
async def show(request: Request):
    data = await request.form()
    option = Validate(**data)
    return {"choosed_option" : option.cars}

@app.get("/test")
async def test(request: Request,value : int = Depends(add_somethink)):
    return {"value" : value}