from django.shortcuts import render

def uploadcsv(request):
    return render(request, 'transactions/uploadcsv.html')

def transactions(request):
    return render(request, 'transactions/transactions.html')
