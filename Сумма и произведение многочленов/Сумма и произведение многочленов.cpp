#include <iostream>

using namespace std;

void Sum(int*, int*, int*, int, int); //сумма многочленов
void Product(int*, int*, int*, int, int); //произведение многочленов
void Output(int*, int, string); //функция вывода массива

int main()
{
	setlocale(LC_ALL, "russian");

	int array1[] = { 2, -2, 1 }, array2[] = { 3, 1 };

	int sum_array[size(array1)] = {};
	int product_array[size(array1) + size(array2) - 1] = {};

	Sum(array1, array2, sum_array, size(array1), size(array2));
	Product(array1, array2, product_array, size(array1), size(array2));

	Output(sum_array, size(sum_array), "Массив суммы:\n");
	Output(product_array, size(product_array), "\nМассив произведения:\n");

	return 0;
}

void Sum(int* mas1, int* mas2, int* sum_mas, int size1, int size2)
{
	__asm
	{
		mov edi, size1
		sub edi, size2
		cmp edi, 0
		jg first
		mov eax, mas1
		mov ebx, mas2
		mov mas1, ebx
		mov mas2, eax
		mov eax, size1
		mov ebx, size2
		mov size1, ebx
		mov size2, eax
		neg edi

	first:
		mov ebx, sum_mas

		mov edx, mas1
		mov ecx, size1
		xor esi, esi
	sum1:
		mov eax, [edx][esi*4]
		add [ebx][esi*4], eax
		inc esi
		loop sum1

		mov edx, mas2
		mov ecx, size2
		xor esi, esi
	sum2:
		mov eax, [edx][esi*4]
		add esi, edi
		add [ebx][esi*4], eax
		inc esi
		sub esi, edi
		loop sum2
	}
}

void Product(int* mas1, int* mas2, int* product_mas, int size1, int size2)
{
	int temp;

	__asm
	{
		mov edi, size1
		sub edi, size2
		cmp edi, 0
		jg first
		mov eax, mas1
		mov ebx, mas2
		mov mas1, ebx
		mov mas2, eax
		mov eax, size1
		mov ebx, size2
		mov size1, ebx
		mov size2, eax
		neg edi

	first:
		mov edx, mas2
		mov eax, size2
		inc eax
		mov temp, eax
		xor esi, esi

	outer_cycle:
		mov eax, temp
		dec eax
		mov temp, eax
		mov ecx, size1

	inner_cycle:
		dec ecx
		mov ebx, mas1
		mov eax, [ebx][ecx*4]
		imul [edx][esi*4]
		mov ebx, product_mas
		add esi, ecx
		add [ebx][esi*4], eax
		sub esi, ecx
		inc ecx
		loop inner_cycle

		inc esi
		mov ecx, temp
		loop outer_cycle
	}
}

void Output(int* array, int size, string text)
{
	int i;

	cout << text;
	for (i = 0; i < size; i++)
		cout << "array[" << i + 1 << "]=" << array[i] << endl;
}