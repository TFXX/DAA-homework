#include <vector>
#include <memory>
#include <array>
#include <iostream>
#include <numeric>

template<typename weight_type>
class Solution
{
public:
	void BackTrack(size_t i)
	{
		if (i >= vec_w_.size())
		{
			if (cw_ < bw_)
			{
				return;
			}

			bw_ = cw_;

			if (!p_snapshot)
			{
				return;
			}

			for (auto &v : *p_snapshot)
			{
				v.clear();
			}

			for (size_t i = 0 ; i < vec_flag_.size(); i++)
			{
				(*p_snapshot)[(vec_flag_[i] == 0)?(0):(1)].emplace_back(i);
			}

			return;
		}

		rw_ -= vec_w_[i];

		if (cw_ + vec_w_[i] <= s1w_)
		{
			vec_flag_[i] = 0;
			cw_ += vec_w_[i];
			BackTrack(i + 1);
			cw_ -= vec_w_[i];
			vec_flag_[i] = 1;
		}

		if (cw_ + rw_ > bw_)
		{
			vec_flag_[i] = 1;
			BackTrack(i + 1);
		}

		rw_ += vec_w_[i];
	}

	bool GetAnswer()
	{
		vec_flag_.resize(vec_w_.size());
		bw_ = 0;
		cw_ = 0;
		rw_ = std::accumulate(vec_w_.cbegin(), vec_w_.cend(), 0);
		BackTrack(0);
		return rw_ - bw_ <= s2w_;
	}
public:
	weight_type s1w_, s2w_;
	std::vector<weight_type> vec_w_;
	std::shared_ptr<std::array<std::vector<size_t>, 2>> p_snapshot = nullptr;
private:
	weight_type bw_, cw_, rw_;
	std::vector<size_t> vec_flag_;
};

int main(int argc, char **argv)
{
	std::cout << "请输入集装箱的数量.\n>";
	size_t n = 0;
	std::cin >> n ;
	
	Solution<std::uint32_t> sltn;
	sltn.vec_w_.resize(n);

	std::cout << "请输入" << n << "个集装箱对应的容量.\n>";

	for (auto &w : sltn.vec_w_)
	{
		std::cin >> w;
	}

	std::cout << "请按照顺序输入两艘船的容量.\n>";
	std::cin >> sltn.s1w_ >> sltn.s2w_;

	sltn.p_snapshot = std::make_shared<std::array<std::vector<size_t>, 2>>();

	if (sltn.GetAnswer())
	{
		std::cout << n << "个集装箱可以全部装入.\n";
	}
	else
	{
		std::cout << n << "个集装箱无法全部装入.\n";
	}


	std::cout << "船1：";
	for (auto i : (*sltn.p_snapshot)[0])
	{
		std::cout << i << ", ";
	}
	
	std::cout << "\n船2：";
	for (auto i : (*sltn.p_snapshot)[1])
	{
		std::cout << i << ", ";
	}

	std::cout << std::endl;
	return 0;
}