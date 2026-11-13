#ifndef WORDINFO_H
#define WORDINFO_H

#include <iostream>
#include <iomanip>
using namespace std;

struct WordInfo {
	string word = "";
	int occurrences = 0;
	int firstOccurrence = 0;

	bool operator<(const WordInfo& other) const;
	bool operator==(const WordInfo& other) const;
};

ostream& operator<<(ostream& out, const WordInfo& w);

#endif