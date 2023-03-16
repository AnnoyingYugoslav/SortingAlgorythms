#include<iostream>
#include<cstdlib>
#include<array>
#include<chrono>
using namespace std;

void merge(int array[], int const left, int const mid, int const right) {
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;
	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne
		= 0, // Initial index of first sub-array
		indexOfSubArrayTwo
		= 0; // Initial index of second sub-array
	int indexOfMergedArray
		= left; // Initial index of merged array

	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne]
			<= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray]
				= leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray]
				= rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray]
			= leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray]
			= rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}
void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return;
	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}
void heapify(int arr[], int N, int i){
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < N && arr[l] > arr[largest])
		largest = l;
	if (r < N && arr[r] > arr[largest])
		largest = r;
	if (largest != i) {
		swap(arr[i], arr[largest]);
		heapify(arr, N, largest);
	}
}
int partition(int arr[], int start, int end)
{
	int pivot = arr[start];
	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot)
			count++;
	}
	int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);
	int i = start, j = end;
	while (i < pivotIndex && j > pivotIndex) {
		while (arr[i] <= pivot) {
			i++;
		}
		while (arr[j] > pivot) {
			j--;
		}
		if (i < pivotIndex && j > pivotIndex) {
			swap(arr[i++], arr[j--]);
		}
	}
	return pivotIndex;
}
void quickSort(int arr[], int start, int end)
{
	if (start >= end)
		return;
	int p = partition(arr, start, end);
	quickSort(arr, start, p - 1);
	quickSort(arr, p + 1, end);
}

const int rozmiar = 1000;
const int druk = 0;

int * random() {
	static int random[rozmiar];//number of ellements - completly random 
	int a = sizeof(random) / sizeof(random[0]); //arr size checker
	int b = 10; //max number value
	srand((unsigned)time(NULL));
	for (int i = 0; i < a; i++) {
		int los = (rand() % b);
		random[i] = los;
	}
	return random;
}
int * vshape() {
	static int vshape[rozmiar]; //number of elements - v shape
	int a = sizeof(vshape) / sizeof(vshape[0]);
	int c = 2 * a;
	int b = 10;
	for (int i = 0; i < (a / 2); i++) {
		int los = (rand() % b);
		c -= los;
		vshape[i] = c;
	}
	for (int i = (a / 2); i < a; i++) {
		int los = (rand() % b);
		vshape[i] = c;
		c = c + los;
	}
	return vshape;
}
int * ashape() {
	static int ashape[rozmiar]; //number of elements - v shape
	int a = sizeof(ashape) / sizeof(ashape[0]);
	int c = 0;
	int b = 10;
	for (int i = 0; i < (a / 2); i++) {
		int los = (rand() % b);
		c += los;
		ashape[i] = c;
	}
	for (int i = (a / 2); i < a; i++) {
		int los = (rand() % b);
		ashape[i] = c;
		c = c - los;
	}
	return ashape;
}
int* rise() {
	static int rise[rozmiar]; //number of elements - v shape
	int a = sizeof(rise) / sizeof(rise[0]);
	int c = 0;
	int b = 10;
	for (int i = 0; i < a; i++) {
		int los = (rand() % b);
		c += los;
		rise[i] = c;
	}
	return rise;
}
int* fall() {
	static int fall[rozmiar]; //number of elements - v shape
	int a = sizeof(fall) / sizeof(fall[0]);
	int c = 5 * a;
	int b = 10;
	for (int i = 0; i < a; i++) {
		int los = (rand() % b);
		c -= los;
		fall[i] = c;
	}
	return fall;
}

