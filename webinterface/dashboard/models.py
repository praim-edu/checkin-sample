from django.db import models
from django.utils import timezone
from django.contrib.auth.models import User


class Token(models.Model):
    token = models.CharField(max_length=30, blank=True, primary_key=True)
    first_seen = models.DateTimeField(auto_now_add=True)
    enabled = models.BooleanField(default=False)

    def __str__(self):
        return str(self.token)

class RegisteredToken(Token):
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    registration_date = models.DateTimeField(auto_now_add=True)


class AccessAttempt(models.Model):
    token = models.ForeignKey(Token, blank=True, null=True)
    date = models.DateTimeField(auto_now_add=True)
    result = models.BooleanField(default=True)
