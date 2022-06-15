#pragma once
#include "CMyString.h"
class CBst
{
public:

	struct List {
		List():Stu_Choose_Class(), Next_Record(nullptr){}
		List(CMyString& Stu_Choose_Class):Stu_Choose_Class(Stu_Choose_Class), Next_Record(nullptr){}
		CMyString Stu_Choose_Class;		//ѧ��ID��Ӧ������ѡ�μ�¼��Ϣ
		List* Next_Record;
	};

	struct Node {

		Node():m_nHeight(1), Stu_Choose_Class(), Sort_Key(), m_pParent(nullptr), m_pLeft(nullptr), m_pRight(nullptr), Next_Record(nullptr) {}
		Node(CMyString& Sort_Key, CMyString& Stu_Choose_Class):m_nHeight(1), Stu_Choose_Class(Stu_Choose_Class), Sort_Key(Sort_Key), m_pParent(nullptr), m_pLeft(nullptr), m_pRight(nullptr), Next_Record(nullptr) {}
		CMyString Stu_Choose_Class;		//ѧ��ID��Ӧ������ѡ�μ�¼��Ϣ
		CMyString Sort_Key;	//AVL����������
		Node* m_pParent;	//���ڵ�
		Node* m_pLeft;		//����
		Node* m_pRight;		//�к���
		List* Next_Record;	//һ��ID���Ӧ���ѡ�μ�¼��������洢
		int m_nHeight;		//�ڵ�߶�

	};


	CBst();
	CBst(CMyString& Stu_ID, CMyString& Stu_Choose_Class);
	~CBst();

	void Insert(CMyString& Sort_Key, CMyString& Stu_Choose_Class);	//����key������ѡ�μ�¼
	void Delete(CMyString& Sort_Key);								//��Sort_Keyɾ����ѧ��������ѡ�μ�¼
	void Delete(CMyString& Sort_Key, CMyString& Record1, CMyString& Record2);			//��Sort_Key + Record ɾ����ѧ����ĳ��ѡ�μ�¼
	void DelLeaf(Node* pNode);										//ɾ��Ҷ�ӽڵ�
	void DelLSingle(Node* pNode);									//ɾ��ֻ��һ�����ӵĽڵ�
	void DelRSingle(Node* pNode);									//ɾ��ֻ��һ���Һ��ӵĽڵ�
	void DelDouble(Node* pNode);									//ɾ��˫�׽ڵ�
	Node* FindNode(CMyString& Sort_Key);							//��key��ѯ

	void AdjustHeight(Node* pNode);									//�����߶�
	int CalcHeight(Node* pNode);									//���㵱ǰ�ڵ�߶�
	int GetHeight(Node* pNode);									//���㵱ǰ�ڵ�߶�
	void LeftRotate(Node* pNode);									//����
	void RightRotate(Node* pNode);									//����

	Node* m_pRoot = nullptr;	//���ڵ�
};

