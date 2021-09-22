#include <algorithm>
#include <iostream>
#include <vector>

struct Vector
{
	unsigned int _size{0};
    std::vector<int> _list;
};

int norm(Vector & data);
void init(Vector & data, unsigned int size);
void clear(Vector & data);
int pop(Vector & data);
void push(Vector & data, int val);

bool cmp(int left, int right)
{
	return left < right;
}

int main( void )
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

	std::sort(v._list.begin(), v._list.end(), cmp);

	std::cout << pop(v) << " ";

	for (size_t i = 0; i < v._size; i++)
	{
		std::cout << v._list[i] << " ";
	}

	std::cout << norm(v) << " ";

	clear(v);

	std::cout << norm(v);
}

int norm(Vector & data)
{
	int sum = 0;
	for (size_t i = 0; i < data._size; i++)
	{
		sum += data._list[i];
	}
	return sum;
}

void init(Vector & data, unsigned int size)
{
	data._list = std::vector<int>(size);
	data._size = size;
}

void clear(Vector & data)
{
	data._list.clear();
	data._size = 0;
}

int pop(Vector & data)
{
    data._size -= 1;
    int saved = data._list[data._size];
    data._list.pop_back();
	return saved;
}

void push(Vector & data, int val)
{
	data._list.push_back(val);
    data._size += 1;
}
