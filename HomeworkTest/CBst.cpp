#include "CBst.h"
#include <string>

CBst::CBst()
{
	m_pRoot = nullptr;
}

CBst::~CBst()
{
}

void CBst::Insert(CMyString& Sort_Key, CMyString& Stu_Choose_Class)
{
	//�п�
	if (m_pRoot == nullptr) {

		m_pRoot = new Node(Sort_Key, Stu_Choose_Class);
		return;

	}

	//����ѧ��ID���ж����ݷ�������������������
	Node* pNode = m_pRoot;
	while (pNode != nullptr) {

		if (strcmp(Sort_Key, pNode->Sort_Key) < 0) {	//�����������С��������������
			if (pNode->m_pLeft == nullptr) {

				Node* pNewNode = new Node(Sort_Key, Stu_Choose_Class);
				pNode->m_pLeft = pNewNode;
				pNewNode->m_pParent = pNode;

				AdjustHeight(pNewNode);					//���²���ڵ㿪ʼ���ϵ����߶�
				return;
			}
			pNode = pNode->m_pLeft;
		}

		else if (strcmp(Sort_Key, pNode->Sort_Key) > 0) {	//����������ݴ�������������
			if (pNode->m_pRight == nullptr) {

				Node* pNewNode = new Node(Sort_Key, Stu_Choose_Class);
				pNode->m_pRight = pNewNode;
				pNewNode->m_pParent = pNode;

				AdjustHeight(pNewNode);					//���²���ڵ㿪ʼ���ϵ����߶�
				return;
			}
			pNode = pNode->m_pRight;
		}

		else {

			if (pNode->Next_Record != nullptr) {

				List* pList = pNode->Next_Record;
				while (pList->Next_Record != nullptr) {

					pList = pList->Next_Record;
				}
				List* pNewList = new List(Stu_Choose_Class);
				pList->Next_Record = pNewList;
				return;
			}

			else {

				List* pNewList = new List(Stu_Choose_Class);
				pNode->Next_Record = pNewList;
				return;
			}
			
			


		}
	}

}

void CBst::Delete(CMyString& Sort_Key)
{
	Node* pNode = FindNode(Sort_Key);		//���ҵ�Ҫɾ���Ľڵ�
	if (pNode == nullptr) {
		return;
	}

	//ɾ�����������ֵ
	if (pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr) {		//Ҷ�ڵ�

		DelLeaf(pNode);
		return;
	}
	if (pNode->m_pLeft != nullptr && pNode->m_pRight == nullptr) {		//���׽ڵ�

		DelLSingle(pNode);
		return;
	}
	if (pNode->m_pRight != nullptr && pNode->m_pLeft == nullptr) {		//�ҵ��׽ڵ�

		DelRSingle(pNode);
		return;
	}
	if (pNode->m_pRight != nullptr && pNode->m_pLeft != nullptr) {		//˫�׽ڵ�

		DelDouble(pNode);
		return;
	}

}
//��������������Record��Ϊ�˷�ֹ�γ�ID��ѧ��ID�ظ�������strstr�ó��Ľ����׼
void CBst::Delete(CMyString& Sort_Key, CMyString& Record1, CMyString& Record2)	
{
	Node* pNode = FindNode(Sort_Key);		//���ҵ�Ҫɾ���Ľڵ�
	if (pNode == nullptr) {
		return;
	}

	if (strstr(pNode->Stu_Choose_Class, Record1) != nullptr && strstr(pNode->Stu_Choose_Class, Record2) != nullptr) {		
		//���1�����ɾ���ļ�¼�洢�ڽڵ��ϣ����ڵ��¼���

		pNode->Stu_Choose_Class = ((std::string)pNode->Stu_Choose_Class + std::string(" ��ɾ��")).c_str();
	}
	else {
		
		List* New_List = pNode->Next_Record;						
		List* New_List_Son = New_List->Next_Record;
		/*���2�����ɾ���ļ�¼�洢�ڽڵ��������ͷ����ϣ�
		ɾ��������ڵ�*/
		if (strstr(New_List->Stu_Choose_Class, Record1) != nullptr && strstr(New_List->Stu_Choose_Class, Record2) != nullptr) {

			pNode->Next_Record = New_List->Next_Record;
			delete New_List;
		}
		/*���3�����ɾ���ļ�¼�洢�ڽڵ���������ͷ����ϣ�ɾ��������ڵ�*/
		else {
			if (New_List_Son == nullptr) {

				printf("ɾ��ʧ�ܣ������ڸ���ѡ�μ�¼��\n");
				return;
			}
			while (strstr(New_List_Son->Stu_Choose_Class, Record1) == nullptr || strstr(New_List_Son->Stu_Choose_Class, Record2) == nullptr) {
				
				New_List = New_List->Next_Record;
				New_List_Son = New_List_Son->Next_Record;
				if (New_List_Son == nullptr) {

					printf("ɾ��ʧ�ܣ������ڸ���ѡ�μ�¼��\n");
					return;
				}

			}
			New_List->Next_Record = New_List_Son->Next_Record;
			delete New_List_Son;
			printf("ɾ���ɹ���\n");
		}
		

	}


}

