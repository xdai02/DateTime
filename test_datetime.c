#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "datetime.h"

void test_is_leap_year() {
    assert(is_leap_year(1) == false);
    assert(is_leap_year(1900) == false);
    assert(is_leap_year(1970) == false);
    assert(is_leap_year(2000) == true);
    assert(is_leap_year(2004) == true);
    assert(is_leap_year(2020) == true);
    assert(is_leap_year(2022) == false);
    assert(is_leap_year(2024) == true);
    assert(is_leap_year(3000) == false);
    assert(is_leap_year(4000) == true);
    assert(is_leap_year(9999) == false);

    printf("[PASS] is_leap_year\n");
}

void test_month_name() {
    assert(strcmp(month_name(JAN), "January") == 0);
    assert(strcmp(month_name(FEB), "February") == 0);
    assert(strcmp(month_name(MAR), "March") == 0);
    assert(strcmp(month_name(APR), "April") == 0);
    assert(strcmp(month_name(MAY), "May") == 0);
    assert(strcmp(month_name(JUN), "June") == 0);
    assert(strcmp(month_name(JUL), "July") == 0);
    assert(strcmp(month_name(AUG), "August") == 0);
    assert(strcmp(month_name(SEP), "September") == 0);
    assert(strcmp(month_name(OCT), "October") == 0);
    assert(strcmp(month_name(NOV), "November") == 0);
    assert(strcmp(month_name(DEC), "December") == 0);

    printf("[PASS] month_name\n");
}

void test_weekday_name() {
    assert(strcmp(weekday_name(SUN), "Sunday") == 0);
    assert(strcmp(weekday_name(MON), "Monday") == 0);
    assert(strcmp(weekday_name(TUE), "Tuesday") == 0);
    assert(strcmp(weekday_name(WED), "Wednesday") == 0);
    assert(strcmp(weekday_name(THU), "Thursday") == 0);
    assert(strcmp(weekday_name(FRI), "Friday") == 0);
    assert(strcmp(weekday_name(SAT), "Saturday") == 0);

    printf("[PASS] day_name\n");
}

void test_days_in_month() {
    assert(days_in_month(2020, FEB) == DAYS_IN_FEBRUARY_LEAP);
    assert(days_in_month(2023, JAN) == 31);
    assert(days_in_month(2023, FEB) == DAYS_IN_FEBRUARY_COMMON);
    assert(days_in_month(2023, MAR) == 31);
    assert(days_in_month(2023, APR) == 30);
    assert(days_in_month(2023, MAY) == 31);
    assert(days_in_month(2023, JUN) == 30);
    assert(days_in_month(2023, JUL) == 31);
    assert(days_in_month(2023, AUG) == 31);
    assert(days_in_month(2023, SEP) == 30);
    assert(days_in_month(2023, OCT) == 31);
    assert(days_in_month(2023, NOV) == 30);
    assert(days_in_month(2023, DEC) == 31);

    printf("[PASS] days_in_month\n");
}

void test_days_in_year() {
    assert(days_in_year(1) == DAYS_IN_COMMON_YEAR);
    assert(days_in_year(1900) == DAYS_IN_COMMON_YEAR);
    assert(days_in_year(1970) == DAYS_IN_COMMON_YEAR);
    assert(days_in_year(2000) == DAYS_IN_LEAP_YEAR);
    assert(days_in_year(2004) == DAYS_IN_LEAP_YEAR);
    assert(days_in_year(2020) == DAYS_IN_LEAP_YEAR);
    assert(days_in_year(2022) == DAYS_IN_COMMON_YEAR);
    assert(days_in_year(2024) == DAYS_IN_LEAP_YEAR);
    assert(days_in_year(3000) == DAYS_IN_COMMON_YEAR);
    assert(days_in_year(4000) == DAYS_IN_LEAP_YEAR);
    assert(days_in_year(9999) == DAYS_IN_COMMON_YEAR);

    printf("[PASS] days_in_year\n");
}

