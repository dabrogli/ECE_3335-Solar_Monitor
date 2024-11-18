import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from datetime import datetime, timedelta
import matplotlib.dates as mdates

# Path to CSV file
file_path = r"C:\Users\Abraham Tom Philips\source\repos\csv_data_generator\data.csv"


fig, axs = plt.subplots(2, 2, figsize=(14, 10))
fig.suptitle("Real-Time Sensor Data", fontsize=16, fontweight='bold', fontname='Times New Roman')

colors = ['blue', 'green', 'orange', 'red']


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


def determine_window_size(start_time, current_time):
    elapsed_time = (current_time - start_time).total_seconds()

    if elapsed_time <= 60:  # First minute
        return timedelta(minutes=1)
    elif elapsed_time <= 600:  # First 10 minutes
        return timedelta(minutes=10)
    elif elapsed_time <= 3600:  # First hour
        return timedelta(hours=1)
    elif elapsed_time <= 86400:  # First day
        return timedelta(hours=12)
    else:  # More than a day
        return timedelta(days=1)


start_time = None


def update(frame):
    global start_time

    try:
        data = pd.read_csv(file_path)

        timestamps = pd.to_datetime(data['Timestamp'])
        voltage = data['Voltage']
        current = data['Current']
        irradiance = data['Irradiance']
        temperature = data['Temperature']

        if start_time is None:
            start_time = timestamps.iloc[0]

       
        current_time = datetime.now()

       
        window_size = determine_window_size(start_time, current_time)
        window_start = current_time - window_size

       
        mask = (timestamps >= window_start) & (timestamps <= current_time)
        timestamps_window = timestamps[mask]
        voltage_window = voltage[mask]
        current_window = current[mask]
        irradiance_window = irradiance[mask]
        temperature_window = temperature[mask]

        # Updated plot data
        lines[0].set_data(timestamps_window, voltage_window)
        lines[1].set_data(timestamps_window, current_window)
        lines[2].set_data(timestamps_window, irradiance_window)
        lines[3].set_data(timestamps_window, temperature_window)

        #x-axis limits
        for ax in axs.flatten():
            ax.set_xlim(window_start, current_time)
            ax.relim()
            ax.autoscale_view()
            ax.xaxis.set_major_formatter(mdates.DateFormatter('%H:%M:%S'))
            for label in ax.get_xticklabels():
                label.set_rotation(45)

    except Exception as e:
        print(f"Error: {e}")

# Animation
ani = animation.FuncAnimation(fig, update, interval=1000)  # Update every second

plt.tight_layout(rect=[0, 0.08, 0.95, 0.95]) 
plt.subplots_adjust(hspace=0.4)
plt.show()
