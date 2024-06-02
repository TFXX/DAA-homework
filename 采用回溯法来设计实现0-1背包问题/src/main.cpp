#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <stack>
#include <algorithm>

template<typename weight_type, typename value_type>
value_type MaxValue(std::vector<weight_type> vec_w, std::vector<value_type> vec_v, const size_t length, const weight_type bag_capacity, std::shared_ptr<std::stack<size_t>> p_stack_snapshot = nullptr)
{
	// a bag and its status
	std::stack<size_t> stack_bag;
	weight_type w = 0;
	value_type v = 0;

	value_type max = 0;

	for (size_t i = 0 ; i < length; i++)
	{
		// 背包尝试放进第i个物品
		if (w + vec_w[i] <= bag_capacity)
		{
			stack_bag.push(i);
			w += vec_w[i];
			v += vec_v[i];
		}

		// if the item is the last of them, it make a situation (a solution of question)
		if (length - 1 != i)
		{
			continue;
		}

		// if current situation is a better solution, update max(best solution)
		max = (max < v)?(v):(max);

		if (nullptr != p_stack_snapshot)
		{
			*p_stack_snapshot = stack_bag;
		}

		// pop the last item from bag
		bool b_empty = false;
		do{
			if(stack_bag.empty())
			{
				b_empty = true;
				break;
			}
			i = stack_bag.top();
			stack_bag.pop();
			w -= vec_w[i];
			v -= vec_v[i];
		}while (length - 1 == i);

		if (b_empty)
		{
			break;
		}
	}

	return max;
}

int main(int argc, char **argv)
{
	size_t n;
	std::cout << "请输入物品数量.\n>";
	std::cin >> n;

	std::vector<int32_t> vec_w, vec_v;

	std::cout << "请输入" << "个物品相应的重量.\n>";
	int32_t w;
	for (size_t i = 0 ; i < n; i++)
	{
		std::cin >> w;
		vec_w.push_back(w);
	}
	
	std::cout << "请输入" << "个物品相应的价值.\n>";
	int32_t v;
	for (size_t i = 0; i < n; i++)
	{
		std::cin >> v;
		vec_v.push_back(v);
	}

	int32_t c;
	std::cout << "请输入背包容量.\n>";
	std::cin >> c;

	std::shared_ptr<std::stack<size_t>> p_stack_snapshot= std::make_shared<std::stack<size_t>>();
	
	std::cout << MaxValue(vec_w, vec_v, n, c, p_stack_snapshot) << "(";

	while (!p_stack_snapshot->empty())
	{
		std::cout << p_stack_snapshot->top() << ", ";
		p_stack_snapshot->pop();
	}

	std::cout << ")";
	
	return 0;
}