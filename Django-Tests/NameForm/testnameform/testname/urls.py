from unicodedata import name
from . import views
from django.urls import path 

urlpatterns = [
    path('',views.get_name,name="get_name")
]

