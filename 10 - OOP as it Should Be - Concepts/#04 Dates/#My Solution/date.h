/*
  A class containing all the implementations of date manipulation functions
  (excluding periods) made in the 8th course (Algorithms & Problem Solving Level 4)

  https://programmingadvices.com/courses/1936515/lectures/44343013/comments/25945231
*/

#pragma once

#pragma warning(disable : 4996)

#include <corecrt.h>

#include <cstdio>
#include <ctime>
#include <string>
#include <vector>

#include "str.h"

class Date {
 public:
  enum DateCompare { Before = -1, Equal = 0, After = 1 };

  Date() { *this = getDateNow(); }

  Date(short days, short year) {
    year_ = year;
    *this = addDaysToDate(*this, days);
  }

  Date(short day, short month, short year) {
    if (isValid(day, month, year)) {
      day_ = day;
      month_ = month;
      year_ = year;
    }
  }

  Date(std::string date) {
    std::vector<std::string> splitted = Str::split(date, "/");
    short day = std::stoi(splitted[0]);
    short month = std::stoi(splitted[1]);
    short year = std::stoi(splitted[2]);

    if (isValid(day, month, year)) {
      day_ = day;
      month_ = month;
      year_ = year;
    }
  }

  short getDay() { return day_; }

  short getMonth() { return month_; }

  short getYear() { return year_; }

  void setDay(short day) {
    if (isValid(day, month_, year_)) day_ = day;
  }

  void setMonth(short month) {
    if (isValid(day_, month, year_)) month_ = month;
  }

  void setYear(short year) {
    if (isValid(day_, month_, year)) year_ = year;
  }

  static bool isLeapYear(short year) {
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
  }

  static bool isBusinessDay(short dayIndex) { return !isWeekend(dayIndex); }

  static bool isEndOfWeek(short dayIndex) { return dayIndex == 6; }

  static bool isWeekend(short dayIndex) {
    // Friday and Saturday
    return dayIndex == 5 || dayIndex == 6;
  }

  static bool isValid(short day, short month, short year) {
    if (year > 9999 || year < 1) return false;
    if (month > 12 || month < 1) return false;
    if (day > getMonthDays(month, year) || day < 1) return false;
    return true;
  }

  static bool isDateBeforeDate2(Date date1, Date date2) {
    if (date1.year_ < date2.year_) {
      return true;
    } else if (date1.year_ == date2.year_) {
      if (date1.month_ < date2.month_) {
        return true;
      } else if (date1.month_ == date2.month_) {
        return date1.day_ < date2.day_;
      }
    }

    return false;
  }

  static bool isDateEqualDate2(Date date1, Date date2) {
    return ((date1.day_ == date2.day_) && (date1.month_ == date2.month_) &&
            (date1.year_ == date2.year_));
  }

  static bool isDateAfterDate2(Date date1, Date date2) {
    return (!isDateBeforeDate2(date1, date2) &&
            !isDateEqualDate2(date1, date2));
  }

  static DateCompare compareDates(Date date1, Date date2) {
    if (isDateBeforeDate2(date1, date2)) {
      return DateCompare::Before;
    } else if (isDateEqualDate2(date1, date2)) {
      return DateCompare::Equal;
    } else {
      return DateCompare::After;
    }
  }

  static int datesDifference(Date date1, Date date2,
                             bool includeEndDay = false) {
    // If date1 is NOT before date2, it will return a negative number
    if (!isDateBeforeDate2(date1, date2) && !isDateEqualDate2(date1, date2))
      return -datesDifference(date2, date1, includeEndDay);

    int days = 0;

    while (true) {
      short date1DaysPassed = daysSinceYearStart(date1);
      short date1YearDays = isLeapYear(date1.year_) ? 366 : 365;
      short date1MonthDays = getMonthDays(date1.month_, date1.year_);

      if (date2.year_ > date1.year_) {
        days += (date1YearDays - date1DaysPassed) + 1;
        date1.day_ = 1;
        date1.month_ = 1;
        date1.year_++;
      } else if (date2.month_ > date1.month_) {
        days += (date1MonthDays - date1.day_) + 1;
        date1.day_ = 1;
        date1.month_++;
      } else {
        days += (date2.day_ - date1.day_);
        date1.day_ = date2.day_;
        break;
      }
    }

    return includeEndDay ? ++days : days;
  }

