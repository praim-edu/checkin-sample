from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^login$', views.LoginView.as_view(), name="login"),
    url(r'^$', views.IndexView.as_view(), name="index"),
    url(r'^testio/$', views.TestIOView.as_view(), name="testio"),
]
