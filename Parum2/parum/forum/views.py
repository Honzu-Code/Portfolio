from django.shortcuts import redirect, render
from django.http import JsonResponse
from .models import *
from django.core.validators import URLValidator
from django.core.exceptions import ValidationError
from django.utils.datastructures import MultiValueDictKeyError
from django.core.paginator import Paginator
from django.db import IntegrityError
import string
import random
from datetime import date
import json


def main(request):
    articles = Article.objects.all().order_by('-pub_date')
    paginator = Paginator(articles,4)
    page_number = request.GET.get('page')
    selected_articles = paginator.get_page(page_number)

    list_of_comments = []
    list_of_categories = []
    for q in selected_articles:
        list_of_comments.append(Comment.objects.filter(article=q).count())
        list_of_categories.append(q.category)
    try:
        user = Account.objects.get(identificator=request.session.get("user_id"))
        data = {"articles": selected_articles,"user": user.username, "img" : user.avatar.url,"numberscomments": json.dumps(list_of_comments), \
                "categories": json.dumps(list_of_categories)}
        return render(request,"main.html",data)
    except Account.DoesNotExist:
        return render(request,"main.html",{"articles": selected_articles,"user": "","numberscomments": json.dumps(list_of_comments), \
                      "categories": json.dumps(list_of_categories)})

def filtertagsarticles(request,name):
    articles = Article.objects.filter(category=name).order_by('-pub_date')

    paginator = Paginator(articles,4)
    page_number = request.GET.get('page')
    selected_articles = paginator.get_page(page_number)
    list_of_comments = []
    list_of_categories = []
    for q in selected_articles:
        list_of_comments.append(Comment.objects.filter(article=q).count())
        list_of_categories.append(q.category)
    try:
        user = Account.objects.get(identificator=request.session.get("user_id"))
        data = {"articles": selected_articles,"user": user.username, "img" : user.avatar.url,"numberscomments": json.dumps(list_of_comments), \
                "categories": json.dumps(list_of_categories)}
        return render(request,"main.html",data)
    except Account.DoesNotExist:
        return render(request,"main.html",{"articles": selected_articles,"user": "","numberscomments": json.dumps(list_of_comments), \
                      "categories": json.dumps(list_of_categories)})

def filtersearcharticles(request):
    if request.method == "POST":
        if validate_data([request.POST["search"]]):
            redirect('main')
        articles = Article.objects.filter(title__contains=request.POST["search"]).order_by('-pub_date')
        paginator = Paginator(articles,4)
        page_number = request.GET.get('page')
        selected_articles = paginator.get_page(page_number)
        list_of_comments = []
        list_of_categories = []

        for q in selected_articles:
            list_of_comments.append(Comment.objects.filter(article=q).count())
            list_of_categories.append(q.category)
        try:
            user = Account.objects.get(identificator=request.session.get("user_id"))
            data = {"articles": selected_articles,"user": user.username, "img" : user.avatar.url,"numberscomments": json.dumps(list_of_comments), \
                    "categories": json.dumps(list_of_categories)}
            return render(request,"main.html",data)
        except Account.DoesNotExist:
            return render(request,"main.html",{"articles": selected_articles,"user": "","numberscomments": json.dumps(list_of_comments), \
                      "categories": json.dumps(list_of_categories)})

def filtertagsquestions(request,name):
    questions = Question.objects.filter(category=name).order_by("-pub_date")
    paginator = Paginator(questions,4)
    page_number = request.GET.get('page')
    selected_questions = paginator.get_page(page_number)
    list_of_answers = []
    list_of_categories = []
    for q in selected_questions:
        list_of_answers.append(Answer.objects.filter(question=q).count())
        list_of_categories.append(q.category)
    try:
        user = Account.objects.get(identificator=request.session.get("user_id"))
        data = {"questions": selected_questions,"user": user.username, "img" : user.avatar.url, "numbersanswers": json.dumps(list_of_answers), \
                "categories": json.dumps(list_of_categories)}
        return render(request,"questions_list.html",data)
    except Account.DoesNotExist:
        return render(request,"questions_list.html",{"questions": selected_questions,"user": "", "numbersanswers": json.dumps(list_of_answers), \
                "categories": json.dumps(list_of_categories)})

