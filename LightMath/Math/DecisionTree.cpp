#include<Math/DecisionTree.h>

using namespace std;

namespace ld
{
	namespace math
	{
		TreeNode* CreateTreeNode(string value)
		{
			TreeNode* pNode = new TreeNode();
			pNode->m_sAttribute = value;
			return pNode;
		}

		bool FindNode(TreeNode* pRoot, string& item)
		{
			if (pRoot->m_sAttribute == item)
				return true;

			bool found = false;

			for (auto i = pRoot->m_vChildren.begin(); found == false && i < pRoot->m_vChildren.end(); i++)
			{
				found = FindNode(*i, item);
			}

			return found;
		}

		void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild)
		{
			if (pParent != nullptr)
			{
				pParent->m_vChildren.push_back(pChild);
			}
		}

		void PrintTreeNode(TreeNode* pNode)
		{
			if (pNode != nullptr)
			{
				printf("value of this node is: %d.\n", atoi(pNode->m_sAttribute.c_str()));
				printf("its children is as the following:\n");
				std::vector<TreeNode*>::iterator i = pNode->m_vChildren.begin();
				while (i < pNode->m_vChildren.end())
				{
					if (*i != nullptr)
						printf("%s\t", (*i)->m_sAttribute.c_str());
					++i;
				}
				printf("\n");
			}
			else
			{
				printf("this node is null.\n");
			}

			printf("\n");
		}

		void PrintTree(TreeNode* pRoot)
		{
			PrintTreeNode(pRoot);

			if (pRoot == nullptr)
				return;

			for (auto i = pRoot->m_vChildren.begin(); i < pRoot->m_vChildren.end(); i++)
			{
				PrintTree(*i);
			}
		}

		void DestroyTree(TreeNode* pRoot)
		{
			if (pRoot == nullptr)
				return;

			for (auto i = pRoot->m_vChildren.begin(); i < pRoot->m_vChildren.end(); i++)
			{
				DestroyTree(*i);
			}
			delete pRoot;
		}

		/*******树的构造*******/
		DecisionTree::DecisionTree() 
		{
			attriNum = 0;
		}
		vector<vector<string>>& DecisionTree::getInfos()
		{
			return infos;
		}
		vector<DecisionTree::attributes*>& DecisionTree::getStatTree()
		{
			return statTree;
		}

		int DecisionTree::pretreatment(string filename, set<int>& readLineNum, vector<int>& readClumNum)
		{
			return 0;
		}

		double DecisionTree::info_D(int deciNum, int sum)
		{
			double pi = (double)deciNum / (double)sum;
			double result = 0.0;
			if ((1.0 - pi) < 0.000001 || (pi - 0.0) < 0.000001)
			{
				return result;
			}
			result = pi * (log(pi) / log((double)2)) + (1 - pi) * (log(1 - pi) / log((double)2));
			return -result;
		}

		double DecisionTree::Info_attr(map<string, attrItem*>& attriItem, double& splitInfo, int lineNum)
		{
			double result = 0.0;
			for (map<string, attrItem*>::iterator item = attriItem.begin();
				item != attriItem.end();
				++item
				)
			{
				double pi = (double)(item->second->itemNum[0]) / (double)lineNum;
				splitInfo += pi * (log(pi) / log((double)2));
				double sub_attr = info_D(item->second->itemNum[1], item->second->itemNum[0]);
				result += pi * sub_attr;
			}
			splitInfo = -splitInfo;
			return result;
		}

		int DecisionTree::compuDecisiNote(vector<DecisionTree::attributes*>& statTree, int deciNum, int lineNum, vector<int>& readClumNum)
		{
			double max_temp = 0;
			int max_attribute = 0;
			//总的yes行的信息量
			double infoD = info_D(deciNum, lineNum);
			for (int i = 0; i < attriNum - 1; i++)
			{
				if (readClumNum[i] == 0)
				{
					double splitInfo = 0.0;
					//info
					double info_temp = Info_attr(statTree[i]->attriItem, splitInfo, lineNum);
					statTree[i]->statResult.push_back(info_temp);
					//gain
					double gain_temp = infoD - info_temp;
					statTree[i]->statResult.push_back(gain_temp);
					//split_info
					statTree[i]->statResult.push_back(splitInfo);
					//gain_info
					double temp = gain_temp / splitInfo;
					statTree[i]->statResult.push_back(temp);
					//得到最大值*/
					if (temp > max_temp)
					{
						max_temp = temp;
						max_attribute = i;
					}
				}
			}
			return max_attribute;
		}

		void DecisionTree::resetStatTree(vector<DecisionTree::attributes*>& statTree, vector<int>& readClumNum)
		{
			for (int i = 0; i < readClumNum.size() - 1; i++)
			{
				if (readClumNum[i] == 0)
				{
					map<string, attrItem*>::iterator it_end = statTree[i]->attriItem.end();
					for (map<string, attrItem*>::iterator it = statTree[i]->attriItem.begin();
						it != it_end; it++)
					{
						delete it->second;
					}
					statTree[i]->attriItem.clear();
					statTree[i]->statResult.clear();
				}
			}
		}


		//int main(int argc, char* argv[]) {
		//	string filename = "tree.txt";
		//	DecisionTree dt;
		//	int attr_node = 0;
		//	TreeNode* treeHead = nullptr;
		//	set<int> readLineNum;
		//	vector<int> readClumNum;
		//	int deep = 0;
		//	if (dt.pretreatment(filename, readLineNum, readClumNum) == 0)
		//	{
		//		dt.CreatTree(treeHead, dt.getStatTree(), dt.getInfos(), readLineNum, readClumNum, deep);
		//	}
		//	return 0;
		//}
	}
}

