#! /usr/bin/python

""" pymysql fetchall example """

import pymysql

con = pymysql.connect('localhost', 'root', 'Hatpunmopmysql!1', 'testdb')

with con:

    cur = con.cursor()
    cur.execute('')