void test_nth_day_of_year() {
    assert(nth_day_of_year(1900, JAN, 1) == 1);
    assert(nth_day_of_year(1900, DEC, 31) == DAYS_IN_COMMON_YEAR);
    assert(nth_day_of_year(1970, FEB, 1) == 32);
    assert(nth_day_of_year(1970, DEC, 1) == 335);
    assert(nth_day_of_year(2000, JAN, 31) == 31);
    assert(nth_day_of_year(2000, FEB, 1) == 32);
    assert(nth_day_of_year(2000, FEB, 29) == 60);
    assert(nth_day_of_year(2000, MAR, 1) == 61);
    assert(nth_day_of_year(2000, NOV, 30) == 335);
    assert(nth_day_of_year(2000, DEC, 31) == DAYS_IN_LEAP_YEAR);
    assert(nth_day_of_year(2023, JAN, 1) == 1);
    assert(nth_day_of_year(2023, FEB, 1) == 32);
    assert(nth_day_of_year(2023, FEB, 28) == 59);
    assert(nth_day_of_year(2023, MAR, 1) == 60);
    assert(nth_day_of_year(2023, NOV, 30) == 334);
    assert(nth_day_of_year(2023, DEC, 31) == DAYS_IN_COMMON_YEAR);

    printf("[PASS] nth_day_of_year\n");
}

void test_weekday() {
    assert(weekday(1900, JAN, 1) == MON);
    assert(weekday(1900, DEC, 31) == MON);
    assert(weekday(1970, FEB, 1) == SUN);
    assert(weekday(1970, DEC, 1) == TUE);
    assert(weekday(2000, JAN, 31) == MON);
    assert(weekday(2000, FEB, 1) == TUE);
    assert(weekday(2000, FEB, 29) == TUE);
    assert(weekday(2000, MAR, 1) == WED);
    assert(weekday(2000, NOV, 30) == THU);
    assert(weekday(2000, DEC, 31) == SUN);
    assert(weekday(2023, JAN, 1) == SUN);
    assert(weekday(2023, FEB, 1) == WED);
    assert(weekday(2023, FEB, 28) == TUE);
    assert(weekday(2023, MAR, 1) == WED);
    assert(weekday(2023, NOV, 30) == THU);
    assert(weekday(2023, DEC, 31) == SUN);

    printf("[PASS] weekday\n");
}

void test_calendar() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int year = tm.tm_year + 1900;
    int month = tm.tm_mon + 1;
    char *str = calendar(year, month);
    printf("%s", str);
    free((void *)str);

    printf("[PASS] calendar\n");
}

void test_time_interval_create() {
    TimeInterval time_interval;

    time_interval = time_interval_create(0, 0, 0, 0, 0);
    assert(time_interval.days == 0);
    assert(time_interval.hours == 0);
    assert(time_interval.minutes == 0);
    assert(time_interval.seconds == 0);
    assert(time_interval.milliseconds == 0);

    time_interval = time_interval_create(1, 2, 3, 4, 5);
    assert(time_interval.days == 1);
    assert(time_interval.hours == 2);
    assert(time_interval.minutes == 3);
    assert(time_interval.seconds == 4);
    assert(time_interval.milliseconds == 5);

    printf("[PASS] time_interval_create\n");
}

void test_time_interval_to_string() {
    TimeInterval time_interval;
    char *str;

    time_interval = time_interval_create(0, 0, 0, 0, 0);
    str = time_interval_to_string(time_interval);
    assert(strcmp(str, "0 day(s) 0 hour(s) 0 minute(s) 0 second(s) 0 millisecond(s)") == 0);
    free(str);

    time_interval = time_interval_create(1, 2, 3, 4, 5);
    str = time_interval_to_string(time_interval);
    assert(strcmp(str, "1 day(s) 2 hour(s) 3 minute(s) 4 second(s) 5 millisecond(s)") == 0);
    free(str);

    printf("[PASS] time_interval_to_string\n");
}

