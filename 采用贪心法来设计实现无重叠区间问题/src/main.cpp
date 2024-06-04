#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <memory>

struct Interval
{
public:
	std::int32_t left_, right_;
};

std::size_t erase_overlap_intervals(std::vector<Interval> &vec_i, std::shared_ptr<std::vector<Interval>> p_vec_snapshot = nullptr)
{
	std::sort(vec_i.begin(), vec_i.end(), [](Interval &i1, Interval &i2){
		return i1.right_ < i2.right_;
	});

	// initiliaze
	std::int32_t last_right = vec_i.front().left_;
	std::size_t num = 0;

	for (auto &i : vec_i)
	{

		// overlap 
		if (i.left_ < last_right)
		{
			num += 1;

			if (p_vec_snapshot)
			{
				p_vec_snapshot->emplace_back(i);
			}
			continue;
		}

		last_right = i.right_;
	}

	return num;
}

int main(int, char**)
{
	std::cout << "请输入活动的数量.\n>";
	
	size_t n;
	
	std::cin >> n;

	std::vector<Interval> vec_i;

	std::cout << "请输入" << n << "个活动对应的开始时间\n>";
	

	Interval temp;
	for (size_t i = 0; i < n; i++)
	{
		std::cin >> temp.left_;
		vec_i.push_back(temp);
	}

	std::cout << "请输入" << n << "个活动对应的结束时间\n>";
	
	for (auto &i : vec_i)
	{
		std::cin >> i.right_;
	}

	std::shared_ptr<std::vector<Interval>> p_snapshot = std::make_shared<std::vector<Interval>>();
	size_t ans = erase_overlap_intervals(vec_i, p_snapshot);

	std::cout << "需要移除" << ans << "个区间:(";

	for (auto &i : *p_snapshot)
	{
		std::cout << "[" << i.left_ <<"," << i.right_ <<"], ";
	}

	std::cout << ")" << std::endl;

	return 0;
}