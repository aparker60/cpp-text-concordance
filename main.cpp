#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>
#include "BST.h"

using namespace std;

//  ------ Global Constants  ------
const int NUM_TREES = 26;
const int WORD_WIDTH = 24;
const int FIRST_WIDTH = 9;
const int OCC_WIDTH = 10;

//  ------  Prototypes  ------
bool isAlpha(char c);
void toLowerCase(string& word);
void cleanWord(string& word);
void insertWord(string& word, int lineNumber, BST<WordInfo> trees[]);
void displayHeader(const string& title);
void displayTableHeader();
void searchConcordance(BST<WordInfo> trees[]);
void displayConcordance(BST<WordInfo> trees[]);

int main() {
	string fileName = "";
	char choice = 'x';

	BST<WordInfo> trees[NUM_TREES];

	cout << "===========================================\n";
	cout << "         TEXT CONCORDANCE PROGRAM\n";
	cout << "===========================================\n\n";
	cout << "Enter input file: ";
	getline(cin, fileName);
	ifstream file(fileName);


	//  ------  File Validation  ------
	if (!file) {
		cout << "Error opening file.\n";
		exit(1);
	}

	char c;
	string word = "";
	int lineNumber = 1;

	auto start = chrono::steady_clock::now();

	while (file.get(c)) {

		if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
			c = tolower(c);
			word += c;
		}
		else {
			if (!word.empty())
				insertWord(word, lineNumber, trees);
			if (c == '\n') {
				lineNumber++;
			}
		}
	}

	auto end = chrono::steady_clock::now();
	chrono::duration<double> timeElapsed = end - start;

	if (!word.empty()) {
		insertWord(word, lineNumber, trees);
	}

	cout << "\nConcordance built in " << timeElapsed << " seconds.\n\n";

	while (choice != 'q' && choice != 'Q') {
		cout << "-------------------------------------------\n";
		cout << "Options:\n\n";
		cout << "  [S] Search for a word\n";
		cout << "  [D] Display full concordance\n";
		cout << "  [Q] Quit\n";
		cout << "-------------------------------------------\n\n";
		cout << "Enter choice: ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 's':
		case 'S':
			searchConcordance(trees);
			break;
		case 'd':
		case 'D':
			displayConcordance(trees);
			break;
		case 'q':
		case 'Q':
			break;
		default:
			cout << "Invalid option.\n\n";
			break;
			}
		}
	}



// ------  Word Processing Functions  ------

	bool isAlpha(char c) {
		return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
	}

	void toLowerCase(string& word) {
		for (int i = 0; i < word.length(); i++) {
			word[i] = tolower(word[i]);
		}
	}

	void cleanWord(string& word) {
		while (!word.empty() && !isAlpha(word[0])) {
			word = word.substr(1);
		}
		while (!word.empty() && !isAlpha(word[word.length() - 1])) {
			word = word.substr(0, word.length() - 1);
		}
	}



//  ------  Concordance Helper Function  ------

	void insertWord(string& word, int lineNumber, BST<WordInfo> trees[]) {
		cleanWord(word);
		if (!word.empty()) {
			int index = word[0] - 'a';

			WordInfo w;
			w.word = word;
			w.occurrences = 1;
			w.firstOccurrence = lineNumber;

			trees[index].insert(w);
		}
		word = "";
	}



//  ------  Output Formatting Functions  ------

	void displayHeader(const string& title) {
		string upperTitle = title;
		for (int i = 0; i < upperTitle.length(); i++) {
			upperTitle[i] = toupper(upperTitle[i]);
		}
		cout << "===========================================\n";
		cout << right << setw(22 + (upperTitle.length() / 2)) << upperTitle << "\n";
		cout << "===========================================\n\n";
	}

	void displayTableHeader() {
		cout << left << setw(WORD_WIDTH) << "Word"
			<< right << setw(FIRST_WIDTH) << "1st"
			<< setw(OCC_WIDTH) << "Occ." << endl;

		cout << "...........................................\n";
	}



//  ------  Concordance Operations  ------

	void searchConcordance(BST<WordInfo> trees[]) {
		string word = "";
		displayHeader("search");
		cout << "Enter word to search: ";
		cin >> word;
		toLowerCase(word);

		cout << "\n";

		WordInfo target;
		target.word = word;

		WordInfo result;

		int index = word[0] - 'a';

		if (trees[index].search(target, result)) {
			displayTableHeader();

			cout << left << setw(WORD_WIDTH) << result.word
				<< right << setw(FIRST_WIDTH) << result.firstOccurrence
				<< setw(OCC_WIDTH) << result.occurrences << "\n\n";
		}
		else {
			cout << "Word not found.\n\n";
		}
	}

	void displayConcordance(BST<WordInfo> trees[]) {
		bool empty = true;
		for (int i = 0; i < NUM_TREES; i++) {
			if (!trees[i].empty()) {
				empty = false;
			}
		}

		cin.ignore();
		if (!empty) {
			displayHeader("Full Concordance");
			for (int i = 0; i < NUM_TREES; i++) {
				if (!trees[i].empty()) {
					cout << "-------------------  " << char('A' + i) << "  -------------------\n";
					displayTableHeader();

					trees[i].inorder(cout);

					cout << "\nPress ENTER to continue...\n";
					cin.get();
				}
			}
		}
		else {
			cout << "Concordance Empty.\n\n";
		}
	}