void test_date_create() {
    Date date;

    date = date_create(2020, FEB, 29);
    assert(date.year == 2020);
    assert(date.month == FEB);
    assert(date.day == 29);

    date = date_create(2000, DEC, 31);
    assert(date.year == 2000);
    assert(date.month == DEC);
    assert(date.day == 31);

    date = date_create(2023, JAN, 1);
    assert(date.year == 2023);
    assert(date.month == JAN);
    assert(date.day == 1);

    printf("[PASS] date_create\n");
}

void test_date_now() {
    Date date = date_now();
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    assert(date.year == tm.tm_year + 1900);
    assert(date.month == tm.tm_mon + 1);
    assert(date.day == tm.tm_mday);

    printf("[PASS] date_now\n");
}

void test_date_compare() {
    Date date1;
    Date date2;

    date1 = date_create(2023, JAN, 1);
    date2 = date_create(2023, JAN, 1);
    assert(date_compare(date1, date2) == 0);

    date1 = date_create(2023, JAN, 1);
    date2 = date_create(2023, JAN, 2);
    assert(date_compare(date1, date2) < 0);

    date1 = date_create(2023, FEB, 5);
    date2 = date_create(2023, JAN, 2);
    assert(date_compare(date1, date2) > 0);

    date1 = date_create(2023, FEB, 5);
    date2 = date_create(2024, FEB, 5);
    assert(date_compare(date1, date2) < 0);

    printf("[PASS] date_compare\n");
}

void test_date_add() {
    Date date;
    Date new_date;

    date = date_create(2000, JAN, 1);
    new_date = date_add(date, 0);
    assert(new_date.year == 2000);
    assert(new_date.month == JAN);
    assert(new_date.day == 1);

    date = date_create(2000, JAN, 31);
    new_date = date_add(date, 1);
    assert(new_date.year == 2000);
    assert(new_date.month == FEB);
    assert(new_date.day == 1);

    date = date_create(2000, FEB, 28);
    new_date = date_add(date, 1);
    assert(new_date.year == 2000);
    assert(new_date.month == FEB);
    assert(new_date.day == 29);

    date = date_create(2000, JAN, 1);
    new_date = date_add(date, 30);
    assert(new_date.year == 2000);
    assert(new_date.month == JAN);
    assert(new_date.day == 31);

    date = date_create(2000, JAN, 1);
    new_date = date_add(date, 31);
    assert(new_date.year == 2000);
    assert(new_date.month == FEB);
    assert(new_date.day == 1);

    date = date_create(2000, JAN, 1);
    new_date = date_add(date, 100);
    assert(new_date.year == 2000);
    assert(new_date.month == APR);
    assert(new_date.day == 10);

    date = date_create(2000, JAN, 1);
    new_date = date_add(date, 365);
    assert(new_date.year == 2000);
    assert(new_date.month == DEC);
    assert(new_date.day == 31);

    date = date_create(2000, JAN, 1);
    new_date = date_add(date, 366);
    assert(new_date.year == 2001);
    assert(new_date.month == JAN);
    assert(new_date.day == 1);

    date = date_create(2023, MAY, 29);
    new_date = date_add(date, 10000);
    assert(new_date.year == 2050);
    assert(new_date.month == OCT);
    assert(new_date.day == 14);

    date = date_create(2000, JAN, 1);
    new_date = date_add(date, -1);
    assert(new_date.year == 1999);
    assert(new_date.month == DEC);
    assert(new_date.day == 31);

    date = date_create(2000, MAR, 1);
    new_date = date_add(date, -28);
    assert(new_date.year == 2000);
    assert(new_date.month == FEB);
    assert(new_date.day == 2);

    date = date_create(2000, MAR, 1);
    new_date = date_add(date, -29);
    assert(new_date.year == 2000);
    assert(new_date.month == FEB);
    assert(new_date.day == 1);

    date = date_create(2000, MAR, 1);
    new_date = date_add(date, -1000);
    assert(new_date.year == 1997);
    assert(new_date.month == JUN);
    assert(new_date.day == 5);

    date = date_create(2023, MAY, 29);
    new_date = date_add(date, -10000);
    assert(new_date.year == 1996);
    assert(new_date.month == JAN);
    assert(new_date.day == 11);

    printf("[PASS] date_add\n");
}

