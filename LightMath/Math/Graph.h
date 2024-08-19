#ifndef __FILE_GRAPH
#define __FILE_GRAPH

#include <LightDiagram.h>
#include <Math/MathConfig.h>
#include <boost/algorithm/algorithm.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <queue>

namespace ld
{
	namespace math
	{
		namespace graph
		{
			template<
				typename VertexTy, typename EdgeTy,
				typename VertexNode = instance<VertexTy>, typename EdgeInsideLayer = instance<std::vector<EdgeTy>>,
				typename VertexVector = std::vector<VertexNode>, typename EdgeMatrix = std::vector<EdgeInsideLayer>
			>
			_LF_C_API(Class) Graph
			{
				VertexVector vertexs;
				EdgeMatrix edges;
			public:
				std::pair<VertexNode, EdgeInsideLayer> operator[](size_t index)
				{
					return std::make_pair < vertexs[index], edges[index]);
				}
				EdgeInsideLayer operator[](typename VertexVector::iterator index)
				{
					return edges[std::distance(vertexs.begin(), index)];
				}
				std::pair<typename VertexVector::iterator, typename EdgeMatrix::iterator> add_vertex(VertexNode vertex, EdgeInsideLayer edgeslayer)
				{
					vertexs.insert(vertexs.end(), vertex);
					edges.insert(edges.end(), edgeslayer);
					return std::make_pair(--vertexs.end(), --edges.end());
				}
			};
		}
	}
}

#endif // !__FILE_GRAPH
