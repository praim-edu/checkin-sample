from django.views.generic import TemplateView
from dashboard.client import send_message
from dashboard.models import AccessAttempt
from django.shortcuts import render_to_response
from django.template.context import RequestContext

class IndexView(TemplateView):
    template_name = "components/index.html"

    def get(self, request):
        context = self.get_context_data()
        last_access = AccessAttempt.objects.all().order_by('-date')
        return render_to_response(self.template_name, {'last_access': last_access})

    def get_context_data(self, **kwargs):
        context = super(IndexView, self).get_context_data(**kwargs)
        context.update({'title': "Dashboard"})
        return context

class TestIOView(TemplateView):
    template_name = "components/testIO.html"

    def post(self, request, *args, **kwargs):
        context = self.get_context_data()
        if 'idl' in request.POST:
            send_message('IDLE')
        elif 'chk' in request.POST:
            send_message('CHECK')
        elif 'suc' in request.POST:
            send_message('ACCEPT')
        elif 'fld' in request.POST:
            send_message('FAIL')
        elif 'sip' in request.POST:
            send_message('SHOWIP')
        else:
            print 'invalid'
        return super(TestIOView, self).render_to_response(context)

    def get_context_data(self, **kwargs):
        context = super(TestIOView, self).get_context_data(**kwargs)
        context.update({'title': "IO Test"})
        return context

class LoginView(TemplateView):
    template_name = "components/login.html"

    def get_context_data(self, **kwargs):
        context = super(LoginView, self).get_context_data(**kwargs)
        context.update({'title': "Log In"})
        return context
