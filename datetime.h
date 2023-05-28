#ifndef _DATETIME_H_
#define _DATETIME_H_

typedef int bool;
#define true 1
#define false 0

#define NANOSECONDS_PER_MICROSECOND 1000
#define NANSECONDS_PER_MILLISECOND (NANOSECONDS_PER_MICROSECOND * 1000)
#define NANOSECONDS_PER_SECOND (NANOSECONDS_PER_MILLISECOND * 1000)
#define MICROSECONDS_PER_MILLISECOND 1000
#define MICROSECONDS_PER_SECOND (MICROSECONDS_PER_MILLISECOND * 1000)
#define MILLISECONDS_PER_SECOND 1000

#define SECONDS_PER_MINUTE 60
#define MINUTES_PER_HOUR 60
#define HOURS_PER_DAY 24
#define DAYS_IN_WEEK 7
#define MONTHS_PER_YEAR 12
#define SECONDS_PER_HOUR (SECONDS_PER_MINUTE * MINUTES_PER_HOUR)
#define SECONDS_PER_DAY (SECONDS_PER_HOUR * HOURS_PER_DAY)
#define SECONDS_PER_WEEK (SECONDS_PER_DAY * DAYS_IN_WEEK)
#define MINUTES_PER_DAY (MINUTES_PER_HOUR * HOURS_PER_DAY)
#define MINUTES_PER_WEEK (MINUTES_PER_DAY * DAYS_IN_WEEK)
#define HOURS_PER_WEEK (HOURS_PER_DAY * DAYS_IN_WEEK)

#define DAYS_IN_COMMON_YEAR 365
#define DAYS_IN_LEAP_YEAR 366
#define DAYS_IN_FEBRUARY_COMMON 28
#define DAYS_IN_FEBRUARY_LEAP 29

typedef enum Month {
    JAN = 1,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC
} Month;

typedef struct Date {
    int year;
    int month;
    int day;
} Date;

typedef struct Time {
    int hour;
    int minute;
    int second;
    int millisecond;
} Time;

bool is_leap_year(int year);
int days_in_month(int year, int month);
int days_in_year(int year);
int nth_day_of_year(int year, int month, int day);

Date date_create(int year, int month, int day);
Date date_now();
int date_compare(Date date1, Date date2);
Date date_add(Date date, int days);
int date_diff(Date date1, Date date2);

Time time_create(int hour, int minute, int second, int millisecond);
Time time_now();
int time_compare(Time time1, Time time2);
Time time_add(Time time, int milliseconds);
int time_diff(Time time1, Time time2);

#endif
