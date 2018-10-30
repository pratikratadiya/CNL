import os
#Install DHCP Package
os.system("yum install dhcp")
#Change Subnet mask ip address to 192.168.5.0
os.system("gedit /etc/dhcp/dhcpd.conf")
#Starting DHCP Service
os.system("systemctl start dhcpd.service")
os.system("systemctl enable dhcpd.service")
os.system("systemctl status dhcpd.service")
