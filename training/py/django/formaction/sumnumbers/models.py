""" sumnumbers models.py """

from django.db import models
from django.forms import ModelForm

class SumOfNumbers(models.Model):
    """ SumOfNumbers Model """

    num1 = models.FloatField()
    num2 = models.FloatField()
    num1Num2Sum = models.FloatField()

class SumOfNumbersForm(ModelForm):
    """ SumbOfNumbers Form """

    class Meta:
        model = SumOfNumbers
        fields = ['num1', 'num2']

    def clean_num1Num2Sum(self):
        num1 = self.cleaned_data['num1']
        num2 = self.cleaned_data['num2']

        return num1 + num2
