from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey , create_engine
import databases

# SQLAlchemy specific code, as with any other app
DATABASE_URL = "mysql://test:LovePy$1@127.0.0.1/testapifast"
# DATABASE_URL = "postgresql://user:password@postgresserver/db"

database = databases.Database(DATABASE_URL)

metadata_obj = MetaData()

blogs = Table(
    "blog",
    metadata_obj,
    Column("id",Integer,primary_key=True),
    Column("name",String),
    Column("description",String)
    )

posts = Table(
    "post",
    metadata_obj,
    Column("id",Integer,primary_key=True),
    Column("description",String),
    Column("blog_fk_key",Integer,ForeignKey("blog.id"))
    )

engine = create_engine(
    DATABASE_URL
)
