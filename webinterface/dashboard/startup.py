
from django.db.models.signals import pre_save
from django.apps.config import AppConfig
from threading import Thread
from time import sleep
from dashboard.server import manage_input

class DashboardConfig(AppConfig):
    name = 'dashboard'

    def ready(self):
        thread = Thread(target = manage_input)
        thread.setDaemon(True)
        thread.start()
        print 'init channels'