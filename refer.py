from datetime import datetime

def calculate_datetime_difference(datetime1, datetime2):
    format = "%Y/%m/%d %H:%M:%S.%f"
    dt1 = datetime.strptime(datetime1, format)
    dt2 = datetime.strptime(datetime2, format)

    if dt1 > dt2:
        difference = dt1 - dt2
        negative = True
    else:
        difference = dt2 - dt1
        negative = False

    days = difference.days
    total_seconds = difference.total_seconds()
    milliseconds = int(difference.total_seconds() * 1000 % 1000)

    if negative:
        days = -days
        milliseconds = -milliseconds

    hours, remainder = divmod(total_seconds, 3600)
    minutes, seconds = divmod(remainder, 60)
    hours %= 24

    return days, int(hours), int(minutes), int(seconds), milliseconds

datetime1 = "2023/05/29 00:00:00.000"
datetime2 = "2023/05/28 00:00:00.001"

days, hours, minutes, seconds, milliseconds = calculate_datetime_difference(datetime1, datetime2)
output = f"{days} days, {hours} hours, {minutes} minutes, {seconds} seconds, {milliseconds} milliseconds"

print(f"Difference: {output}")
