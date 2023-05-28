#include "datetime.h"
#include "time.h"

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

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

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
        return 0;
    }
}

int days_in_year(int year) {
    return is_leap_year(year) ? DAYS_IN_LEAP_YEAR : DAYS_IN_COMMON_YEAR;
}

int nth_day_of_year(int year, int month, int day) {
    int days = 0;
    for (int i = 1; i < month; i++) {
        days += days_in_month(year, i);
    }
    return days + day;
}

Date date_create(int year, int month, int day) {
    Date date = {year, month, day};
    return date;
}

Date date_now() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    return date_create(tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
}

int date_compare(Date date1, Date date2) {
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

Date date_add(Date date, int days) {
    struct tm tm_date = {0};
    tm_date.tm_year = date.year - 1900;
    tm_date.tm_mon = date.month - 1;
    tm_date.tm_mday = date.day + days;

    mktime(&tm_date);

    Date new_date = {tm_date.tm_year + 1900, tm_date.tm_mon + 1, tm_date.tm_mday};
    return new_date;
}

int date_diff(Date date1, Date date2) {
    struct tm tm_date1 = {0};
    tm_date1.tm_year = date1.year - 1900;
    tm_date1.tm_mon = date1.month - 1;
    tm_date1.tm_mday = date1.day;

    struct tm tm_date2 = {0};
    tm_date2.tm_year = date2.year - 1900;
    tm_date2.tm_mon = date2.month - 1;
    tm_date2.tm_mday = date2.day;

    time_t time1 = mktime(&tm_date1);
    time_t time2 = mktime(&tm_date2);

    double diff_seconds = difftime(time1, time2);
    return (int)(diff_seconds / SECONDS_PER_DAY);
}

Time time_create(int hour, int minute, int second, int millisecond) {
    Time time = {hour, minute, second, millisecond};
    return time;
}

Time time_now() {
    Time time;

#ifdef _WIN32
    SYSTEMTIME st;
    GetLocalTime(&st);
    time = (Time){st.wHour, st.wMinute, st.wSecond, st.wMilliseconds};
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm *tm = localtime(&tv.tv_sec);
    time = (Time){tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec / MICROSECONDS_PER_MILLISECOND};
#endif

    return time;
}

int time_compare(Time time1, Time time2) {
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

Time time_add(Time time, int milliseconds) {
    int total_milliseconds = time.millisecond + milliseconds;

    int total_seconds = time.second + total_milliseconds / MILLISECONDS_PER_SECOND;
    time.millisecond = total_milliseconds % MILLISECONDS_PER_SECOND;

    int total_minutes = time.minute + total_seconds / SECONDS_PER_MINUTE;
    time.second = total_seconds % SECONDS_PER_MINUTE;

    int total_hours = time.hour + total_minutes / MINUTES_PER_HOUR;
    time.minute = total_minutes % MINUTES_PER_HOUR;

    time.hour = total_hours % HOURS_PER_DAY;

    return time;
}

int time_diff(Time time1, Time time2) {
    int total_ms1 = (time1.hour * SECONDS_PER_HOUR + time1.minute * SECONDS_PER_MINUTE + time1.second) * MILLISECONDS_PER_SECOND + time1.millisecond;
    int total_ms2 = (time2.hour * SECONDS_PER_HOUR + time2.minute * SECONDS_PER_MINUTE + time2.second) * MILLISECONDS_PER_SECOND + time2.millisecond;
    return total_ms1 - total_ms2;
}
