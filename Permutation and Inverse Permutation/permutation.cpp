
#include<bits/stdc++.h>
using namespace std;


int* inversePermutation(int arr1[],int size) //return type- address of integer array
{
   int* a = new int[size];
  for (int i = 0; i < size; i++) {
	int x=arr1[i];
	int y=arr1[x-1]; 
	a[i]=y;
  }
  cout << "inverse permutation of numbers =>"<< " "; 
   for (int i = 0; i < size; i++){
    cout <<a[i] << " "; 
   }
   std::cout << std::endl;
	return a; //address of a returned
}

string* Arraypermutation(int arr1[],string arr2[],int size){
 
	 string* arr4 = new string[size];

    for (int i = 0; i < size; i++) {
	int x=arr1[i]; 
	arr4[i]=arr2[x-1];
  }
  cout << "permutation of letters Array =>"<< " "; 
   for (int i = 0; i < size; i++){
    cout << arr4[i] << " "; 
   }
   std::cout << std::endl;
	return arr4;
}

void Arrayinversepermutation(string bde[],int abc[],int size){
 
	string arr5[size];

    for (int i = 0; i < size; i++) {
	int x=abc[i]; 
	arr5[i]=bde[x-1];
  }
  cout << "Inverse permutation of letters Array =>"<< " "; 
   for (int i = 0; i < size; i++){
    cout << arr5[i] << " "; 
   }

}

// Main method 
int main()
{
	 int arr1[] = {1,2,4,5,3};
	 string arr2[] = {"a","b","c","d","e"};
	 int size = sizeof(arr1) / sizeof(arr1[0]);
 	 int* result1= inversePermutation(arr1, size);
	 string* result2=Arraypermutation(arr1,arr2,size);
	 Arrayinversepermutation(result2,result1,size);
 	 return 0;
}
