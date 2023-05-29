#include <stdio.h>
#include <stdlib.h>
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

void test_nth_day_of_week() {
    assert(nth_day_of_week(1900, JAN, 1) == MON);
    assert(nth_day_of_week(1900, DEC, 31) == MON);
    assert(nth_day_of_week(1970, FEB, 1) == SUN);
    assert(nth_day_of_week(1970, DEC, 1) == TUE);
    assert(nth_day_of_week(2000, JAN, 31) == MON);
    assert(nth_day_of_week(2000, FEB, 1) == TUE);
    assert(nth_day_of_week(2000, FEB, 29) == TUE);
    assert(nth_day_of_week(2000, MAR, 1) == WED);
    assert(nth_day_of_week(2000, NOV, 30) == THU);
    assert(nth_day_of_week(2000, DEC, 31) == SUN);
    assert(nth_day_of_week(2023, JAN, 1) == SUN);
    assert(nth_day_of_week(2023, FEB, 1) == WED);
    assert(nth_day_of_week(2023, FEB, 28) == TUE);
    assert(nth_day_of_week(2023, MAR, 1) == WED);
    assert(nth_day_of_week(2023, NOV, 30) == THU);
    assert(nth_day_of_week(2023, DEC, 31) == SUN);

    printf("[PASS] nth_day_of_week\n");
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
#if 0
    Date date1 = date_create(2023, JAN, 1);
    Date date2 = date_create(2000, DEC, 31);
    assert(date_compare(date1, date2) > 0);
    assert(date_compare(date2, date1) < 0);
    assert(date_compare(date1, date1) == 0);
#endif
    printf("[TODO] date_compare\n");
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
#if 0
    Time time1 = time_create(7, 30, 0, 0);
    Time time2 = time_create(16, 0, 0, 0);
    assert(time_compare(time1, time2) < 0);
    assert(time_compare(time2, time1) > 0);
    assert(time_compare(time1, time1) == 0);
#endif
    printf("[TODO] time_compare\n");
}

void test_time_add() {
#if 0
    Time time;
    Time new_time;

    time = time_create(0, 0, 0);
    new_time = time_add(time, 0);
    assert(new_time.hour == 0);
    assert(new_time.minute == 0);
    assert(new_time.second == 0);

    time = time_create(0, 0, 0);
    new_time = time_add(time, 1);
    assert(new_time.hour == 0);
    assert(new_time.minute == 0);
    assert(new_time.second == 1);

    time = time_create(23, 59, 59);
    new_time = time_add(time, 1);
    assert(new_time.hour == 0);
    assert(new_time.minute == 0);
    assert(new_time.second == 0);

    time = time_create(11, 30, 0);
    new_time = time_add(time, 3601);
    assert(new_time.hour == 12);
    assert(new_time.minute == 30);
    assert(new_time.second == 1);

    time = time_create(0, 0, 0);
    new_time = time_add(time, -1);
    assert(new_time.hour == 23);
    assert(new_time.minute == 59);
    assert(new_time.second == 59);

    time = time_create(11, 30, 0);
    new_time = time_add(time, -3601);
    assert(new_time.hour == 10);
    assert(new_time.minute == 29);
    assert(new_time.second == 59);
#endif
    printf("[TOOD] time_add\n");
}

void test_time_diff() {
#if 0
    Time time1;
    Time time2;

    time1 = time_create(0, 0, 0);
    time2 = time_create(0, 0, 0);
    assert(time_diff(time1, time2) == 0);

    time1 = time_create(23, 59, 59);
    time2 = time_create(0, 0, 0);
    assert(time_diff(time1, time2) == 86399);

    time1 = time_create(12, 0, 0);
    time2 = time_create(12, 0, 0);
    assert(time_diff(time1, time2) == 0);

    time1 = time_create(12, 0, 0);
    time2 = time_create(13, 0, 0);
    assert(time_diff(time1, time2) == -3600);

    time1 = time_create(12, 0, 0);
    time2 = time_create(11, 0, 0);
    assert(time_diff(time1, time2) == 3600);

    time1 = time_create(12, 0, 0);
    time2 = time_create(12, 30, 0);
    assert(time_diff(time1, time2) == -1800);

    time1 = time_create(12, 30, 0);
    time2 = time_create(12, 0, 0);
    assert(time_diff(time1, time2) == 1800);
#endif
    printf("[TODO] time_diff\n");
}

int main() {
    test_is_leap_year();
    test_days_in_month();
    test_days_in_year();
    test_nth_day_of_year();
    test_nth_day_of_week();

    test_date_create();
    test_date_now();
    test_date_compare();
    test_date_add();
    test_date_diff();

    test_time_create();
    test_time_now();
    test_time_compare();
    test_time_add();
    test_time_diff();

    printf("[PASS] All\n");
    return 0;
}
