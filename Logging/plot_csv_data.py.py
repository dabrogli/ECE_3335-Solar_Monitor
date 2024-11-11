import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from datetime import datetime, timedelta
import matplotlib.dates as mdates

#path to CSV file
file_path = r"C:\Users\Abraham Tom Philips\source\repos\csv_data_generator\data.csv" 

# 2x2 grid layout
fig, axs = plt.subplots(2, 2, figsize=(14, 10))
fig.suptitle("Real-Time Sensor Data", fontsize=16, fontweight='bold', fontname='Times New Roman')

colors = ['blue', 'green', 'orange', 'red']

# Labels 
titles = ["Voltage Over Time", "Current Over Time", "Irradiance Over Time", "Temperature Over Time"]
y_labels = ['Voltage (V)', 'Current (A)', 'Irradiance (W/m2)', 'Temperature (C)']


lines = []
for ax, color, title, y_label in zip(axs.flatten(), colors, titles, y_labels):
    line, = ax.plot([], [], color=color)
    ax.set_title(title, fontsize=14, fontweight='bold', fontname='Times New Roman', pad=20)
    ax.set_ylabel(y_label, fontsize=12, fontname='Times New Roman')
    ax.grid(True)
    lines.append(line)
axs[1, 0].set_xlabel('Time', fontsize=12, fontname='Times New Roman')
axs[1, 1].set_xlabel('Time', fontsize=12, fontname='Times New Roman')

# Function to update the plot in real-time
def update(frame):
    try:
        data = pd.read_csv(file_path)

        timestamps = pd.to_datetime(data['Timestamp'])
        voltage = data['Voltage']
        current = data['Current']
        irradiance = data['Irradiance']
        temperature = data['Temperature']

       
        current_time = timestamps.iloc[-1]
        window_start = current_time - timedelta(seconds=10)
        mask = (timestamps >= window_start) & (timestamps <= current_time)
        
        
        timestamps_window = timestamps[mask]
        voltage_window = voltage[mask]
        current_window = current[mask]
        irradiance_window = irradiance[mask]
        temperature_window = temperature[mask]

        lines[0].set_data(timestamps_window, voltage_window)
        lines[1].set_data(timestamps_window, current_window)
        lines[2].set_data(timestamps_window, irradiance_window)
        lines[3].set_data(timestamps_window, temperature_window)

        for ax in axs.flatten():
            ax.set_xlim(timestamps_window.iloc[0], timestamps_window.iloc[-1])
            ax.relim()          
            ax.autoscale_view() 
            ax.xaxis.set_major_formatter(mdates.DateFormatter('%H:%M:%S'))
            for label in ax.get_xticklabels():
                label.set_rotation(45)

    except Exception as e:
        print(f"Error: {e}")

ani = animation.FuncAnimation(fig, update, interval=1000)  # Update every 1  second

plt.tight_layout(rect=[0, 0.08, 0.95, 0.95]) 
plt.subplots_adjust(hspace=0.4)
plt.show()