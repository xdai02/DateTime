from datetime import datetime, timedelta

# Define time format
fmt = "%H:%M:%S.%f"

# Store the times
time_str1 = "17:35:23.643"
time_obj1 = datetime.strptime(time_str1, fmt)

time_str2 = "7:53:32.346"
time_obj2 = datetime.strptime(time_str2, fmt)

# Calculate the difference
delta = time_obj1 - time_obj2

# Get the difference in milliseconds
diff_ms = delta.total_seconds() * 1000

print(f"Difference in milliseconds: {diff_ms}")
