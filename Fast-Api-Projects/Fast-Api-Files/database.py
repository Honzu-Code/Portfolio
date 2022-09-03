from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey , create_engine 
from sqlalchemy.dialects.mysql import MEDIUMBLOB
import databases

# SQLAlchemy specific code, as with any other app
DATABASE_URL = "mysql://test:LovePy$1@127.0.0.1/testapifast"
# DATABASE_URL = "postgresql://user:password@postgresserver/db"

database = databases.Database(DATABASE_URL)

metadata_obj = MetaData()

account = Table(
    "account",
    metadata_obj,
    Column("id",Integer,primary_key=True),
    Column("user",String),
    Column("photo",String)
    )
    
#blogs = Table(
#    "blog",
#    metadata_obj,
#    Column("id",Integer,primary_key=True),
#    Column("name",String),
#    Column("description",String)
#    )

engine = create_engine(
    DATABASE_URL
)

metadata_obj.create_all(engine)