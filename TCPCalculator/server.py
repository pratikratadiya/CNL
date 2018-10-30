import socket
import sys
import select

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('localhost', 10000)
sock.bind(server_address)

print("Starting up on %s port %s" % server_address)

sock.listen(1)

while True:
	print("Waiting for connection")
	connection, client_address = sock.accept()
	
	print("Connection from ",client_address)
	
	ready = select.select([connection],[],[],15)

	if ready[0]:
		try:
			
			while True:
				equation = connection.recv(16)	
				print("Received: ",equation)
				if equation:
					print("Sending the result back to client")
					result = eval(str(equation.decode()))
					connection.sendall(str(result).encode())
				else:
					print("No more operations from client")
					break
		finally:
			connection.close()