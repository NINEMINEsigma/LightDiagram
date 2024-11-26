#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

template<typename T, typename Q>
decltype(auto) Max(T&& first, Q&& second)
{
    return first > second ? first : second;
}
template<typename T, typename Q>
decltype(auto) Min(T&& first, Q&& second)
{
    return first < second ? first : second;
}
template<typename T, typename ...Args>
decltype(auto) Max(T&& first, T&& second, Args&&... args)
{
    return Max(Max(std::forward<T>(first), std::forward<T>(second)), std::forward<Args>(args)...);
}
template<typename T, typename ...Args>
decltype(auto) Min(T&& first, T&& second, Args&&... args)
{
    return Min(Min(std::forward<T>(first), std::forward<T>(second)), std::forward<Args>(args)...);
}

using namespace std;

short dp[10010][10010];

int main()
{
    int t, k;
    cin >> t >> k;
    vector<int> taskTimes(t);
    for (auto& item : taskTimes)
    {
        cin >> item;
    }
    // 前缀和数组
    vector<int> prefixSum(t + 1, 0);
    for (int i = 1; i <= t; ++i)
    {
        prefixSum[i] = prefixSum[i - 1] + taskTimes[i - 1];
    }

    // 动态规划数组
    for (int j = 0; j <= k; ++j)
    {
        dp[0][j] = 0;
    }

    // 填充动态规划数组
    for (int i = 1; i <= t; ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            for (int p = 0; p < i; ++p)
            {
                dp[i][j] = Min(dp[i][j], dp[p][j - 1] + (prefixSum[i] - prefixSum[p]));
            }
        }
    }

    // 回溯任务分配
    vector<pair<int, int>> result(k, { 0, 0 });
    int i = t, j = k;
    while (j > 0)
    {
        for (int p = 0; p < i; ++p)
        {
            if (dp[i][j] == dp[p][j - 1] + (prefixSum[i] - prefixSum[p]))
            {
                result[j - 1] = { p + 1, i };
                i = p;
                break;
            }
        }
        --j;
    }

    // 格式化输出
    for (auto& [start, end] : result)
    {
        cout << to_string(start) + " " + to_string(end) + "\n";
    }
    return 0;
}
