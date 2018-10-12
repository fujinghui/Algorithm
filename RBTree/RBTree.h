#pragma once
#include<iostream>
#include<queue>
#include <assert.h>
/*
�������һ����ƽ��Ķ�������������͵���;��ʵ�ֹ������顣
�����������5��Լ���������ƣ�
1. ÿ���ڵ�����Ǻ�ɫ�������Ǻ�ɫ��
2. ���ڵ��Ǻ�ɫ��
3. ÿ��Ҷ�ӽڵ㣨NIL���Ǻ�ɫ������Ҷ�ӽڵ㣬��ָΪ��(NIL��NULL)��Ҷ�ӽڵ�
4. ���һ���ڵ��Ǻ�ɫ�ģ��������ӽڵ�����Ǻ�ɫ�ġ�
5. ��һ���ڵ㵽�ýڵ������ڵ������·���ϰ�����ͬ��Ŀ�ĺڽڵ㡣

��Լ������5���ɵã��Ӹ�������Ҭ�ӵ����·����������̵�·����2����������������������ƽ��ġ�
*/

/*
���class��������������ıȽϵ���䣬�Ұѳ���ֵȫ����������ߣ���ֹ��дһ���Ⱥŵ������
*/
class RBTree
{
private:
	typedef enum
	{
		RBT_COLOR_RED,
		RBT_COLOR_BLACK,
	}RBTColor;
	typedef struct __RBTreeNode
	{
		__RBTreeNode* pParent;
		__RBTreeNode* pLeft;
		__RBTreeNode* pRight;
		RBTColor Color;
		int Value;
	}RBTreeNode, *pRBTreeNode;
private:
	void InsertFixUP(pRBTreeNode pInsertNode);						//����InsertNode֮�󣬵��������
	void DeleteFixUp(pRBTreeNode pFixNode);						//ɾ��DeleteNode֮�󣬵��������
	void SingleLeft(pRBTreeNode &pNode, pRBTreeNode &newTop);		//����ת�������µĶ���
	void SingleRight(pRBTreeNode &pNode, pRBTreeNode &newTop);		//����ת�������µĶ���
	void ReplaceParent(pRBTreeNode pBeReplacedNode, pRBTreeNode pReplaceNode);	//��pReplaceNode�ĸ��ڵ��޸�ΪpBeReplacedNode��
	bool GetMinNode(pRBTreeNode pNode, pRBTreeNode &pMinNode);					//��ȡ��С�Ľڵ�
public:
	RBTree();
	~RBTree();
	bool FindElement(int Value);									//�������ݣ��ҵ�����true�����򷵻�false
	void BFS();														//��ȱ���
	bool isEmpty();													//�п�
	bool GetMax(pRBTreeNode pNode, int &MaxValue);					//��ȡ���ֵ
	bool GetMin(pRBTreeNode pNode, int &MinValue);					//��ȡ��Сֵ
	void DeleteElement(int DeleteValue);							//ɾ���ƶ���Ԫ��
	void InsertData(int InsertValue);								//����
private:
	pRBTreeNode pRoot;												//���ڵ�ָ��
	pRBTreeNode pNil;												//�սڵ�
};

