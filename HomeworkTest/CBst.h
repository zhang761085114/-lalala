#pragma once
#include "CMyString.h"
class CBst
{
public:

	struct List {
		List():Stu_Choose_Class(), Next_Record(nullptr){}
		List(CMyString& Stu_Choose_Class):Stu_Choose_Class(Stu_Choose_Class), Next_Record(nullptr){}
		CMyString Stu_Choose_Class;		//学生ID对应的所有选课记录信息
		List* Next_Record;
	};

	struct Node {

		Node():m_nHeight(1), Stu_Choose_Class(), Sort_Key(), m_pParent(nullptr), m_pLeft(nullptr), m_pRight(nullptr), Next_Record(nullptr) {}
		Node(CMyString& Sort_Key, CMyString& Stu_Choose_Class):m_nHeight(1), Stu_Choose_Class(Stu_Choose_Class), Sort_Key(Sort_Key), m_pParent(nullptr), m_pLeft(nullptr), m_pRight(nullptr), Next_Record(nullptr) {}
		CMyString Stu_Choose_Class;		//学生ID对应的所有选课记录信息
		CMyString Sort_Key;	//AVL树排序依据
		Node* m_pParent;	//父节点
		Node* m_pLeft;		//左孩子
		Node* m_pRight;		//有孩子
		List* Next_Record;	//一个ID会对应多个选课记录，用链表存储
		int m_nHeight;		//节点高度

	};


	CBst();
	CBst(CMyString& Stu_ID, CMyString& Stu_Choose_Class);
	~CBst();

	void Insert(CMyString& Sort_Key, CMyString& Stu_Choose_Class);	//根据key来插入选课记录
	void Delete(CMyString& Sort_Key);								//用Sort_Key删除该学生的所有选课记录
	void Delete(CMyString& Sort_Key, CMyString& Record1, CMyString& Record2);			//用Sort_Key + Record 删除该学生的某条选课记录
	void DelLeaf(Node* pNode);										//删除叶子节点
	void DelLSingle(Node* pNode);									//删除只有一个左孩子的节点
	void DelRSingle(Node* pNode);									//删除只有一个右孩子的节点
	void DelDouble(Node* pNode);									//删除双亲节点
	Node* FindNode(CMyString& Sort_Key);							//用key查询

	void AdjustHeight(Node* pNode);									//调整高度
	int CalcHeight(Node* pNode);									//计算当前节点高度
	int GetHeight(Node* pNode);									//计算当前节点高度
	void LeftRotate(Node* pNode);									//左旋
	void RightRotate(Node* pNode);									//右旋

	Node* m_pRoot = nullptr;	//根节点
};

