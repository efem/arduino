import serial
import MySQLdb

conn = MySQLdb.connect("127.0.0.1", "root", "r00t", "test")



print 'Zaimportowano'


c = conn.cursor()
c.execute("SELECT * FROM pracownicy")
for rec in c.fetchall():
    print "ID: %d\nNick: %s\nHaslo: %s\nKarta: %s\n" % (rec[0], rec[1], rec[2], rec[3])
