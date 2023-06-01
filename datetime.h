#ifndef _DATETIME_H_
#define _DATETIME_H_

#include <time.h>

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

#define MILLISECONDS_PER_MINUTE (MILLISECONDS_PER_SECOND * SECONDS_PER_MINUTE)
#define MILLISECONDS_PER_HOUR (MILLISECONDS_PER_MINUTE * MINUTES_PER_HOUR)
#define MILLISECONDS_PER_DAY (MILLISECONDS_PER_HOUR * HOURS_PER_DAY)
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

typedef enum Weekday {
    SUN,
    MON,
    TUE,
    WED,
    THU,
    FRI,
    SAT
} Weekday;

typedef struct TimeInterval {
    int days;
    int hours;
    int minutes;
    int seconds;
    int milliseconds;
} TimeInterval;

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
 * @brief Get the full name of the month.
 * @param month The month.
 * @return Returns the full name of the month.
 */
const char *month_name(Month month);

/**
 * @brief Get the full name of the weekday.
 * @param weekday The weekday.
 * @return Returns the full name of the weekday.
 */
const char *weekday_full_name(Weekday weekday);

/**
 * @brief Get the abbreviated name of the weekday.
 * @param weekday The weekday.
 * @return Returns the abbreviated name of the weekday.
 */
const char *weekday_abbr_name(Weekday weekday);

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
 * @brief Determine the day of the week.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @return Returns the day of the week.
 */
Weekday weekday(int year, int month, int day);

/**
 * @brief Get the string representation of the calendar for the given month.
 * @param year The year.
 * @param month The month.
 * @return Returns the string representation of the calendar for the given month.
 * @note The caller must free the returned string.
 */
char *calendar(int year, int month);

/**
 * @brief Create a TimeInterval object.
 * @param days The days.
 * @param hours The hours.
 * @param minutes The minutes.
 * @param seconds The seconds.
 * @param milliseconds The milliseconds.
 * @return Returns the TimeInterval object.
 */
TimeInterval time_interval_create(int days, int hours, int minutes, int seconds, int milliseconds);

/**
 * @brief Get the string representation of the time interval.
 * @param time_interval The TimeInterval object.
 * @return Returns the string representation of the time interval.
 * @note The caller must free the returned string.
 */
char *time_interval_to_string(TimeInterval time_interval);

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
 * @brief Get the the days between two Date objects.
 * @param date1 The first Date object.
 * @param date2 The second Date object.
 * @return Returns the days between two Date objects.
 */
int date_diff(Date date1, Date date2);

/**
 * @brief Get the string representation (yyyy-mm-dd) of the date.
 * @param date The Date object.
 * @return Returns the string representation of the date.
 * @note The caller must free the returned string.
 */
char *date_to_string(Date date);

/**
 * @brief Get the string representation (Day Mon dd yyyy) of the date.
 * @param date The Date object.
 * @return Returns the string representation of the date.
 * @note The caller must free the returned string.
 */
char *date_ascii_string(Date date);

/**
 * @brief Create a Time object.
 * @param hour The hour.
 * @param minute The minute.
 * @param second The second.
 * @param millisecond The millisecond.
 * @return Returns the Time object.
 */
Time time_create(int hour, int minute, int second, int millisecond);

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
 * @param milliseconds The number of milliseconds to add/subtract.
 * @return Returns the new Time object.
 */
Time time_add(Time time, int milliseconds);

/**
 * @brief Get the milliseconds between two Time objects.
 * @param time1 The first Time object.
 * @param time2 The second Time object.
 * @return Returns the milliseconds between two Time objects.
 */
int time_diff(Time time1, Time time2);

/**
 * @brief Get the string representation (hh:mm:ss.fff) of the time.
 * @param time The Time object.
 * @return Returns the string representation of the time.
 * @note The caller must free the returned string.
 */
char *time_to_string(Time time);

/**
 * @brief Get the string representation (hh:mm:ss) of the time.
 * @param time The Time object.
 * @return Returns the string representation of the time.
 * @note The caller must free the returned string.
 */
char *time_ascii_string(Time time);

/**
 * @brief Create a DateTime object.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @param hour The hour.
 * @param minute The minute.
 * @param second The second.
 * @param millisecond The millisecond.
 * @return Returns the Date object.
 */
DateTime datetime_create(int year, int month, int day, int hour, int minute, int second, int millisecond);

/**
 * @brief Get the current datetime.
 * @return Returns the DateTime object.
 */
DateTime datetime_now();