auto mergesort(int which) {
	int* p;
	int list[rozmiar];
	int l = 0;
	if (which == 1) {
		p = random();
	}
	else if (which == 2) {
		p = vshape();
	}
	else if (which == 3) {
		p = ashape();
	}
	else if (which == 4) {
		p = rise();
	}
	else if (which == 5) {
		p = fall();
	}
	else {
		p = random();
	}
	int a = sizeof(list) / sizeof(list[0]);
	for (int i = 0; i < a; i++) {
		list[i] = *(p + i);
	}
	auto begin = chrono::high_resolution_clock::now();
	mergeSort(list, 0, a - 1);
	auto end = chrono::high_resolution_clock::now();
	auto dur = end - begin;
	auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
	if (druk == 1) { for (int b = 0; b < a; b++) { cout << list[b]; } }
	return ms;
}
auto heapsort(int which) {
	int* p;
	int list[rozmiar];
	int l = 0;
	if (which == 1) {
		p = random();
	}
	else if (which == 2) {
		p = vshape();
	}
	else if (which == 3) {
		p = ashape();
	}
	else if (which == 4) {
		p = rise();
	}
	else if (which == 5) {
		p = fall();
	}
	else {
		p = random();
	}
	int a = sizeof(list) / sizeof(list[0]);
	for (int i = 0; i < a; i++) {
		list[i] = *(p + i);
	}
	auto begin = chrono::high_resolution_clock::now();
	for (int i = a / 2 - 1; i >= 0; i--)
		heapify(list, a, i);
	for (int i = a - 1; i > 0; i--) {
		swap(list[0], list[i]);
		heapify(list, i, 0);
	}
	auto end = chrono::high_resolution_clock::now();
	auto dur = end - begin;
	auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
	if (druk == 1) { for (int b = 0; b < a; b++) { cout << list[b]; } }
	return ms;
}
auto bubblesort(int which) {
	int* p;
	int list[rozmiar];
	if (which == 1) {
		p = random();
	}
	else if (which == 2) {
		p = vshape();
	}
	else if (which == 3) {
		p = ashape();
	}
	else if (which == 4) {
		p = rise();
	}
	else if (which == 5) {
		p = fall();
	}
	else {
		p = random();
	}
	int a = sizeof(list) / sizeof(list[0]);
	for (int i = 0; i < a; i++) {
		list[i] = *(p + i);
	}
	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < (a - 1); i++) {
		for (int j = 0; j < (a - i - 1); j++) {
			if (list[j] > list[j + 1]) {
				swap(list[j], list[j + 1]);
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	auto dur = end - begin;
	auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
	if (druk == 1) { for (int b = 0; b < a; b++) { cout << list[b]; } }
	return ms;
}
auto selectionsort(int which) {
	int* p;
	int list[rozmiar];
	int l = 0;
	if (which == 1) {
		p = random();
	}
	else if (which == 2) {
		p = vshape();
	}
	else if (which == 3) {
		p = ashape();
	}
	else if (which == 4) {
		p = rise();
	}
	else if (which == 5) {
		p = fall();
	}
	else {
		p = random();
	}
	int a = sizeof(list) / sizeof(list[0]);
	for (int i = 0; i < a; i++) {
		list[i] = *(p + i);
	}
	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < (a - 1); i++) {
		l = i;
		for (int j = (i + 1); j < a; j++) {
			if (list[j] < list[l]) {
				l = j;
			}
		}
		swap(list[l], list[i]);
	}
	auto end = chrono::high_resolution_clock::now();
	auto dur = end - begin;
	auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
	if (druk == 1) { for (int b = 0; b < a; b++) { cout << list[b]; } }
	return ms;
}
auto insertionsort(int which){
	int* p;
	int list[rozmiar];
	int l = 0;
	if (which == 1) {
		p = random();
	}
	else if (which == 2) {
		p = vshape();
	}
	else if (which == 3) {
		p = ashape();
	}
	else if (which == 4) {
		p = rise();
	}
	else if (which == 5) {
		p = fall();
	}
	else {
		p = random();
	}
	int a = sizeof(list) / sizeof(list[0]);
	for (int i = 0; i < a; i++) {
		list[i] = *(p + i);
	}
	auto begin = chrono::high_resolution_clock::now();
	int key, j;
	for (int i = 1; i < a; i++)
	{
		key = list[i];
		j = i - 1;
		while (j >= 0 && list[j] > key)
		{
			list[j + 1] = list[j];
			j = j - 1;
		}
		list[j + 1] = key;
	}
	auto end = chrono::high_resolution_clock::now();
	auto dur = end - begin;
	auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
	if (druk == 1) { for (int b = 0; b < a; b++) { cout << list[b]; } }
	return ms;
}
auto quicksort(int which) {
	int* p;
	int list[rozmiar];
	int l = 0;
	if (which == 1) {
		p = random();
	}
	else if (which == 2) {
		p = vshape();
	}
	else if (which == 3) {
		p = ashape();
	}
	else if (which == 4) {
		p = rise();
	}
	else if (which == 5) {
		p = fall();
	}
	else {
		p = random();
	}
	int a = sizeof(list) / sizeof(list[0]);
	for (int i = 0; i < a; i++) {
		list[i] = *(p + i);
	}
	auto begin = chrono::high_resolution_clock::now();
	quickSort(list, 0, (a - 1));
	auto end = chrono::high_resolution_clock::now();
	auto dur = end - begin;
	auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
	if (druk == 1) { for (int b = 0; b < a; b++) { cout << list[b]; } }
	return ms;
}
int main() {
	auto timer = 0;
	for (int y = 0; y < 301; y++) {
		for (int x = 0; x < y; x++) {
			timer += quicksort(2);
			//cout << "\n";
		}
		cout << y * rozmiar;
		cout << " ";
		cout << timer;
		cout << "\n";
		timer = 0;
	}
	return 1;
}