void RBTree::InsertFixUP(pRBTreeNode pInsertNode)
{
	/*
	����ڵ�󣬶Ժ�����ĵ���������
	���ݱ�����ڵ�ĸ��ڵ����������Խ����������������
	1. ������Ľڵ�ĸ��ڵ��Ǻ�ɫ
	���ʱ��������ͻ��������Լ������5��
	��������£�������ڵ���һ�����ڷǿ��游�ڵ�ģ���һ���Ľ���������ڵ�Ҳһ����������ڵ�(��ʹ����ڵ�Ϊ�գ�����Ҳ��֮Ϊ���ڣ��սڵ㱾����Ǻ�ɫ�ڵ�)��
	����"����ڵ�����"�������������һ������Ϊ3������������ۡ�����ĺ���˼·�ǣ�����ɫ�Ľڵ��Ƶ����ڵ㣬Ȼ�󽫸��ڵ�����Ϊ��ɫ��

	**�Ե�ǰ�ڵ�ĸ��ڵ����游�ڵ������Ϊ��**
	**��Ӧ�ģ�����ǰ�ڵ�ĸ��ڵ����游�ڵ���Һ���ʱ���Ѷ�Ӧ��right��left��������**

	1.1 ��ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ���ҵ�ǰ�ڵ���游�ڵ����һ���ӽڵ㣨����ڵ㣩Ҳ�Ǻ�ɫ��
	1. �������ڵ㡱��Ϊ��ɫ��
	2. ��������ڵ㡱��Ϊ��ɫ��
	3. �����游�ڵ㡱��Ϊ����ɫ����
	4. �����游�ڵ㡱��Ϊ����ǰ�ڵ㡱(��ɫ�ڵ�)������֮������ԡ���ǰ�ڵ㡱���в�����
	1.2 ��ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ������ڵ��Ǻ�ɫ���ҵ�ǰ�ڵ����丸�ڵ���Һ��ӡ�
	1. �������ڵ㡱��Ϊ���µĵ�ǰ�ڵ㡱��
	2. �ԡ��µĵ�ǰ�ڵ㡱Ϊ֧�����������
	1.3 ��ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ������ڵ��Ǻ�ɫ���ҵ�ǰ�ڵ����丸�ڵ�����ӡ�
	1. �������ڵ㡱��Ϊ����ɫ����
	2. �����游�ڵ㡱��Ϊ����ɫ����
	3. �ԡ��游�ڵ㡱Ϊ֧�����������


	2. ������Ľڵ�ĸ��ڵ��Ǻ�ɫ
	ʲôҲ����Ҫ�����ڵ㱻�������Ȼ�Ǻ������
	3. ������Ľڵ��Ǹ��ڵ㣺
	ֱ�ӰѴ˽ڵ�ͿΪ��ɫ��
	*/

	pRBTreeNode pFixNode = pInsertNode;;
	//������ڵ��Ǻ�ɫ�������ڵ�ĸ��ڵ���Nil��Ϊ��ɫ����
	while (RBT_COLOR_RED == pFixNode->pParent->Color)
	{
		//1. ��������ڵ�ĸ���Ϊ�游�ڵ������
		if (pFixNode->pParent == pFixNode->pParent->pParent->pLeft)
		{
			//��ȡ����ڵ�(�游�ڵ���Һ���)
			pRBTreeNode pUncle = pFixNode->pParent->pParent->pRight;
			//1.1 �������ڵ�Ϊ��ɫ�����1.1.1
			if (RBT_COLOR_RED == pUncle->Color)
			{
				//�Ѹ��ڵ������ڵ㶼��Ϊ��ɫ
				pFixNode->pParent->Color = RBT_COLOR_BLACK;
				pUncle->Color = RBT_COLOR_BLACK;
				//���游�ڵ��Ϊ��ɫ
				pFixNode->pParent->pParent->Color = RBT_COLOR_RED;
				//���¼�������ڵ�Ϊ�游�ڵ�
				pFixNode = pFixNode->pParent->pParent;
			}
			//1.2 ����ڵ㲻Ϊ��ɫ���ҵ����ڵ�Ϊ�游�ڵ���Һ��ӡ����ʱ���ԼӴ�����ת��Ϊ���1.3
			else if (pFixNode == pFixNode->pParent->pRight)
			{
				//�ӵ����ڵ�ĸ��ڵ㿪ʼ��ת
				pFixNode = pFixNode->pParent;
				//��¼���µĶ���
				pRBTreeNode pNewTop = nullptr;
				SingleLeft(pFixNode->pParent->pLeft, pNewTop);
				//�������õ����ڵ�
				pFixNode = pNewTop->pLeft;
			}
			//1.3 ����ڵ�Ϊ�ڣ��ҵ����ڵ�Ϊ���ڵ������
			else if (pFixNode == pFixNode->pParent->pLeft)
			{
				//�Ѹ��ڵ��ɺ�ɫ
				pFixNode->pParent->Color = RBT_COLOR_BLACK;
				//���游�ڵ��ɺ�ɫ
				pFixNode->pParent->pParent->Color = RBT_COLOR_RED;
				//���游�ڵ�����ת(ע�⵽Ϊ���ڵ�����)
				pFixNode = pFixNode->pParent->pParent;
				//��¼���µĶ���
				pRBTreeNode pNewTop = nullptr;
				if (pRoot == pFixNode)
				{
					SingleRight(pRoot, pNewTop);
				}
				else if (pFixNode == pFixNode->pParent->pLeft)
				{
					SingleRight(pFixNode->pParent->pLeft, pNewTop);
				}
				else if (pFixNode == pFixNode->pParent->pRight)
				{
					SingleRight(pFixNode->pParent->pRight, pNewTop);
				}
				//�������õ�����
				pFixNode = pNewTop->pLeft;
			}
		}
		//2. ��������ڵ�ĸ��ڵ�Ϊ�游�ڵ���Һ��ӣ������1�У���left��right��������
		else if (pFixNode->pParent == pFixNode->pParent->pParent->pRight)
		{
			//��ȡ����ڵ㣨�游�ڵ�����ӣ�
			pRBTreeNode pUncle = pFixNode->pParent->pParent->pLeft;
			//2.1 �������ڵ�Ϊ��ɫ
			if (RBT_COLOR_RED == pUncle->Color)
			{
				//�Ѹ��ڵ������ڵ㶼��Ϊ��ɫ
				pFixNode->pParent->Color = RBT_COLOR_BLACK;
				pUncle->Color = RBT_COLOR_BLACK;
				//���游�ڵ��Ϊ��ɫ
				pFixNode->pParent->pParent->Color = RBT_COLOR_RED;
				//���¼�������ڵ�Ϊ�游�ڵ�
				pFixNode = pFixNode->pParent->pParent;
			}
			//2.2 ����ڵ�Ϊ��ɫ���ҵ����ڵ�Ϊ���׽ڵ�����ӣ���Ӧ���1.2�����һ�����
			else if (pFixNode == pFixNode->pParent->pLeft)
			{
				//�ӵ����ڵ�ĸ��ڵ㿪ʼ��ת
				pFixNode = pFixNode->pParent;
				//��¼���µĶ���
				pRBTreeNode pNewTop = nullptr;
				SingleRight(pFixNode->pParent->pRight, pNewTop);
				//�������õ����ڵ�
				pFixNode = pNewTop->pRight;
			}
			//2.3 ����ڵ�Ϊ��ɫ���ҵ����ڵ�Ϊ���ڵ���Һ��ӣ���Ӧ���1.3�����һ�����
			else if (pFixNode == pFixNode->pParent->pRight)
			{
				//�Ѹ��ڵ��Ϊ��ɫ
				pFixNode->pParent->Color = RBT_COLOR_BLACK;
				//���游�ڵ��Ϊ��ɫ
				pFixNode->pParent->pParent->Color = RBT_COLOR_RED;
				//���游�ڵ��������ת��ע�⵽Ϊ���ڵ�������
				pFixNode = pFixNode->pParent->pParent;
				//��¼���½ڵ�
				pRBTreeNode pNewTop = nullptr;
				if (pRoot == pFixNode)
				{
					SingleLeft(pRoot, pNewTop);
				}
				else if (pFixNode == pFixNode->pParent->pLeft)
				{
					SingleLeft(pFixNode->pParent->pLeft, pNewTop);
				}
				else if (pFixNode == pFixNode->pParent->pRight)
				{
					SingleLeft(pFixNode->pParent->pRight, pNewTop);
				}
				//�������õ����ڵ�
				pFixNode = pNewTop->pRight;
			}
		}
	}
	//���Ѹ��ڵ�����Ϊ��ɫ
	pRoot->Color = RBT_COLOR_BLACK;
}