void test_date_diff() {
    Date date1;
    Date date2;

    date1 = date_create(2000, JAN, 1);
    date2 = date_create(2000, JAN, 1);
    assert(date_diff(date1, date2) == 0);

    date1 = date_create(2000, JAN, 1);
    date2 = date_create(2000, JAN, 2);
    assert(date_diff(date1, date2) == -1);

    date1 = date_create(2000, FEB, 1);
    date2 = date_create(2000, MAR, 1);
    assert(date_diff(date1, date2) == -29);

    date1 = date_create(2023, FEB, 1);
    date2 = date_create(2023, MAR, 1);
    assert(date_diff(date1, date2) == -28);

    date1 = date_create(2024, DEC, 31);
    date2 = date_create(2023, MAY, 29);
    assert(date_diff(date1, date2) == 582);

    date1 = date_create(3000, MAY, 29);
    date2 = date_create(2023, MAY, 29);
    assert(date_diff(date1, date2) == 356842);

    printf("[PASS] date_diff\n");
}

void test_date_to_string() {
    Date date;
    char *str;

    date = date_create(2000, JAN, 1);
    str = date_to_string(date);
    assert(strcmp(str, "2000-01-01") == 0);
    free(str);

    date = date_create(2000, FEB, 29);
    str = date_to_string(date);
    assert(strcmp(str, "2000-02-29") == 0);
    free(str);

    date = date_create(2023, MAY, 17);
    str = date_to_string(date);
    assert(strcmp(str, "2023-05-17") == 0);
    free(str);

    date = date_create(2024, DEC, 4);
    str = date_to_string(date);
    assert(strcmp(str, "2024-12-04") == 0);
    free(str);

    printf("[PASS] date_to_string\n");
}

void test_time_create() {
    Time time;

    time = time_create(0, 0, 0, 0);
    assert(time.hour == 0);
    assert(time.minute == 0);
    assert(time.second == 0);
    assert(time.millisecond == 0);

    time = time_create(23, 59, 59, 999);
    assert(time.hour == 23);
    assert(time.minute == 59);
    assert(time.second == 59);
    assert(time.millisecond == 999);

    printf("[PASS] time_create\n");
}

void test_time_now() {
    const int DELAY = 2;

    Time t1 = time_now();
    time_t t2 = time(NULL);
    struct tm tm = *localtime(&t2);

    assert(t1.hour == tm.tm_hour);
    assert(t1.minute == tm.tm_min);
    assert(t1.second <= tm.tm_sec + DELAY);
    assert(t1.millisecond < MILLISECONDS_PER_SECOND);

    printf("[PASS] time_now\n");
}

void test_time_compare() {
    Time time1;
    Time time2;

    time1 = time_create(7, 30, 23, 567);
    time2 = time_create(7, 30, 23, 567);
    assert(time_compare(time1, time2) == 0);

    time1 = time_create(7, 30, 0, 0);
    time2 = time_create(7, 30, 0, 1);
    assert(time_compare(time1, time2) < 0);

    time1 = time_create(7, 30, 5, 0);
    time2 = time_create(7, 30, 2, 1);
    assert(time_compare(time1, time2) > 0);

    time1 = time_create(7, 32, 0, 0);
    time2 = time_create(7, 30, 12, 677);
    assert(time_compare(time1, time2) > 0);

    time1 = time_create(17, 30, 0, 0);
    time2 = time_create(7, 30, 0, 0);
    assert(time_compare(time1, time2) > 0);

    printf("[PASS] time_compare\n");
}

