#include "datetime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * @brief Get the full name of the month.
 * @param month The month.
 * @return Returns the full name of the month.
 */
const char *month_name(Month month) {
    switch (month) {
    case JAN:
        return "January";
    case FEB:
        return "February";
    case MAR:
        return "March";
    case APR:
        return "April";
    case MAY:
        return "May";
    case JUN:
        return "June";
    case JUL:
        return "July";
    case AUG:
        return "August";
    case SEP:
        return "September";
    case OCT:
        return "October";
    case NOV:
        return "November";
    case DEC:
        return "December";
    default:
        fprintf(stderr, "Error: month must be 1 ~ 12.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Get the full name of the weekday.
 * @param weekday The weekday.
 * @return Returns the full name of the weekday.
 */
const char *weekday_full_name(Weekday weekday) {
    switch (weekday) {
    case SUN:
        return "Sunday";
    case MON:
        return "Monday";
    case TUE:
        return "Tuesday";
    case WED:
        return "Wednesday";
    case THU:
        return "Thursday";
    case FRI:
        return "Friday";
    case SAT:
        return "Saturday";
    default:
        fprintf(stderr, "Error: day must be 0 ~ 6.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Get the abbreviated name of the weekday.
 * @param weekday The weekday.
 * @return Returns the abbreviated name of the weekday.
 */
const char *weekday_abbr_name(Weekday weekday) {
    switch (weekday) {
    case SUN:
        return "Sun";
    case MON:
        return "Mon";
    case TUE:
        return "Tue";
    case WED:
        return "Wed";
    case THU:
        return "Thu";
    case FRI:
        return "Fri";
    case SAT:
        return "Sat";
    default:
        fprintf(stderr, "Error: day must be 0 ~ 6.\n");
        exit(EXIT_FAILURE);
    }
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
 * @param date The Date object.
 * @return Returns true if the date is valid, otherwise returns false.
 */
static bool __is_valid_date(Date date) {
    if (date.year < MIN_YEAR || date.year > MAX_YEAR) {
        fprintf(stderr, "Error: year must be %d ~ %d.\n", MIN_YEAR, MAX_YEAR);
        return false;
    }

    if (date.month < JAN || date.month > DEC) {
        fprintf(stderr, "Error: month must be 1 ~ 12.\n");
        return false;
    }

    if (date.day < 1 || date.day > days_in_month(date.year, date.month)) {
        fprintf(stderr, "Error: only %d days in %s %d.\n", days_in_month(date.year, date.month), month_name(date.month), date.year);
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
    Date date;
    int i = 0;
    int days = 0;

    date.year = year;
    date.month = month;
    date.day = day;
    exit_if_fail(__is_valid_date(date));

    for (i = 1; i < month; i++) {
        days += days_in_month(year, i);
    }
    return days + day;
}

/**
 * @brief Determine the day of the week.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @return Returns the day of the week.
 */
Weekday weekday(int year, int month, int day) {
    Date date;
    int h;

    date.year = year;
    date.month = month;
    date.day = day;
    exit_if_fail(__is_valid_date(date));

    if (month < 3) {
        month += 12;
        year--;
    }
    h = (day + (26 * (month + 1)) / 10 + year + year / 4 - year / 100 + year / 400) % DAYS_IN_WEEK;
    h = (h + 6) % DAYS_IN_WEEK;
    return (Weekday)h;
}

/**
 * @brief Get the string representation of the calendar for the given month.
 * @param year The year.
 * @param month The month.
 * @return Returns the string representation of the calendar for the given month.
 * @note The caller must free the returned string.
 */
char *calendar(int year, int month) {
    char *calendar = NULL;
    int days = 0;
    Weekday first_day;
    int k = 0;
    int i = 0;
    char buf[32];

    calendar = (char *)malloc(sizeof(char) * 256);
    return_value_if_fail(calendar != NULL, NULL);

    sprintf(calendar, "            %s %04d\n", month_name(month), year);
    days = days_in_month(year, month);
    first_day = weekday(year, month, 1);
    strcat(calendar, " Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    for (k = 0; k < first_day; k++) {
        strcat(calendar, "     ");
    }

    for (i = 1; i <= days; i++) {
        sprintf(buf, "%4d ", i);
        strcat(calendar, buf);
        k++;
        if (k >= DAYS_IN_WEEK) {
            k = 0;
            strcat(calendar, "\n");
        }
    }

    if (k != 0) {
        strcat(calendar, "\n");
    }

    return calendar;
}

/**
 * @brief Determine whether the time interval is valid.
 * @param time_interval The TimeInterval object.
 * @return Returns true if the time interval is valid, otherwise returns false.
 */
static bool __is_valid_time_interval(TimeInterval time_interval) {
    if (time_interval.days < 0) {
        fprintf(stderr, "Error: days must be greater than or equal to 0.\n");
        return false;
    }

    if (time_interval.hours < 0 || time_interval.hours >= HOURS_PER_DAY) {
        fprintf(stderr, "Error: hours must be 0 ~ 23.\n");
        return false;
    }

    if (time_interval.minutes < 0 || time_interval.minutes >= MINUTES_PER_HOUR) {
        fprintf(stderr, "Error: minutes must be 0 ~ 59.\n");
        return false;
    }

    if (time_interval.seconds < 0 || time_interval.seconds >= SECONDS_PER_MINUTE) {
        fprintf(stderr, "Error: seconds must be 0 ~ 59.\n");
        return false;
    }

    if (time_interval.milliseconds < 0 || time_interval.milliseconds >= MILLISECONDS_PER_SECOND) {
        fprintf(stderr, "Error: milliseconds must be 0 ~ 999.\n");
        return false;
    }

    return true;
}

/**
 * @brief Normalize the time interval.
 * @param time_interval The TimeInterval object.
 */
static void __time_interval_normalize(TimeInterval *time_interval) {
    return_if_fail(time_interval != NULL);

    if (time_interval->milliseconds >= MILLISECONDS_PER_SECOND) {
        time_interval->seconds += time_interval->milliseconds / MILLISECONDS_PER_SECOND;
        time_interval->milliseconds %= MILLISECONDS_PER_SECOND;
    }

    if (time_interval->seconds >= SECONDS_PER_MINUTE) {
        time_interval->minutes += time_interval->seconds / SECONDS_PER_MINUTE;
        time_interval->seconds %= SECONDS_PER_MINUTE;
    }

    if (time_interval->minutes >= MINUTES_PER_HOUR) {
        time_interval->hours += time_interval->minutes / MINUTES_PER_HOUR;
        time_interval->minutes %= MINUTES_PER_HOUR;
    }

    if (time_interval->hours >= HOURS_PER_DAY) {
        time_interval->days += time_interval->hours / HOURS_PER_DAY;
        time_interval->hours %= HOURS_PER_DAY;
    }
}

/**
 * @brief Create a TimeInterval object.
 * @param days The days.
 * @param hours The hours.
 * @param minutes The minutes.
 * @param seconds The seconds.
 * @param milliseconds The milliseconds.
 * @return Returns the TimeInterval object.
 */
TimeInterval time_interval_create(int days, int hours, int minutes, int seconds, int milliseconds) {
    TimeInterval time_interval;
    time_interval.days = days;
    time_interval.hours = hours;
    time_interval.minutes = minutes;
    time_interval.seconds = seconds;
    time_interval.milliseconds = milliseconds;
    __time_interval_normalize(&time_interval);
    exit_if_fail(__is_valid_time_interval(time_interval));
    return time_interval;
}

/**
 * @brief Get the string representation of the time interval.
 * @param time_interval The TimeInterval object.
 * @return Returns the string representation of the time interval.
 * @note The caller must free the returned string.
 */
char *time_interval_to_string(TimeInterval time_interval) {
    char *time_interval_string = NULL;
    return_value_if_fail(__is_valid_time_interval(time_interval), NULL);

    time_interval_string = (char *)malloc(sizeof(char) * 128);
    return_value_if_fail(time_interval_string != NULL, NULL);

    sprintf(time_interval_string, "%d day(s) %d hour(s) %d minute(s) %d second(s) %d millisecond(s)", time_interval.days, time_interval.hours, time_interval.minutes, time_interval.seconds, time_interval.milliseconds);
    return time_interval_string;
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
    date.year = year;
    date.month = month;
    date.day = day;
    exit_if_fail(__is_valid_date(date));
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
    exit_if_fail(__is_valid_date(date1) && __is_valid_date(date2));

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
    exit_if_fail(__is_valid_date(date));

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

    exit_if_fail(__is_valid_date(date1) && __is_valid_date(date2));

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
 * @brief Get the string representation (yyyy-mm-dd) of the date.
 * @param date The Date object.
 * @return Returns the string representation of the date.
 * @note The caller must free the returned string.
 */
char *date_to_string(Date date) {
    char *date_string = NULL;
    return_value_if_fail(__is_valid_date(date), NULL);

    date_string = (char *)malloc(sizeof(char) * 11);
    return_value_if_fail(date_string != NULL, NULL);

    sprintf(date_string, "%04d-%02d-%02d", date.year, date.month, date.day);
    return date_string;
}

/**
 * @brief Get the string representation (Day Mon dd yyyy) of the date.
 * @param date The Date object.
 * @return Returns the string representation of the date.
 * @note The caller must free the returned string.
 */
char *date_ascii_string(Date date) {
    char *date_string = NULL;
    struct tm tm = {0};
    char weekday_abbr[4] = {0};
    return_value_if_fail(__is_valid_date(date), NULL);

    tm.tm_year = date.year - 1900;
    tm.tm_mon = date.month - 1;
    tm.tm_mday = date.day;

    date_string = (char *)calloc(16, sizeof(char));
    return_value_if_fail(date_string != NULL, NULL);

    strcpy(weekday_abbr, weekday_abbr_name(weekday(date.year, date.month, date.day)));
    strftime(date_string, 13, " %b %d %Y", &tm);
    memmove(date_string + 3, date_string, 12);
    memcpy(date_string, weekday_abbr, 3);
    return date_string;
}

/**
 * @brief Determine whether the time is valid.
 * @param time The Time object.
 * @return Returns true if the time is valid, otherwise returns false.
 */
static bool __is_valid_time(Time time) {
    if (time.hour < 0 || time.hour >= HOURS_PER_DAY) {
        fprintf(stderr, "Error: hour must be 0 ~ 23.\n");
        return false;
    }

    if (time.minute < 0 || time.minute >= MINUTES_PER_HOUR) {
        fprintf(stderr, "Error: minute must be 0 ~ 59.\n");
        return false;
    }

    if (time.second < 0 || time.second >= SECONDS_PER_MINUTE) {
        fprintf(stderr, "Error: second must be 0 ~ 59.\n");
        return false;
    }

    if (time.millisecond < 0 || time.millisecond >= MILLISECONDS_PER_SECOND) {
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
    time.hour = hour;
    time.minute = minute;
    time.second = second;
    time.millisecond = millisecond;
    exit_if_fail(__is_valid_time(time));
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
    exit_if_fail(__is_valid_time(time1) && __is_valid_time(time2));

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
    exit_if_fail(__is_valid_time(time));

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
 * @brief Get the milliseconds between two Time objects.
 * @param time1 The first Time object.
 * @param time2 The second Time object.
 * @return Returns the milliseconds between two Time objects.
 */
int time_diff(Time time1, Time time2) {
    int milliseconds1;
    int milliseconds2;
    exit_if_fail(__is_valid_time(time1) && __is_valid_time(time2));

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
    return_value_if_fail(__is_valid_time(time), NULL);

    time_string = (char *)malloc(sizeof(char) * 13);
    return_value_if_fail(time_string != NULL, NULL);

    sprintf(time_string, "%02d:%02d:%02d.%03d", time.hour, time.minute, time.second, time.millisecond);
    return time_string;
}

/**
 * @brief Get the string representation (hh:mm:ss) of the time.
 * @param time The Time object.
 * @return Returns the string representation of the time.
 * @note The caller must free the returned string.
 */
char *time_ascii_string(Time time) {
    char *time_string = NULL;
    struct tm tm = {0};
    return_value_if_fail(__is_valid_time(time), NULL);

    tm.tm_hour = time.hour;
    tm.tm_min = time.minute;
    tm.tm_sec = time.second;

    time_string = (char *)calloc(9, sizeof(char));
    return_value_if_fail(time_string != NULL, NULL);

    strftime(time_string, 9, "%H:%M:%S", &tm);
    return time_string;
}

/**
 * @brief Determine whether the datetime is valid.
 * @param datetime The DateTime object.
 * @return Returns true if the datetime is valid, otherwise returns false.
 */
static bool __is_valid_datetime(DateTime datetime) {
    return __is_valid_date(datetime.date) && __is_valid_time(datetime.time);
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
    datetime.date = date_create(year, month, day);
    datetime.time = time_create(hour, minute, second, millisecond);
    exit_if_fail(__is_valid_datetime(datetime));
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
 * @brief Create a DateTime object from the Unix timestamp (since 1970-01-01 00:00:00 UTC).
 * @param timestamp The Unix timestamp. The range of timestamp is 0 ~ 2147483647 (2038-01-19 03:14:07 UTC).
 * @return Returns the DateTime object.
 */
DateTime datetime_from_timestamp(time_t timestamp) {
    DateTime datetime;
    struct tm *tm = NULL;

    const time_t MAX_TIMESTAMP = 2147483647;
    if (timestamp > MAX_TIMESTAMP) {
        fprintf(stderr, "Error: timestamp must be less than or equal to %ld.\n", (long)MAX_TIMESTAMP);
        exit(EXIT_FAILURE);
    }

    tm = gmtime(&timestamp);
    datetime.date = date_create(tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    datetime.time = time_create(tm->tm_hour, tm->tm_min, tm->tm_sec, 0);
    return datetime;
}

/**
 * @brief Convert the DateTime object to the Unix timestamp (since 1970-01-01 00:00:00 UTC).
 * @param datetime The DateTime object.
 * @return Returns the Unix timestamp.
 */
time_t datetime_to_timestamp(DateTime datetime) {
    const int SECONDS_PER_COMMON_YEAR = DAYS_IN_COMMON_YEAR * SECONDS_PER_DAY;
    const int SECONDS_PER_LEAP_YEAR = DAYS_IN_LEAP_YEAR * SECONDS_PER_DAY;

    int years_passed = 0;
    int leap_years_passed = 0;
    int non_leap_years_passed = 0;
    time_t seconds_passed = 0;
    int days_passed_current_year = 0;
    int year;

    exit_if_fail(__is_valid_datetime(datetime));

    years_passed = datetime.date.year - 1970;

    for (year = 1970; year < datetime.date.year; year++) {
        if (is_leap_year(year)) {
            leap_years_passed++;
        }
    }
    non_leap_years_passed = years_passed - leap_years_passed;

    seconds_passed = ((time_t)non_leap_years_passed * SECONDS_PER_COMMON_YEAR) + ((time_t)leap_years_passed * SECONDS_PER_LEAP_YEAR);

    days_passed_current_year = nth_day_of_year(datetime.date.year, datetime.date.month, datetime.date.day) - 1;
    seconds_passed += ((time_t)days_passed_current_year * SECONDS_PER_DAY) + (datetime.time.hour * SECONDS_PER_HOUR) + (datetime.time.minute * SECONDS_PER_MINUTE) + datetime.time.second;

    return seconds_passed;
}

/**
 * @brief Create a DateTime object from the ordinal (since 0001-01-01 00:00:00).
 * @param ordinal The ordinal.
 * @return Returns the DateTime object.
 */
DateTime datetime_from_ordinal(int ordinal) {
    DateTime datetime;
    int year = 1;
    int month = JAN;
    int days = 0;

    if (ordinal <= 0) {
        fprintf(stderr, "Error: ordinal must be greater than 0.\n");
        exit(EXIT_FAILURE);
    }

    while (ordinal > 0) {
        days = days_in_year(year);

        if (ordinal >= days) {
            ordinal -= days;
            year++;
        } else {
            for (month = JAN; month <= DEC; month++) {
                days = days_in_month(year, month);
                if (ordinal >= days) {
                    ordinal -= days;
                } else {
                    break;
                }
            }
            break;
        }
    }

    datetime.date = date_create(year, month, ordinal);
    datetime.time = time_create(0, 0, 0, 0);
    return datetime;
}

/**
 * @brief Convert the DateTime object to the ordinal (since 0001-01-01 00:00:00).
 * @param datetime The DateTime object.
 * @return Returns the ordinal.
 */
int datetime_to_ordinal(DateTime datetime) {
    int ordinal = 0;
    int year;
    int month;
    exit_if_fail(__is_valid_datetime(datetime));

    for (year = 1; year < datetime.date.year; year++) {
        ordinal += days_in_year(year);
    }

    for (month = JAN; month < datetime.date.month; month++) {
        ordinal += days_in_month(datetime.date.year, month);
    }

    ordinal += datetime.date.day;
    return ordinal;
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
    exit_if_fail(__is_valid_datetime(datetime1) && __is_valid_datetime(datetime2));

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

/**
 * @brief Add days and milliseconds to the datetime.
 * @param datetime The DateTime object.
 * @param days The number of days to add/subtract.
 * @param milliseconds The number of milliseconds to add/subtract.
 * @return DateTime The new DateTime object.
 */
DateTime datetime_add(DateTime datetime, int days, int milliseconds) {
    TimeInterval time_interval;
    exit_if_fail(__is_valid_datetime(datetime));

    datetime.date = date_add(datetime.date, days);

    if (milliseconds >= 0) {
        time_interval = time_interval_create(0, 0, 0, 0, milliseconds);
        datetime.date = date_add(datetime.date, time_interval.days);

        datetime.time.millisecond += time_interval.milliseconds;
        if (datetime.time.millisecond >= MILLISECONDS_PER_SECOND) {
            datetime.time.second++;
            datetime.time.millisecond %= MILLISECONDS_PER_SECOND;
        }

        datetime.time.second += time_interval.seconds;
        if (datetime.time.second >= SECONDS_PER_MINUTE) {
            datetime.time.minute++;
            datetime.time.second %= SECONDS_PER_MINUTE;
        }

        datetime.time.minute += time_interval.minutes;
        if (datetime.time.minute >= MINUTES_PER_HOUR) {
            datetime.time.hour++;
            datetime.time.minute %= MINUTES_PER_HOUR;
        }

        datetime.time.hour += time_interval.hours;
        if (datetime.time.hour >= HOURS_PER_DAY) {
            datetime.date = date_add(datetime.date, 1);
            datetime.time.hour %= HOURS_PER_DAY;
        }
    } else {
        time_interval = time_interval_create(0, 0, 0, 0, -milliseconds);
        datetime.date = date_add(datetime.date, -time_interval.days);

        datetime.time.millisecond -= time_interval.milliseconds;
        if (datetime.time.millisecond < 0) {
            datetime.time.second--;
            datetime.time.millisecond += MILLISECONDS_PER_SECOND;
        }

        datetime.time.second -= time_interval.seconds;
        if (datetime.time.second < 0) {
            datetime.time.minute--;
            datetime.time.second += SECONDS_PER_MINUTE;
        }

        datetime.time.minute -= time_interval.minutes;
        if (datetime.time.minute < 0) {
            datetime.time.hour--;
            datetime.time.minute += MINUTES_PER_HOUR;
        }

        datetime.time.hour -= time_interval.hours;
        if (datetime.time.hour < 0) {
            datetime.date = date_add(datetime.date, -1);
            datetime.time.hour += HOURS_PER_DAY;
        }
    }

    return datetime;
}

/**
 * @brief Get the difference between two DateTime objects.
 * @param datetime1 The first DateTime object.
 * @param datetime2 The second DateTime object.
 * @return TimeInterval The difference between two DateTime objects.
 */
TimeInterval datetime_diff(DateTime datetime1, DateTime datetime2) {
    TimeInterval time_interval;
    DateTime temp;
    int days_diff = 0;
    int milliseconds_diff = 0;

    exit_if_fail(__is_valid_datetime(datetime1) && __is_valid_datetime(datetime2));

    if (datetime_compare(datetime1, datetime2) < 0) {
        temp = datetime1;
        datetime1 = datetime2;
        datetime2 = temp;
    }

    days_diff = date_diff(datetime1.date, datetime2.date);
    milliseconds_diff = time_diff(datetime1.time, datetime2.time);

    if (milliseconds_diff < 0) {
        days_diff--;
        milliseconds_diff += MILLISECONDS_PER_DAY;
    }

    time_interval = time_interval_create(days_diff, 0, 0, 0, milliseconds_diff);
    return time_interval;
}

/**
 * @brief Get the string representation (yyyy-mm-dd hh:mm:ss.fff) of the datetime.
 * @param datetime The DateTime object.
 * @return Returns the string representation of the datetime.
 * @note The caller must free the returned string.
 */
char *datetime_to_string(DateTime datetime) {
    char *datetime_str = NULL;
    char *date_str = NULL;
    char *time_str = NULL;
    return_value_if_fail(__is_valid_datetime(datetime), NULL);

    date_str = date_to_string(datetime.date);
    time_str = time_to_string(datetime.time);
    datetime_str = (char *)malloc(sizeof(char) * (strlen(date_str) + strlen(time_str) + 2));
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

/**
 * @brief Get the string representation (Day Mon dd hh:mm:ss yyyy) of the datetime.
 * @param datetime DateTime Time object.
 * @return Returns the string representation of the datetime.
 * @note The caller must free the returned string.
 */
char *datetime_ascii_string(DateTime datetime) {
    char *datetime_string = NULL;
    struct tm tm = {0};
    char weekday_abbr[4] = {0};
    return_value_if_fail(__is_valid_datetime(datetime), NULL);

    tm.tm_year = datetime.date.year - 1900;
    tm.tm_mon = datetime.date.month - 1;
    tm.tm_mday = datetime.date.day;
    tm.tm_hour = datetime.time.hour;
    tm.tm_min = datetime.time.minute;
    tm.tm_sec = datetime.time.second;

    datetime_string = (char *)calloc(25, sizeof(char));
    return_value_if_fail(datetime_string != NULL, NULL);

    strcpy(weekday_abbr, weekday_abbr_name(weekday(datetime.date.year, datetime.date.month, datetime.date.day)));
    strftime(datetime_string, 22, " %b %d %H:%M:%S %Y", &tm);
    memmove(datetime_string + 3, datetime_string, 21);
    memcpy(datetime_string, weekday_abbr, 3);
    return datetime_string;
}

/**
 * @brief Replaces all occurrences of the specified substring in the string with the specified new substring.
 * @param str The string to be replaced.
 * @param old_str The replaced substring.
 * @param new_str The new substring.
 * @return The string after replacing.
 */
static char *str_replace_string(char *str, const char *old_str, const char *new_str) {
    size_t old_str_len;
    size_t new_str_len;
    char *p = NULL;

    return_value_if_fail(str != NULL && old_str != NULL && new_str != NULL, str);

    old_str_len = strlen(old_str);
    new_str_len = strlen(new_str);
    return_value_if_fail(old_str_len > 0, str);

    p = str;
    while ((p = strstr(p, old_str))) {
        memmove(p + new_str_len, p + old_str_len, strlen(p + old_str_len) + 1);
        memcpy(p, new_str, new_str_len);
        p += new_str_len;
    }

    return str;
}

/**
 * @brief Adjust the weekday generated by the ctime()/strftime() in C library.
 * @param str The string to be adjusted.
 * @param year The year.
 * @param month The month.
 * @param day The day.
 * @return Returns the string after adjusting.
 */
static char *__adjust_weekday(char *str, int year, int month, int day) {
    char weekday_abbr[4] = {0};
    char weekday_full[10] = {0};

    return_value_if_fail(str != NULL, NULL);
    return_value_if_fail(__is_valid_date(date_create(year, month, day)), str);

    strcpy(weekday_abbr, weekday_abbr_name(weekday(year, month, day)));
    strcpy(weekday_full, weekday_full_name(weekday(year, month, day)));

    str_replace_string(str, "Sunday", weekday_full);
    str_replace_string(str, "Monday", weekday_full);
    str_replace_string(str, "Tuesday", weekday_full);
    str_replace_string(str, "Wednesday", weekday_full);
    str_replace_string(str, "Thursday", weekday_full);
    str_replace_string(str, "Friday", weekday_full);
    str_replace_string(str, "Saturday", weekday_full);

    str_replace_string(str, "Sun", weekday_abbr);
    str_replace_string(str, "Mon", weekday_abbr);
    str_replace_string(str, "Tue", weekday_abbr);
    str_replace_string(str, "Wed", weekday_abbr);
    str_replace_string(str, "Thu", weekday_abbr);
    str_replace_string(str, "Fri", weekday_abbr);
    str_replace_string(str, "Sat", weekday_abbr);

    return str;
}

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
char *datetime_format_string(DateTime datetime, const char *format) {
    char *datetime_string = NULL;
    struct tm tm = {0};
    return_value_if_fail(__is_valid_datetime(datetime) && format != NULL, NULL);

    tm.tm_year = datetime.date.year - 1900;
    tm.tm_mon = datetime.date.month - 1;
    tm.tm_mday = datetime.date.day;
    tm.tm_hour = datetime.time.hour;
    tm.tm_min = datetime.time.minute;
    tm.tm_sec = datetime.time.second;

    datetime_string = (char *)malloc(sizeof(char) * 128);
    return_value_if_fail(datetime_string != NULL, NULL);

    strftime(datetime_string, 128, format, &tm);
    __adjust_weekday(datetime_string, datetime.date.year, datetime.date.month, datetime.date.day);
    datetime_string = (char *)realloc(datetime_string, sizeof(char) * (strlen(datetime_string) + 1));

    return datetime_string;
}
