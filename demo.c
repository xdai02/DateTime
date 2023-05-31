#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"

int main() {
    printf("\n==================== TODAY ====================\n");
    Date today = date_now();
    char *today_str = date_to_string(today);
    printf("Today is %s (%s)\n", today_str, day_name(nth_day_of_week(today.year, today.month, today.day)));
    free(today_str);

    printf("\n==================== CALENDAR ====================\n");
    char *calendar_str = calendar(today.year, today.month);
    printf("%s\n", calendar_str);
    free(calendar_str);

    printf("\n==================== DATE ====================\n");
    Date date = date_add(today, 15);
    char *date_str = date_to_string(date);
    printf("15 days later is %s (%s)\n", date_str, day_name(nth_day_of_week(date.year, date.month, date.day)));
    free(date_str);

    int date_difference = date_diff(today, date);
    char *date1_str = date_to_string(today);
    char *date2_str = date_to_string(date);
    printf("The difference between %s and %s is %d days\n\n", date1_str, date2_str, date_difference);
    free(date1_str);
    free(date2_str);

    printf("\n==================== TIME ====================\n");
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

    return 0;
}