def filtersearchquestions(request):
    if request.method == "POST":
        if validate_data([request.POST["search"]]):
            redirect('main')
        questions = Question.objects.filter(title__contains=request.POST["search"]).order_by("-pub_date")
        paginator = Paginator(questions,4)
        page_number = request.GET.get('page')
        selected_questions = paginator.get_page(page_number)

        list_of_answers = []
        list_of_categories = []
        for q in selected_questions:
            list_of_answers.append(Answer.objects.filter(question=q).count())
            list_of_categories.append(q.category)
        try:
            user = Account.objects.get(identificator=request.session.get("user_id"))
            data = {"questions": selected_questions,"user": user.username, "img" : user.avatar.url, "numbersanswers": json.dumps(list_of_answers), \
                "categories": json.dumps(list_of_categories)}
            return render(request,"questions_list.html",data)
        except Account.DoesNotExist:
            return render(request,"questions_list.html",{"questions": selected_questions,"user": "", "numbersanswers": json.dumps(list_of_answers), \
                "categories": json.dumps(list_of_categories)})

def account(request,name):
    if request.method == "POST":
        if name == "register":

            username = request.POST["username"]
            password = request.POST["password"]
            email = request.POST["email"]

            if validate_data([username,password,email]):
                return render(request,"account.html",{"what": name,"message": "Some field/s is/are empty or is/are link/s"})
            else:
                    check_data = Account.objects.filter(username=username)
                    check_data_2 = Account.objects.filter(email=email)
                    print(check_data,check_data_2)
                    if check_data or check_data_2:
                        return render(request,"account.html",{"what": name,"message": "UserName or Email exist"})
                    ident = "".join(random.choices(string.ascii_uppercase + string.digits,k=10))
                    try:
                        avatar = request.FILES["avatar"]
                        new_user = Account.objects.create(identificator=ident,username=username,password=password,email=email,avatar=avatar)
                    except MultiValueDictKeyError:
                        new_user = Account.objects.create(identificator=ident,username=username,password=password,email=email)
                    new_user.save()
                    request.session["user_id"] = ident
                    return redirect('main')

        elif name == "login":
            username = request.POST["username"]
            password = request.POST["password"]
            if validate_data([username,password]):
                return render(request,"account.html",{"what": name,"message": "Some field/s is/are empty or is/are link/s"})
            else:
                try:
                    check_data = Account.objects.get(username=username,password=password)
                    request.session["user_id"] = check_data.identificator
                    return redirect('main')
                except Account.DoesNotExist:
                    return render(request,"account.html",{"what": name,"message": "Incorrect UserName or Password"})
        else:
            pass
    return render(request,"account.html",{"what": name})

#article views

def article(request,name):
    try:
        specific_article = Article.objects.get(id=name)
    except (Article.DoesNotExist):
        return redirect('main')

    number_of_comments = Comment.objects.filter(article=specific_article).count()
    category = specific_article.category

    try:
        owner = "false"
        comments_for_article = Comment.objects.filter(article=specific_article)
        replays_for_article = Replay.objects.filter(article=specific_article)
        print(replays_for_article)
        user = Account.objects.get(identificator=request.session.get("user_id"))
        get_article = Article.objects.filter(id=name,who_writed=user).first()
        if get_article is not None:
            owner = "true"
        return render(request,"article.html",{"user": user.username, "img" : user.avatar.url, "article": specific_article, "comments": comments_for_article, "owner" : owner, \
                      "numberscomments": number_of_comments, "category": category, "what" : "AddComment","replays": replays_for_article})
    except (Account.DoesNotExist):
        return render(request,"article.html",{"user": "", "img" : "", "article": specific_article, "comments": comments_for_article, "owner" : owner, \
                      "numberscomments": number_of_comments, "category": category,"replays": replays_for_article})

def writearticle(request):
    if request.method == "POST":
        article_title = request.POST["title"].strip()
        article_description = request.POST["description"].strip()
        article_category = request.POST["category"]
        user = Account.objects.get(identificator=request.session.get("user_id"))
        if validate_data([article_title,article_description]):
            return render(request,"write_article.html",{"user": user.username,"img" : user.avatar.url,"message" : "Some field/s is/are empty or is/are link/s"})
        try:
            imagetitle = request.FILES["imagetitle"]
            new_article = Article.objects.create(title=article_title,pub_date=date.today().strftime("%Y-%m-%d"),who_writed=user,text=article_description,category=article_category,image_of_title=imagetitle)
        except MultiValueDictKeyError:
            new_article = Article.objects.create(title=article_title,pub_date=date.today().strftime("%Y-%m-%d"),who_writed=user,text=article_description,category=article_category)
        new_article.save()
        return redirect('main')
    try:
        user = Account.objects.get(identificator=request.session.get("user_id"))
        return render(request,"write_article.html",{"user": user.username,"img" : user.avatar.url,"what": "Write", "message": ""})
    except Account.DoesNotExist:
        return redirect('main')


