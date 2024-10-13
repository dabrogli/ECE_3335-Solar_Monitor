#Dante

import serial, time, threading
import serial.tools.list_ports as port_list
import csv, io

class time_break:
	value = True

	def __init__(self):
		self.value = True
	
	def end_read(self):
		self.value = False
		print(self.value)

def end_read():
	print("Timer is Done")
	loop = False
	print(loop)

ser = serial.Serial()
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

ser.port = 'COM11'
ser.baudrate = 9600	

tb = time_break()

data = [[],[],[]]


##Reading the serial.

with open('2024-10-12_arduino_test_output_2_16_17_correct.csv', 'w', newline='') as csvfile:
	csv_writer = csv.writer(csvfile, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
	csv_writer.writerow(["in_voltage", "v_voltage", "v_current"])
	
#	for x in range (0, len(data[0])):
#		csv_writer.writerow([data[0][x], data[1][x], data[2][x]])


	ser.open()
	time.sleep(.1)
	for v_in in range (16, 18):
	
		input(f"Next:{v_in} V\nPress any key... >")
		
		for x in range(0, 1000):
			
			ser.flushInput()
			ser.flushOutput()
			sio.flush()
			time.sleep(.05)
			ser_in_line = ser.readline().decode("utf-8")
			
			
			print(f"v_in {v_in}\t| x {x}\t| {ser_in_line}")
			#print(ser_in_line)
			
			ser_in_line = ser_in_line.replace("\r\n", "")
			
			ser_in_list = ser_in_line.split(",")
			
			try:
				v_voltage = float(ser_in_list[0])
				v_current = float(ser_in_list[1])
			except:
				x = x - 1
				continue
			
			
			#data[0].append(v_in)
			#data[1].append(v_voltage)
			#data[2].append(v_current)
			
			csv_writer.writerow([v_in, v_voltage, v_current])
			

	ser.close()

#with open('2024-10-12_arduino_test_output_2_16_17_correct.csv', 'w', newline='') as csvfile:
#	csv_writer = csv.writer(csvfile, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
#	csv_writer.writerow(["in_voltage", "out_1_voltage", "out_current"])
	
#	for x in range (0, len(data[0])):
#		csv_writer.writerow([data[0][x], data[1][x], data[2][x]])