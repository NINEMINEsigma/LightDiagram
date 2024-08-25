#ifndef __FILE_DECISIONTREE
#define __FILE_DECISIONTREE

#include<Math/MathConfig.h>

namespace ld
{
	namespace math
	{
		/*******树的构造*******/
		_LF_C_API(Struct) TreeNode 
		{
			string m_sAttribute;//节点名字
			int m_iDeciNum;  //yes 数
			int m_iUnDecinum; //no 数
			std::vector<TreeNode*> m_vChildren;
		};
		TreeNode* CreateTreeNode(std::string value);
		bool FindNode(TreeNode* pRoot, std::string& item);
		void ConnectTreeNodes(TreeNode* pParent, TreeNode* pChild);
		void PrintTreeNode(TreeNode* pNode);
		void PrintTree(TreeNode* pRoot);
		void DestroyTree(TreeNode* pRoot);


		/*******树的构造*******/
		_LF_C_API(Class) DecisionTree 
		{
		private:
			_LF_C_API(Struct) attrItem
			{
				//itemNum[0] = itemLine.size()
				//itemNum[1] = decision num
				std::vector<int>	itemNum;
				//可用行
				std::set<int>		itemLine; 
			};
			//重点
			_LF_C_API(Struct) attributes
			{
				//属性名字
				std::string attriName; 
				std::vector<double> statResult;
				//存放子目录的信息
				std::map<std::string, attrItem*> attriItem;
			};

			std::vector<attributes*> statTree;
			int attriNum;
			std::vector<std::vector<string>> infos;
			//作用不大
			std::map<std::string, int> attr_clum;

		public:
			DecisionTree();
			std::vector<std::vector<std::string>>& getInfos();
			std::vector<attributes*>& getStatTree();
			/*
			* @function CreatTree 预处理函数，负责读入数据，并生成信息矩阵和属性标记
			* @param: filename 文件名
			* @param: readLineNum 可使用行set
			* @param: readClumNum 可用属性vector 0可用 1不可用
			* @return int 返回函数执行状态
			*/
			int pretreatment(std::string filename, std::set<int>& readLineNum, std::vector<int>& readClumNum);
			int statister(std::vector<std::vector<string>>& infos, std::vector<attributes*>& statTree,std::set<int>& readLine, std::vector<int>& readClumNum);
			/*
			* @function compuDecisiNote 计算C4.5
			* @param: statTree 为状态树，此树动态更新，但是由于是DFS对数据更新，所以不必每次新建状态树
			* @param: deciNum Yes的数据量
			* @param: lineNum 计算set的行数
			* @param: readClumNum 用于计算的set
			* @return int 信息量最大的属性号
			*/
			int compuDecisiNote(std::vector<attributes*>& statTree, int deciNum, int lineNum, std::vector<int>& readClumNum);
			/*
			* @function Info_attr info_D 总信息量
			* @param: deciNum 有效信息数
			* @param: sum 总信息量
			* @return double 总信息量比例
			*/
			double info_D(int deciNum, int sum);
			/*
			* @function resetStatTree 清理状态树
			* @param: statTree 状态树
			* @param: readClumNum 需要清理的属性set
			* @return void
			*/
			void resetStatTree(std::vector<attributes*>& statTree, std::vector<int>& readClumNum);
			/*
			* @function Info_attr 总信息量
			* @param: deciNum 有效信息数
			* @param: sum 总信息量
			* @return double
			*/
			double Info_attr(std::map<string, attrItem*>& attriItem, double& splitInfo, int lineNum);
			void CreatTree(TreeNode*& treeHead, std::vector<attributes*>& statTree, std::vector<std::vector<std::string>>& infos,std::set<int>& readLine, std::vector<int>& readClumNum, int deep);
		};
	}
}


#endif // !__FILE_DECISIONTREE
