#include<test.h>

using namespace ld::algorithm;

using namespace std;

auto ___auto___ = []()
	{
		cin.tie(nullptr)->sync_with_stdio(false), cout.tie(nullptr);
		return 0;
	};

using namespace std;

using _CurTy = char;
constexpr _CurTy wall = 'X';
constexpr _CurTy able = '+';
constexpr _CurTy start = 'S';
constexpr _CurTy target = 'C';

bool check_path(const _CurTy& currnet, const _CurTy& next, const int& dx, const int& dy)
{
    return next != wall;
}


int sol() 
{
    //init
    int n, m, k, d;
    cin >> n >> m >> k >> d;
    vector<vector<char>> mapper(n, vector<char>(n, able));
    vector<vector<int>> values(n, vector<int>(n, 0));
    vector<pair<int, int>> starts;
    set<pair<int, int>> ends;
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        y--;
        x--;
        mapper[y][x] = start;
        starts.push_back(make_pair(x, y));
    }
    while (k--)
    {
        int x, y, c;
        cin >> x >> y >> c;
        y--;
        x--;
        mapper[y][x] = target;
        values[y][x] += c;
        ends.insert(make_pair(x, y));
    }
    while (d--)
    {
        int x, y;
        cin >> x >> y;
        y--;
        x--;
        mapper[y][x] = wall;
    }
    //bfs
    auto dis_record = Get_BFS_Matrix_4<
        vector<pair<int, int>>,vector,char,decltype(function(check_path)),int
    >(starts, mapper, function(check_path));
    //check
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            auto current = mapper[i][j];
            if (current == wall)
                cout << ConsoleColor::Red << current;
            else if (current == start)
                cout << ConsoleColor::Green << current;
            else if (current == target)
                cout << ConsoleColor::Yellow << dis_record[i][j];
            else
                cout << ConsoleColor::None << dis_record[i][j];
            cout << " ";
        }
        cout << "\n";
    }
    cout << ConsoleColor::None;
    //result
    size_t result = 0;
    for (auto&& [x, y] : ends)
    {
        result += values[y][x] * dis_record[y][x];
    }
    cout << result << endl;
    return 0;
}

#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define inf 0x3f3f3f3f3f3f3f3f
#define rep(i,a,b) for(auto i=a;i<=b;++i)
#define bep(i,a,b) for(auto i=a;i>=b;--i)
#define lowbit(x) x&(-x)
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define PI acos(-1)
#define pb push_back
#define eps 1e-6
const int mod = 1e9 + 7;
const int MOD = 1e4 + 7;
const int N = 4e5 + 10;
const int M = 1111;
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };
int dxy[][2] = { {0,1},{1,0},{1,1},{-1,1} };
using namespace std;

bool vis[M][M];
int dis[M][M];
int con[M * M][3];
queue<PII> que;

int n, m, k, d;

void BFS() {
    while (que.size()) {
        PII top = que.front();
        que.pop();
        rep(i, 0, 3) {
            int x = top.first + dx[i];
            int y = top.second + dy[i];
            if (vis[x][y] == 1) {
                if (dis[x][y] > dis[top.first][top.second] + 1) {
                    dis[x][y] = dis[top.first][top.second] + 1;
                    que.push({ x,y });
                }
            }
        }
    }
}

void solve() {
    memset(dis, INF, sizeof(dis));
    cin >> n >> m >> k >> d;
    rep(i, 1, n) {
        rep(j, 1, n) {
            vis[i][j] = 1;
        }
    }
    while (m--) {
        int x, y;
        cin >> x >> y;
        que.push({ x,y });
        dis[x][y] = 0;
    }
    //rep(i, 0, k - 1) cin >> con[i][0] >> con[i][1] >> con[i][2];
    map<int, map<int, int>> values;
    while (k--)
    {
        int x, y, c;
        cin >> x >> y >> c;
        values[x][y] += c;
    }
    while (d--) {
        int x, y;
        cin >> x >> y;
        vis[x][y] = 0;
    }
    BFS();
    //check
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (vis[j][i]==0)
                cout << ConsoleColor::Red << wall;
            else
                cout << ConsoleColor::None << dis[j][i];
            cout << " ";
        }
        cout << "\n";
    }
    cout << ConsoleColor::None;
    //result
    ll ans = 0;
    //while (k > 0) 
    //{
    //    k--;
    //    ans += dis[con[k][0]][con[k][1]] * con[k][2];
    //}
    for (auto&& [x, item] : values)
    {
        for (auto&& [y, count] : item)
        {
            ans += dis[x][y] * count;
        }
    }
    cout << ans << endl;
}

int main() 
{
    sol();
    return 0;
}