import math
import os
#import subrpocess

def calc_class(inp):
	
	if(int(inp[0]) < 127):
		return 'A'
	
	if(int(inp[0]) >= 128 and int(inp[0]) <= 191 ):
		return 'B'

	if(int(inp[0]) >= 192 and int(inp[0]) < 223 ):
		return 'C'
	return 'D'


def calc_subnet(inp):
	
	ip = ""
	
	if inp is 'A':
		ip = ip + '255.0.0.0'
	if inp is 'B':
		ip = ip + '255.255.0.0'
	if inp is 'C':
		ip = ip + '255.255.255.0'
	return ip
	

'''
Input is default subnet, extra 1's and class of IP
'''
def new_subnet_mask(inp , num , cl):
	temp = inp.split('.')
	
	print(temp)
	cnt = 0
	for i in range(7 , 7 - num , -1 ):
		cnt = cnt + 2**i
	
	if cl is 'A':
		i = 1
	if cl is 'B':
		i = 2
	if cl is 'C':
		i = 3	
	
	temp[i] = str(cnt)
	
#	print('Haha',temp[i])
	
	string = temp[0] + '.' + temp[1] + '.' +  temp[2] + '.' + temp[3]  
	
	return string
		
'''
Input is class of IP, number of 1's required and number of subnets being created
'''
def display(cla , bits , num):
	if cla is 'A':
		i = 1
	if cla is 'B':
		i = 2
	if cla is 'C':
		i = 3	
		
	div = 2**bits
	
	temp = 256/div
	
	start = []
	end = []
	
	for it in range(num):
		start.append(int(temp*it))
		end.append(int(temp*(it+1) - 1))
	
	print(start)
	print(end)
	
	return


def check_subnet(ip1 , sub , ip2):
	ip1 = ip1.split('.')
	sub = sub.split('.')
	ip2 = ip2.split('.')
	
	res1 = []
	res2 = []
	
	ans = 0

	for i in range(4):
		temp1 = int(ip1[i]) & int(sub[i]) 
		temp2 = int(ip2[i]) & int(sub[i])
		
		res1.append(temp1)
		res2.append(temp2)
		
		if temp1 != temp2:
			ans = 1	
	
	print(res1)
	print(res2)
	
	return ans
	

#os.system('ifconfig')

ip_raw = str(raw_input('Enter IP address of this computer : '))

print(ip_raw)

final_ip = ip_raw.split('.')

print(final_ip)

cl_ip = calc_class(final_ip)

print(cl_ip)

subnet = calc_subnet(cl_ip)

print(subnet)

count = int(raw_input('Enter number of subnets : '))

ones = math.ceil((float(math.log(count,2))))

print(ones)

new_sub = new_subnet_mask(subnet , int(ones) , cl_ip)


print(new_sub)

#os.system('sudo ifconfig wlp60s0 %s netmask %s'%(ip_raw , new_sub))

display(cl_ip , ones , count)


#new_ip = str(raw_input('Enter IP of another host : ')) 

#ans = check_subnet(ip_raw , new_sub , new_ip)

#if ans is 0:
#	print('The new IP entered is in the same subnet')
#if ans is 1:
#	print('The new IP entered is not in the same subnet')
	
#os.system("ifconfig")

#os.system("ping %s"%(new_ip))
