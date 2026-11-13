#include <iostream>
#include "WordInfo.h"

using namespace std;

bool WordInfo::operator<(const WordInfo& other) const {
	return word < other.word;
}

bool WordInfo::operator==(const WordInfo& other) const {
	return word == other.word;
}

ostream& operator<<(ostream& out, const WordInfo& w) {
	out << left << setw(24) << w.word
		<< right << setw(8) << w.firstOccurrence
		<< setw(10) << w.occurrences << endl;
	return out;
}