void CBst::DelLeaf(Node* pNode)
{
	//ɾ��Ҷ��
	Node* pParent = pNode->m_pParent;
	if (strcmp(pNode->Sort_Key, pParent->Sort_Key) > 0) {

		pParent->m_pRight = nullptr;
	}
	else {

		pParent->m_pLeft = nullptr;
	}
	AdjustHeight(pParent);
	delete pNode;
	
}

void CBst::DelLSingle(Node* pNode)
{
	//ɾ������
	Node* pP = pNode->m_pParent;
	Node* pL = pNode->m_pLeft;
	if (strcmp(pNode->Sort_Key, pP->Sort_Key) > 0) {

		pP->m_pRight = pL;
		
	}
	else {

		pP->m_pLeft = pL;
	}
	pL->m_pParent = pP;
	AdjustHeight(pL);
	delete pNode;
}

void CBst::DelRSingle(Node* pNode)
{
	//ɾ���ҵ���
	Node* pP = pNode->m_pParent;
	Node* pR = pNode->m_pRight;
	if (strcmp(pNode->Sort_Key, pP->Sort_Key) < 0) {

		pP->m_pLeft = pR;

	}
	else {

		pP->m_pRight = pR;
	}
	pR->m_pParent = pP;
	AdjustHeight(pR);
	delete pNode;

}

void CBst::DelDouble(Node* pNode)
{
	//ɾ��˫�׽ڵ�
	//�������������ֵ
	Node* pLeftMax = pNode->m_pLeft;
	while (pLeftMax->m_pRight != nullptr) {

		pLeftMax = pLeftMax->m_pRight;
	}

	//����
	char New_Sort_Key[100];
	char New_Stu_Choose_Class[100];
	strcpy_s(New_Sort_Key, 100, pLeftMax->Sort_Key);
	strcpy_s(New_Stu_Choose_Class, 100, pLeftMax->Stu_Choose_Class);

	pNode->Sort_Key = New_Sort_Key;
	pNode->Stu_Choose_Class = New_Stu_Choose_Class;
	pNode->Next_Record = pLeftMax->Next_Record;

	//ɾ�����������ֵ
	if (pLeftMax->m_pLeft == nullptr && pLeftMax->m_pRight == nullptr) {		//Ҷ�ڵ�

		DelLeaf(pLeftMax);
	}
	if (pLeftMax->m_pLeft != nullptr && pLeftMax->m_pRight == nullptr) {		//���׽ڵ�

		DelLSingle(pLeftMax);
	}
}

