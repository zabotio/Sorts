/** This is an implementation of a binary insertion sort */

#include <iostream>
#include <ctime>
#include <random>

using namespace std;

const int size = 100000; // Adjusts size of array to sort

/** Just a little helper function for printin the array */
void print(int *arr){
	for(int i=0; i<size; i++){
		cout << arr[i] << ' ';
		if((i+1)%10==0) cout << endl;
	}
	cout << endl;
}

/** A little helper function to check if array is sorted 
  * returns: true if sorted, false otherwise */
bool check(int *arr){
	for(int i=0; i<size-1; i++) if(arr[i]>arr[i+1]) return false;
	return true;
}

/** First version of binary search
  * recursive search
  * param: arr - the array to search
  * param: lo - low end of search range
  * param: hi - high end of search range
  * param: val - value to insert 
  * reutrns: index to place val */
/*int search(int *arr, int lo, int hi, int val){
	if(lo >= hi) return (val>=arr[lo]) ? lo+1 : lo;
	int mid = (lo>>1) + (hi>>1);
	if(arr[mid]>val) return search(arr, lo, mid-1, val);
	else if(arr[mid]<val) return search(arr, mid+1, hi, val);
	else{
		while(arr[++mid] == val);
		return mid;
	}
}*/

/** First version of binary search
  * loop search
  * param: arr - the array to search
  * param: lo - low end of search range
  * param: hi - high end of search range
  * param: val - value to insert */
int search(int *arr, int lo, int hi, int val){
	for(int i=hi>>1; lo<hi; i=(lo>>1)+(hi>>1)){
		if(val > arr[i]) lo = i+1;
		else if(val < arr[i]) hi = i-1;
		else{
			while(arr[++i] == val);
			return i;
		}
	}
	return (val >= arr[lo]) ? lo+1 : lo;
}

/** Binary insertion sort
  * param: arr - the array to sort */
void binSort(int *arr){
	for(int i=1, ins, temp; i<size; ++i){
		if(arr[i] < arr[i-1]){
			ins = search(arr, 0, i-1, arr[i]);
			temp = arr[i];
			for(int j=i; j>ins; --j) arr[j] = arr[j-1];
			arr[ins] = temp;
		}
	}
}

/** Just an ordinary insertion sort for comparison */
void insSort(int *arr){
	for(int i=1, ins=0, temp=0; i<size; ++i){
		if(arr[i] >= arr[i-1]) continue;
		ins = i-1;
		while(--ins >= 0 && arr[ins] > arr[i]);
		temp = arr[i];
		for(int j=i; j>ins+1; --j) arr[j] = arr[j-1];
		arr[ins] = temp;
	}
}

int main(){
	double sop = clock();
	random_device rd;
	mt19937 r(rd());
	double start, end;
	int *arr = new int[size];
	for(int i=0; i<size; ++i) arr[i] = r()%size;
	//print(arr);
	start = clock();
	binSort(arr);
	end = clock();
	cout << (end-start-sop)/CLOCKS_PER_SEC << endl;
	//print(arr);
	cout << check(arr) << endl;
	delete[] arr;
}