void test_time_add() {
    Time time;
    Time new_time;

    time = time_create(0, 0, 0, 0);
    new_time = time_add(time, 0);
    assert(new_time.hour == 0);
    assert(new_time.minute == 0);
    assert(new_time.second == 0);
    assert(new_time.millisecond == 0);

    time = time_create(0, 0, 0, 0);
    new_time = time_add(time, 1);
    assert(new_time.hour == 0);
    assert(new_time.minute == 0);
    assert(new_time.second == 0);
    assert(new_time.millisecond == 1);

    time = time_create(23, 59, 59, 999);
    new_time = time_add(time, 1);
    assert(new_time.hour == 0);
    assert(new_time.minute == 0);
    assert(new_time.second == 0);
    assert(new_time.millisecond == 0);

    time = time_create(11, 30, 0, 0);
    new_time = time_add(time, 3601);
    assert(new_time.hour == 11);
    assert(new_time.minute == 30);
    assert(new_time.second == 3);
    assert(new_time.millisecond == 601);

    time = time_create(17, 35, 23, 643);
    new_time = time_add(time, 100000);
    assert(new_time.hour == 17);
    assert(new_time.minute == 37);
    assert(new_time.second == 3);
    assert(new_time.millisecond == 643);

    time = time_create(0, 0, 0, 0);
    new_time = time_add(time, -1);
    assert(new_time.hour == 23);
    assert(new_time.minute == 59);
    assert(new_time.second == 59);
    assert(new_time.millisecond == 999);

    time = time_create(11, 30, 0, 0);
    new_time = time_add(time, -3601);
    assert(new_time.hour == 11);
    assert(new_time.minute == 29);
    assert(new_time.second == 56);
    assert(new_time.millisecond == 399);

    time = time_create(17, 35, 23, 643);
    new_time = time_add(time, -100000);
    assert(new_time.hour == 17);
    assert(new_time.minute == 33);
    assert(new_time.second == 43);
    assert(new_time.millisecond == 643);

    printf("[PASS] time_add\n");
}

void test_time_diff() {
    Time time1;
    Time time2;

    time1 = time_create(0, 0, 0, 0);
    time2 = time_create(0, 0, 0, 0);
    assert(time_diff(time1, time2) == 0);

    time1 = time_create(23, 59, 59, 999);
    time2 = time_create(0, 0, 0, 0);
    assert(time_diff(time1, time2) == 86399999);

    time1 = time_create(12, 0, 0, 0);
    time2 = time_create(12, 0, 0, 0);
    assert(time_diff(time1, time2) == 0);

    time1 = time_create(12, 0, 0, 0);
    time2 = time_create(13, 0, 0, 0);
    assert(time_diff(time1, time2) == -3600000);

    time1 = time_create(12, 0, 0, 0);
    time2 = time_create(11, 0, 0, 0);
    assert(time_diff(time1, time2) == 3600000);

    time1 = time_create(12, 0, 0, 0);
    time2 = time_create(12, 30, 0, 0);
    assert(time_diff(time1, time2) == -1800000);

    time1 = time_create(12, 30, 0, 0);
    time2 = time_create(12, 0, 0, 0);
    assert(time_diff(time1, time2) == 1800000);

    time1 = time_create(17, 35, 23, 643);
    time2 = time_create(7, 53, 32, 346);
    assert(time_diff(time1, time2) == 34911297);

    printf("[PASS] time_diff\n");
}

void test_time_to_string() {
    Time time;
    char *str;

    time = time_create(0, 0, 0, 0);
    str = time_to_string(time);
    assert(strcmp(str, "00:00:00.000") == 0);
    free(str);

    time = time_create(23, 59, 59, 999);
    str = time_to_string(time);
    assert(strcmp(str, "23:59:59.999") == 0);
    free(str);

    time = time_create(12, 0, 0, 0);
    str = time_to_string(time);
    assert(strcmp(str, "12:00:00.000") == 0);
    free(str);

    time = time_create(12, 30, 0, 0);
    str = time_to_string(time);
    assert(strcmp(str, "12:30:00.000") == 0);
    free(str);

    time = time_create(12, 30, 17, 0);
    str = time_to_string(time);
    assert(strcmp(str, "12:30:17.000") == 0);
    free(str);

    time = time_create(12, 30, 17, 123);
    str = time_to_string(time);
    assert(strcmp(str, "12:30:17.123") == 0);
    free(str);

    printf("[PASS] time_to_string\n");
}

