import serial
import MySQLdb

# Sprawdzamy czy Ardu podlaczone
connected = False

# Otworz port com4 na 9600
ser = serial.Serial("COM4", 9600)

# dopoki nie podlaczone
#while not connected:
#    serin = ser.read()
#    connected = True





conn = MySQLdb.connect("127.0.0.1", "root", "r00t", "test")
rfid = ser.read()
print rfid
#while 1:
   
#    c = conn.cursor()
#    c.execute("SELECT * FROM pracownicy")
#    for rec in c.fetchall():
#        print "ID: %d\nNick: %s\nHaslo: %s\nKarta: %s\n" % (rec[0], rec[1], rec[2], rec[3])



ser.close()