from django.db import models
from django import forms 

class Test(models.Model):
    name = models.CharField(max_length=50)

class Somethink(models.Model):
    somethink = models.CharField(max_length=20)

class Contact(models.Model):
    name = models.CharField(max_length=255)
    message = models.CharField(max_length=255)

