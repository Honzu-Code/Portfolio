# Generated by Django 3.2.9 on 2021-12-03 15:16

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('forum', '0018_auto_20211203_1222'),
    ]

    operations = [
        migrations.AddField(
            model_name='answer',
            name='result_opinions',
            field=models.IntegerField(default=0),
        ),
    ]
