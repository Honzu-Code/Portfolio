from codecs import ignore_errors
from urllib import response
from fastapi.testclient import TestClient

from main import app

client = TestClient(app)

users = ["first","second","third","fourth","sixth","seventh","eight","nineth","ten"]
photos = []

def create_item():
    response = client.post("/create",data={"user": users[0]},files={"file" : ("photos/blad.png", open("photos/blad.png",errors="ignore"), "image/png")})
    assert response.status_code == 200
    assert response.status_code == 422


create_item()