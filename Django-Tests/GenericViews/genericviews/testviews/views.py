from re import template
from typing import List
from django.shortcuts import render , get_object_or_404
from .models import Contact, Somethink, Test
from django.views.generic import ListView ,FormView
from . import forms


class ShowTest(ListView):
    queryset = Test.objects.order_by("name")
    template_name = "first.html"
    context_object_name = "Tests"
    
class ShowSpecificTest(ListView):
    template_name = "second.html"
    context_object_name = "Specifics"

    def get_queryset(self):
        return get_object_or_404(Test,pk=self.kwargs["number"])

class ShowAllData(ListView):
    template_name = "third.html"

    def get_queryset(self):
        return Somethink.objects.all()

    def get_context_data(self, **kwargs):
        data = super().get_context_data(**kwargs)
        data["test"] = Test.objects.filter(pk=self.kwargs["number"]).first()
        data["somethink"] = Somethink.objects.filter(pk=self.kwargs["number"]).first()
        return data

class ContactFormView(FormView):
    template_name = "contact.html"
    form_class = forms.ContactForm
    success_url = '/showdatas/1'

    def form_valid(self,form):
        return super().form_valid(form)