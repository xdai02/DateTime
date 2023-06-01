#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"

int main() {
    Date today = date_now();
    char *today_str = date_to_string(today);
    printf("Today is %s (%s)\n", today_str, weekday_full_name(weekday(today.year, today.month, today.day)));
    free(today_str);
    printf("\n");

    char *calendar_str = calendar(today.year, today.month);
    printf("%s\n", calendar_str);
    free(calendar_str);
    printf("\n");

    Date date = date_add(today, 15);
    char *date_str = date_to_string(date);
    printf("15 days later is %s (%s)\n", date_str, weekday_full_name(weekday(date.year, date.month, date.day)));
    free(date_str);

    int date_difference = date_diff(today, date);
    char *date1_str = date_to_string(today);
    char *date2_str = date_to_string(date);
    printf("The difference between %s and %s is %d days\n\n", date1_str, date2_str, date_difference);
    free(date1_str);
    free(date2_str);

    Time now = time_now();
    char *now_str = time_to_string(now);
    printf("The current time is %s\n", now_str);
    free(now_str);

    Time time = time_add(now, -3600);
    char *time_str = time_to_string(time);
    printf("3600 milliseconds ago is %s\n", time_str);
    free(time_str);

    int time_difference = time_diff(now, time);
    char *time1_str = time_to_string(now);
    char *time2_str = time_to_string(time);
    printf("The difference between %s and %s is %d milliseconds\n", time1_str, time2_str, time_difference);
    free(time1_str);
    free(time2_str);
    printf("\n");

    DateTime datetime1 = datetime_create(today.year, today.month, today.day, now.hour, now.minute, now.second, now.millisecond);
    char *datetime1_str = datetime_to_string(datetime1);
    printf("The current datetime is %s\n", datetime1_str);

    DateTime datetime2 = datetime_create(2024, JAN, 1, 0, 0, 0, 0);
    TimeInterval time_interval = datetime_diff(datetime1, datetime2);
    char *datetime2_str = datetime_to_string(datetime2);
    char *time_interval_str = time_interval_to_string(time_interval);
    printf("Time interval between %s and %s is %s\n", datetime1_str, datetime2_str, time_interval_str);
    free(datetime1_str);
    free(datetime2_str);
    free(time_interval_str);
    printf("\n");

    return 0;
}