void RBTree::DeleteFixUp(pRBTreeNode pFixNode)
{
	/*
	�ָ��������Լ��������
	*/
	while (pFixNode != pRoot&&RBT_COLOR_BLACK == pFixNode->Color)
	{
		//1. ����������Ǹ��ڵ������
		if (pFixNode == pFixNode->pParent->pLeft)
		{
			pRBTreeNode pBrotherNode = pFixNode->pParent->pRight;			//�ֵܽڵ�
																			//1.1 ����ֵܽڵ�Ϊ��ɫ����ֻ�ܵ��������������
			if (RBT_COLOR_RED == pBrotherNode->Color)
			{
				//���ֵܽڵ����ɫ��Ϊ��ɫ
				pBrotherNode->Color = RBT_COLOR_BLACK;
				//�Ѹ��ڵ����ɫ��Ϊ��ɫ
				pFixNode->pParent->Color = RBT_COLOR_RED;
				//�Ը��ڵ�Ϊ���ڵ�����
				pRBTreeNode pPivot = pFixNode->pParent;
				pRBTreeNode pNewTop = nullptr;
				//����parent��ָ�룬��Ϊ��ת�������޸�parentָ��
				pRBTreeNode pBackParent = pFixNode->pParent;
				if (pRoot = pPivot)
				{
					SingleLeft(pRoot, pNewTop);
				}
				else if (pPivot == pPivot->pParent->pLeft)
				{
					SingleLeft(pPivot->pParent->pLeft, pNewTop);
				}
				else if (pPivot == pPivot->pParent->pRight)
				{
					SingleLeft(pPivot->pParent->pRight, pNewTop);
				}
				//�ָ�pFixNode��parentָ��
				pFixNode->pParent = pBackParent;
			}
			//1.2 ����ֵܽڵ��Ǻ�ɫ���ֵܽڵ�����Һ��Ӿ�Ϊ��ɫ
			else if (RBT_COLOR_BLACK == pBrotherNode->pLeft->Color&&RBT_COLOR_BLACK == pBrotherNode->pRight->Color)
			{
				//���ֵܽڵ�Ⱦ�ɺ�ɫ
				pBrotherNode->Color = RBT_COLOR_RED;
				//FixUpNode�޸�Ϊ���׽ڵ�
				pFixNode = pFixNode->pParent;
			}
			//1.3 ����ֵܽڵ��Ǻ�ɫ�����ֵܽڵ�����Ϊ��ɫ���Һ���Ϊ��ɫ
			else if (RBT_COLOR_RED == pBrotherNode->pLeft->Color&&RBT_COLOR_BLACK == pBrotherNode->pRight->Color)
			{
				//������ɫ
				RBTColor tempNodeColor = pBrotherNode->pLeft->Color;
				pBrotherNode->pLeft->Color = pBrotherNode->Color;
				pBrotherNode->Color = tempNodeColor;
				//����parent��ָ�룬��Ϊ��ת�������޸�parentָ��
				pRBTreeNode pBackParent = pFixNode->pParent;
				//��pBrotherNode��������
				pRBTreeNode pNewTop = nullptr;
				SingleRight(pBrotherNode->pParent->pRight, pNewTop);
				//�ָ�pFixNode��parentָ��
				pFixNode->pParent = pBackParent;
			}
			//1.4 ����ֵܽڵ��Ǻ�ɫ�����ֵܽڵ���Һ���Ϊ��ɫ���ֵܽڵ�����ӿ�����������ɫ
			else if (RBT_COLOR_RED == pBrotherNode->pRight->Color)
			{
				pBrotherNode->Color = pFixNode->pParent->Color;
				pFixNode->pParent->Color = RBT_COLOR_BLACK;
				pBrotherNode->pRight->Color = RBT_COLOR_BLACK;
				//��pFixNode->pParent����
				pRBTreeNode pPivot = pFixNode->pParent;
				pRBTreeNode pNewTop = nullptr;
				if (pRoot == pPivot)
				{
					SingleLeft(pPivot, pNewTop);
				}
				else if (pPivot == pPivot->pParent->pLeft)
				{
					SingleLeft(pPivot->pParent->pLeft, pNewTop);
				}
				else if (pPivot == pPivot->pParent->pRight)
				{
					SingleLeft(pPivot->pParent->pRight, pNewTop);
				}
				pFixNode = pRoot;
			}
		}
		//2. ��������ڵ��Ǹ��ڵ���Һ���
		else if (pFixNode == pFixNode->pParent->pRight)
		{
			pRBTreeNode pBrotherNode = pFixNode->pParent->pLeft;
			//2.1 ����ֵܽڵ�Ϊ��ɫ�ڵ㣬��ֻ��ͨ��ѡ��������������������������
			if (RBT_COLOR_RED == pBrotherNode->Color)
			{
				//���ֵܽڵ����ɫ��Ϊ��ɫ
				pBrotherNode->Color = RBT_COLOR_BLACK;
				//�Ѹ��ڵ����ɫ��Ϊ��ɫ
				pFixNode->pParent->Color = RBT_COLOR_RED;
				//�Ը��ڵ�Ϊ������������
				pRBTreeNode pPivot = pFixNode->pParent;
				pRBTreeNode pNewTop = nullptr;
				//ͬ�����ݸ��ڵ�ָ��
				pRBTreeNode pBackParent = pFixNode->pParent;
				//
				if (pRoot == pPivot)
				{
					SingleRight(pRoot, pNewTop);
				}
				else if (pPivot == pPivot->pParent->pLeft)
				{
					SingleRight(pPivot->pParent->pLeft, pNewTop);
				}
				else if (pPivot == pPivot->pParent->pRight)
				{
					SingleRight(pPivot->pParent->pRight, pNewTop);
				}

				//�ָ�pFixNode��Parentָ��
				pFixNode->pParent = pBackParent;
			}
			//2.2 ����ֵܽڵ��Ǻ�ɫ���ֵܽڵ�����Һ��Ӿ�Ϊ��ɫ
			else if (RBT_COLOR_BLACK == pBrotherNode->pLeft->Color&&RBT_COLOR_BLACK == pBrotherNode->pRight->Color)
			{
				//�ֵܽڵ����ɫ��Ϊ��ɫ
				pBrotherNode->Color = RBT_COLOR_RED;
				//FixUpNode �޸�Ϊ���ڵ�
				pFixNode = pFixNode->pParent;
			}
			//2.3 ����ֵܽڵ��Ǻ�ɫ�������ֵܽڵ��Һ���Ϊ��ɫ������Ϊ��ɫ
			else if (RBT_COLOR_BLACK == pBrotherNode->pLeft->Color&&RBT_COLOR_RED == pBrotherNode->pRight->Color)
			{
				//������ɫ
				RBTColor tempNodeColor = pBrotherNode->pRight->Color;
				pBrotherNode->pRight->Color = pBrotherNode->Color;
				pBrotherNode->Color = tempNodeColor;

				//����parentָ��
				pRBTreeNode pBackParent = pFixNode->pParent;
				//��pBrotherNode��������
				pRBTreeNode pNewTop = nullptr;
				SingleLeft(pBrotherNode->pParent->pLeft, pNewTop);
				//�ָ�pFixNode��parentָ��
				pFixNode->pParent = pBrotherNode;
			}
			//2.4. ����ֵܽڵ��Ǻ�ɫ,���ֵܽڵ������Ǻ�ɫ,�Һ�����ɫ����
			else if (RBT_COLOR_RED == pBrotherNode->pLeft->Color)
			{
				pBrotherNode->Color = pFixNode->pParent->Color;
				pFixNode->pParent->Color = RBT_COLOR_BLACK;
				pBrotherNode->pLeft->Color = RBT_COLOR_BLACK;
				pRBTreeNode pPivot = pFixNode->pParent;
				pRBTreeNode pNewTop = nullptr;
				if (pRoot == pPivot)
				{
					SingleRight(pPivot, pNewTop);
				}
				else if (pPivot == pPivot->pParent->pLeft)
				{
					SingleRight(pPivot->pParent->pLeft, pNewTop);
				}
				else if (pPivot == pPivot->pParent->pRight)
				{
					SingleRight(pPivot->pParent->pRight, pNewTop);
				}
				//��ִ������һ����һ��������ã�ֱ������Ϊ���ڵ��´��˳�
				pFixNode = pRoot;
			}
		}
	}
	pFixNode->Color = RBT_COLOR_BLACK;
}

