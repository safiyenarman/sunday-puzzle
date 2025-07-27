#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

// In this function, I am performing a clockwise spiral traversal of the matrix.
// I am concatenating the characters in the traversal order into the string 'searchInSpiral'.
// I format the output using - between each collected word as shown in the sample runs.
void spiralSearch(const vector<vector<string> > &matrix, int numRows, int numCols, string & searchInSpiral) {
	string word;
	int rowStart = 0, rowEnd = numRows - 1;
	int colStart = 0, colEnd = numCols - 1;
	bool toPutDash = false;

	while ((rowStart <= rowEnd) && (colStart <= colEnd)) {
		// I start from the top row (left to right)
		for (int col = colStart; col <= colEnd; col++)
			word += (matrix[rowStart][col]);
		rowStart++;
		if (!word.empty()) {
			if (toPutDash)
				cout << "-";
			searchInSpiral += word;
			toPutDash = true;
			cout << word;
		}
		word = "";

		// Then I go down the rightmost column
		for (int row = rowStart; row <= rowEnd; row++)
			word += (matrix[row][colEnd]);
		colEnd--;
		if (!word.empty()) {
			if (toPutDash)
				cout << "-";
			searchInSpiral += word;
			cout << word;
			toPutDash = true;
		}
		word = "";

		// I move from right to left along the bottom row
		if (rowStart <= rowEnd) {
			for (int col = colEnd; col >= colStart; col--)
				word += (matrix[rowEnd][col]);
			rowEnd--;
			if (!word.empty()) {
				if (toPutDash)
					cout << "-";
				searchInSpiral += word;
				cout << word;
				toPutDash = true;
			}
			word = "";
		}

		// Finally, I move up the leftmost column
		if (colStart <= colEnd) {
			for (int row = rowEnd; row >= rowStart; row--)
				word += (matrix[row][colStart]);
			colStart++;
			if (!word.empty()) {
				if (toPutDash)
					cout << "-";
				searchInSpiral += word;
				cout << word;
				toPutDash = true;
			}
			word = "";
		}
	}
}

// In this function, I am performing a counter-clockwise spiral traversal of the matrix.
// I store the result in 'searchInCounterSpiral' and print each collected segment with -'s.
void  CounterSpiralSearch(const vector<vector<string> > &matrix, int numRows, int numCols, string &searchInCounterSpiral) {
	cout << endl;
	int rowStart2 = 0, rowEnd2 = numRows - 1;
	int colStart2 = 0, colEnd2 = numCols - 1;
	string word2;
	bool toPuthDash2 = false;

	while ((rowStart2 <= rowEnd2) && (colStart2 <= colEnd2)) {
		// I start by moving from right to left on the top row
		word2 = "";
		for (int col = colEnd2; col >= colStart2; col--)
			word2 += (matrix[rowStart2][col]);
		rowStart2++;
		if (!word2.empty()) {
			if (toPuthDash2)
				cout << "-";
			searchInCounterSpiral += word2;
			cout << word2;
			toPuthDash2 = true;
		}

		// I move down the leftmost column
		word2 = "";
		for (int row = rowStart2; row <= rowEnd2; row++)
			word2 += (matrix[row][colStart2]);
		colStart2++;
		if (!word2.empty()) {
			if (toPuthDash2)
				cout << "-";
			searchInCounterSpiral += word2;
			cout << word2;
			toPuthDash2 = true;
		}

		// I go left to right on the bottom row
		if (rowStart2 <= rowEnd2) {
			word2 = "";
			for (int col = colStart2; col <= colEnd2; col++)
				word2 += (matrix[rowEnd2][col]);
			rowEnd2--;
			if (!word2.empty()) {
				if (toPuthDash2)
					cout << "-";
				searchInCounterSpiral += word2;
				cout << word2;
				toPuthDash2 = true;
			}
		}

		// Finally, I move up the rightmost column
		if (colStart2 <= colEnd2) {
			word2 = "";
			for (int row = rowEnd2; row >= rowStart2; row--)
				word2 += (matrix[row][colEnd2]);
			colEnd2--;
			if (!word2.empty()) {
				if (toPuthDash2)
					cout << "-";
				searchInCounterSpiral += word2;
				cout << word2;
				toPuthDash2 = true;
			}
		}
	}
}

int main() {
	string fileName;
	cin >> fileName;

	ifstream input(fileName.c_str());
	if (!input.fail()) {
		string line;
		getline(input, line);
		istringstream iss(line);
		int count;
		iss >> count;

		vector<vector<string>> matrix(count);

		// I fill the matrix with single-character strings
		for (int i = 0; i < count; i++) {
			if (getline(input, line)) {
				const string& word = line;
				for (int j = 0; j < word.length(); j++) {
					matrix[i].push_back(word.substr(j, 1));
				}
			}
		}

		int numRows = matrix.size();
		int numCols = matrix[0].size();

		string searchInSpiral;
		string searchInCounterSpiral;

		if (getline(input, line)) {
			// I check if there is a list of words to search for
			int searchCount;
			istringstream iss2(line);
			iss2 >> searchCount;

			// If no words are given, I just print spiral outputs
			if (searchCount == 0) {
				spiralSearch(matrix, numRows, numCols, searchInSpiral);
				CounterSpiralSearch(matrix, numRows, numCols, searchInCounterSpiral);
			}
			else {
				// I perform both spiral and counter-spiral search
				spiralSearch(matrix, numRows, numCols, searchInSpiral);
				CounterSpiralSearch(matrix, numRows, numCols, searchInCounterSpiral);

				cout << endl;
				cout << "*-*-*-*-*-*-*-*-*-*";
				string searchedOnes[searchCount];
				cout << endl;

				// I collect the words that need to be searched
				for (int i = 0; i < searchCount; i++) {
					if (getline(input, line)) {
						searchedOnes[i] = line;
					}
				}

				// I search each word in both spiral strings
				int s = 0;
				while (s < searchCount) {
					if (searchInSpiral.find(searchedOnes[s]) != string::npos)
						cout << searchedOnes[s] << " found with spiral search!" << endl;
					else if (searchInCounterSpiral.find(searchedOnes[s]) != string::npos)
						cout << searchedOnes[s] << " found with counter-spiral search!" << endl;
					else
						cout << searchedOnes[s] << " not found!" << endl;
					s++;
				}

				cout << "*-*-*-*-*-*-*-*-*-*" << endl;

				// Calculation of score based on search results
				int points = 0;
				for (int i = 0; i < searchCount; i++) {
					if (searchInSpiral.find(searchedOnes[i]) != string::npos && searchedOnes[i].length() <= 5)
						points += searchedOnes[i].length() * 2;
					else if (searchInSpiral.find(searchedOnes[i]) != string::npos && searchedOnes[i].length() > 5)
						points += (searchedOnes[i].length() * 2) + 2;
					else if (searchInCounterSpiral.find(searchedOnes[i]) != string::npos && searchedOnes[i].length() <= 5)
						points += (searchedOnes[i].length() * 2) + 1;
					else if (searchInCounterSpiral.find(searchedOnes[i]) != string::npos && searchedOnes[i].length() > 5)
						points += (searchedOnes[i].length() * 2) + 3;
					else
						points -= 5;
				}
				cout << "Your score is: " << points << endl;
			}
		}
	}
	else {
		cout << "Could not open the file " << fileName << endl;
	}
	return 0;
}
