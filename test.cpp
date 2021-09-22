#include <algorithm>
#include <iostream>
#include <vector>

class Vector 
{
	unsigned int size;
	int * list_d{nullptr};
	int list_s [1000];
	std::vector<int> list_v;

public:
	~Vector()
	{
		delete [] list_d;
		list_d = nullptr;

		list_v.clear();

		size = 0;
	}

	Vector() = delete;

	Vector(unsigned int size, int val = 0)
	{		
		this->size = size;

		list_d = new int [size];

		list_v = std::vector<int>(size, val);
	}

	Vector(const Vector & other)
	{
		this->size = other.size;
		this->list_d = new int [other.size];
		std::copy(other.list_d, other.list_d + other.size, this->list_d);
	}

	Vector(Vector && other)
	{
		this->size = other.size;
		other.size = 0;

		this->list_d = other.list_d;
		other.list_d = nullptr;

		std::move(std::begin(other.list_s), std::end(other.list_s), &this->list_s[0]);

		this->list_v = std::exchange(other.list_v, {});
	}

	const int
	operator[](const unsigned int idx)
	{
		return this->list_v[idx];
	}

	Vector &
	operator+=(const int value)
	{
		this->list_s[size] = value;

		this->size += 1;
		this->list_v.push_back(value);

		return *this;
	}

	friend std::istream &
	operator>>(std::istream & is, Vector & obj)
	{
		for (size_t i = 0; i < obj.size; i++)
		{
			is >> obj.list_d[i] >> obj.list_v[i] >> obj.list_s[i];
		}

		return is;
	}

	friend std::ostream &
	operator<<(std::ostream & os, const Vector & obj)
	{
		for (size_t i = 0; i < obj.size; i++)
		{
			os << obj.list_d[i] << " " << obj.list_v[i] << " " << obj.list_s[i] << "\n";
		}
		
		return os;
	}
};


int main(int argc, char const *argv[])
{
	Vector v(2);

	std::cin >> v;

	v += 12;

	std::cout << v[2];

	return 0;
}
