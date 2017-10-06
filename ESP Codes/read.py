import socket
HOST = '172.20.8.165'    	# Set the remote host, for testing it is localhost
PORT = 50939            # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.send('Where there is love there is life')
data = s.recv(1024)
s.close()
print 'Received', repr(data)