void RBTree::SingleLeft(pRBTreeNode & pNode, pRBTreeNode & newTop)
{
	/*
	k2									k1
	\							 /     \
	k1				      k2		  N
	\
	N
	*/

	pRBTreeNode k2 = pNode;
	pRBTreeNode k1 = pNode->pRight;
	k2->pRight = k1->pLeft;
	//�޸�k1���ӵĸ��ڵ�
	if (k1->pLeft)
	{
		k1->pLeft->pParent = k2;
	}
	k1->pLeft = k2;
	//�޸�k1�ĸ��ڵ�
	k1->pParent = pNode->pParent;
	//�޸�k2�ĸ��ڵ�
	k2->pParent = k1;
	//���ؽ��
	pNode = k1;
	newTop = k1;
}

void RBTree::SingleRight(pRBTreeNode & pNode, pRBTreeNode & newTop)
{
	/*
	k2									 k1
	/							   /     \
	k1								 N         k2
	/
	N
	*/

	pRBTreeNode k2 = pNode;
	pRBTreeNode k1 = pNode->pLeft;
	k2->pLeft = k1->pRight;
	//�޸�k1�Һ��ӵĸ��ڵ�
	if (k1->pRight)
	{
		k1->pRight->pParent = k2;
	}
	k1->pRight = k2;
	//�޸�k1�ĸ��ڵ�
	k1->pParent = pNode->pParent;
	//�޸�k2�ĸ��ڵ�
	k2->pParent = k1;
	//���ؽ��
	pNode = k1;
	newTop = k1;
}

