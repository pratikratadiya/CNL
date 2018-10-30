import socket
import sys
import select

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('localhost', 10000)
sock.bind(server_address)

print("Starting up on %s port %s" % server_address)

sock.listen(1)

# file = open('filename','r')
# file.read() to get file contents

while True:
	print("Waiting for connection")
	connection, client_address = sock.accept()
	
	print("Connection from ",client_address)
	
	ready = select.select([connection],[],[],15)

	if ready[0]:
		try:
			
			while True:
				data = connection.recv(16)	
				print("Received: ",data)
				if data:
					print("Sending data back to the client")
					capsdata = str(data.decode()).upper()
					connection.sendall(capsdata.encode())
				else:
					print("No more data from client")
					break
		finally:
			connection.close()