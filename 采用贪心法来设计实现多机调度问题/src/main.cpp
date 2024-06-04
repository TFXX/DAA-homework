#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <memory>

template <typename duration_type>
struct Job{
public:
	size_t index;
	duration_type duration;
};

template <typename duration_type>
struct Machine{
	size_t index_;
	duration_type duration_;
};

template<typename duration_type>
duration_type MaxDuration(std::vector<Job<duration_type>> &vec_jobs, std::vector<Machine<duration_type>> &vec_m, std::shared_ptr<std::vector<std::tuple<size_t, size_t, duration_type>>> p_snapshot = nullptr )
{
	std::sort(vec_jobs.begin(), vec_jobs.end(), [](auto &j1, auto &j2){
		return j1.duration > j2.duration;
	});

	for (auto &j : vec_jobs)
	{
		auto iter_min = vec_m.begin();
		for (auto iter = vec_m.begin(); iter != vec_m.cend(); iter++)
		{
			if (iter->duration_ < iter_min->duration_)
			{
				iter_min = iter;
			}
		}

		iter_min->duration_ += j.duration;
		
		if (p_snapshot)
		{
			p_snapshot->emplace_back(j.index, iter_min->index_, iter_min->duration_);
		}
	}

	auto p_max = std::max_element(vec_m.cbegin(), vec_m.cend(), [](auto &m1, auto &m2){
		return m1.duration_ < m2.duration_;
	});

	return p_max->duration_;
}
int main(int, char **)
{
	std::cout << "请输入作业数量.\n>";

	size_t n = 0;
	std::cin >> n;

	std::vector<Job<uint32_t>> vec_j(n);

	std::cout << "请输入" << n << "个作业对应的时间.\n>";

	size_t i = 0;
	for (auto &j : vec_j)
	{
		j.index = i++;
		std::cin >> j.duration;
	}

	std::cout << "请输入机器数量.\n>";

	size_t m = 0;
	std::cin >> m;

	std::vector<Machine<uint32_t>> vec_m(m);
	i = 0;
	for (auto &m : vec_m)
	{
		m.index_ = i++;
		m.duration_ = 0;
	}

	std::shared_ptr<std::vector<std::tuple<size_t, size_t, uint32_t>>> p_snapshot = std::make_shared<std::vector<std::tuple<size_t, size_t, uint32_t>>>();

	std::cout << "最短完成时间：" << MaxDuration(vec_j, vec_m, p_snapshot) << '\n';
	std::sort(p_snapshot->begin(), p_snapshot->end(), [](auto &t1, auto &t2){
		return std::get<0>(t1) < std::get<0>(t2);
	});

	for (auto &t : *p_snapshot)
	{
		std::cout 
			<< "作业" << std::get<0>(t) 
			<< "分配到了机器" << std::get<1>(t) 
			<< "上，时间段的开始时间是" << std::get<2>(t) 
			<< "\n";
	}
	
	return 0;
}