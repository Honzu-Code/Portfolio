from django.contrib import admin

from testviews.forms import ContactForm
from .models import Contact, Somethink, Test
from .forms import ContactForm

admin.site.register(Test)
admin.site.register(Somethink)