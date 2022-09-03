from django.urls import path
from .views import ContactFormView, ShowAllData, ShowSpecificTest, ShowTest

urlpatterns = [
    path('',ShowTest.as_view()),
    path('data/<number>/',ShowSpecificTest.as_view()),
    path('showdatas/<number>/',ShowAllData.as_view()),
    path('form',ContactFormView.as_view()),
]
