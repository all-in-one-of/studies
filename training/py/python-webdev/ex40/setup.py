try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

config = {
    'description': 'Learn Python The Hardway EX40',
    'author': 'Adam Harder',
    'url': 'URL',
    'download_url': 'URL',
    'author_email': 'bj.adam.h@gmail.com',
    'version': '0.1',
    'install_requires': ['nose'],
    'packages': ['ex40'],
    'scripts': [],
    'name': 'projectname'
}

setup(**config)