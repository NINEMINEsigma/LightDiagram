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
#define EdgePointerTo_Member_Name to
			/// <summary>
			/// VertexTy是节点类型
			/// EdgeTy是边类型,与节点类型相同或者是一个整数类型,否则需要包含一个size_t类型或者节点类型的成员(名称为EdgePointerTo_Member_Name)
			/// VertexNode是节点容器储存的类型,默认使用instance智能指针
			/// EdgeInsideLayer是边容器储存某个节点的边的类型,默认使用instance<vector>智能指针
			/// VertexVector是节点容器类型,必须能够使用operator[](size_t)读写
			/// EdgeMatrix是储存全部边的边容器,必须能够使用operator[](size_t)读写
			/// 
			/// 在进行各种搜索或者插入时,如果EdgeTy的类型是整数则会转换为size_t后作为顺序引索
			/// 如果EdgeTy的类型与节点类型一致则会搜索节点对应的顺序引索并使用
			/// 如果EdgeTy的类型是类类型则必须包含一个名称为EdgePointerTo_Member_Name的成员,类型为节点类型或可转换为size_t顺序引索的类型
			/// </summary>
			template<
				typename VertexTy, typename EdgeTy = size_t,
				typename VertexNode = instance<VertexTy>, typename EdgeInsideLayer = instance<std::vector<EdgeTy>>,
				typename VertexVector = std::vector<VertexNode>, typename EdgeMatrix = std::vector<EdgeInsideLayer>
			>
			_LF_C_API(Class) Graph
			{
				VertexVector vertexs;
				EdgeMatrix edges;
			public:
				using all_tag = type_list<VertexTy, EdgeTy, VertexNode, EdgeInsideLayer, VertexVector, EdgeMatrix>;

				//通过有序编号获得节点与边
				std::pair<VertexNode, EdgeInsideLayer> operator[](size_t index)
				{
					return std::make_pair(vertexs[index], edges[index]);
				}
				//通过节点获取边
				EdgeInsideLayer operator[](VertexVector index)
				{
					return edges[std::distance(vertexs.begin(), std::find(vertexs.begin(), vertexs.end(), index))];
				}
				std::pair<typename VertexVector::iterator, typename EdgeMatrix::iterator> add_vertex(VertexNode vertex, EdgeInsideLayer edgeslayer)
				{
					vertexs.insert(vertexs.end(), std::move(vertex));
					edges.insert(edges.end(), std::move(edgeslayer));
					return std::make_pair(--vertexs.end(), --edges.end());
				}
				operator const VertexVector& () const
				{
					return vertexs;
				}
				operator const EdgeMatrix& () const
				{
					return edges;
				}
				size_t size() const
				{
					if constexpr (if_func_exist(size) < decltype(vertexs), size_t() > )
					{
						return vertexs.size();
					}
					else
					{
						return std::distance(vertexs.begin(), vertexs.end());
					}
				}

				/// <summary>
				/// _VisitedContainer是以size_t引索的容器,对应相对index的节点,应保证其operator[](size_t)不会越界或赋值
				/// </summary>
				template<typename _VisitedContainer>
				void reachable(size_t start, _VisitedContainer& visited)
				{
					std::stack<size_t> q;
					q.push(start);
					visited[start] = 1;

					while (!q.empty())
					{
						size_t curr = q.top();
						q.pop();

						if constexpr (is_ld_instance_v<decltype(edges[0])>)
						{
							for (auto& neighbor : *edges[curr].get_ptr())
							{
								reachable_tool(start, visited, q, neighbor);
							}
						}
						else if constexpr (std::is_pointer_v<decltype(edges[0])>)
						{
							for (auto& neighbor : *edges[curr])
							{
								reachable_tool(start, visited, q, neighbor);
							}
						}
						else
						{
							for (auto& neighbor : edges[curr])
							{
								reachable_tool(start, visited, q, neighbor);
							}
						}
					}
				}

				/// <summary>
				/// _VisitedContainer是以size_t引索的容器,对应相对index的节点,应保证其operator[](size_t)不会越界或赋值
				/// _Pr是谓词,用于判断边能否经过,其具有一个操作符(在这个Graph模板类的视角)
				/// bool operator()(const decltype(*this)&,const std::remove_ref<decltype(edges[0][0])>&)
				/// </summary>
				template<typename _VisitedContainer,typename _Pr>
				void reachable(size_t start, _VisitedContainer& visited, const _Pr& predicate)
				{
					std::stack<size_t> q;
					q.push(start);
					visited[start] = 1;

					while (!q.empty())
					{
						size_t curr = q.top();
						q.pop();

						if constexpr (is_ld_instance_v<decltype(edges[0])>)
						{
							for (auto& neighbor : *edges[curr].get_ptr())
							{
								if (predicate(*this, neighbor))
									reachable_tool(start, visited, q, neighbor);
							}
						}
						else if constexpr (std::is_pointer_v<decltype(edges[0])>)
						{
							for (auto& neighbor : *edges[curr])
							{
								if (predicate(*this, neighbor))
									reachable_tool(start, visited, q, neighbor);
							}
						}
						else
						{
							for (auto& neighbor : edges[curr])
							{
								if (predicate(*this, neighbor))
									reachable_tool(start, visited, q, neighbor);
							}
						}
					}
				}
			private:
				template<typename _InsideVec,typename _VisitedContainer>
				inline void reachable_tool(const size_t& start, _VisitedContainer& visited, std::stack<size_t>& q, _InsideVec& neighbor)
				{
					if constexpr (std::is_integral_v<typename generate_full_decay_typen<_InsideVec>::origin>)
					{
						visited[(size_t)neighbor] = 1;
					}
					else if constexpr (std::is_same_v<std::decay_t<_InsideVec>, VertexTy>)
					{
						visited[
							std::distance(
								vertexs.begin(),
								std::find(vertexs.begin(), vertexs.end(), neighbor))
						] = 1;
					}
					else 
					{
						visited[
							std::distance(
								vertexs.begin(),
								std::find(vertexs.begin(), vertexs.end(), neighbor.EdgePointerTo_Member_Name))
						] = 1;
					}
				}
			};
		}
	}
}

#endif // !__FILE_GRAPH
