#pragma once

#include <string>

#include <ostream>

class Date {
public:
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	Date();
	Date(int year, int month, int day) :
		year(year), month(month), day(day), valid(true) {}

	bool checkDateValid(const std::string& dateString);


private:
	int year;
	int month;
	int day;

	bool valid;
};

bool operator<(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

std::ostream& operator<<(std::ostream& os, const Date& date);

Date ParseDate(std::istream& is);