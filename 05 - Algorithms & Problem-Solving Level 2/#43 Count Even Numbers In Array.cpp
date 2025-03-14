// Count Even Numbers In Array
// https://programmingadvices.com/courses/1811531/lectures/41430577/comments/25787908

#include <iostream>

using namespace std;

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

void AddElements(int arr[], int length)
{
	for (int i = 0; i < length; i++)
		arr[i] = RandomNumber(1, 100);
}

int CountEvenNumsInArray(int arr[], int length)
{
	int count = 0;
	for (int i = 0; i < length; i++)
		if (arr[i] % 2 == 0) count++;
	return count;
}

void PrintArray(int arr[], int length)
{
	for (int i = 0; i < length; i++)
		cout << arr[i] << ' ';
	cout << endl;
}

int main()
{
	srand((unsigned)time(NULL));
	int arr[100], length;
	cout << "Number Of Elements: ";
	cin >> length;
	AddElements(arr, length);
	cout << "\nArray Elements:";
	PrintArray(arr, length);
	cout << "\nEven Numbers Count In Array: " << CountEvenNumsInArray(arr, length) << endl;
}