void RBTree::ReplaceParent(pRBTreeNode pBeReplacedNode, pRBTreeNode pReplaceNode)
{
	//�滻�ڵ㲢�޸ĸ��ڵ�Ĳ���
	//1. ���pBeReplacedNode�Ǹ��ڵ�
	if (pBeReplacedNode == pRoot)
	{
		pRoot = pReplaceNode;
	}
	//2. ���pBeReplacedNode�Ǹ��ڵ������
	else if (pBeReplacedNode == pBeReplacedNode->pParent->pLeft)
	{
		pBeReplacedNode->pParent->pLeft = pReplaceNode;
	}
	//3. ���pBeReplacedNode�Ǹ��ڵ���Һ���
	else if (pBeReplacedNode == pBeReplacedNode->pParent->pRight)
	{
		pBeReplacedNode->pParent->pRight = pReplaceNode;
	}
	//4. �޸�pReplaceNode�ĸ��׽ڵ�
	pReplaceNode->pParent = pBeReplacedNode->pParent;
}

bool RBTree::GetMinNode(pRBTreeNode pNode, pRBTreeNode & pMinNode)
{
	if (nullptr == pNode || pNode == pNil)
		return false;
	pRBTreeNode pPreNode = pNode->pParent;
	while (pNil != pNode)
	{
		pPreNode = pNode;
		pNode = pNode->pLeft;
	}
	pMinNode = pPreNode;
	return true;
}

