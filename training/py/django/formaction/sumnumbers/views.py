""" sumnumbers views """

from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.urls import reverse
from sumnumbers.models import SumOfNumbers, SumOfNumbersForm

def index(request):
    """ index view """

    # an example of processing submitted form data before committing to the db
    if request.method == 'POST':

        sum_of_numbers_form = SumOfNumbersForm(request.POST)

        if sum_of_numbers_form.is_valid():
            sum_of_numbers_form.save()
            return HttpResponseRedirect(reverse('index'))
    else:
        sum_of_numbers_form = SumOfNumbersForm()


    sum_of_numbers = SumOfNumbers.objects.all()

    return render(request, 'sumnumbers/index.html', {'form': sum_of_numbers_form, 'sum_of_numbers': sum_of_numbers})