  static Date addDaysToDate(Date date, short days) {
    while (days != 0) {
      short daysSinceYearBegan = daysSinceYearStart(date);
      short yearDays = isLeapYear(date.year_) ? 366 : 365;
      short monthDays = getMonthDays(date.month_, date.year_);

      if (days + daysSinceYearBegan > yearDays) {
        days = days - (yearDays - daysSinceYearBegan) - 1;
        date.day_ = 1;
        date.month_ = 1;
        date.year_++;
      } else if (days + date.day_ > monthDays) {
        days = days - (monthDays - date.day_) - 1;
        date.day_ = 1;
        date.month_++;
      } else {
        date.day_ += days;
        days = 0;
      }
    }

    return date;
  }

  static Date addMonthsToDate(Date date, short months) {
    short monthsToYears = months / 12;
    if (monthsToYears > 0) {
      date = addYearsToDate(date, monthsToYears);
      months %= 12;
    }

    short monthsLeftInTheYear = 12 - date.month_;
    if (months > monthsLeftInTheYear) {
      date.year_++;
      date.month_ = months - monthsLeftInTheYear;
    } else {
      date.month_ += months;
    }

    short monthDays = getMonthDays(date.month_, date.year_);
    if (date.day_ > monthDays) date.day_ = monthDays;

    return date;
  }

  static Date addYearsToDate(Date date, short years) {
    date.year_ += years;
    if (!isLeapYear(date.year_) && date.month_ == 2 && date.day_ == 29)
      date.day_ = 28;
    return date;
  }

  static Date subDaysFromDate(Date date, short days) {
    while (days != 0) {
      short daysSinceYearBegan = daysSinceYearStart(date);

      if (days >= daysSinceYearBegan) {
        days -= daysSinceYearBegan;
        date.year_--;
        date.month_ = 12;
        date.day_ = 31;
      } else if (days >= date.day_) {
        days -= date.day_;
        date.month_--;
        date.day_ = getMonthDays(date.month_, date.year_);
      } else {
        date.day_ -= days;
        days = 0;
      }
    }

    return date;
  }

  static Date subMonthsFromDate(Date date, short months) {
    short monthsToYears = months / 12;
    if (monthsToYears > 0) {
      date = subYearsFromDate(date, monthsToYears);
      months %= 12;
    }

    if (months >= date.month_) {
      date.year_--;
      date.month_ = 12 - (months - date.month_);
    } else {
      date.month_ -= months;
    }

    short monthDays = getMonthDays(date.month_, date.year_);
    if (date.day_ > monthDays) date.day_ = monthDays;

    return date;
  }

  static Date subYearsFromDate(Date date, short years) {
    date.year_ -= years;
    if (!isLeapYear(date.year_) && date.month_ == 2 && date.day_ == 29)
      date.day_ = 28;
    return date;
  }

  static std::string dateToString(Date date) {
    return std::to_string(date.day_) + "/" + std::to_string(date.month_) + "/" +
           std::to_string(date.year_);
  }

  static Date getDateNow() {
    // Avoid default constructor to not fall into infinite recursion loop
    Date date(0, 0, 0);
    time_t t = time(0);  // get time now
    tm* now = localtime(&t);
    date.year_ = now->tm_year + 1900;
    date.month_ = now->tm_mon + 1;
    date.day_ = now->tm_mday;
    return date;
  }

  static Date getDateFromDayOrder(short days, short year) {
    short month;

    for (month = 1; month <= 12; month++) {
      short monthDays = getMonthDays(month, year);
      if (monthDays < days) {
        days -= monthDays;
        continue;
      }
      break;
    }

    return Date(days, month, year);
  }

