#include <vector>
#include <memory>
#include <array>
#include <iostream>

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
		}

		rw_ -= vec_w_[i];

		if (cw_ + vec_w_[i] < s1w_)
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
		vec_flag_->resize(vec_w_.size());
		BackTrack(0);
		return rw_ - bw_ < s2w_;
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
	size_t n = 0;
	std::cin >> n ;
	
	Solution<std::uint32_t> sltn;
	sltn.vec_w_.resize(n);

	for (auto &w : sltn.vec_w_)
	{
		std::cin >> w;
	}

	std::cin >> sltn.s1w_ >> sltn.s2w_;
	return 0;
}