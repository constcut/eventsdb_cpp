#include "date.h"

#include <sstream>
#include <iostream>
#include <iomanip>


using namespace std;



int Date::GetYear() const {
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}


Date::Date() : year(0), month(0),
day(0), valid(false) {}



bool Date::checkDateValid(const string& dateString) {
	istringstream ss(dateString);

	if (isdigit(ss.peek()) == false && ss.peek() != '-' && ss.peek() != '+')
		throw runtime_error("Wrong date format: " + dateString);

	ss >> year;

	if (ss.peek() != '-') {
		throw runtime_error("Wrong date format: " + dateString);
		return false;
	}
	ss.ignore(1);

	if (isdigit(ss.peek()) == false && ss.peek() != '-' && ss.peek() != '+')
		throw runtime_error("Wrong date format: " + dateString);

	ss >> month;

	if (ss.peek() != '-') {
		throw runtime_error("Wrong date format: " + dateString);
		return false;
	}
	ss.ignore(1);


	if (isdigit(ss.peek()) == false && ss.peek() != '-' && ss.peek() != '+')
		throw runtime_error("Wrong date format: " + dateString);

	ss >> day;

	if (ss.eof() == false)
		throw runtime_error("Wrong date format: " + dateString);

	if (month < 1 || month > 12) {
		throw range_error("Month value is invalid: " + to_string(month));
		return false;
	}

	if (day > 31 || day < 1) {
		throw range_error("Day value is invalid: " + to_string(day));
		return false;
	}

	valid = true;
	return valid;
}



ostream& operator<<(ostream& os, const Date& date) {
	return os << setw(4) << setfill('0') << date.GetYear() << "-"
		<< setw(2) << setfill('0') << date.GetMonth() << "-"
		<< setw(2) << setfill('0') << date.GetDay();
}



bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear())
		return lhs.GetYear() < rhs.GetYear();
	else {
		if (lhs.GetMonth() != rhs.GetMonth())
			return lhs.GetMonth() < rhs.GetMonth();
		else
			return lhs.GetDay() < rhs.GetDay();
	}
}



bool operator==(const Date& lhs, const Date& rhs) {
	return (lhs.GetYear() == rhs.GetYear())
		&& (lhs.GetMonth() == rhs.GetMonth())
		&& (lhs.GetDay() == rhs.GetDay());
}



Date ParseDate(istream& is) {
	string dateStr;
	is >> dateStr;

	Date date;
	if (date.checkDateValid(dateStr))
		return date;

	return Date{};
}