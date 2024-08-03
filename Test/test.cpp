
//#include "test.h"
#include<LightDiagram.h>

using namespace ld;
//using namespace std;
using namespace ld::container;

int main()
{
	int a[10] = { 99,99 };
	ld::accu_container_instance<int,ld::container::accurate::arrayX<int>> s(10);
	int c = 0;
	for (auto& i : *s.get_ptr())
	{
		i = c;
		c++;
	}
	for (auto& i : *s.get_ptr())
	{
		std::cout << i << "\n";
	}
}