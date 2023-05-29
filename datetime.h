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

typedef enum Day {
    SUN,
    MON = 1,
    TUE,
    WED,
    THU,
    FRI,
    SAT
} Day;

typedef struct Date {
    int year;
    int month;
    int day;
} Date;

typedef struct Time {
    int hour;
    int minute;
    int second;
} Time;

typedef struct DateTime {
    Date date;
    Time time;
} DateTime;

/**
 * @brief Determine whether the year is a leap year.
 * @param year The year.
 * @return Returns true if the year is a leap year, otherwise returns false.
 */
bool is_leap_year(int year);

/**
 * @brief Get the number of days in the month.
 * @param year The year.
 * @param month The month.
 * @return Returns the number of days in the month.
 */
int days_in_month(int year, int month);

/**
 * @brief Get the number of days in the year.
 * @param year The year.
 * @return Returns the number of days in the year.
 */
int days_in_year(int year);

/**
 * @brief Determine the given date is the n-th day of the year.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @return Returns the n-th day of the year.
 */
int nth_day_of_year(int year, int month, int day);

/**
 * @brief Determine the given date is the n-th day of the week.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @return Returns the n-th day of the week.
 */
Day nth_day_of_week(int year, int month, int day);

/**
 * @brief Create a Date object.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @return Returns the Date object.
 */
Date date_create(int year, int month, int day);

/**
 * @brief Get the current date.
 * @return Returns the Date object.
 */
Date date_now();

/**
 * @brief Compare two Date objects.
 * @param date1 The first Date object.
 * @param date2 The second Date object.
 * @return Returns 1 if date1 is greater than date2.
 *         Returns -1 if date1 is less than date2.
 *         Returns 0 if date1 is equal to date2.
 */
int date_compare(Date date1, Date date2);

/**
 * @brief Add days to the date.
 * @param date The Date object.
 * @param days The number of days to add/subtract.
 * @return Returns the new Date object.
 */
Date date_add(Date date, int days);

/**
 * @brief Get the difference between two Date objects.
 * @param date1 The first Date object.
 * @param date2 The second Date object.
 * @return Returns the difference between two Date objects.
 */
int date_diff(Date date1, Date date2);

/**
 * @brief Create a Time object.
 * @param hour The hour.
 * @param minute The minute.
 * @param second The second.
 * @return Returns the Time object.
 */
Time time_create(int hour, int minute, int second);

/**
 * @brief Get the current time.
 * @return Returns the Time object.
 */
Time time_now();

/**
 * @brief Compare two Time objects.
 * @param time1 The first Time object.
 * @param time2 The second Time object.
 * @return Returns 1 if time1 is greater than time2.
 *         Returns -1 if time1 is less than time2.
 *         Returns 0 if time1 is equal to time2.
 */
int time_compare(Time time1, Time time2);

/**
 * @brief Add seconds to the time.
 * @param time The Time object.
 * @param seconds The number of seconds to add/subtract.
 * @return Returns the new Time object.
 */
Time time_add(Time time, int second);

/**
 * @brief Get the difference between two Time objects.
 * @param time1 The first Time object.
 * @param time2 The second Time object.
 * @return Returns the difference between two Time objects.
 */
int time_diff(Time time1, Time time2);

#endif