def editarticle(request,name):
    #check in future against change name in bar  (validation of data)
    if request.method == "POST":
        new_article_title = request.POST["title"]
        new_article_description = request.POST["description"].strip()
        new_article_category = request.POST["category"]
        #print(new_article_title,new_article_description)
        try:
            user = Account.objects.get(identificator=request.session.get("user_id"))
            get_article = Article.objects.get(id=name)
            get_article.title = new_article_title
            get_article.text = new_article_description
            get_article.category = new_article_category
        except (Article.DoesNotExist,Account.DoesNotExist):
            return render('main')
        if validate_data([new_article_title,new_article_description]):
            return render(request,"write_article.html",{"user": user.username,"img" : user.avatar.url,"what": "Edit","nameofarticle" : name, \
                          "message" : "Some field/s is/are empty or is/are link/s"})
        try:
            imagetitle = request.FILES["imagetitle"]
            get_article.image_of_title = imagetitle
        except MultiValueDictKeyError:
            pass
        get_article.save()
        return redirect('main')
    try:
        user = Account.objects.get(identificator=request.session.get("user_id"))
        get_article = Article.objects.filter(id=name,who_writed=user).first()
        if get_article is None:
            return redirect('article',name=name)
        return render(request,"write_article.html",{"user": user.username, "img" : user.avatar.url,"what": "Edit","nameofarticle" : name,"textofarticle": get_article.text})
    except (Account.DoesNotExist,Article.DoesNotExist):
        return redirect('main')

def addcomment(request,name):
    if request.is_ajax and request.method == "POST":
        try:
            which_article = Article.objects.get(id=name)
            comment_text = request.POST["comment"]
            if comment_text != "" and comment_text.startswith(" ") is False:
                user = Account.objects.get(identificator=request.session.get("user_id"))
                new_comment = Comment.objects.create(article=which_article,who_comment=user,text=comment_text)
                new_comment.save()
                return redirect('article',name=name)
        except (Account.DoesNotExist,Article.DoesNotExist):
            return redirect('main')
    return redirect('main')

def editcomment(request,article,comment):
    if request.method == "POST":
        try:
            check_article = Article.objects.get(id=article)
            edited_comment = Comment.objects.get(id=comment)
            if request.session.get("user_id") == edited_comment.who_comment.identificator:
                edited_comment.text = request.POST["comment"]
                edited_comment.save()
                return redirect('article',name=check_article.title)
        except (Article.DoesNotExist,Comment.DoesNotExist):
            return redirect('main')
    try:
        specific_article = Article.objects.get(id=article)
    except (Article.DoesNotExist):
        return redirect('main')
    number_of_comments = Comment.objects.filter(article=specific_article).count()
    category = specific_article.category
    try:
        comments_for_article = Comment.objects.filter(article=specific_article)
        user = Account.objects.get(identificator=request.session.get("user_id"))
        which_comment = Comment.objects.get(id=comment)
        return render(request,"article.html",{"user": user.username, "img" : user.avatar.url, "what": "EditComment","article": specific_article, \
                      "comments" : comments_for_article,"comment": which_comment,"numberscomments": number_of_comments, "category": category})
    except (Article.DoesNotExist,Account.DoesNotExist,Comment.DoesNotExist):
        redirect('main')

def addreplay(request,comment):
    if request.method == "POST":
        try:
            which_comment = Comment.objects.get(id=comment)
            specific_article = Article.objects.get(id=which_comment.article.title)
            replay_text = request.POST["replay"]
            if replay_text != "" and replay_text.startswith(" ") is False:
                user = Account.objects.get(identificator=request.session.get("user_id"))
                new_replay = Replay.objects.create(comment=which_comment,who_replay=user,text=replay_text,article=specific_article)
                new_replay.save()
                return redirect('article',name=which_comment.article.title)
        except (Account.DoesNotExist,Comment.DoesNotExist):
            return redirect('main')
    try:
        which_comment = Comment.objects.get(id=comment)
        specific_article = Article.objects.get(id=which_comment.article.title)
    except (Comment.DoesNotExist,Article.DoesNotExist):
        return redirect('main')
    number_of_comments = Comment.objects.filter(article=specific_article).count()
    category = specific_article.category
    try:
        comments_for_article = Comment.objects.filter(article=specific_article)
        replays_for_article = Replay.objects.filter(article=specific_article)
        user = Account.objects.get(identificator=request.session.get("user_id"))
        return render(request,"article.html",{"user": user.username, "img" : user.avatar.url, "what": "CreateReplay","article": specific_article, \
                      "comments" : comments_for_article,"comment": which_comment,"numberscomments": number_of_comments, "category": category,"replays": replays_for_article})
    except (Account.DoesNotExist):
        return redirect('main')

