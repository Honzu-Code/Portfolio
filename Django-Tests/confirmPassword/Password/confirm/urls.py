from django.contrib.auth import views as auth_views
from . import views
from django.urls import path , re_path,include

urlpatterns = [
    #re_path(r'password_reset/$', auth_views.PasswordResetView.as_view(), name='password_reset'),
    #re_path(r'password_reset/done/$', auth_views.PasswordResetDoneView.as_view(), name='password_reset_done'),
    #re_path(r'reset/<uidb64>/<token>/',
    #    auth_views.PasswordResetConfirmView.as_view(), name='password_reset_confirm'),
    #re_path(r'reset/done/$', auth_views.PasswordResetCompleteView.as_view(), name='password_reset_complete'),
    re_path('accounts/',include('django.contrib.auth.urls')),
    re_path('', views.signup, name = 'signup'),  
    path('signup/', views.signup, name = 'signup'),  
    path('activate/<uidb64>/<token>/',views.activate,name="activate"), 
]