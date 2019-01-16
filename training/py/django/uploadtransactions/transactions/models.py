from django.db import models
from django.forms import ModelForm

class CSVFile(models.Model):
	csv_file = models.FileField(upload_to="csvfiles/")
	upload_date = models.DateTimeField(auto_now_add=True)
	#daterange
	#is_imported

# FileUpload form class
class CSVUploadForm(ModelForm):
	class Meta:
		model = CSVFile
		fields = ('csv_file',)