#define _CRT_SECURE_NO_WARNINGS

constexpr auto ques_path = "E:/LightDiagram/Test/data";

#include<LightDiagram.h>

using namespace std;
using namespace ld;

class Solution {
public:
    int minMovesToCaptureTheQueen(int r1, int r2, int b1, int b2, int q1, int q2) {
        return 2 - 
            ((r1 == q1 && 
                (r1 != b1 || 
                    !((b2 > r2) != (b2 > q2)))) || 
                (r2 == q2 && 
                    (r2 != b2 || 
                        !((b1 > r1) != (b1 > q1)))) ||
                (b1 - q1 == b2 - q2 && 
                    (b1 - r1 != b2 - r2 ||
                        !((r1 > b1) != (r1 > q1)))) ||
                (b1 - q1 == q2 - b2 &&
                    (b1 - r1 != r2 - b2 ||
                        !((r1 > b1) != (r1 > q1)))));
    }
};


template<typename ANSIO>
void solve(ANSIO& anss)
{
    Solution core;
    auto result = core.minMovesToCaptureTheQueen(
        next<int>(cin),
        next<int>(cin),
        next<int>(cin),
        next<int>(cin),
        next<int>(cin),
        next<int>(cin)
    );
    check_ans(result);
}

//try_solve_io_ques("");

struct int_conter
{
    easy_init(value);
    declare_binding_instance(int, value);
};

int main()
{
    declare_global_binding_instance(int_conter, conter);
    auto&& first = binding(conter->value, conter, 5);
    cout << conter->value.get_ref() << endl;
}
