from django.shortcuts import render 
from django.http import HttpResponse, HttpResponseRedirect

from .models import NameForm

def get_name(request):
    if request.method == "POST":
        form = NameForm(request.POST)
        if form.is_valid():
            return HttpResponse("Work")
    else:
        form = NameForm()
    return render(request,'name.html',{"form" : form})

