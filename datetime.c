#include "datetime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
 * @brief Get the the days between two Date objects.
 * @param date1 The first Date object.
 * @param date2 The second Date object.
 * @return Returns the days between two Date objects.
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
 * @brief Get the string representation (yyyy/mm/dd) of the date.
 * @param date The Date object.
 * @return Returns the string representation of the date.
 * @note The caller must free the returned string.
 */
char *date_to_string(Date date) {
    char *date_string = NULL;
    exit_if_fail(__is_valid_date(date.year, date.month, date.day));

    date_string = (char *)malloc(sizeof(char) * 11);
    return_value_if_fail(date_string != NULL, NULL);

    sprintf(date_string, "%04d/%02d/%02d", date.year, date.month, date.day);
    return date_string;
}

/**
 * @brief Determine whether the time is valid.
 * @param hour The hour.
 * @param minute The minute.
 * @param second The second.
 * @param millisecond The millisecond.
 * @return Returns true if the time is valid, otherwise returns false.
 */
static bool __is_valid_time(int hour, int minute, int second, int millisecond) {
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

    if (millisecond < 0 || millisecond >= MILLISECONDS_PER_SECOND) {
        fprintf(stderr, "Error: millisecond must be 0 ~ 999.\n");
        return false;
    }

    return true;
}

/**
 * @brief Create a Time object.
 * @param hour The hour.
 * @param minute The minute.
 * @param second The second.
 * @param millisecond The millisecond.
 * @return Returns the Time object.
 */
Time time_create(int hour, int minute, int second, int millisecond) {
    Time time;
    exit_if_fail(__is_valid_time(hour, minute, second, millisecond));
    time.hour = hour;
    time.minute = minute;
    time.second = second;
    time.millisecond = millisecond;
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
    time = time_create(st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec);
    time = time_create(tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec / MILLISECONDS_PER_SECOND);
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
    exit_if_fail(__is_valid_time(time1.hour, time1.minute, time1.second, time1.millisecond));
    exit_if_fail(__is_valid_time(time2.hour, time2.minute, time2.second, time2.millisecond));

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

    if (time1.millisecond > time2.millisecond) {
        return 1;
    } else if (time1.millisecond < time2.millisecond) {
        return -1;
    }

    return 0;
}

/**
 * @brief Add seconds to the time.
 * @param time The Time object.
 * @param milliseconds The number of milliseconds to add/subtract.
 * @return Returns the new Time object.
 */
Time time_add(Time time, int milliseconds) {
    int total_milliseconds = 0;
    exit_if_fail(__is_valid_time(time.hour, time.minute, time.second, time.millisecond));

    total_milliseconds = time.millisecond + milliseconds;

    if (total_milliseconds < 0) {
        time.second += total_milliseconds / MILLISECONDS_PER_SECOND - 1;
        time.millisecond = total_milliseconds % MILLISECONDS_PER_SECOND + MILLISECONDS_PER_SECOND;
    } else {
        time.second += total_milliseconds / MILLISECONDS_PER_SECOND;
        time.millisecond = total_milliseconds % MILLISECONDS_PER_SECOND;
    }

    if (time.second < 0) {
        time.minute += time.second / SECONDS_PER_MINUTE - 1;
        time.second = time.second % SECONDS_PER_MINUTE + SECONDS_PER_MINUTE;
    } else {
        time.minute += time.second / SECONDS_PER_MINUTE;
        time.second = time.second % SECONDS_PER_MINUTE;
    }

    if (time.minute < 0) {
        time.hour += time.minute / MINUTES_PER_HOUR - 1;
        time.minute = time.minute % MINUTES_PER_HOUR + MINUTES_PER_HOUR;
    } else {
        time.hour += time.minute / MINUTES_PER_HOUR;
        time.minute = time.minute % MINUTES_PER_HOUR;
    }

    time.hour = (time.hour + HOURS_PER_DAY) % HOURS_PER_DAY;
    return time;
}

/**
 * @brief Get the difference between two Time objects.
 * @param time1 The first Time object.
 * @param time2 The second Time object.
 * @return Returns the difference between two Time objects.
 */
