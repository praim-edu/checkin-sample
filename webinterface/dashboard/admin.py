from django.contrib import admin
from models import Token, AccessAttempt, RegisteredToken


class TokenAdmin(admin.ModelAdmin):
    list_display = ('token', 'first_seen', 'enabled',)
    list_filter = ('enabled',)

admin.site.register(Token, TokenAdmin)

class AccessAttemptAdmin(admin.ModelAdmin):
    list_display = ('token', 'date', 'result')
    list_filter = ('result',)

admin.site.register(AccessAttempt, AccessAttemptAdmin)

class RegisteredTokenAdmin(admin.ModelAdmin):
    list_display = ('user', 'registration_date')
    list_filter = ('registration_date',)

admin.site.register(RegisteredToken, RegisteredTokenAdmin)
