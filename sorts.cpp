#include <iostream>
#include <cstdlib>

using namespace std;


int* genList(int bound, int length){
	int *list = new int[length];

	srand(time(NULL));
	for (int i = 0; i < length; i++){
		list[i] = rand() % bound;
	}
	return list;
}

int *genAscendingList(int start, int step, int length){
	int *list = new int[length];
	if (length > 0){
		list[0] = start;
		for (int i = 1; i < length; i++) list[i] = list[i-1] + step;
	}
	return list;
}

int *genDescendingList(int start, int step, int length){
	int *list = new int[length];
	if (length > 0){
		list[length - 1] = start;
		for (int i = length - 2; i >= 0; i--) list[i] = list[i+1] + step;
	}
	return list;

}


void printList(int list[], int length){
	cout << "{";
	for (int i = 0; i < length - 1; i++){
		cout << list[i] << ", ";
	}
	cout << list[length - 1] << "}" << endl;
	return;
}

int bubble(int list[], int n){
	int i = 1, j;
	bool swapMade = true;

	int comparisons = 0;

	while (i < n && swapMade){
		swapMade = false;
		for (j = 0; j < n - i; j++){
			comparisons++;
			if (list[j] > list[j + 1]){
				int temp = list[j + 1];
				list[j + 1] = list[j];
				list[j] = temp;
				swapMade = true;
			}
		}
		//printList(list, n);
		i++;
	}
	return comparisons;
}

void algorithmTest( int (*alg)(int *, int) ){
	int operations = -1;

	int bound = 500;
	int step = 50;

	int lengths[] = {20, 40};
	int numCases = sizeof(lengths) / sizeof(int);

	for (int i = 0; i < numCases; i++){

		int *list = genList(bound, lengths[i]);
		int *sorted = genAscendingList(bound, step, lengths[i]);
		int *reversed = genDescendingList(bound, step, lengths[i]);


		cout << "LISTS" << endl;
		cout << "   Random: "; printList(list, lengths[i]);
		cout << "   Sorted: "; printList(sorted, lengths[i]);
		cout << "Reveresed: "; printList(reversed, lengths[i]);
		cout << endl;

		cout << "Sorting the random list . . ." << endl;
		operations = alg(list, lengths[i]);
		printList(list, lengths[i]);
		cout << operations << " operations made when n = " << lengths[i] << endl;
		cout << endl;


		cout << "Sorting the sorted list . . ." << endl;
		operations = alg(sorted, lengths[i]);
		printList(sorted, lengths[i]);
		cout << operations << " operations made when n = " << lengths[i] << endl;
		cout << endl;

		cout << "Sorting the reversed list . . ." << endl;
		operations = alg(reversed, lengths[i]);
		printList(reversed, lengths[i]);
		cout << operations << " operations made when n = " << lengths[i] << endl;
		cout << endl;


		delete[] list;
		delete[] sorted;
		delete[] reversed;
	}

	return;
}

int main(void){

	//bubbleTest();	
	algorithmTest( &bubble);

	return 0;
}