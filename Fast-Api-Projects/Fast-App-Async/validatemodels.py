from pydantic import BaseModel ,validator

class BlogIn(BaseModel):
    name: str
    description: str

    @validator("name","description")
    def no_number_as_first(cls,v):
        if not v:
            raise ValueError("This field is empty")
        if(v[0].isdigit()):
            raise ValueError(f"name {v} cannot start from number")
        return v

class Blog(BaseModel):
    id: int
    name: str
    description: str



class PostIn(BaseModel):
    description: str
    blog_id: int

    @validator("description")
    def no_number_as_first(cls,v):
        if(v[0].isdigit()):
            raise ValueError("name cannot start from number")
        return v

class Post(BaseModel):
    id: int
    description: str
    blog_id: int