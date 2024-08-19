#include<Math/Graph.h>
using namespace std;

#pragma region dijkstra

namespace ld
{
    namespace math
    {
        namespace graph
        {
            // graph是一个邻接列表
            /*
            void dijkstra(int s, _In_opt_ std::vector<std::vector<Edge>>& graph, _In_opt_ std::vector<Index_Type>& dist)
            {
                int n = graph.size();
                dist.assign(n, std::numeric_limits<Weight_Type>::max());
                std::priority_queue<std::pair<Weight_Type, Index_Type >, std::vector<pair<Weight_Type, Index_Type>>, std::greater<pair<Weight_Type, Index_Type>>> pq;

                dist[s] = 0;
                pq.push({ 0, s });

                while (!pq.empty())
                {
                    auto u = pq.top().second;
                    auto d = pq.top().first;
                    pq.pop();

                    if (d != dist[u])
                    {
                        continue;
                    }

                    for (auto& e : graph[u])
                    {
                        auto v = e.to;
                        auto w = e.weight;

                        if (dist[u] + w < dist[v])
                        {
                            dist[v] = dist[u] + w;
                            pq.push({ dist[v], v });
                        }
                    }
                }
            }
            */
        }
    }
}

#pragma endregion


