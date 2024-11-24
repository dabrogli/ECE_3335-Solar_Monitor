import serial, time, threading
import serial.tools.list_ports as port_list
import csv, io

#Setting up the values.
data_heading = ['Voltage_True (V)', 'Current True (A)', 'Power True (W)', 'Voltage Read (V)', 'Current Read (A)', 'Power Read (W)']
data = [[],[],[],[],[],[]]

#Setting up the serial port.
ser = serial.Serial()
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

ser.port = '/dev/ttyUSB0'
ser.baud = 9600

#The file name to save to.
file_name = '2024-11-23_Photodiode Sensor cirucits .csv'

#Section opening and writing to the file.
with open(file_name, 'w', newline='') as csvfile:
	csv_writer = csv.writer(csvfile, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
	csv_writer.writerow(data_heading)

	ser.open()
	time.sleep(0.1)

	for i_in in range(17, 21):
		input(f"Set to: {i_in} V\nPress Any Key > ")
		cur_true = input("True Current (A) > ")

		for x in range(0, 100):
			ser.flushInput()
			ser.flushOutput()
			sio.flush()

			ser_in_line = ser.readline().decode("utf-8").strip()

			if not ser_in_line or 'Panel Voltage ->' not in ser_in_line or 'Panel Current ->' not in ser_in_line or 'Panel Power ->' not in ser_in_line:
				x = x - 1
				continue

			print(f"{x}] {ser_in_line}")

			vol_read = float(ser_in_line.split('Photodiode 1 Current ->')[1].split(' 1')[0])
			cur_read = float(ser_in_line.split('Panel Current ->')[1].split(' A')[0])
			pow_read = float(ser_in_line.split('Panel Power ->')[1].split(' W')[0])

			csv_writer.writerow([vol_true, cur_true, pow_true, vol_read, cur_read, pow_read])
