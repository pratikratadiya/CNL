import socket

while True:
	option = input("--Lookup--\n1.Find URL\n2.Find IP address\nChose your choice: ")

	if option == '1':
		ip = input("Enter the IP address: ")
		print("The corresponding URL is ", socket.gethostbyaddr(ip)[0])

	elif option == '2':
		url = input("Enter the url: ")
		print("The corresponding URL is ", socket.gethostbyname(url))
	choice = input("Do you wish to continue(yes/no): ")
	if choice == 'no':
		break