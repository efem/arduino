import MySQLdb


conn = MySQLdb.connect("85.17.145.35", "efem_arduino", "arduino", "efem_arduino")

c = conn.cursor()
c.execute("SELECT * FROM pracownicy WHERE imie = 'Peter'")
#print c.fetchall()
t = c.fetchall()
k = len(t)

if k > 0:
    print "TAK"
    print k
    print t
for rec in t:
            print "ID: %d\nNick: %s\nNazwisko: %s\nKarta: %s\n" % (rec[0], rec[1], rec[2], rec[3])
        