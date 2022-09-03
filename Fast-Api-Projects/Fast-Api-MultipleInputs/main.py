from fastapi import FastAPI, File, UploadFile, Request
from fastapi.templating import Jinja2Templates
from fastapi.staticfiles import StaticFiles
from fastapi.responses import HTMLResponse
from pydantic import BaseModel, ValidationError
from database import blogs,posts, database

app = FastAPI()

app.mount("/static", StaticFiles(directory="static"),name="static")


templates = Jinja2Templates(directory="templates")

@app.on_event("startup")
async def startup():
    await database.connect()

@app.on_event("shutdown")
async def shutdown():
    await database.disconnect()

@app.get("/create",response_class=HTMLResponse)
async def create(request: Request):
    return templates.TemplateResponse("create_data.html",{"request" : request})

@app.post("/create")
async def create_post(request: Request):
    data = await request.form()
    return {"data" : data}
