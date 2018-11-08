import bluetooth

bd_addr = '20:15:04:28:37:22'
print 'Send data'

port = 1

sock = bluetooth.BluetoothSocket( bluetooth.RFCOMM )

sock.connect((bd_addr, port))


data = "W"
sock.send(data)

sock.close()