void test_datetime_create() {
    DateTime datetime;

    datetime = datetime_create(2000, JAN, 1, 0, 0, 0, 0);
    assert(datetime.date.year == 2000);
    assert(datetime.date.month == JAN);
    assert(datetime.date.day == 1);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_create(2023, MAY, 29, 23, 59, 59, 999);
    assert(datetime.date.year == 2023);
    assert(datetime.date.month == MAY);
    assert(datetime.date.day == 29);
    assert(datetime.time.hour == 23);
    assert(datetime.time.minute == 59);
    assert(datetime.time.second == 59);
    assert(datetime.time.millisecond == 999);

    printf("[PASS] datetime_create\n");
}

void test_datetime_now() {
    const int DELAY = 2;
    DateTime datetime = datetime_now();
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    assert(datetime.date.year == tm.tm_year + 1900);
    assert(datetime.date.month == tm.tm_mon + 1);
    assert(datetime.date.day == tm.tm_mday);
    assert(datetime.time.hour == tm.tm_hour);
    assert(datetime.time.minute == tm.tm_min);
    assert(datetime.time.second <= tm.tm_sec + DELAY);
    assert(datetime.time.millisecond < MILLISECONDS_PER_SECOND);

    printf("[PASS] datetime_now\n");
}

void test_datetime_from_timestamp() {
    DateTime datetime;

    datetime = datetime_from_timestamp(0);
    assert(datetime.date.year == 1970);
    assert(datetime.date.month == JAN);
    assert(datetime.date.day == 1);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_timestamp(86400);
    assert(datetime.date.year == 1970);
    assert(datetime.date.month == JAN);
    assert(datetime.date.day == 2);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_timestamp(2678400);
    assert(datetime.date.year == 1970);
    assert(datetime.date.month == FEB);
    assert(datetime.date.day == 1);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_timestamp(31536000);
    assert(datetime.date.year == 1971);
    assert(datetime.date.month == JAN);
    assert(datetime.date.day == 1);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_timestamp(978220800);
    assert(datetime.date.year == 2000);
    assert(datetime.date.month == DEC);
    assert(datetime.date.day == 31);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_timestamp(1685318400);
    assert(datetime.date.year == 2023);
    assert(datetime.date.month == MAY);
    assert(datetime.date.day == 29);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_timestamp(253402214400);
    assert(datetime.date.year == 9999);
    assert(datetime.date.month == DEC);
    assert(datetime.date.day == 31);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    printf("[PASS] datetime_from_timestamp\n");
}

void test_datetime_to_timestamp() {
    assert(datetime_to_timestamp(datetime_create(1970, JAN, 1, 0, 0, 0, 0)) == 0);
    assert(datetime_to_timestamp(datetime_create(1970, JAN, 2, 0, 0, 0, 0)) == 86400);
    assert(datetime_to_timestamp(datetime_create(1970, FEB, 1, 0, 0, 0, 0)) == 2678400);
    assert(datetime_to_timestamp(datetime_create(1971, JAN, 1, 0, 0, 0, 0)) == 31536000);
    assert(datetime_to_timestamp(datetime_create(2000, DEC, 31, 0, 0, 0, 0)) == 978220800);
    assert(datetime_to_timestamp(datetime_create(2023, MAY, 29, 0, 0, 0, 0)) == 1685318400);
    assert(datetime_to_timestamp(datetime_create(9999, DEC, 31, 0, 0, 0, 0)) == 253402214400);

    printf("[PASS] datetime_to_timestamp\n");
}

