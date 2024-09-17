#include<test.h>

using namespace ld::algorithm;

using namespace std;

auto ___auto___ = []()
	{
		cin.tie(nullptr)->sync_with_stdio(false), cout.tie(nullptr);
		return 0;
	};

constexpr char wall = '#';
constexpr char able = '+';
constexpr char horizontal = '-';
constexpr char vertical = '|';
constexpr char onlydown = '.';
constexpr char start = 'S';
constexpr char target = 'T';

bool check_path(const char& current, const char& next, const int& dx, const int& dy)
{
	if (next == wall)
		return false;
	switch (current)
	{
	case wall:
		return false;
	case horizontal:
		return dy == 0;
	case vertical:
		return dx == 0;
	case onlydown:
		return dy == 1;
	default:
		return true;
	}
}

int main()
{
	//init
	int r, c;
	cin >> r >> c;
	vector<vector<char>> mapper(r, vector<char>(c));
	int startx, starty, targetx, targety;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			char current;
			cin >> current;
			mapper[i][j] = current;
			if (current == start)
			{
				starty = i;
				startx = j;
			}
			else if (current == target)
			{
				targety = i;
				targetx = j;
			}
		}
	}
	//dfs
	auto start_record = Get_DFS_Matrix_4<
		int, vector, char, function<bool(const char&, const char&, const int&, const int&)>
	>(startx, starty, mapper, function(check_path));
	auto target_record = Get_rDFS_Matrix_4<
		int, vector, char, function<bool(const char&, const char&, const int&, const int&)>
	>(targetx, targety, mapper, function(check_path));
	//check
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (start_record[i][j] && target_record[i][j])
				cout << ConsoleColor::Yellow << mapper[i][j];
			else if (start_record[i][j] && !target_record[i][j])
				cout << ConsoleColor::Green << mapper[i][j];
			else if (!start_record[i][j] && target_record[i][j])
				cout << ConsoleColor::Red << mapper[i][j];
			else
				cout << ConsoleColor::None << mapper[i][j];
			cout << " ";
		}
		cout << "\n";
	}
	cout << ConsoleColor::None;
	//result
	int res = 0;
	if (start_record[targety][targetx])
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (start_record[i][j] && !target_record[i][j]) res++; 
			}
		}
		cout << res;
	}
	else cout << "I'm stuck!";
}