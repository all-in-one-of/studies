#! /usr/bin/python

""" example from zetcode tutorial - http://zetcode.com/python/pymysql/ """

import pymysql

con = pymysql.connect('localhost', 'ahfx', '12345', 'world', cursorclass=pymysql.cursors.DictCursor)

try:

    cur = con.cursor()
    cur.execute('SELECT * FROM City LIMIT 10')

    rows = cur.fetchall()

    for row in rows:
        print('{} {} {}'.format(row['ID'], row['Name'], row['Population']))

except pymysql.Error as e:

    print("Error %d: %s" % (e.args[0],e.args[1]))
    sys.exit(1)

finally:
    if con:
        con.close()