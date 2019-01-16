"""fileuploadsite URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from django.conf import settings
from django.conf.urls.static import static

from uploader import views as uploader_views

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', uploader_views.uploadimages, name='uploadimages'),
    path('viewimages/', uploader_views.viewimages, name='viewimages'),
] + static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)


"""
Django does not serve MEDIA_ROOT by default. That would be dangerous in production environment.
But in development stage, we could cut short.

+ static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
enables Django to serve files from MEDIA_URL. This works only in developement stage.

See django.conf.urls.static.static reference for details. See also this discussion about serving media files.
"""
