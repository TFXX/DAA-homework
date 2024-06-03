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

template<typename duration_type>
duration_type MaxDuration(std::vector<Job<duration_type>> &vec_jobs, const size_t machine_num, std::shared_ptr<std::vector<std::pair<size_t, size_t>>> p_snapshot = nullptr )
{
	std::sort(vec_jobs.begin(), vec_jobs.end(), [](Job<duration_type> &j1, Job<duration_type> &j2){
		return j1 > j2;
	});

	std::vector<duration_type> vec_duration_sum(machine_num, 0);

	for (auto &j : vec_jobs)
	{
		auto iter_min = vec_duration_sum;
		for (auto iter = vec_duration_sum.begin(); iter != vec_duration_sum.cend(); iter++)
		{
			if (*iter < *iter_min)
			{
				iter_min = iter;
			}
		}

		*iter_min += j.duration;
	}

	duration_type max_duration = vec_duration_sum.front();
	for (auto d : vec_duration_sum)
	{
		if (max_duration < d)
		{
			max_duration = d;
		}
	}

	return max_duration;
}
int main(int, char **)
{

	return 0;
}