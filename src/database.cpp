#include "database.h"

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void Database::Add(const Date& date, const string& event) {
	if (events[date].count(event) == 0) {
		events[date].insert(event);
		eventsSeq[date].push_back(event);
	}
}


void Database::Print(ostream& os) const {
	for (const auto& [date, eventSet] : eventsSeq)
		for (const auto& e : eventSet)  
			os << date << " " << e << endl;
}


vector<pair<Date, string>> Database::FindIf(std::function<bool(const Date&, const string&)> predicate) const {
	vector<pair<Date, string>> found;
	for (auto& [date, eventsSet] : eventsSeq) {
		for (auto& e : eventsSet)
			if (predicate(date, e)) 
				found.push_back(make_pair(date, e));
	}
	return found;
}


int Database::RemoveIf(std::function<bool(const Date&, const string&)> predicate) {

	int count = 0;

	vector<Date> eraseDates;

	for (auto& [date, eventsSet] : events) {

		for (auto it = eventsSet.begin(), end{eventsSet.end()}; 
			it != end;)
			if (predicate(date, *it)) {
				eventsSeq[date].erase(remove(eventsSeq[date].begin(), eventsSeq[date].end(), *it));
				it = eventsSet.erase(it);
				++count;
			}
			else
				++it;

		if (eventsSet.empty())
			eraseDates.push_back(date);
	}

	for (const auto& d : eraseDates) {
		events.erase(d);
		eventsSeq.erase(d);
	}

	return count;
}



pair<Date, string> Database::Last(const Date& date) const {

	if (eventsSeq.empty() || date < eventsSeq.begin()->first) 
		throw invalid_argument("invalid_argument");

	auto it = eventsSeq.upper_bound(date);
	if (it != eventsSeq.begin())
		--it;
	
	return make_pair(it->first, *(it->second.rbegin()));
}


