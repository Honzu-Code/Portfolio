from email import message
from unicodedata import name
from requests import request
from fastapi import FastAPI,Request ,Form , Body
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from fastapi.responses import HTMLResponse
from database import database , blogs , posts
from validatemodels import Blog, BlogIn, PostIn
from pydantic import ValidationError
import json

app = FastAPI()

app.mount("/static", StaticFiles(directory="static"),name="static")

templates = Jinja2Templates(directory="templates")


@app.on_event("startup")
async def startup():
    await database.connect()


@app.on_event("shutdown")
async def shutdown():
    await database.disconnect()


@app.get("/blogs/", response_class=HTMLResponse)
async def read_blogs(request: Request):
    query = blogs.select()
    data = await database.fetch_all(query)
    return templates.TemplateResponse("blogs.html",{"request": request,"blogs":data})

@app.get("/blog/",response_class=HTMLResponse)
async def show_blog(id: int,request: Request):
    blog_query = blogs.select().where(blogs.c.id == id)
    posts_query = posts.select().where(posts.c.blog_fk_key == id)
    data_blog = await database.fetch_one(blog_query)
    data_posts = await database.fetch_all(posts_query)
    return templates.TemplateResponse("blog.html",{"request": request,"blog":data_blog,"posts":data_posts})

@app.get("/create_blogs/", response_class=HTMLResponse)
async def create_blog(request: Request):
    return templates.TemplateResponse("create_blog.html",{"request": request})


@app.post("/create_blogs/")
async def create_blog(request: Request):
    b = await request.form()
    try:
        new_blog = BlogIn(**b)
        query = blogs.insert().values(name=new_blog.name,description=new_blog.description)
        await database.execute(query)
    except ValidationError as e:
        message = json.loads(e.json())
        return message[0]["msg"]
    return  {"newdata": new_blog}

@app.get("/create_posts/", response_class=HTMLResponse)
async def create_post(request: Request):
    return templates.TemplateResponse("create_post.html",{"request": request})

@app.post("/create_posts/")
async def create_post(request: Request):
    p = await request.form()
    try:
        new_post = PostIn(**p)
        query = posts.insert().values(description=new_post.description,blog_fk_key=new_post.blog_id)
        await database.execute(query)
    except ValidationError as e:
        message = json.loads(e.json())
        return message[0]["msg"]
    return {"newdata": new_post}
