#include<test.h>

using namespace ld::algorithm;

using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int>& nums) 
    {
        int m = nums[0];
        for (int i = 1; i < nums.size(); i++) 
        {
            nums[i] = max(nums[i], nums[i] + nums[i - 1]);
            m = max(m, nums[i]);
        }
        return m;
    }
};

int main()
{
	Solution s;
	vector<int> nums = { -2,1,-3,4,-1,2,1,-5,4 };
	auto a = s.maxSubArray(nums);
	cout << a;
}