void test_datetime_from_ordinal() {
    DateTime datetime;

    datetime = datetime_from_ordinal(1);
    assert(datetime.date.year == 1);
    assert(datetime.date.month == JAN);
    assert(datetime.date.day == 1);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_ordinal(100);
    assert(datetime.date.year == 1);
    assert(datetime.date.month == APR);
    assert(datetime.date.day == 10);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_ordinal(1000);
    assert(datetime.date.year == 3);
    assert(datetime.date.month == SEP);
    assert(datetime.date.day == 27);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_ordinal(10000);
    assert(datetime.date.year == 28);
    assert(datetime.date.month == MAY);
    assert(datetime.date.day == 18);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_ordinal(100000);
    assert(datetime.date.year == 274);
    assert(datetime.date.month == OCT);
    assert(datetime.date.day == 16);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_ordinal(730920);
    assert(datetime.date.year == 2002);
    assert(datetime.date.month == MAR);
    assert(datetime.date.day == 11);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_from_ordinal(740000);
    assert(datetime.date.year == 2027);
    assert(datetime.date.month == JAN);
    assert(datetime.date.day == 19);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    printf("[PASS] datetime_from_ordinal\n");
}

void test_datetime_to_ordinal() {
    printf(" TODO TODO TODO TODO TODO");
    printf("[PASS] datetime_to_ordinal\n");
}

void test_datetime_compare() {
    DateTime datetime1;
    DateTime datetime2;

    datetime1 = datetime_create(2000, JAN, 1, 0, 0, 0, 0);
    datetime2 = datetime_create(2000, JAN, 1, 0, 0, 0, 0);
    assert(datetime_compare(datetime1, datetime2) == 0);

    datetime1 = datetime_create(2000, JAN, 1, 0, 0, 0, 0);
    datetime2 = datetime_create(2000, JAN, 1, 0, 0, 0, 1);
    assert(datetime_compare(datetime1, datetime2) < 0);

    datetime1 = datetime_create(2000, JAN, 1, 0, 0, 0, 0);
    datetime2 = datetime_create(2000, JAN, 1, 0, 0, 1, 0);
    assert(datetime_compare(datetime1, datetime2) < 0);

    datetime1 = datetime_create(2000, JAN, 1, 0, 0, 0, 0);
    datetime2 = datetime_create(2000, JAN, 1, 0, 1, 0, 0);
    assert(datetime_compare(datetime1, datetime2) < 0);

    datetime1 = datetime_create(2000, JAN, 1, 0, 0, 0, 0);
    datetime2 = datetime_create(2000, JAN, 1, 1, 0, 0, 0);
    assert(datetime_compare(datetime1, datetime2) < 0);

    datetime1 = datetime_create(2000, JAN, 1, 0, 0, 0, 0);
    datetime2 = datetime_create(2000, JAN, 2, 0, 0, 0, 0);
    assert(datetime_compare(datetime1, datetime2) < 0);

    datetime1 = datetime_create(2000, JAN, 1, 0, 0, 0, 0);
    datetime2 = datetime_create(2000, FEB, 1, 0, 0, 0, 0);
    assert(datetime_compare(datetime1, datetime2) < 0);

    datetime1 = datetime_create(2000, JAN, 1, 0, 0, 0, 0);
    datetime2 = datetime_create(2001, JAN, 1, 0, 0, 0, 0);
    assert(datetime_compare(datetime1, datetime2) < 0);

    printf("[PASS] datetime_compare\n");
}

