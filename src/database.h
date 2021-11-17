#pragma once

#include "date.h"
#include <map>
#include <string>
#include <set>

#include <ostream>
#include <functional>

#include "node.h"


class Database {
public:

	void parseCommand(const std::string& commandLine);

	void Add(const Date& date, const std::string& event);

	void Print(std::ostream& os) const;

	vector<pair<Date, string>> FindIf(std::function<bool(const Date&, const string&)> predicate) const;
	int RemoveIf(std::function<bool(const Date&, const string&)> predicate);

	pair<Date, string> Last(const Date& date) const;

private:
	std::map<Date, std::set<std::string>> events;
	std::map<Date, std::vector<std::string>> eventsSeq;
};

