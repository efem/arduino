import serial
import MySQLdb

# Sprawdzamy czy Ardu podlaczone
#bconnected = False

# Otworz port com4 na 9600
ser = serial.Serial("COM4", 9600)

# dopoki nie podlaczone
#while not connected:
#    serin = ser.read()
#    connected = True




#dodac obsluge wyjatkow
conn = MySQLdb.connect("85.17.145.35", "efem_arduino", "arduino", "efem_arduino")
tag= "TAG"
pomieszczenie="1";

while 1:
    rfid = ser.readline()
    rfid = str(rfid)
    print rfid
    #print rfid.find(tag,-1)
    
    
    if rfid.find(tag,0) >= 0:
        #print rfid
        
        id = rfid[4:16]
        #print id
        c = conn.cursor()
        zmienna = "SELECT * FROM uprawnienia WHERE ID_pracownik = (SELECT ID_pracownik FROM pracownicy WHERE karta='%s') AND ID_pomieszczenie='%s'" % (id, pomieszczenie)
        print zmienna;
        c.execute(zmienna)
        t = c.fetchall()
        k = len(t)
        if k > 0:
            ser.write("1")
            for rec in t:
                umiesc = "INSERT INTO logi VALUES (NULL, '%s', '%s', NULL)" % (rec[1], pomieszczenie)
                print umiesc
                c.execute(umiesc)
                print "ID: %s\nDostep: OK\nDostep zalogowano: OK" % id
        else:
            ser.write("0")
            
         

ser.close()