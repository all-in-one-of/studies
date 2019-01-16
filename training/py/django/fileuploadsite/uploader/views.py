from django.shortcuts import render
from uploader.models import UploadForm, Upload
from django.http import HttpResponseRedirect
from django.urls import reverse

def uploadimages(request):
	if request.method=="POST":
		img = UploadForm(request.POST, request.FILES)
		if img.is_valid():
			img.save()
			return HttpResponseRedirect(reverse('imageupload'))
	else:
		img = UploadForm()

	return render(request, 'uploadimages.html', {'form':img})


def viewimages(request):

	images = Upload.objects.all().order_by('-upload_date')

	return render(request, 'viewimages.html', {'images':images})