def editreplay(request,comment,replay):
    if request.method == "POST":
        try:
            replay_text = request.POST["replay"]
            which_comment = Comment.objects.get(id=comment)
            new_replay = Replay.objects.get(id=replay)
            user = Account.objects.get(identificator=request.session.get("user_id"))
            if request.session.get("user_id") == new_replay.who_replay.identificator:
                new_replay.text = replay_text
                new_replay.save()
                return redirect('article',name=which_comment.article.title)
        except (Account.DoesNotExist,Comment.DoesNotExist,Replay.DoesNotExist):
            return redirect('main')
    try:
        which_comment = Comment.objects.get(id=comment)
        specific_article = Article.objects.get(title=which_comment.article.title)
        replay = Replay.objects.get(id=replay)
    except (Comment.DoesNotExist,Article.DoesNotExist):
        return redirect('main')
    number_of_comments = Comment.objects.filter(article=specific_article).count()
    category = specific_article.category
    try:
        comments_for_article = Comment.objects.filter(article=specific_article)
        replays_for_article = Replay.objects.filter(article=specific_article)
        user = Account.objects.get(identificator=request.session.get("user_id"))
        return render(request,"article.html",{"user": user.username, "img" : user.avatar.url, "what": "EditReplay","article": specific_article, \
                      "comments" : comments_for_article,"comment": which_comment,"numberscomments": number_of_comments, "category": category,"replays": replays_for_article,
                      "replay" : replay})
    except (Account.DoesNotExist):
        return redirect('main')

#question views:





def askquestion(request):
    if request.method == "POST":
        question_title = request.POST["title"].strip()
        question_description = request.POST["description"].strip()
        question_category = request.POST["category"]
        user = Account.objects.get(identificator=request.session.get("user_id"))
        if validate_data([question_title,question_description]):
            return render(request,"write_question.html",{"user": user.username,"img" : user.avatar.url,"message" : "Some field/s is/are empty or is/are link/s"})
        #if quesiton.title exist add
        new_question = Question.objects.create(title=question_title,pub_date=date.today().strftime("%Y-%m-%d"),who_writed=user,text=question_description,category=question_category)
        new_question.save()
        return redirect('main')
    try:
        user = Account.objects.get(identificator=request.session.get("user_id"))
        return render(request,"write_question.html",{"user": user.username,"img" : user.avatar.url,"what": "Write", "message": ""})
    except Account.DoesNotExist:
        return redirect('main')

def editquestion(request,name):
    #check in future against change name in bar  (validation of data)
    if request.method == "POST":
        new_question_title = request.POST["title"]
        new_question_description = request.POST["description"].strip()
        new_question_category = request.POST["category"]
        #print(new_article_title,new_article_description)
        try:
            user = Account.objects.get(identificator=request.session.get("user_id"))
            get_question = Question.objects.get(id=name)
            get_question.title = new_question_title
            get_question.text = new_question_description
            get_question.category = new_question_category
        except (Question.DoesNotExist,Account.DoesNotExist):
            return render('main')
        if validate_data([new_question_title,new_question_description]):
            return render(request,"write_question.html",{"user": user.username,"img" : user.avatar.url,"what": "Edit","nameofquestion" : name, \
                          "message" : "Some field/s is/are empty or is/are link/s"})
        get_question.save()
        return redirect('question',name=get_question.id)
    try:
        user = Account.objects.get(identificator=request.session.get("user_id"))
        get_question = Question.objects.filter(id=name,who_writed=user).first()
        if get_question is None:
            return redirect('question',name=name)
        return render(request,"write_question.html",{"user": user.username, "img" : user.avatar.url,"what": "Edit","nameofquestion" : name,"textofquestion": get_question.text})
    except (Account.DoesNotExist,Question.DoesNotExist):
        return redirect('main')

def addanswer(request,name):
    if request.method == "POST":
        try:
            which_question = Question.objects.get(id=name)
            answer_text = request.POST["answer"]
            if answer_text != "" and answer_text.startswith(" ") is False:
                user = Account.objects.get(identificator=request.session.get("user_id"))
                new_answer = Answer.objects.create(question=which_question,who_answer=user,text=answer_text)
                new_answer.save()
                return redirect('question',name=name)
        except (Account.DoesNotExist,Question.DoesNotExist):
            return redirect('main')
    return redirect('main')

