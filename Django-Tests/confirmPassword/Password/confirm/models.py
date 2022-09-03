from django.db import models
from django.contrib.auth.models import User

class Account(models.Model):
    username = models.CharField(max_length=100)
    password = models.CharField(max_length=20)
    email = models.EmailField()
