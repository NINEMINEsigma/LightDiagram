#define _CRT_SECURE_NO_WARNINGS

#define is_monitor_the_constructor_of_anyclass false
#define binding_instance_manager

#include<LightDiagram.h>

using namespace ld;
using namespace ld::resources;
using namespace std;

sync_with_stdio_false(__auto__);

//  ∑| x − xc | + | i − yc |
// i=l
int calc(int x, int l, int r, int k)
{
	int xc = (k + 1) / 2, yc = (k + 1) / 2, sum = 0;
	for (int i = l; i <= r; i++)
		sum += abs(x - xc) + abs(i - yc);
	return sum;
}

vector<int> getonce(const int& m, const int& k, vector<int>& L, vector<int>& R)
{
	scanf("%d", &m);
	int x = 0, l = 0, r = 0;
	int s = numeric_limits<int>::max();
	bool is_s_init = false;
	for (int i = 1; i <= k; i++)
	{
		int temp;
		if (L[i] == R[i])
		{
			int ka, ma;
			do
			{
				if (m & 1)
				{
					ka = (k + 1) / 2;
					ma = (m + 1) / 2;
					temp = calc(i, ka - ma + 1, ka - ma + m, k);
					if (temp < s)
					{
						s = temp;
						is_s_init = true;
						x = i;
						l = ka - ma + 1;
						r = ka - ma + m;
					}
					else if (temp == s && i < x)
					{
						x = i;
						l = ka - ma + 1;
						r = ka - ma + m;
					}
					else if (temp == s && i == x && (k + 1) / 2 - (m + 1) / 2 + 1 < l)
					{
						l = ka - ma + 1;
						r = ka - ma + m;
					}
				}
				else
				{
					ka = (k + 1) / 2;
					ma = m / 2;
					temp = calc(i, ka - ma, ka + ma - 1, k);
					if (temp < s)
					{
						s = temp;
						is_s_init = true;
						x = i;
						l = ka - ma;
						r = ka + ma - 1;
					}
					else if (temp == s && i < x)
					{
						x = i;
						l = ka - ma;
						r = ka + ma - 1;
					}
					else if (temp == s && i == x && (k + 1) / 2 - m / 2 < l)
					{
						l = ka - ma;
						r = ka + ma - 1;
					}
				}

			} while (false);
		}
		if (L[i] >= m)
		{
			temp = calc(i, L[i] - m + 1, L[i], k);
			if (temp < s)
			{
				s = temp;
				is_s_init = true;
				x = i;
				l = L[i] - m + 1;
				r = L[i];
			}
			else if (temp == s && i < x)
			{
				x = i;
				l = L[i] - m + 1;
				r = L[i];
			}
			else if (temp == s && i == x && L[i] - m + 1 < l)
			{
				l = L[i] - m + 1;
				r = L[i];
			}
		}
		if (R[i] + m - 1 <= k)
		{
			temp = calc(i, R[i], R[i] + m - 1, k);
			if (temp < s)
			{
				s = temp;
				is_s_init = true;
				x = i;
				l = R[i];
				r = R[i] + m - 1;
			}
			else if (temp == s && i < x)
			{
				x = i;
				l = R[i];
				r = R[i] + m - 1;
			}
			else if (temp == s && i == x && R[i] < l)
			{
				l = R[i];
				r = R[i] + m - 1;
			}
		}
	}
	if (is_s_init == false)
	{
		return { -1 };
	}
	L[x] = min(L[x], l - 1); R[x] = max(R[x], r + 1);
	return { x, l, r };
}

void solve()
{
	//init
	int n, k;
	auto&& _temp = cin;
	while (cin >> n)
	{
		cin >> k;
		vector<int> L(k + 10, 0), R(k + 10, 0);
		for (int i = 1; i <= k; i++)
			L[i] = R[i] = (k + 1) / 2;
		while (n--)
		{
			for (auto&& i : getonce(next<int>(cin), k, L, R))
			{
				cout << i << " ";
			}
			cout << "\n";
		}
	}
}

int main()
{
	GlobalExceptionInit
		for (int i = 1, e = 4; i <= e; i++)
		{
			console.LogMessage(to_string(i));
			string path = "D:/CCSP/2016/ticket_chooser/data/"; path += to_string(i) + ".in";
			tool_file input(path);
			input.redirect_cin();
			solve();
			cin.sync();
			cin.clear();
			cout << "------------------------------------------" << endl;
		}
	GlobalExcpetionApply
}
