# Generated by Django 3.2.9 on 2021-11-30 17:06

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('forum', '0015_replay_article'),
    ]

    operations = [
        migrations.RenameField(
            model_name='replay',
            old_name='ans_date',
            new_name='rep_date',
        ),
    ]