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




#dodac obsluge wyjatkow
conn = MySQLdb.connect("127.0.0.1", "root", "r00t", "test")
tag= "TAG"
while 1:
    rfid = ser.readline()
    rfid = str(rfid)
    print rfid
    #print rfid.find(tag,-1)
    
    
    if rfid.find(tag,0) >= 0:
        print rfid
        
        id = rfid[4:16]
        print id
        c = conn.cursor()
        c.execute("SELECT * FROM pracownicy WHERE karta='%s'" % id)
       
            
        for rec in c.fetchall():
            print "ID: %d\nNick: %s\nNazwisko: %s\nKarta: %s\n" % (rec[0], rec[1], rec[2], rec[3])
            #ser.flush()
            ser.write("1")
        #ser.write("1")
    ser.write("0")

ser.close()