RBTree::RBTree()
{
	pRoot = nullptr;

	pNil = new RBTreeNode();
	pNil->pLeft = nullptr;
	pNil->pRight = nullptr;
	pNil->pParent = nullptr;
	pNil->Color = RBT_COLOR_BLACK;
	pNil->Value = 0xFFFFFFFF;
}

RBTree::~RBTree()
{
	if (!isEmpty())
	{
		std::queue<pRBTreeNode>nodeQue;
		nodeQue.push(pRoot);								//���ڵ����
		while (!nodeQue.empty())							//���зǿ�
		{
			pRBTreeNode pNode = nodeQue.front();
			pRBTreeNode pLeft = pNode->pLeft;
			pRBTreeNode pRight = pNode->pRight;
			//�����ͷ���Դ
			nodeQue.pop();
			if (pLeft != pNil)nodeQue.push(pLeft);
			if (pRight != pNil)nodeQue.push(pRight);
		}
	}
	if (pNil)												//����ǿսڵ�
	{
		delete pNil;
		pNil = nullptr;
	}
}

bool RBTree::FindElement(int Value)
{
	if (isEmpty())
	{
		return false;
	}
	pRBTreeNode pCurrent = pRoot;
	while (pNil != pCurrent)
	{
		if (Value<pCurrent->Value)
		{
			pCurrent = pCurrent->pLeft;
		}
		else if (Value>pCurrent->Value)
		{
			pCurrent = pCurrent->pRight;
		}
		else
		{
			return true;
		}
	}
	return false;
}

