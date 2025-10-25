import csv
from datetime import datetime
from collections import defaultdict

def analyze_attendance(file_path):
    # Read the CSV file
    with open(file_path, 'r') as file:
        reader = csv.DictReader(file)
        data = list(reader)
    
    # Extract unique dates when classes were conducted
    unique_dates = set()
    student_attendance = defaultdict(set)  # student -> set of dates attended
    
    for row in data:
        if row['Status'].lower() == 'present':
            # Extract date from timestamp (first 10 characters: YYYY-MM-DD)
            date = row['Timestamp'][:10]
            unique_dates.add(date)
            student_attendance[row['Name']].add(date)
    
    # Calculate total classes conducted
    total_classes = len(unique_dates)
    
    # Generate attendance summary
    print("Attendance Summary:")
    print("=" * 50)
    
    for student, attended_dates in sorted(student_attendance.items()):
        classes_attended = len(attended_dates)
        print(f"{student} has attended {classes_attended} classes out of {total_classes} classes conducted")
    
    # Additional statistics
    print("\nAdditional Statistics:")
    print("=" * 50)
    print(f"Total classes conducted: {total_classes}")
    print(f"Total students: {len(student_attendance)}")
    
    for student, attended_dates in sorted(student_attendance.items()):
        classes_attended = len(attended_dates)
        attendance_percentage = (classes_attended / total_classes) * 100
        print(f"{student}: {attendance_percentage:.1f}% attendance")

# Run the analysis
if __name__ == "__main__":
    analyze_attendance(r'C:\Users\soova\Downloads\RFID Based Attendance System\attendance.txt') # Provide the file path of your .txt file 