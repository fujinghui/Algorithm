#include<iostream>
#include "RBTree.h"
#pragma warning(disable:4996)

int main()
{
	RBTree rbTree;
	//����
	int n[]= { 12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17 };
	for (int i = 0; i < 20; i++)
	{
		rbTree.InsertData(n[i]);
	}
	rbTree.BFS();
	std::cout << "------------------------------" << std::endl;
	//ɾ��
	for (int i = 0; i <20; i++)
	{
		std::cout << "ɾ��" << n[i] << "��" << std::endl;
		rbTree.DeleteElement(n[i]);
		rbTree.BFS();
	}
	//������������
	std::cout << "������������" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		rbTree.InsertData(i);
	}
	//����3
	std::cout << "����3" << std::endl;
	std::cout << "���:" << rbTree.FindElement(3) << std::endl;
	rbTree.BFS();
	std::cout << "------------------------------" << std::endl;
	//ɾ����������,ֻ������
	for (int i = 99; i >= 3; i--)
	{
		rbTree.DeleteElement(i);
	}
	//��ȱ���
	rbTree.BFS();
	std::cout << "------------------------------" << std::endl;
	system("pause");
	return 0;
}