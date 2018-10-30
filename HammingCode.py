hamcode = [0] * 11
rec = [0] * 11
parity = [0] * 4

data = input("Enter the code: ")

hamcode[10],hamcode[9],hamcode[8],hamcode[6],hamcode[5],hamcode[4],hamcode[2]=[int(i) for i in data]
hamcode[0] = hamcode[2]^hamcode[4]^hamcode[6]^hamcode[8]^hamcode[10]
hamcode[1] = hamcode[2]^hamcode[5]^hamcode[6]^hamcode[9]^hamcode[10]
hamcode[3] = hamcode[4]^hamcode[5]^hamcode[6]
hamcode[7] = hamcode[8]^hamcode[9]^hamcode[10]
print("Data to be transmitted is ", ''.join(map(str,hamcode[::-1])))

data = input("Enter the received codeword: ")
rec = [int(i) for i in data[::-1]]

parity[0] = rec[0]^rec[2]^rec[4]^rec[6]^rec[8]^rec[10]
parity[1] = rec[1]^rec[2]^rec[5]^rec[6]^rec[9]^rec[10]
parity[2] = rec[3]^rec[4]^rec[5]^rec[6]
parity[3] = rec[7]^rec[8]^rec[9]^rec[10]

if parity.count(0) == len(parity):
	print("No error exists")

else:
	bin_parity = ''.join(map(str,parity[::-1]))
	err = int(bin_parity,2)

	print("Error exists at bit number %s from right " % err)
	rec[err-1] = 1 if rec[err-1] == 0 else 0

	print("Corrected code ",''.join(map(str,rec[::-1])))