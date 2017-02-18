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

int select(int list[], int n){
	int comparisons = 0;
	for (int i = 0; i < n - 1; i++){
		int minIndex = i;
		for (int j = i + 1; j < n; j++){
			if (list[j] < list[minIndex]) minIndex = j;
			comparisons++;
		}
		int temp = list[i];
		list[i] = list[minIndex];
		list[minIndex] = temp;
	}
	return comparisons;
}

int insert(int list[], int n){
	int comparisons = 0;
	for (int i = 0; i < n - 1; i++){
		for (int j = i + 1; j > 0; j--){

			comparisons++;
			if (list[j] >= list[j - 1]) break;


			int temp = list[j - 1];
			list[j - 1] = list[j];
			list[j] = temp;
		}
	}
	return comparisons;
}

void mergeZip(int list[], int L, int R){
	int buffer[R - L + 1];
	int M = (L + R) / 2;
	int i = L, j = M + 1, h = 0;

	while ( (i <= M) && (j <= R) ){
		if (list[i] < list[j]) buffer[h++] = list[i++];
		else                   buffer[h++] = list[j++];
	}
	while (i <= M) buffer[h++] = list[i++];
	while (j <= R) buffer[h++] = list[j++];
	for (h = 0; h < (R - L + 1); h++) list[L + h] = buffer[h];

	return;
}

void mergeDiv(int list[], int L, int R){
	if (L >= R) return;
	
	int M = (L + R) / 2;
	mergeDiv(list, L, M);
	mergeDiv(list, M + 1, R);
	mergeZip(list, L, R);
	return;
}

int merge(int list[], int n){
	mergeDiv(list, 0, n - 1);
	return -1;
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

int median(int a, int b, int c){
	if ( (a <= b && b <= c) || (c <= b && b <= a) ) return b;
	if ( (a <= c && c <= b) || (b <= c && c <= a) ) return c;
	return a;
}

void quicksort(int list[], int L, int R){
	cout << "Quicksort called: L = " << L << ", R = " << R << endl;
	printList(list, 20);

	if (L >= R){
	       cout << "Base case reached." << endl;
       	       return;
	}

	int pivot = median(list[L], list[(L+R)/2], list[R]);
	cout << "pivot = " << pivot << endl;
	int i = L, j = R;

	while (i < j){
		while (list[i] <= pivot && i < j) i++;
		while (list[j] >= pivot && i < j) j--;

		int temp = list[i];
		list[i] = list[j];
		list[j] = temp;

		cout << "i = " << i << ", j = " << j << endl;
		cout << "Swap made." << endl << endl;

		i++;
		j--;
	}
	//int M = i;
	//quicksort(list, L, M);
	//quicksort(list, M + 1, R);
	
	quicksort(list, L, i - 1);
	quicksort(list, i, R);
	return;
}

int quick(int list[], int n){
	quicksort(list, 0, n - 1);
	return -1;
}

int main(void){

	//bubbleTest();	
	algorithmTest( &quick);

	return 0;
}