void RBTree::BFS()
{
	if (isEmpty())return;
	std::queue<pRBTreeNode>nodeQue;
	nodeQue.push(pRoot);

	//BFS
	int TreeHeight = 0;
	while (!nodeQue.empty())
	{
		int nCurrentLevelSize = nodeQue.size();						//��¼��ǰ��Ԫ�صĸ���
		int nCnt = 0;
		std::cout << "��" << TreeHeight + 1 << "��";
		while (nCnt < nCurrentLevelSize)
		{
			pRBTreeNode acessNode = nodeQue.front();
			nodeQue.pop();
			if (acessNode == pRoot)
			{
				std::cout << acessNode->Value << "���ڵ㣬��ɫ" << acessNode->Color << ")" << ' ';
			}
			else
			{
				if (acessNode->pParent->pLeft == acessNode)
				{
					std::cout << "[(" << acessNode->Value << "��ɫ" << acessNode->Color << ')' << '(' << acessNode->pParent->Value << "������)]" << ' ';
				}
				else if (acessNode->pParent->pRight == acessNode)
				{
					std::cout << "[(" << acessNode->Value << "��ɫ" << acessNode->Color << ')' << '(' << acessNode->pParent->Value << "���Һ���)]" << ' ';
				}
			}

			//��һ���Ԫ��
			pRBTreeNode pLeft = acessNode->pLeft;
			pRBTreeNode pRight = acessNode->pRight;
			if (pNil != pLeft)
			{
				nodeQue.push(pLeft);
			}
			if (pNil != pRight)
			{
				nodeQue.push(pRight);
			}
			++nCnt;
		}
		TreeHeight++;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool RBTree::isEmpty()											//�п�
{
	return pRoot == nullptr;
}

bool RBTree::GetMax(pRBTreeNode pNode, int & MaxValue)
{
	if (nullptr == pNode)
	{
		return false;
	}
	while (pNode)
	{
		MaxValue = pNode->Value;
		pNode = pNode->pRight;
	}
	return true;

}

bool RBTree::GetMin(pRBTreeNode pNode, int & MinValue)
{
	if (nullptr == pNode)
		return false;
	while (pNode)
	{
		MinValue = pNode->Value;
		pNode = pNode->pLeft;
	}
	return true;
}

void RBTree::DeleteElement(int DeleteValue)
{
	/*
	ɾ������
	����˼·���£�
	1. �����������һ�ö�������������ڵ�ɾ����
	�����������
	1. ��ɾ���ڵ�û�ж��ӣ���ΪҶ�ڵ㣬��ʱֱ��ɾ�����ɡ��ÿսڵ㶥������λ�á�
	2. ��ɾ���ڵ�ֻ��һ���ӽڵ㣬��ʱ��ֱ��ɾ���ýڵ㣬Ȼ���øýڵ��Ψһ�ӽڵ㶥������
	3. ��ɾ���ڵ��������ӽڵ㣬��Ҫ���ҵ�����ֱ�Ӻ�̽ڵ㣬��ֵ���Ƶ�����λ�ã�Ȼ��ɾ�����ĺ�̽ڵ㣬��Ϊ���ĺ�̽ڵ㲻�����������ǿ��ӽڵ㣬��������������ֻ����һ�Ρ�
	2. ���������
	��ɾ���ڵ���п���Υ��2,4,5����Լ���������ڶ������ǵ�����������ʹ֮����Լ��������
	*/

	if (isEmpty())
		return;
	//���ҵ�Ҫɾ���Ľڵ�
	pRBTreeNode pCurrent = pRoot;
	pRBTreeNode pDeletedNode = nullptr;
	while (pNil != pCurrent)
	{
		if (DeleteValue<pCurrent->Value)
		{
			pCurrent = pCurrent->pLeft;
		}
		else if (DeleteValue>pCurrent->Value)
		{
			pCurrent = pCurrent->pRight;
		}
		else
		{
			pDeletedNode = pCurrent;
			break;
		}
	}
	//2. ���δ�ҵ�����ֱ���˳�
	if (nullptr == pDeletedNode)return;
	//3. ִ��ɾ�������������pDeletedNode,pRealDeleteNode,pFixUpNode.

	pRBTreeNode pRealDeleteNode = nullptr;
	pRBTreeNode pFixUpNode = nullptr;
	RBTColor RealDeleteColor;

	//3.1���������Ϊ��
	if (pNil == pDeletedNode->pLeft)
	{
		pRealDeleteNode = pDeletedNode;
		RealDeleteColor = pRealDeleteNode->Color;
		pFixUpNode = pRealDeleteNode->pRight;
		//�滻
		ReplaceParent(pRealDeleteNode, pRealDeleteNode->pRight);
	}
	//3.2 ���������Ϊ��
	else if (pNil == pDeletedNode->pRight)
	{
		pRealDeleteNode = pDeletedNode;
		RealDeleteColor = pRealDeleteNode->Color;
		pFixUpNode = pRealDeleteNode->pLeft;
		//�滻
		ReplaceParent(pRealDeleteNode, pRealDeleteNode->pLeft);
	}
	//3.3 ���������������Ϊ��
	else
	{
		/*
		����������������С�Ľڵ���������������Ľڵ����滻������ѡ������������С�Ľڵ㡣�������Ա�֤���������������ʲ���
		*/
		//��ȡ׼��ɾ���ڵ������������С�ڵ㣬pRealDeleteNodeһ������pNil
		bool GetMinRet = GetMinNode(pDeletedNode->pRight, pRealDeleteNode);
		assert(GetMinRet);
		assert(pRealDeleteNode != pNil);
		RealDeleteColor = pRealDeleteNode->Color;
		//��С�ĵ���������Ѷ�λpNil,����pRight�������ĺ�̽ڵ㡣
		pFixUpNode = pRealDeleteNode->pRight;
		//˼·������С�㣨pRealDeleteNode�����滻��Ҫɾ���ĵ㣨pDeletedNode����λ�ã����������
		if (pRealDeleteNode->pParent == pDeletedNode)
		{
			pFixUpNode->pParent = pRealDeleteNode;
		}
		else
		{
			//��pRealDeleteNode���ڵ�ָ�� pRealDeleteNode->pRight
			ReplaceParent(pRealDeleteNode, pRealDeleteNode->pRight);
			//��pRealDeleteNode���ҽڵ�ӹ�ԭ��pDeletedNode���ҽڵ�
			pRealDeleteNode->pRight = pDeletedNode->pRight;
			//��pRealDeleteNode���ҽڵ�ĸ��ڵ�ָ��pRealDeleteNode(������һ����ΪpNil)
			pRealDeleteNode->pRight->pParent = pRealDeleteNode;
		}
		//��pDeleteNode���ڵ�ָ��pRealDeleteNode
		ReplaceParent(pDeletedNode, pRealDeleteNode);
		//��pRealDeleteNode����ڵ�ӹ�ԭ��pDeleteNode���ҽڵ�
		pRealDeleteNode->pLeft = pDeletedNode->pLeft;
		//��pRealDeleteNode�����ӵĸ��ڵ�ָ��pRealDeleteNode(������һ����ΪpNil)
		pRealDeleteNode->pLeft->pParent = pRealDeleteNode;
		// ʹ��pDeleteNode����ɫ
		pRealDeleteNode->Color = pDeletedNode->Color;
	}
	//4. ��pFixUpNode��ִ�е���
	if (RBT_COLOR_BLACK == RealDeleteColor)
	{
		DeleteFixUp(pFixUpNode);
	}
	//5. ������ڵ�����
	if (pRoot == pNil)
		pRoot = nullptr;
	delete pDeletedNode;
}

void RBTree::InsertData(int InsertValue)
{
	/*
	����ڵ㣺
	�Զ���������ķ�������һ���ڵ㡣
	һ��ʼҪ�ѽڵ����ɫ���Ϊ��ɫ�������Ϊ��ɫ���ᵼ�¸���Ҷ�ӵ�·���ϣ�����һ��·��һ������ĺ�ɫ�ڵ㡣����Ǻ��ѵ����ġ�
	��һ������ǣ��Ѳ���Ľڵ���ɫΪ��ɫ������Υ��Լ������1235��ֻΥ��һ��Լ����������Ҫ������������١�
	�����ͨ��һϵ�е���ת����ɫ�Ȳ�����ʹ֮���³�Ϊһ�ź������
	*/
	//��������������Ҫ����Ľڵ��ǵ�һ���ڵ�
	if (isEmpty())
	{
		pRoot = new RBTreeNode();
		pRoot->Color = RBT_COLOR_BLACK;
		pRoot->Value = InsertValue;
		pRoot->pLeft = pNil;
		pRoot->pRight = pNil;
		pRoot->pParent = pNil;
		return;
	}
	//2. �ҵ���Ҫ�����λ��
	pRBTreeNode pPreNode = pRoot->pParent;
	pRBTreeNode pCurrent = pRoot;
	while (pNil != pCurrent)
	{
		pPreNode = pCurrent;
		if (InsertValue <= pCurrent->Value)
		{
			pCurrent = pCurrent->pLeft;
		}
		else
		{
			pCurrent = pCurrent->pRight;
		}
	}
	//3. �����ݲ��뵽��ȷ��λ��
	pRBTreeNode pInsertNode = new RBTreeNode();
	pInsertNode->Color = RBT_COLOR_RED;
	pInsertNode->Value = InsertValue;
	pInsertNode->pLeft = pNil;
	pInsertNode->pRight = pNil;
	pInsertNode->pParent = pPreNode;
	if (InsertValue <= pPreNode->Value)
	{
		pPreNode->pLeft = pInsertNode;
	}
	else
	{
		pPreNode->pRight = pInsertNode;
	}
	//4. ����
	InsertFixUP(pInsertNode);
}
