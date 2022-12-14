# Generated by Django 3.2.9 on 2021-11-18 14:21

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Account',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('identificator', models.CharField(max_length=10)),
                ('username', models.CharField(max_length=50)),
                ('password', models.CharField(max_length=50)),
                ('email', models.EmailField(max_length=254)),
                ('avatar', models.ImageField(default='default.png', upload_to='profiles')),
            ],
        ),
        migrations.CreateModel(
            name='Article',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(max_length=200)),
                ('image_of_title', models.ImageField(default='article.png', upload_to='article')),
                ('pub_date', models.DateField()),
                ('text', models.TextField()),
                ('who_writed', models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='forum.account')),
            ],
        ),
    ]
