#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

template<typename ValueType, typename WeightType, typename NumType>
void g(std::vector<std::vector<ValueType>>& dp, WeightType C, NumType n)
{
	for (NumType i = 0; i <= n; i++)
	{
		dp.emplace_back(C + 1, 0);
	}
}

template<typename ValueType, typename WeightType, typename NumType>
void f(std::vector<std::vector<ValueType>> &dp, WeightType C, NumType n, std::vector<WeightType> &w, std::vector<ValueType> &v)
{
	for (NumType i = 1; i <= n; i++)
	{
		for (WeightType j = 1; j <= C; j++)
		{
			if (w[i] > j)
			{
				dp[i][j] = dp[i - 1][j];
				continue;
			}

			dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
		}
	}
}

int main()
{
	std::uint32_t C, n;

	std::cout << "C = ";
	std::cin >> C;
	std::cout << "n = ";
	std::cin >> n;

	std::vector<std::uint32_t> w_vec, v_vec;

	std::cout << "v[" << n << "] : ";
	v_vec.emplace_back(0);
	for (std::uint32_t i = 0; i < n; i++)
	{
		std::uint32_t v;
		std::cin >> v;
		v_vec.emplace_back(v);
	}

	std::cout << "w[" << n << "] : ";
	w_vec.emplace_back(0);
	for (std::uint32_t i = 0; i < n; i++)
	{
		std::uint32_t w;
		std::cin >> w;
		w_vec.emplace_back(w);
	}

	std::vector<std::vector<std::uint32_t>> dp;
	g(dp, C, n);

	f(dp, C, n, w_vec, v_vec);

	std::cout << "dp[" << n << "][" << C << "] = " << dp[n][C] << std::endl;
}