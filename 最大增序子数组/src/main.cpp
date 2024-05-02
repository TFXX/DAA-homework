#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

template<typename ValueType, typename LengthType, typename DirectType>
void g(std::vector<std::vector<LengthType>> &dp, std::vector<std::vector<DirectType>>& next, std::vector<ValueType>& s1, std::vector<ValueType>& s2)
{
	for (LengthType i = 0; i < s1.size(); i++)
	{
		dp.emplace_back(s2.size(), 0);
		next.emplace_back(s2.size(), 0);
	}
}

template<typename ValueType, typename LengthType, typename DirectType>
void f(std::vector<std::vector<LengthType>> &dp, std::vector<std::vector<DirectType>>& next, std::vector<ValueType> &s1, std::vector<ValueType> &s2)
{
	for (size_t i = 1; i < s1.size(); i++)
	{
		for (size_t j = 1; j < s2.size(); j++)
		{
			if (s1[i] == s2[j])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
				next[i][j] = 2; // up-left
				continue;
			}
			
			if (dp[i - 1][j] >= dp[i][j - 1])
			{
				dp[i][j] = dp[i - 1][j];
				next[i][j] = 3; // up
			}
			else
			{
				dp[i][j] = dp[i][j - 1];
				next[i][j] = 1; // lefy
			}
		}
	}
}

template<typename ValueType, typename DirectType>
void h(std::vector<std::vector<DirectType>> &next, std::stack<ValueType> &ans, std::vector<ValueType>& s1, std::vector<ValueType>& s2)
{
	for (size_t i = s1.size() - 1, j = s2.size() - 1; j > 0 && i > 0;)
	{
		switch (next[i][j])
		{
		case 2:
			ans.push(s1[i]);	// up-left
			i--;
			j--;
			break;
		case 1:
			j--;	// left
			break;
		case 3:
			i--;	// up
			break;
		default:
			abort();
		}
	}
}

int main(int argc, char **argv)
{
	std::cout << "n = ";
	std::uint32_t n;
	std::cin >> n;

	std::vector<int32_t> src_vec, s1_vec, s2_vec;

	std::cout << "array[" << n << "] : ";
	for (std::uint32_t i = 0; i < n; i++)
	{
		std::int32_t v;
		std::cin >> v;
		src_vec.emplace_back(v);
	}

	s1_vec.emplace_back(0);
	for (auto v : src_vec)
	{
		s1_vec.emplace_back(v);
	}

	std::sort(src_vec.begin(), src_vec.end());

	s2_vec.emplace_back(0);
	for (auto v : src_vec)
	{
		s2_vec.emplace_back(v);
	}

	std::vector<std::vector<std::uint32_t>> dp, next;
	g(dp, next, s1_vec, s2_vec);
	f(dp, next, s1_vec, s2_vec);

	std::stack<std::int32_t> ans;
	h(next, ans, s1_vec, s2_vec);

	std::cout << "LCS[" << dp[s1_vec.size() - 1][s2_vec.size() - 1] << "] : ";
	while (!ans.empty())
	{
		std::cout << ans.top() << " ";
		ans.pop();
	}
}