""" utils for interacting with os and the file system """

import os

def create_dir(file_path):
    """ get the directory of a given file, if the dir doesnt exist create it """

    dir_name = os.path.dirname(file_path)

    if not os.path.isdir(dir_name):
        os.makedirs(dir_name)
