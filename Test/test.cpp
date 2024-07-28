
//#include "test.h"
#include<LightDiagram.h>

using namespace ld;
//using namespace std;
using namespace ld::container;

int main()
{
	int a[10] = { 0 };
	stack s(&a[10],&a[0],sizeof(int));
	std::cout << s.get_full_size();
	return 0;
}