void test_datetime_add() {
    DateTime datetime;

    datetime = datetime_create(2023, MAY, 29, 14, 40, 1, 0);
    datetime = datetime_add(datetime, 3, 100);
    assert(datetime.date.year == 2023);
    assert(datetime.date.month == JUN);
    assert(datetime.date.day == 1);
    assert(datetime.time.hour == 14);
    assert(datetime.time.minute == 40);
    assert(datetime.time.second == 1);
    assert(datetime.time.millisecond == 100);

    datetime = datetime_create(2023, MAY, 29, 23, 59, 59, 900);
    datetime = datetime_add(datetime, 0, 100);
    assert(datetime.date.year == 2023);
    assert(datetime.date.month == MAY);
    assert(datetime.date.day == 30);
    assert(datetime.time.hour == 0);
    assert(datetime.time.minute == 0);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 0);

    datetime = datetime_create(2023, MAY, 29, 14, 40, 1, 0);
    datetime = datetime_add(datetime, -2, 100);
    assert(datetime.date.year == 2023);
    assert(datetime.date.month == MAY);
    assert(datetime.date.day == 27);
    assert(datetime.time.hour == 14);
    assert(datetime.time.minute == 40);
    assert(datetime.time.second == 1);
    assert(datetime.time.millisecond == 100);

    datetime = datetime_create(2023, MAY, 29, 14, 40, 1, 0);
    datetime = datetime_add(datetime, -2, -100);
    assert(datetime.date.year == 2023);
    assert(datetime.date.month == MAY);
    assert(datetime.date.day == 27);
    assert(datetime.time.hour == 14);
    assert(datetime.time.minute == 40);
    assert(datetime.time.second == 0);
    assert(datetime.time.millisecond == 900);

    datetime = datetime_create(2023, MAY, 29, 0, 0, 0, 0);
    datetime = datetime_add(datetime, 0, -100);
    assert(datetime.date.year == 2023);
    assert(datetime.date.month == MAY);
    assert(datetime.date.day == 28);
    assert(datetime.time.hour == 23);
    assert(datetime.time.minute == 59);
    assert(datetime.time.second == 59);
    assert(datetime.time.millisecond == 900);

    printf("[PASS] datetime_add\n");
}

void test_datetime_diff() {
    TimeInterval time_interval;
    DateTime datetime1;
    DateTime datetime2;

    datetime1 = datetime_create(2023, MAY, 30, 22, 57, 28, 0);
    datetime2 = datetime_create(2023, MAY, 31, 22, 59, 29, 100);
    time_interval = datetime_diff(datetime1, datetime2);
    assert(time_interval.days == 1);
    assert(time_interval.hours == 0);
    assert(time_interval.minutes == 2);
    assert(time_interval.seconds == 1);
    assert(time_interval.milliseconds == 100);

    datetime1 = datetime_create(2023, JUN, 1, 0, 0, 0, 0);
    datetime2 = datetime_create(2023, MAY, 31, 23, 59, 59, 999);
    time_interval = datetime_diff(datetime1, datetime2);
    assert(time_interval.days == 0);
    assert(time_interval.hours == 0);
    assert(time_interval.minutes == 0);
    assert(time_interval.seconds == 0);
    assert(time_interval.milliseconds == 1);

    printf("[PASS] datetime_diff\n");
}

void test_datetime_to_string() {
    DateTime datetime;
    char *str;

    datetime = datetime_create(2000, JAN, 1, 0, 0, 0, 0);
    str = datetime_to_string(datetime);
    assert(strcmp(str, "2000-01-01 00:00:00.000") == 0);
    free(str);

    datetime = datetime_create(2000, JAN, 1, 23, 59, 59, 999);
    str = datetime_to_string(datetime);
    assert(strcmp(str, "2000-01-01 23:59:59.999") == 0);
    free(str);

    printf("[PASS] datetime_to_string\n");
}

int main() {
    test_is_leap_year();
    test_month_name();
    test_weekday_name();
    test_days_in_month();
    test_days_in_year();
    test_nth_day_of_year();
    test_weekday();
    test_calendar();

    test_time_interval_create();
    test_time_interval_to_string();

    test_date_create();
    test_date_now();
    test_date_compare();
    test_date_add();
    test_date_diff();
    test_date_to_string();

    test_time_create();
    test_time_now();
    test_time_compare();
    test_time_add();
    test_time_diff();
    test_time_to_string();

    test_datetime_create();
    test_datetime_now();
    test_datetime_from_timestamp();
    test_datetime_to_timestamp();
    test_datetime_from_ordinal();
    test_datetime_compare();
    test_datetime_add();
    test_datetime_diff();
    test_datetime_to_string();

    printf("[PASS] All\n");
    return 0;
}
