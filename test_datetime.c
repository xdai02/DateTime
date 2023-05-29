#include <stdio.h>
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
}

int main() {
    test_is_leap_year();
    test_days_in_month();
    test_days_in_year();
    test_nth_day_of_year();

    return 0;
}
