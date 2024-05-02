#include <iostream>
#include <optional>
#include <vector>

template<typename IndexType, typename ValueType>
std::optional<IndexType> f(const std::vector<ValueType> &a, ValueType v)
{
	IndexType l = 0, h = a.size() - 1;
	while (l <= h)
	{
		IndexType mid = (l + h) / 2;
		if (a[mid] > v)
		{
			h = mid - 1;
			continue;	
		}
		
		if (a[mid] < v)
		{
			l = mid + 1;
			continue;
		}

		for (IndexType i = mid; i > 0; i --)
		{
			if (a[i - 1] != v)
			{
				return i;
			}
		}

		return 0;
	}

	return std::nullopt;
}

int main(int argc, char **argv)
{
	std::cout << "size = ";
	size_t size;
	std::cin >> size;

	std::vector<uint32_t> num_vec;
	std::cout << "array[" << size << "] : ";
	for (size_t i = 0; i < size; i++)
	{
		uint32_t n;
		std::cin >> n;
		num_vec.emplace_back(n);
	}

	std::cout << "dest = ";
	std::uint32_t dest;
	std::cin >> dest;

	std::optional<uint32_t> res = f<size_t, uint32_t>(num_vec, dest);
	if (!res.has_value())
	{
		std::cout << -1;
		return 0;
	}

	std::cout << "array[" << *res << "] = " << num_vec[*res];

	return 0;
}