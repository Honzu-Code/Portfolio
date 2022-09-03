from fastapi import FastAPI, Request
from fastapi.templating import Jinja2Templates
from pydantic import BaseModel

app = FastAPI()
templates = Jinja2Templates(directory="templates")

class Item(BaseModel):
    name: str
    roll: int
    
@app.post("/")
async def create_item(item: Item):
    return item

@app.get("/")
async def index(request: Request):
    return templates.TemplateResponse("test_body.html", {"request": request})