from django.db import models
import datetime

from django.db.models.base import Model

class Account(models.Model):
    identificator = models.CharField(max_length=10)
    username = models.CharField(max_length=50)
    password = models.CharField(max_length=50)
    email = models.EmailField()
    avatar = models.ImageField(upload_to='profiles',default='default.png')

    def __str__(self):
        return self.username

class Article(models.Model):
    title = models.CharField(max_length=200)
    image_of_title = models.ImageField(upload_to='article',default='article.png')
    pub_date= models.DateField()
    category = models.CharField(max_length=50,default="coding")
    who_writed = models.ForeignKey(
        Account,
        on_delete=models.CASCADE,
        null=True,
    )
    text = models.TextField()

    def __str__(self):
        return self.title

class Question(models.Model):
    title = models.CharField(max_length=200)
    pub_date = models.DateField()
    category = models.CharField(max_length=50,default="coding")
    who_writed = models.ForeignKey(
        Account,
        on_delete=models.CASCADE,
        null=True
    )
    text = models.TextField()

    def __str__(self):
        return self.title

class Comment(models.Model):
    article = models.ForeignKey(
        Article,
        on_delete=models.CASCADE,
        null=True
    )
    who_comment = models.ForeignKey(
        Account,
        on_delete=models.CASCADE,
        null=True
    )
    text = models.TextField()
    com_date= models.DateField(default=datetime.date.today)

    def __str__(self):
        return self.text

class Answer(models.Model):
    question = models.ForeignKey(
        Question,
        on_delete=models.CASCADE,
        null=True
    )
    who_answer = models.ForeignKey(
        Account,
        on_delete=models.CASCADE,
        null=True,
        related_name="owners"
    )
    opinions = models.ManyToManyField(Account,through="Opinon",related_name="opinion")
    result_opinions = models.IntegerField(default=0)
    text = models.TextField()
    ans_date= models.DateField(default=datetime.date.today)
    def __str__(self):
        return self.text

class Opinon(models.Model):
    who_opinion = models.ForeignKey(Account,on_delete=models.CASCADE)
    which_answer = models.ForeignKey(Answer,on_delete=models.CASCADE)
    like = models.BooleanField(default=False)

    def __str__(self):
        return "Opinion " + str(self.id)
class Replay(models.Model):
    comment = models.ForeignKey(
        Comment,
        on_delete=models.CASCADE,
        null=True
    )
    who_replay = models.ForeignKey(
        Account,
        on_delete=models.CASCADE,
        null=True
    )
    article = models.ForeignKey(
        Article,
        on_delete=models.CASCADE,
        null=True
    )
    text = models.TextField()
    rep_date= models.DateField(default=datetime.date.today)
    def __str__(self):
        return self.text