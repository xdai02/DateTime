#include "datetime.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#define return_if(expr) \
    if (expr) {         \
        return;         \
    }

#define return_if_fail(expr) \
    if (!(expr)) {           \
        return;              \
    }

#define return_value_if(expr, ret) \
    if (expr) {                    \
        return (ret);              \
    }

#define return_value_if_fail(expr, ret) \
    if (!(expr)) {                      \
        return (ret);                   \
    }

#define exit_if(expr)       \
    if (expr) {             \
        exit(EXIT_FAILURE); \
    }

#define exit_if_fail(expr)  \
    if (!(expr)) {          \
        exit(EXIT_FAILURE); \
    }

#define MIN_YEAR 1
#define MAX_YEAR 9999

/**
 * @brief Determine whether the year is a leap year.
 * @param year The year.
 * @return Returns true if the year is a leap year, otherwise returns false.
 */
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/**
 * @brief Get the number of days in the month.
 * @param year The year.
 * @param month The month.
 * @return Returns the number of days in the month.
 */
int days_in_month(int year, int month) {
    switch (month) {
    case JAN:
    case MAR:
    case MAY:
    case JUL:
    case AUG:
    case OCT:
    case DEC:
        return 31;
    case APR:
    case JUN:
    case SEP:
    case NOV:
        return 30;
    case FEB:
        return is_leap_year(year) ? DAYS_IN_FEBRUARY_LEAP : DAYS_IN_FEBRUARY_COMMON;
    default:
        fprintf(stderr, "Error: month must be 1 ~ 12.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Get the number of days in the year.
 * @param year The year.
 * @return Returns the number of days in the year.
 */
int days_in_year(int year) {
    return is_leap_year(year) ? DAYS_IN_LEAP_YEAR : DAYS_IN_COMMON_YEAR;
}

/**
 * @brief Determine whether the date is valid.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @return Returns true if the date is valid, otherwise returns false.
 */
static bool __is_valid_date(int year, int month, int day) {
    if (year < MIN_YEAR || year > MAX_YEAR) {
        fprintf(stderr, "Error: year must be %d ~ %d.\n", MIN_YEAR, MAX_YEAR);
        return false;
    }

    if (month < JAN || month > DEC) {
        fprintf(stderr, "Error: month must be 1 ~ 12.\n");
        return false;
    }

    if (day < 1 || day > days_in_month(year, month)) {
        fprintf(stderr, "Error: only %d days in %d/%d.\n", days_in_month(year, month), year, month);
        return false;
    }

    return true;
}

/**
 * @brief Determine the given date is the n-th day of the year.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @return Returns the n-th day of the year.
 */
int nth_day_of_year(int year, int month, int day) {
    int i = 0;
    int days = 0;

    exit_if_fail(__is_valid_date(year, month, day));

    for (i = 1; i < month; i++) {
        days += days_in_month(year, i);
    }
    return days + day;
}

/**
 * @brief Determine the given date is the n-th day of the week.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @return Returns the n-th day of the week.
 */
Day nth_day_of_week(int year, int month, int day) {
    int h;

    exit_if_fail(__is_valid_date(year, month, day));

    if (month < 3) {
        month += 12;
        year--;
    }
    h = (day + (26 * (month + 1)) / 10 + year + year / 4 - year / 100 + year / 400) % DAYS_IN_WEEK;
    h = (h + 6) % DAYS_IN_WEEK;
    return (Day)h;
}

/**
 * @brief Create a Date object.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @return Returns the Date object.
 */
Date date_create(int year, int month, int day) {
    Date date;
    exit_if_fail(__is_valid_date(year, month, day));
    date.year = year;
    date.month = month;
    date.day = day;
    return date;
}

/**
 * @brief Get the current date.
 * @return Returns the Date object.
 */
Date date_now() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return date_create(tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
}

/**
 * @brief Compare two Date objects.
 * @param date1 The first Date object.
 * @param date2 The second Date object.
 * @return Returns 1 if date1 is greater than date2.
 *         Returns -1 if date1 is less than date2.
 *         Returns 0 if date1 is equal to date2.
 */
int date_compare(Date date1, Date date2) {
    exit_if_fail(__is_valid_date(date1.year, date1.month, date1.day));
    exit_if_fail(__is_valid_date(date2.year, date2.month, date2.day));

    if (date1.year > date2.year) {
        return 1;
    } else if (date1.year < date2.year) {
        return -1;
    }

    if (date1.month > date2.month) {
        return 1;
    } else if (date1.month < date2.month) {
        return -1;
    }

    if (date1.day > date2.day) {
        return 1;
    } else if (date1.day < date2.day) {
        return -1;
    }

    return 0;
}

/**
 * @brief Add days to the date.
 * @param date The Date object.
 * @param days The number of days to add/subtract.
 * @return Returns the new Date object.
 */
Date date_add(Date date, int days) {
    struct tm tm_date = {0};
    exit_if_fail(__is_valid_date(date.year, date.month, date.day));

    tm_date.tm_year = date.year - 1900;
    tm_date.tm_mon = date.month - 1;
    tm_date.tm_mday = date.day + days;

    mktime(&tm_date);
    return date_create(tm_date.tm_year + 1900, tm_date.tm_mon + 1, tm_date.tm_mday);
}

/**
 * @brief Get the difference between two Date objects.
 * @param date1 The first Date object.
 * @param date2 The second Date object.
 * @return Returns the difference between two Date objects.
 */
int date_diff(Date date1, Date date2) {
    struct tm tm_date1 = {0};
    struct tm tm_date2 = {0};
    time_t time1;
    time_t time2;
    double diff_seconds = 0;

    exit_if_fail(__is_valid_date(date1.year, date1.month, date1.day));
    exit_if_fail(__is_valid_date(date2.year, date2.month, date2.day));

    tm_date1.tm_year = date1.year - 1900;
    tm_date1.tm_mon = date1.month - 1;
    tm_date1.tm_mday = date1.day;
    tm_date2.tm_year = date2.year - 1900;
    tm_date2.tm_mon = date2.month - 1;
    tm_date2.tm_mday = date2.day;

    time1 = mktime(&tm_date1);
    time2 = mktime(&tm_date2);
    diff_seconds = difftime(time1, time2);
    return (int)(diff_seconds / SECONDS_PER_DAY);
}

/**
 * @brief Determine whether the time is valid.
 * @param hour The hour.
 * @param minute The minute.
 * @param second The second.
 * @return Returns true if the time is valid, otherwise returns false.
 */
static bool __is_valid_time(int hour, int minute, int second) {
    if (hour < 0 || hour >= HOURS_PER_DAY) {
        fprintf(stderr, "Error: hour must be 0 ~ 23.\n");
        return false;
    }

    if (minute < 0 || minute >= MINUTES_PER_HOUR) {
        fprintf(stderr, "Error: minute must be 0 ~ 59.\n");
        return false;
    }

    if (second < 0 || second >= SECONDS_PER_MINUTE) {
        fprintf(stderr, "Error: second must be 0 ~ 59.\n");
        return false;
    }

    return true;
}

/**
 * @brief Create a Time object.
 * @param hour The hour.
 * @param minute The minute.
 * @param second The second.
 * @return Returns the Time object.
 */
Time time_create(int hour, int minute, int second) {
    Time time;
    exit_if_fail(__is_valid_time(hour, minute, second));
    time.hour = hour;
    time.minute = minute;
    time.second = second;
    return time;
}

/**
 * @brief Get the current time.
 * @return Returns the Time object.
 */
Time time_now() {
    Time time;

#ifdef _WIN32
    SYSTEMTIME st;
#else
    struct timeval tv;
    struct tm *tm;
#endif

#ifdef _WIN32
    GetLocalTime(&st);
    time = time_create(st.wHour, st.wMinute, st.wSecond);
#else
    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec);
    time = time_create(tm->tm_hour, tm->tm_min, tm->tm_sec);
#endif

    return time;
}

/**
 * @brief Compare two Time objects.
 * @param time1 The first Time object.
 * @param time2 The second Time object.
 * @return Returns 1 if time1 is greater than time2.
 *         Returns -1 if time1 is less than time2.
 *         Returns 0 if time1 is equal to time2.
 */
int time_compare(Time time1, Time time2) {
    exit_if_fail(__is_valid_time(time1.hour, time1.minute, time1.second));
    exit_if_fail(__is_valid_time(time2.hour, time2.minute, time2.second));

    if (time1.hour > time2.hour) {
        return 1;
    } else if (time1.hour < time2.hour) {
        return -1;
    }

    if (time1.minute > time2.minute) {
        return 1;
    } else if (time1.minute < time2.minute) {
        return -1;
    }

    if (time1.second > time2.second) {
        return 1;
    } else if (time1.second < time2.second) {
        return -1;
    }

    return 0;
}

/**
 * @brief Add seconds to the time.
 * @param time The Time object.
 * @param seconds The number of seconds to add/subtract.
 * @return Returns the new Time object.
 */
Time time_add(Time time, int seconds) {
    struct tm tm_time = {0};
    exit_if_fail(__is_valid_time(time.hour, time.minute, time.second));

    tm_time.tm_hour = time.hour;
    tm_time.tm_min = time.minute;
    tm_time.tm_sec = time.second + seconds;

    mktime(&tm_time);
    return time_create(tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
}

/**
 * @brief Get the difference between two Time objects.
 * @param time1 The first Time object.
 * @param time2 The second Time object.
 * @return Returns the difference between two Time objects.
 */
int time_diff(Time time1, Time time2) {
    struct tm tm_time1 = {0};
    struct tm tm_time2 = {0};
    time_t time_seconds1;
    time_t time_seconds2;
    double diff_seconds = 0;

    exit_if_fail(__is_valid_time(time1.hour, time1.minute, time1.second));
    exit_if_fail(__is_valid_time(time2.hour, time2.minute, time2.second));

    tm_time1.tm_hour = time1.hour;
    tm_time1.tm_min = time1.minute;
    tm_time1.tm_sec = time1.second;
    tm_time2.tm_hour = time2.hour;
    tm_time2.tm_min = time2.minute;
    tm_time2.tm_sec = time2.second;

    time_seconds1 = mktime(&tm_time1);
    time_seconds2 = mktime(&tm_time2);
    diff_seconds = difftime(time_seconds1, time_seconds2);
    return (int)diff_seconds;
}
