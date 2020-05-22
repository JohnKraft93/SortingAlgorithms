/*
280
sortingClassDemo
John Kraft
*/

#include <iostream>
#include <ctime>
#include <string>
using namespace std;

const int MAX_CHARS = 10;
const int MAX_STRINGS = 1000;

void cr(int n = 1) {
	for (int i = 0; i < n; i++)
		cout << endl;
} //cr

class Sorter {
private:
	string workspace[MAX_STRINGS];
	string randomString();
	void quickSort(int first, int last);
public:
	Sorter();
	void load();
	void display();
	void bubbleSort();
	void selectionSort();
	void insertionSort();
	void shellSort();
	void qSort();
	bool isSorted();
};

Sorter::Sorter() { //there's nothing to do
}

string Sorter::randomString() {
	//pre:	none
	//post:	return a string of MAX_CHARS random lowercase characters
	string s = "";
	for (int i = 0; i < MAX_CHARS; i++) {
		char randomChar = char(rand() % 26 + 97);
		s += randomChar;
	}
	return s;
} //randomString

void Sorter::load() {
	//pre:	none
	//post:	workspace is loaded with random strings
	for (int i = 0; i < MAX_STRINGS; i++)
		workspace[i] = randomString();
} //load

void Sorter::display() {
	//pre:	none
	//post:	display workspace elements, separated by blanks
	//		for testing purposes with VERY small arrays
	for (int i = 0; i < MAX_STRINGS; i++)
		cout << workspace[i] << " ";
	cout << endl;
} //display

void Sorter::bubbleSort() {
	//pre:	none
	//post:	the workspace array is sorted in ascending order
	for (int pass = 0; pass < MAX_STRINGS - 1; pass++) {
		for (int pos = 0; pos < MAX_STRINGS - pass - 1; pos++) {
			if (workspace[pos] > workspace[pos + 1]) {
				string temp = workspace[pos];
				workspace[pos] = workspace[pos + 1];
				workspace[pos + 1] = temp;
			}
		}
	}
} //bubbleSort

void Sorter::selectionSort() {
	//pre:	none
	//post:	the workspace array is sorted in ascending order
	for (int i = 0; i < MAX_STRINGS; i++) {
		int maxPos = 0;
		for (int j = 1; j < MAX_STRINGS - i; j++) {
			if (workspace[j] > workspace[maxPos]) {
				maxPos = j;
			}
		}
		string temp = workspace[maxPos];
		workspace[maxPos] = workspace[MAX_STRINGS - i - 1];
		workspace[MAX_STRINGS - i - 1] = temp;
	}
} //selectionSort

void Sorter::insertionSort() {
	//pre:	none
	//post:	the workspace array is sorted in ascending order
	for (int pass = 1; pass < MAX_STRINGS; pass++) {
		string key = workspace[pass];
		int j = pass - 1;
		while (j >= 0 && workspace[j] > key) {
			workspace[j + 1] = workspace[j];
			j--;
		}
		workspace[j + 1] = key;
	}
} //insertionSort

void Sorter::shellSort() {
	//pre:	none
	//post:	the workspace array is sorted in ascending order
	int gap = MAX_STRINGS / 2;
	while (gap > 0) {
		for (int i = gap; i < MAX_STRINGS; i++) {
			for (int k = i - gap; k >= 0; k -= gap) {
				if (workspace[k+gap] >= workspace[k]) {
					break;
				}
				else {
					string temp = workspace[k + gap];
					workspace[k+gap] = workspace[k];
					workspace[k] = temp;
				}
			}
		}
		gap = gap / 2;
	}
} //shellSort

void Sorter::quickSort(int first, int last) {
	int low = first;
	int high = last;
	string partition = workspace[(low + high) / 2];
	do {
		while (workspace[low] < partition) {
			low++;
		}
		while (workspace[high] > partition) {
			high--;
		}
		if (low <= high) {
			string temp = workspace[low];
			workspace[low] = workspace[high];
			workspace[high] = temp;
			low++;
			high--;
		}
	} while (low < high);

	if (first < high) {
		quickSort(first, high);
	}
	if (low < last) {
		quickSort(low, last);
	}
} //quickSort helper

void Sorter::qSort() {
	//pre:	none
	//post:	the workspace array is sorted in ascending order
	quickSort(0, MAX_STRINGS - 1);
} //quickSort


bool Sorter::isSorted() {
	//pre:	none
	//post: returns true if the workspace is ascending sorted,
	//		false otherwise
	for (int i = 0; i < MAX_STRINGS - 1; i++)
		if (workspace[i] > workspace[i + 1])
			return false;
	return true;
} //isSorted

int main() {
	srand(time(NULL));
	clock_t start, stop;
	Sorter s1 = Sorter(); //use s1 with bubble sort
	s1.load();
	Sorter s2 = Sorter(s1); //use s2 with selection sort
	Sorter s3 = Sorter(s1); //use s3 with insertion sort
	Sorter s4 = Sorter(s1); //use s4 with shell sort
	Sorter s5 = Sorter(s1); //use s5 with quick sort

	//test bubble sort
	start = clock();
	s1.bubbleSort();
	stop = clock();
	//s1.display();

	if (!s1.isSorted()) {
		cout << "Error: bubble sort failed";
		cr(2);
		exit(EXIT_FAILURE);
	}
	else {
		double elapsedTime = ((double)stop - start) / CLOCKS_PER_SEC;
		cout << "Bubble Sort time: " << elapsedTime << endl;
	}
	cr(2);


	//test selection sort
	start = clock();
	s2.selectionSort();
	stop = clock();

	if (!s2.isSorted()) {
		cout << "Error: selection sort failed";
		cr(2);
		exit(EXIT_FAILURE);
	}
	else {
		double elapsedTime = ((double)stop - start) / CLOCKS_PER_SEC;
		cout << "Selection Sort time: " << elapsedTime << endl;
	}
	cr(2);


	//test insertion sort
	start = clock();
	s3.insertionSort();
	stop = clock();

	if (!s3.isSorted()) {
		cout << "Error: selection sort failed";
		cr(2);
		exit(EXIT_FAILURE);
	}
	else {
		double elapsedTime = ((double)stop - start) / CLOCKS_PER_SEC;
		cout << "Insertion Sort time: " << elapsedTime << endl;
	}
	cr(2);

	//test shell sort
	start = clock();
	s4.shellSort();
	stop = clock();
	
	if (!s4.isSorted()) {
		cout << "Error: shell sort failed";
		cr(2);
		exit(EXIT_FAILURE);
	}
	else {
		double elapsedTime = ((double)stop - start) / CLOCKS_PER_SEC;
		cout << "Shell Sort time: " << elapsedTime << endl;
	}
	cr(2);
	
	//test quick sort
	start = clock();
	s5.qSort();
	stop = clock();
	
	if (!s5.isSorted()) {
		cout << "Error: quick sort failed";
		cr(2);
		exit(EXIT_FAILURE);
	}
	else {
		double elapsedTime = ((double)stop - start) / CLOCKS_PER_SEC;
		cout << "Quick Sort time: " << elapsedTime << endl;
	}
	cr(2);
}