  static short getDayIndex(Date date) {
    short a, y, m;
    a = (14 - date.month_) / 12;
    y = date.year_ - a;
    m = date.month_ + (12 * a) - 2;
    return (date.day_ + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
  }

  static short getDayIndex(short day, short month, short year) {
    short a, y, m;
    a = (14 - month) / 12;
    y = year - a;
    m = month + (12 * a) - 2;
    return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
  }

  static std::string getDayName(short dayIndex) {
    std::string daysNames[7] = {"Sun", "Mon", "Tue", "Wed",
                                "Thu", "Fri", "Sat"};
    return daysNames[dayIndex];
  }

  static short getMonthDays(short month, short year) {
    short monthsDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return month == 2 ? (isLeapYear(year) ? 29 : 28) : monthsDays[month - 1];
  }

  static std::string getMonthName(short month) {
    std::string monthsNames[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    return monthsNames[month - 1];
  }

  static short daysSinceYearStart(Date date) {
    short days = date.day_;
    for (short i = 1; i < date.month_; i++) days += getMonthDays(i, date.year_);
    return days;
  }

  static short daysUntilEndOfWeek(short dayIndex) { return 6 - dayIndex; }

  static short daysUntilEndOfMonth(Date date) {
    return getMonthDays(date.month_, date.year_) - date.day_;
  }

  static short daysUntilEndOfYear(Date date) {
    return (isLeapYear(date.year_) ? 366 : 365) - daysSinceYearStart(date);
  }

  static void monthCalendar(short month, short year) {
    short dayIndex = getDayIndex(1, month, year);
    short monthDays = getMonthDays(month, year);
    std::string monthName = getMonthName(month);

    printf("\n ______________%s________________\n\n", monthName.c_str());
    printf(" Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    for (short i = 0; i < dayIndex; i++) printf("     ");
    for (short i = 1; i <= monthDays; i++) {
      printf(" %3d ", i);
      if ((dayIndex + i) % 7 == 0) printf("\n");
    }
    printf("\n _________________________________\n");
  }

  static void yearCalendar(short year) {
    printf("\n _________________________________\n\n");
    printf("%18s - %d\n", "Calendar", year);
    printf(" _________________________________\n");

    for (short month = 1; month <= 12; month++) monthCalendar(month, year);
  }

  static short calculateVacationDays(Date vacationStart, Date vacationEnd) {
    short vacationPeriod = datesDifference(vacationStart, vacationEnd);
    short dayIndex = getDayIndex(vacationStart);
    short actualVacationDays = 0;

    for (; vacationPeriod > 0; vacationPeriod--) {
      if (isBusinessDay(dayIndex)) actualVacationDays++;
      if (++dayIndex > 6) dayIndex = 0;
    }

    return actualVacationDays;
  }

  static Date calculateVacationEnd(Date vacationStart, short vacationDays) {
    short dayIndex = getDayIndex(vacationStart);
    short vacationPeriod = vacationDays;

    for (short i = 1; i <= vacationPeriod; i++) {
      if (isWeekend(dayIndex)) vacationPeriod++;
      if (++dayIndex > 6) dayIndex = 0;
    }

    return addDaysToDate(vacationStart, vacationPeriod);
  }

  static int calculateAgeInDays(Date date) {
    Date dateNow = getDateNow();
    return datesDifference(date, dateNow);
  }

  // Object-specific methods:

  bool isLeapYear() { return isLeapYear(year_); }

  bool isBusinessDay() { return isBusinessDay(this->getDayIndex()); }

  bool isEndOfWeek() { return isEndOfWeek(this->getDayIndex()); }

  bool isWeekend() { return isWeekend(this->getDayIndex()); }

  bool isDateBeforeDate2(Date date2) { return isDateBeforeDate2(*this, date2); }

  bool isDateEqualDate2(Date date2) { return isDateEqualDate2(*this, date2); }

  bool isDateAfterDate2(Date date2) { return isDateAfterDate2(*this, date2); }

  DateCompare compareDates(Date date2) { return compareDates(*this, date2); }

  int datesDifference(Date date2, bool includeEndDay = false) {
    return datesDifference(*this, date2, includeEndDay);
  }

  Date addDaysToDate(short days) { return addDaysToDate(*this, days); }

  Date addMonthsToDate(short months) { return addMonthsToDate(*this, months); }

  Date addYearsToDate(short years) { return addYearsToDate(*this, years); }

  Date subDaysFromDate(short days) { return subDaysFromDate(*this, days); }

  Date subMonthsFromDate(short months) {
    return subMonthsFromDate(*this, months);
  }

  Date subYearsFromDate(short years) { return subYearsFromDate(*this, years); }

  std::string toString() { return dateToString(*this); }

  short getDayIndex() { return getDayIndex(*this); };

  std::string getDayName() { return getDayName(this->getDayIndex()); }

  short getMonthDays() { return getMonthDays(month_, year_); }

  std::string getMonthName() { return getMonthName(month_); }

  short daysSinceYearStart() { return daysSinceYearStart(*this); }

  short daysUntilEndOfWeek() { return daysUntilEndOfWeek(this->getDayIndex()); }

  short daysUntilEndOfMonth() { return daysUntilEndOfMonth(*this); }

  short daysUntilEndOfYear() { return daysUntilEndOfYear(*this); }

  void monthCalendar() { return monthCalendar(month_, year_); }

  void yearCalendar() { return yearCalendar(year_); }

  short calculateVacationDays(Date vacationEnd) {
    return calculateVacationDays(*this, vacationEnd);
  }

  Date calculateVacationEnd(short vacationDays) {
    return calculateVacationEnd(*this, vacationDays);
  }

  int calculateAgeInDays() { return calculateAgeInDays(*this); }

 private:
  short day_ = 0;
  short month_ = 0;
  short year_ = 0;
};
