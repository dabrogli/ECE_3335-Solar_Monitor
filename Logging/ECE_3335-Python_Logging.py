#Dante's Code
import serial, time, threading
import serial.tools.list_ports as port_list
import csv, io

#Begins the data.

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


tb = time_break()

#Setting up the serial object and the io object to flush it.
ser = serial.Serial()
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

#Serial information.
ser.port = 'COM11'
ser.baudrate = 9600	

data = [[],[],[]]

##Reading the serial.
#Opens the file so that each loop writes to the file as the data is collected
#in the case that an error occurs.
with open('2024-10-17_arduino_test_new_load_dep_01.csv', 'w', newline='') as csvfile:
	csv_writer = csv.writer(csvfile, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
	csv_writer.writerow(["in_voltage", "v_vol_raw", "v_cur_raw", "v_in_meas", "i_in_meas"])

	#Beginning reading from the selected serial port.
	ser.open()
	time.sleep(.1)
	
	#The range of voltage reading.
	for v_in in range (0, 21):
	
		#Allowing pause to adjust the supply.
		input(f"Next:{v_in} V\nPress any key... >")
		
		#Taking a given amount of data points.
		for x in range(0, 100):
			
			ser.flushInput()
			ser.flushOutput()
			sio.flush()
			
			#Reading and interpreting the serial data.
			ser_in_line = ser.readline().decode("utf-8")
			
			#For monitoring output as it occurs.
			print(f"v_in {v_in}\t| x {x}\t| {ser_in_line}")
			
			ser_in_line = ser_in_line.replace("\r\n", "")
			
			ser_in_list = ser_in_line.split(",")
			
			#Repeats this loop in the case that the data collected
			#miss-formatted.
			try:
				v_vol_raw = float(ser_in_list[0])
				v_cur_raw = float(ser_in_list[1])
				v_in_meas = float(ser_in_list[2])
				i_in_meas = float(ser_in_list[3])
			except:
				x = x - 1
				continue
			
			#Writes to the currently open file.
			csv_writer.writerow([v_in, v_vol_raw, v_cur_raw, v_in_meas, i_in_meas])
			

	ser.close()
##End of script

#Updated needs to be tested

import serial
import time
import io
import csv
from datetime import datetime


ser = serial.Serial()
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

# Serial information
ser.port = 'COM11'  
ser.baudrate = 9600


csv_file_path = 'real_time_data.csv'
with open(csv_file_path, 'a', newline='') as csvfile:
    csv_writer = csv.writer(csvfile, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
    
    
    if csvfile.tell() == 0:
        csv_writer.writerow(["Timestamp", "in_voltage", "v_vol_raw", "v_cur_raw", "v_in_meas", "i_in_meas"])

    
    ser.open()
    time.sleep(0.1)


    for v_in in range(0, 21):  # From 0V to 20V
        input(f"Next: {v_in} V\nPress any key... >") 
        
      
        for x in range(0, 100):
            try:
                
                ser.flushInput()
                ser.flushOutput()
                sio.flush()
                
                ser_in_line = ser.readline().decode("utf-8").strip()
                print(f"v_in {v_in}\t| x {x}\t| {ser_in_line}")
                
                ser_in_list = ser_in_line.split(",")
                
                
                v_vol_raw = float(ser_in_list[0])
                v_cur_raw = float(ser_in_list[1])
                v_in_meas = float(ser_in_list[2])
                i_in_meas = float(ser_in_list[3])
                
                
                timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')
                
              
                csv_writer.writerow([timestamp, v_in, v_vol_raw, v_cur_raw, v_in_meas, i_in_meas])
                csvfile.flush()  
                
            except (ValueError, IndexError):
                x -= 1
                continue

    ser.close()


