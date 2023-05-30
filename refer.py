from datetime import datetime

# Define two datetime objects
datetime2 = datetime(2023, 5, 30, 14, 30)
datetime1 = datetime(2023, 5, 31, 18, 30)

# Calculate the difference between the two dates
difference = datetime2 - datetime1
print(type(difference))

print('The difference between the two dates is: ', difference)
