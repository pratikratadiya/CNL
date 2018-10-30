import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('localhost', 10000)
sock.connect(server_address)

print("Connecting to %s port %s" % server_address)

while True:
	message = input("Enter the equation: ")
	print("Calculating result\n")
	sock.sendall(message.encode())

	data = sock.recv(16)
	print("Result is: %s" % data.decode())

	a = input("\nDo you wish to continue?(Yes/No): ")
	if a == 'No':
		break

print("Closing connection")
sock.close()