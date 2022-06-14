#include <windows.h>
#include <iostream>

using namespace std;

struct info {
	int min = 0;
	int max = 0;
	int* arr = NULL;
	int size = 0;
	int average = 0;
};

DWORD WINAPI Min_max(LPVOID aa) {

	printf("Stream Min_max open \n");

	info* a = (info*)aa;
	a->min = a->arr[0];
	a->max = a->arr[0];

	for (int i = 1; i < a->size; i++)
	{
		if (a->max < a->arr[i]) {
			a->max = a->arr[i];
		}Sleep(7);
		if (a->min > a->arr[i]) {
			a->min = a->arr[i];
		}Sleep(7);
	}

	printf("Min: %d %s", a->min, "\n");
	printf("Max: %d %s", a->max, "\n");
	printf("Stream Min_max close\n");
	return 0;
}

DWORD WINAPI Average(LPVOID aa) {

	printf("Stream Average open \n");

	info* a = (info*)aa;

	for (int i = 0; i < a->size; i++) {
		a->average += a->arr[i];
		Sleep(12);
	}
	a->average /= (a->size);
	printf("Average: %d %s", a->average, "\n");
	printf("Stream Average close\n");
	return 0;
}

int main()
{
	int size;
	printf("Input array size: ");
	scanf_s("%d", &size);
	int* arr = new int[size];
	printf("Input elements of array: ");
	for (int i = 0; i < size; i++) {
		scanf_s("%d", &arr[i]);
	}

	struct info* a = new info;
	a->arr = arr;
	a->size = size;

	LPTHREAD_START_ROUTINE mm = (LPTHREAD_START_ROUTINE)Min_max;
	HANDLE hThread_mm;
	DWORD IDThread_mm;
	hThread_mm = CreateThread(NULL, 0, mm, (LPVOID)a, 0, &IDThread_mm);
	if (hThread_mm == NULL)
		return GetLastError();


	LPTHREAD_START_ROUTINE av = (LPTHREAD_START_ROUTINE)Average;
	HANDLE hThread_av;
	DWORD IDThread_av;
	hThread_av = CreateThread(NULL, 0, av, (LPVOID)a, 0, &IDThread_av);
	if (hThread_av == NULL)
		return GetLastError();

	WaitForSingleObject(hThread_mm, INFINITE);
	WaitForSingleObject(hThread_av, INFINITE);

	CloseHandle(hThread_mm);
	CloseHandle(hThread_av);

	for (int i = 0; i < size; i++) {
		if (arr[i] == a->max) arr[i] = a->average;
		if (arr[i] == a->min) arr[i] = a->average;
	}

	printf("New array: ");
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}

	delete[] arr;
	delete a;

	return 0;
}