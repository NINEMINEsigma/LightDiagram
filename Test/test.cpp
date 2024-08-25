#include<test.h>
#include<Math/Graph.h>

using namespace ld::math::graph;
using namespace Eigen;
using namespace llm::Spark;

string allstr;

int main()
{
	console.LogMessage("start");
	bitmap_instance bitmap(900, 900);
	bitmap.DrawBitmapTriangle(20, 20, 200, 200, 200, 20, 15, 1, 0, 0, bitmap_instance::SetBitmapPixelType::overlay);
	bitmap.SaveBitMap("D:/Testing Dir/test.bmp");
	console.LogMessage("end");
}


