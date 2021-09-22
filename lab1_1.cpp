#include <algorithm>
#include <iostream>
struct Vector
{
    unsigned int _size{0};
    int *_list{nullptr};
};

int norm(Vector &data);
void init(Vector &data, unsigned int size);
void clear(Vector &data);
int pop(Vector &data);
void push(Vector &data, int val);

bool cmp(int left, int right)
{
    return left < right;
}

int main(void)
{
	Vector v;
	unsigned int size = 0;
	std::cin >> size;
    int push_val = 0;
	std::cin >> push_val;

	init(v, size);
	for (size_t i = 0; i < v._size; i++)
	{
		std::cin >> v._list[i];
	}

	push(v, push_val);

	for (size_t i = 0; i < v._size; i++)
	{
		std::cout << v._list[i] << " ";
	}

    std::sort(v._list, v._list + v._size, cmp);

	std::cout << pop(v) << " ";

	for (size_t i = 0; i < v._size; i++)
	{
		std::cout << v._list[i] << " ";
	}

	std::cout << norm(v) << " ";

	clear(v);

	std::cout << norm(v);
}

int norm(Vector &data)
{
    int sum = 0;
    for (size_t i = 0; i < data._size; i++)
    {
        sum += data._list[i];
    }
    return sum;
}

void init(Vector &data, unsigned int size)
{
    data._size = size;
    data._list = new int [size]; //
}

void clear(Vector &data)
{
    data._size = 0;
    delete[] data._list;
}

int pop(Vector &data)
{
    data._size -= 1;
    int tmp = data._list[data._size];
    int *arr = new int[data._size];
    for (size_t i = 0; i < data._size; i++)
    {
        arr[i] = data._list[i];
    }
    delete [] data._list; //
    data._list = arr;
    return tmp;
}

void push(Vector &data, int val)
{
    data._size++;
    int *arr = new int[data._size];
    for (size_t i = 0; i < data._size - 1; i++)
    {
        arr[i] = data._list[i];
    }
    arr[data._size - 1] = val;
    delete [] data._list; //
    data._list = arr;
}