int time_diff(Time time1, Time time2) {
    int milliseconds1;
    int milliseconds2;

    exit_if_fail(__is_valid_time(time1.hour, time1.minute, time1.second, time1.millisecond));
    exit_if_fail(__is_valid_time(time2.hour, time2.minute, time2.second, time2.millisecond));

    milliseconds1 = (time1.hour * MINUTES_PER_HOUR * SECONDS_PER_MINUTE + time1.minute * SECONDS_PER_MINUTE + time1.second) * MILLISECONDS_PER_SECOND + time1.millisecond;
    milliseconds2 = (time2.hour * MINUTES_PER_HOUR * SECONDS_PER_MINUTE + time2.minute * SECONDS_PER_MINUTE + time2.second) * MILLISECONDS_PER_SECOND + time2.millisecond;
    return milliseconds1 - milliseconds2;
}

/**
 * @brief Get the string representation (hh:mm:ss.fff) of the time.
 * @param time The Time object.
 * @return Returns the string representation of the time.
 * @note The caller must free the returned string.
 */
char *time_to_string(Time time) {
    char *time_string = NULL;
    exit_if_fail(__is_valid_time(time.hour, time.minute, time.second, time.millisecond));

    time_string = (char *)malloc(sizeof(char) * 13);
    return_value_if_fail(time_string != NULL, NULL);

    sprintf(time_string, "%02d:%02d:%02d.%03d", time.hour, time.minute, time.second, time.millisecond);
    return time_string;
}

/**
 * @brief Determine whether the datetime is valid.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @param hour The hour.
 * @param minute The minute.
 * @param second The second.
 * @param millisecond The millisecond.
 * @return Returns true if the datetime is valid, otherwise returns false.
 */
static bool __is_valid_datetime(int year, int month, int day, int hour, int minute, int second, int millisecond) {
    return __is_valid_date(year, month, day) && __is_valid_time(hour, minute, second, millisecond);
}

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
DateTime datetime_create(int year, int month, int day, int hour, int minute, int second, int millisecond) {
    DateTime datetime;
    exit_if_fail(__is_valid_datetime(year, month, day, hour, minute, second, millisecond));
    datetime.date = date_create(year, month, day);
    datetime.time = time_create(hour, minute, second, millisecond);
    return datetime;
}

/**
 * @brief Get the current datetime.
 * @return Returns the DateTime object.
 */
DateTime datetime_now() {
    DateTime datetime;
    datetime.date = date_now();
    datetime.time = time_now();
    return datetime;
}

/**
 * @brief Compare two DateTime objects.
 * @param datetime1 The first DateTime object.
 * @param datetime2 The second DateTime object.
 * @return Returns 1 if datetime1 is greater than datetime2.
 *         Returns -1 if datetime1 is less than datetime2.
 *         Returns 0 if datetime1 is equal to datetime2.
 */
int datetime_compare(DateTime datetime1, DateTime datetime2) {
    exit_if_fail(__is_valid_datetime(datetime1.date.year, datetime1.date.month, datetime1.date.day, datetime1.time.hour, datetime1.time.minute, datetime1.time.second, datetime1.time.millisecond));
    exit_if_fail(__is_valid_datetime(datetime2.date.year, datetime2.date.month, datetime2.date.day, datetime2.time.hour, datetime2.time.minute, datetime2.time.second, datetime2.time.millisecond));

    if (date_compare(datetime1.date, datetime2.date) > 0) {
        return 1;
    } else if (date_compare(datetime1.date, datetime2.date) < 0) {
        return -1;
    }

    if (time_compare(datetime1.time, datetime2.time) > 0) {
        return 1;
    } else if (time_compare(datetime1.time, datetime2.time) < 0) {
        return -1;
    }

    return 0;
}

#if 0
DateTime datetime_add(DateTime datetime, int milliseconds) {
}

int datetime_diff(DateTime datetime1, DateTime datetime2) {
}
#endif

/**
 * @brief Get the string representation (yyyy/mm/dd hh:mm:ss.fff) of the datetime.
 * @param datetime The DateTime object.
 * @return Returns the string representation of the datetime.
 * @note The caller must free the returned string.
 */
char *datetime_to_string(DateTime datetime) {
    char *datetime_str = NULL;
    char *date_str = NULL;
    char *time_str = NULL;
    exit_if_fail(__is_valid_datetime(datetime.date.year, datetime.date.month, datetime.date.day, datetime.time.hour, datetime.time.minute, datetime.time.second, datetime.time.millisecond));

    date_str = date_to_string(datetime.date);
    time_str = time_to_string(datetime.time);
    datetime_str = (char *)malloc(sizeof(char) * (strlen(date_str) + strlen(time_str) + 1));
    if (datetime_str == NULL) {
        free(date_str);
        free(time_str);
        return NULL;
    }

    sprintf(datetime_str, "%s %s", date_str, time_str);
    free(date_str);
    free(time_str);
    return datetime_str;
}
