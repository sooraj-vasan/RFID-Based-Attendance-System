import serial
from datetime import datetime
import time

PORT = "COM8" # Use the port of your system from Device Manager
BAUD = 9600

print("🚀 RFID Attendance Logger Started...")
print("💾 Saving to: attendance.txt (CSV format)")

# Create file with headers if it doesn't exist
try:
    with open("attendance.txt", "r", encoding="utf-8") as f:
        pass
except FileNotFoundError:
    with open("attendance.txt", "w", encoding="utf-8") as f:
        f.write("Name,Status,Timestamp\n")
    print("📄 Created new attendance.txt file with headers")

while True:
    try:
        ser = serial.Serial(PORT, BAUD, timeout=1)
        print(f"✅ Connected to {PORT}")
        
        while True:
            line = ser.readline().decode(errors="ignore").strip()
            if line:
                print(f"Raw data: {line}")
                
                # Parse data
                if " - " in line:
                    name, status = line.split(" - ")
                elif "," in line:
                    name, status = line.split(",")
                else:
                    print(f"Unknown format: {line}")
                    continue
                
                name = name.strip()
                status = status.strip()
                timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                
                # Append to text file in CSV format
                with open("attendance.txt", "a", encoding="utf-8") as file:
                    file.write(f"{name},{status},{timestamp}\n")
                
                print(f"✅ Logged: {name} - {status} at {timestamp}")
                
    except KeyboardInterrupt:
        print("\n🛑 Stopped by user")
        break
    except Exception as e:
        print(f"Error: {e}")
        time.sleep(5)