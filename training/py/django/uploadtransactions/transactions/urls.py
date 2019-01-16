from django.urls import path
from . import views

urlpatterns = [
	path('', views.transactions, name='transactions'), #transactions
	path('uploadcsv/', views.uploadcsv, name='uploadcsv'), #uploadcsv
]