def editanswer(request,question,answer):
    if request.method == "POST":
        try:
            check_question = Question.objects.get(id=question)
            edited_answer = Answer.objects.get(id=answer)
            if request.session.get("user_id") == edited_answer.who_answer.identificator:
                edited_answer.text = request.POST["answer"]
                edited_answer.save()
                return redirect('question',name=check_question.id)
        except (Question.DoesNotExist,Comment.DoesNotExist):
            return redirect('main')
    try:
        specific_question = Question.objects.get(id=question)
    except (Question.DoesNotExist):
        return redirect('main')
    category = specific_question.category
    try:
        answers_for_article = Answer.objects.filter(question=specific_question)
        user = Account.objects.get(identificator=request.session.get("user_id"))
        which_answer = Answer.objects.get(id=answer)
        return render(request,"question.html",{"user": user.username, "img" : user.avatar.url, "what": "Edit","question": specific_question, \
                      "answers" : answers_for_article,"answer": which_answer,"category" : category})
    except (Question.DoesNotExist,Account.DoesNotExist,Answer.DoesNotExist):
        return redirect('main')

def listofquestions(request):
    questions = Question.objects.all().order_by("-pub_date")

    paginator = Paginator(questions,4)
    page_number = request.GET.get('page')
    selected_questions = paginator.get_page(page_number)
    list_of_answers = []
    list_of_categories = []
    for q in selected_questions:
        list_of_answers.append(Answer.objects.filter(question=q).count())
        list_of_categories.append(q.category)
    try:
        user = Account.objects.get(identificator=request.session.get("user_id"))
        data = {"questions": selected_questions,"user": user.username, "img" : user.avatar.url, "numbersanswers": json.dumps(list_of_answers), \
                "categories": json.dumps(list_of_categories)}
        return render(request,"questions_list.html",data)
    except Account.DoesNotExist:
        return render(request,"questions_list.html",{"questions": selected_questions,"user": "", "numbersanswers": json.dumps(list_of_answers), \
                "categories": json.dumps(list_of_categories)})

def question(request,name):
    try:
        specific_question = Question.objects.get(id=name)
    except (Question.DoesNotExist):
        return redirect('main')
    category = specific_question.category
    try:
        answers_for_question = Answer.objects.filter(question=specific_question)
        user = Account.objects.get(identificator=request.session.get("user_id"))
        return render(request,"question.html",{"user": user.username, "img" : user.avatar.url, "question": specific_question, "answers": answers_for_question, \
                      "category" : category})
    except (Account.DoesNotExist):
        return render(request,"question.html",{"user": "", "img" : "", "question": specific_question, "answers": answers_for_question, "category" : category})

#modify this views in next days
def addansweropinion(request,name,answer,what):
    try:
        specific_question = Question.objects.get(id=name)
        specific_answer = Answer.objects.get(id=answer)
        user = Account.objects.get(identificator=request.session.get("user_id"))
    except (Question.DoesNotExist,Answer.DoesNotExist,Account.DoesNotExist):
        return redirect('main')
    if specific_answer.who_answer == user:
        return redirect('question',name=name)
    if user in specific_answer.opinions.all():
        if what == "Up" or what == "Down":
            what_opinion = Opinon.objects.get(who_opinion = user,which_answer = specific_answer)
            if what_opinion.like == True and what == "Down":
                what_opinion.like = False
                what_opinion.save()
            elif what_opinion.like == False and what == "Up":
                what_opinion.like = True
                what_opinion.save()
            else:
                specific_answer.opinions.remove(user)
    else:
        if what == "Up" or what == "Down":
            if what == "Up":
                new_opinion = Opinon.objects.create(who_opinion=user,which_answer=specific_answer,like=True)
                new_opinion.save()
            else:
                new_opinion = Opinon.objects.create(who_opinion=user,which_answer=specific_answer,like=False)
                new_opinion.save()
        else:
            pass

    print(specific_answer.opinions.all())
    print("With True")
    print(Opinon.objects.filter(which_answer = specific_answer,like=True).count())
    print("With False")
    print(Opinon.objects.filter(which_answer = specific_answer,like=False).count())
    specific_answer.result_opinions = (Opinon.objects.filter(which_answer = specific_answer,like=True).count() - \
                                      Opinon.objects.filter(which_answer = specific_answer,like=False).count())
    specific_answer.save()
    # return JsonResponse({"result": specific_answer.result_opinions})
    return redirect('question',name=name)
def logout(request):
    try:
        del request.session['user_id']
    except KeyError:
        pass
    return redirect('main')

def is_string_an_url(url_string: str) -> bool:
    validate_url = URLValidator()
    try:
        validate_url(url_string)
    except ValidationError as exception:
        return False
    return True

def validate_data(data):
    for x in data:
        if x == "" or is_string_an_url(x):
            return True
    return False
