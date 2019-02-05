#! /usr/bin/python

import os

def filesize_stat():
    """ get the file size of the specified directory using os.stat"""

    # ensure path is os compliant
    path = os.path.abspath(os.getcwd())

    return os.stat(path).st_size

def filesize_du():
    """ get the file size of the specified directory using bash du"""

    # ensure path is os compliant
    path = os.path.abspath(os.getcwd())

    import subprocess

    return subprocess.check_output(['du', path])

if __name__ == '__main__':

    import timeit

    print('filesize_stat time: {}'.format(timeit.timeit("filesize_stat()", setup="from __main__ import filesize_stat", number=10)))

    print('filesize_du time: {}'.format(timeit.timeit("filesize_du()", setup="from __main__ import filesize_du", number=10  )))
