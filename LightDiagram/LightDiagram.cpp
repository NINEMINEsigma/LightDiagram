#include "LightDiagram.h"

function_base::function_bases_type function_base::function_bases;


ld_test::ld_test()
{
	std::cout << "ld test awake successful\n";
}

namespace ld
{
	//virtual empty functions
	undering::~undering() {}
	i_any_architecture::~i_any_architecture() {}

}
