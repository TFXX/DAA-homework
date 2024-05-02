#include <iostream>
#include <cstdint>
#include <cmath>

using namespace std;

uint32_t *a;
uint32_t l; 

struct Pos
{
	uint32_t x;
	uint32_t y;
};

void p()
{
	for (uint32_t i = 0; i < l; i++)
	{
		for (uint32_t j = 0; j < l; j++)
		{
			printf("%2u ", *(a + (i * l) + j));
		}

		printf("\n");
	}

	printf("\n");
}


uint32_t g_count = 1;

void h()
{
	g_count++;
}

void g(Pos &origin, Pos dirty)
{
	*(a + ((dirty.x) * l) + dirty.y) = g_count;
}

void f(Pos origin,  uint32_t k, Pos dirty)
{
	if (1 == k)
	{
		return ;
	}

	h();
	k = k/2;

	Pos origin2{origin.x + k, origin.y + k};
	if (dirty.x - origin.x < k && dirty.y - origin.y < k)
	{
		g(origin, {origin2.x - 1, origin2.y});
		g(origin, {origin2.x, origin2.y - 1});
		g(origin, {origin2.x, origin2.y});
		f(origin, k, dirty);

		f({ origin.x + k, origin.y }, k, { origin2.x, origin2.y - 1 });
		f({ origin.x, origin.y + k}, k, { origin2.x - 1, origin2.y });
		f({ origin.x + k, origin.y + k }, k, { origin2.x, origin2.y});

		return;
	}

	// up-right
	if (dirty.x - origin.x < k && dirty.y - origin.y>= k)
	{
		g(origin, { origin2.x, origin2.y});
		g(origin, { origin2.x, origin2.y - 1});
		g(origin, { origin2.x - 1, origin2.y - 1});
		f({origin.x, origin.y + k}, k, {dirty.x, dirty.y - k});
		
		f({ origin.x + k, origin.y }, k, { origin2.x, origin2.y - 1 });
		f({ origin.x, origin.y }, k, { origin2.x - 1, origin2.y - 1});
		f({ origin.x + k, origin.y + k }, k, { origin2.x, origin2.y });
		return;
	}

	// down-left
	if (dirty.x - origin.x >= k && dirty.y - origin.y < k)
	{
		g(origin, { origin2.x, origin2.y });
		g(origin, { origin2.x - 1, origin2.y });
		g(origin, { origin2.x - 1, origin2.y - 1 });
		f({ origin.x + k, origin.y }, k, { dirty.x - k, dirty.y });
		
		f({ origin.x, origin.y }, k, { origin2.x - 1, origin2.y - 1 });
		f({ origin.x, origin.y + k }, k, { origin2.x - 1, origin2.y });
		f({ origin.x + k, origin.y + k }, k, { origin2.x, origin2.y });
		return;
	}

	// down-right
	if (dirty.x - origin.x >= k && dirty.y - origin.y >= k)
	{
		g(origin, { origin2.x - 1, origin2.y - 1});
		g(origin, { origin2.x - 1, origin2.y });
		g(origin, { origin2.x, origin2.y - 1 });
		f({ origin.x + k, origin.y + k}, k, { dirty.x - k, dirty.y - k });
		
		f({ origin.x, origin.y }, k, { origin2.x - 1, origin2.y - 1 });
		f({ origin.x + k, origin.y }, k, { origin2.x, origin2.y - 1 });
		f({ origin.x, origin.y + k }, k, { origin2.x - 1, origin2.y });
		return;
	}
}


int main(int argc, char **argv)
{
	cout << "k = ";
	uint32_t k;
	cin >> k;
	k = 1 << k;
	l = k;
	a = new std::uint32_t[k * k]{ 0 };

	Pos origin{ 0, 0 }, dirty;

	cout << "dirty.x = ";
	cin >> dirty.x;
	dirty.x--;

	std::cout << "dirty.y = ";
	cin >> dirty.y;
	dirty.y--;

	g(origin, dirty);
	f(origin, k, dirty);

	p();
	
	delete[] a;
	return 0;
}