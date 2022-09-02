from django.urls import path
from . import views

urlpatterns=[
    path('',views.main,name="main"),

    path('account/<name>/',views.account,name="account"),
    path('logout',views.logout,name="logout"),

    path('article/<name>/',views.article,name="article"),
    path('writearticle',views.writearticle,name="writearticle"),
    path('editarticle/<name>/',views.editarticle,name="editarticle"),
    path('addcomment/<name>/',views.addcomment,name="addcomment"),
    path('editcomment/<article>/<comment>/',views.editcomment,name="editcomment"),
    path('filtertagsarticles/<name>/',views.filtertagsarticles,name="filtertagsarticles"),
    path('filtersearcharticles',views.filtersearcharticles,name="filtersearcharticles"),
    


    path('askquestion',views.askquestion,name="askquestion"),
    path('editquestion/<name>/',views.editquestion,name="editquestion"),
    path('questions',views.listofquestions,name="listofquestions"),
    path('question/<name>/',views.question,name="question"),
    path('addanswer/<name>/',views.addanswer,name="addanswer"),
    path('editanswer/<question>/<answer>/',views.editanswer,name="editanswer"),
    path('filtertagsquestions/<name>/',views.filtertagsquestions,name="filtertagsquestions"),
    path('filtersearchquestions',views.filtersearchquestions,name="filtersearchquestions"),
    path('addansweropinion/<name>/<answer>/<what>/',views.addansweropinion,name="addansweropinion"),
    path('addreplay/<comment>/',views.addreplay,name="addreplay"),
    path('editreplay/<comment>/<replay>/',views.editreplay,name="editreplay"),
]