CBst::Node* CBst::FindNode(CMyString& Sort_Key)
{

	//����Sort_Key���ж����ݷ�������������������
	Node* pNode = m_pRoot;
	while (pNode != nullptr) {

		if (strcmp(Sort_Key, pNode->Sort_Key) < 0) {	//�������С��������������
			pNode = pNode->m_pLeft;
		}

		else if (strcmp(Sort_Key, pNode->Sort_Key) > 0) {	//������ݴ�������������
			pNode = pNode->m_pRight;
		}

		else {	//���˵���ҵ���

			return pNode;
		}
	}
	return nullptr;
}

void CBst::AdjustHeight(Node* pNode)
{
	Node* pParent = pNode->m_pParent;
	while (pParent != nullptr) {

		pParent->m_nHeight = CalcHeight(pParent);

		//�жϴ˽ڵ��Ƿ�ƽ��
		if (GetHeight(pParent->m_pRight) - GetHeight(pParent->m_pLeft) > 1) {
			Node* p500 = pParent;
			Node* p900 = p500->m_pRight;
			if (GetHeight(p900->m_pLeft) > GetHeight(p900->m_pRight)) {

				//����
				RightRotate(p900);
				LeftRotate(p500);
				return;
			}
			else {

				//����
				LeftRotate(p500);
				return;
			}
			
		}
		else if (GetHeight(pParent->m_pLeft) - GetHeight(pParent->m_pRight) > 1) {

			Node* p60 = pParent;
			Node* p20 = pParent->m_pLeft;
			if (GetHeight(p20->m_pLeft) > GetHeight(p20->m_pRight)) {

				RightRotate(p60);		//����
				return;
			}
			else {
				//����
				LeftRotate(p20);
				RightRotate(p60);
				return;
			}
			
			
		}
		pParent = pParent->m_pParent;
	}
}

int CBst::CalcHeight(Node* pNode)
{
	int nLeftHeight = (pNode->m_pLeft == nullptr ? 0 : pNode->m_pLeft->m_nHeight);
	int nRightHeight = (pNode->m_pRight == nullptr ? 0 : pNode->m_pRight->m_nHeight);
	return (nLeftHeight >= nRightHeight ? nLeftHeight + 1 : nRightHeight + 1);
}

int CBst::GetHeight(Node* pNode)
{
	return pNode == nullptr ? 0 : pNode->m_nHeight;
}

void CBst::LeftRotate(Node* pNode)
{
	Node* pP = pNode->m_pParent;
	Node* pR = pNode->m_pRight;
	Node* pRL = pR->m_pLeft;

	pNode->m_pParent = pR;
	pNode->m_pRight = pRL;

	pR->m_pParent = pP;
	pR->m_pLeft = pNode;

	if (pRL != nullptr) {

		pRL->m_pParent = pNode;
	}
	if (pP == nullptr) {

		//���ڵ㣬�������Ľڵ���Ϊ�µĸ��ڵ�
		m_pRoot = pR;
	}

	else {

		if (pP->m_pLeft == pNode) {

			pP->m_pLeft = pR;
		}
		else {

			pP->m_pRight = pR;
		}
	}
	

	

	pNode->m_nHeight = CalcHeight(pNode);
	pR->m_nHeight = CalcHeight(pR);
}

void CBst::RightRotate(Node* pNode)
{
	Node* pP = pNode->m_pParent;
	Node* pL = pNode->m_pLeft;
	Node* pLR = pL->m_pRight;

	pL->m_pParent = pP;
	pL->m_pRight = pNode;

	pNode->m_pParent = pL;
	pNode->m_pLeft = pLR;

	if (pLR != nullptr) {

		pLR->m_pParent = pNode;
	}
	
	if (pP == nullptr) {

		//���ڵ㣬�������Ľڵ���Ϊ�µĸ��ڵ�
		m_pRoot = pL;
	}

	else {

		if (pP->m_pLeft == pNode) {

			pP->m_pLeft = pL;
		}
		else {

			pP->m_pRight = pL;
		}
	}
	

	pNode->m_nHeight = CalcHeight(pNode);
	pL->m_nHeight = CalcHeight(pL);
}
