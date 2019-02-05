#! /usr/bin/python

""" get mysql version """

import pymysql

con = pymysql.connect('localhost', 'root', 'Hatpunmopmysql!1', 'testdb')

with con:

    cur = con.cursor()
    cur.execute("SELECT VERSION()")

    version = cur.fetchone()

    print("Database Version: {}".format(version[0]))
