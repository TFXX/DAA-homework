#include <iostream>
#include <algorithm>
#include <vector>

int32_t *p_a; 
size_t size;

template<typename ValueType>
void merge(size_t begin, size_t mid, size_t end)
{
	std::vector<ValueType> temp(end - begin);
	
	size_t i = begin, j = mid, k = 0;

	while (i < mid && j < end)
	{
		if (p_a[i] < p_a[j])
		{
			temp[k] = p_a[i];
			i++;
		}
		else
		{
			temp[k] = p_a[j];
			j++;
		}
		k++;
	}

	while (i < mid)
	{
		temp[k] = p_a[i];
		i++;
		k++;
	}

	while (j < end)
	{
		temp[k] = p_a[j];
		j++;
		k++;
	}

	std::copy(temp.begin(), temp.end(), p_a);
}

template <typename T>
void g(std::vector<T> &index_vec)
{
	std::vector<T> temp_vec;
	for (T i = 0; i < index_vec.size() - 1; i += 2)
	{
		temp_vec.emplace_back(index_vec[i]);
	}

	temp_vec.emplace_back(size);
	index_vec.swap(temp_vec);
}


void f()
{
	std::vector<size_t> index_vec;
	index_vec.emplace_back(0);
	for (size_t i = 0; i < size - 1; i++)
	{
		if (p_a[i] > p_a[i + 1])
		{
			index_vec.emplace_back(i + 1);
		}
	}
	index_vec.emplace_back(size);


	// "cnt" is the num of piece
	size_t cnt = (index_vec.size() - 1);

	while (cnt > 1)
	{
		for (size_t i = 0, j = 0; j < cnt / 2; j++)
		{
			merge<int32_t>(index_vec[i], index_vec[i + 1], index_vec[i + 2]);
			i += 2;
		}

		g(index_vec);
		cnt = index_vec.size() - 1;
	}
}


int main(int argc, char *argv[])
{
	std::cout << "size = ";
	std::cin >> size;

	p_a = new int32_t[size];

	std::cout << "source[" << size << "] : ";
	for (size_t i = 0; i < size; i++)
	{
		std::cin >> p_a[i];
	}

	std::clock_t start = std::clock();
	f();
	std::clock_t end = std::clock();

	std::cout << "result[" << size << "] : ";
	for (size_t i = 0; i < size; i++)
	{
		std::cout << p_a[i] << " ";
	}

	std::cout << "(" << (end - start) << "ms)";

	delete[] p_a;
}