/**
 * @brief Create a DateTime object from the Unix timestamp (since 1970-01-01 00:00:00 UTC).
 * @param timestamp The Unix timestamp. The range of timestamp is 0 ~ 2147483647 (2038-01-19 03:14:07 UTC).
 * @return Returns the DateTime object.
 */
DateTime datetime_from_timestamp(time_t timestamp);

/**
 * @brief Convert the DateTime object to the Unix timestamp (since 1970-01-01 00:00:00 UTC).
 * @param datetime The DateTime object.
 * @return Returns the Unix timestamp.
 */
time_t datetime_to_timestamp(DateTime datetime);

/**
 * @brief Create a DateTime object from the ordinal (since 0001-01-01 00:00:00).
 * @param ordinal The ordinal.
 * @return Returns the DateTime object.
 */
DateTime datetime_from_ordinal(int ordinal);

/**
 * @brief Convert the DateTime object to the ordinal (since 0001-01-01 00:00:00).
 * @param datetime The DateTime object.
 * @return Returns the ordinal.
 */
int datetime_to_ordinal(DateTime datetime);

/**
 * @brief Compare two DateTime objects.
 * @param datetime1 The first DateTime object.
 * @param datetime2 The second DateTime object.
 * @return Returns 1 if datetime1 is greater than datetime2.
 *         Returns -1 if datetime1 is less than datetime2.
 *         Returns 0 if datetime1 is equal to datetime2.
 */
int datetime_compare(DateTime datetime1, DateTime datetime2);

/**
 * @brief Add days and milliseconds to the datetime.
 * @param datetime The DateTime object.
 * @param days The number of days to add/subtract.
 * @param milliseconds The number of milliseconds to add/subtract.
 * @return DateTime The new DateTime object.
 */
DateTime datetime_add(DateTime datetime, int days, int milliseconds);

/**
 * @brief Get the difference between two DateTime objects.
 * @param datetime1 The first DateTime object.
 * @param datetime2 The second DateTime object.
 * @return TimeInterval The difference between two DateTime objects.
 */
TimeInterval datetime_diff(DateTime datetime1, DateTime datetime2);

/**
 * @brief Get the string representation (yyyy-mm-dd hh:mm:ss.fff) of the datetime.
 * @param datetime The DateTime object.
 * @return Returns the string representation of the datetime.
 * @note The caller must free the returned string.
 */
char *datetime_to_string(DateTime datetime);

/**
 * @brief Get the string representation (Day Mon dd hh:mm:ss yyyy) of the datetime.
 * @param datetime DateTime Time object.
 * @return Returns the string representation of the datetime.
 * @note The caller must free the returned string.
 */
char *datetime_ascii_string(DateTime datetime);

/**
 * @brief Get the specified string representation of the datetime.
 * @param datetime The DateTime object.
 * @param format The format string.
 * | Specifier | Replaced by                                               | Example                  |
 * | %a        | Abbreviated weekday name                                  | Sun                      |
 * | %A        | Full weekday name                                         | Sunday                   |
 * | %b        | Abbreviated month name                                    | Mar                      |
 * | %B        | Full month name                                           | March                    |
 * | %c        | Date and time representation for the current locale       | Sun Aug 19 02:56:02 2012 |
 * | %d        | Day of the month (01-31)                                  | 19                       |
 * | %H        | Hour in 24h format (00-23)                                | 14                       |
 * | %I        | Hour in 12h format (01-12)                                | 02                       |
 * | %j        | Day of the year (001-366)                                 | 231                      |
 * | %m        | Month as a decimal number (01-12)                         | 08                       |
 * | %M        | Minute (00-59)                                            | 55                       |
 * | %p        | AM or PM                                                  | PM                       |
 * | %S        | Second (00-61)                                            | 02                       |
 * | %U        | Week number of the year (Sunday as the first day) (00-53) | 33                       |
 * | %w        | Weekday as a decimal number (0-6)                         | 4                        |
 * | %W        | Week number of the year (Monday as the first day) (00-53) | 34                       |
 * | %x        | Date representation for the current locale                | 08/19/12                 |
 * | %X        | Time representation for the current locale                | 02:50:06                 |
 * | %y        | Year without century (00-99)                              | 01                       |
 * | %Y        | Year with century                                         | 2001                     |
 * | %z        | Timezone offset (+0000)                                   | +0000                    |
 * | %%        | A % sign                                                  | %                        |
 * @return Returns the specified string representation of the datetime.
 * @note The caller must free the returned string.
 */
char *datetime_format_string(DateTime datetime, const char *format);

#endif
