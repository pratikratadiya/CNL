import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('localhost', 10000)
sock.connect(server_address)

print("Connecting to %s port %s" % server_address)

# file = open('filename','w')
# file.write('Content')
# file.close()

while True:
	message = input("Enter the string to be converted: ")
	print("Sending message\n")
	sock.sendall(message.encode())

	amount_received = 0
	amount_expected = len(message)

	while amount_received < amount_expected:
		data = sock.recv(16)
		amount_received += len(data)
		print("Received: %s" % data.decode())

	a = input("\nDo you wish to resend?(Yes/No): ")
	if a == 'No':
		break

print("Closing connection")
sock.close()