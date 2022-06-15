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
	//判空
	if (m_pRoot == nullptr) {

		m_pRoot = new Node(Sort_Key, Stu_Choose_Class);
		return;

	}

	//根据学生ID来判断数据放在左子树还是右子树
	Node* pNode = m_pRoot;
	while (pNode != nullptr) {

		if (strcmp(Sort_Key, pNode->Sort_Key) < 0) {	//如果插入数据小，则往左子树插
			if (pNode->m_pLeft == nullptr) {

				Node* pNewNode = new Node(Sort_Key, Stu_Choose_Class);
				pNode->m_pLeft = pNewNode;
				pNewNode->m_pParent = pNode;

				AdjustHeight(pNewNode);					//从新插入节点开始向上调整高度
				return;
			}
			pNode = pNode->m_pLeft;
		}

		else if (strcmp(Sort_Key, pNode->Sort_Key) > 0) {	//如果插入数据大，则往右子树插
			if (pNode->m_pRight == nullptr) {

				Node* pNewNode = new Node(Sort_Key, Stu_Choose_Class);
				pNode->m_pRight = pNewNode;
				pNewNode->m_pParent = pNode;

				AdjustHeight(pNewNode);					//从新插入节点开始向上调整高度
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
	Node* pNode = FindNode(Sort_Key);		//先找到要删除的节点
	if (pNode == nullptr) {
		return;
	}

	//删除左子树最大值
	if (pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr) {		//叶节点

		DelLeaf(pNode);
		return;
	}
	if (pNode->m_pLeft != nullptr && pNode->m_pRight == nullptr) {		//左单亲节点

		DelLSingle(pNode);
		return;
	}
	if (pNode->m_pRight != nullptr && pNode->m_pLeft == nullptr) {		//右单亲节点

		DelRSingle(pNode);
		return;
	}
	if (pNode->m_pRight != nullptr && pNode->m_pLeft != nullptr) {		//双亲节点

		DelDouble(pNode);
		return;
	}

}
//这里设置了两个Record是为了防止课程ID与学生ID重复，导致strstr得出的结果不准
void CBst::Delete(CMyString& Sort_Key, CMyString& Record1, CMyString& Record2)	
{
	Node* pNode = FindNode(Sort_Key);		//先找到要删除的节点
	if (pNode == nullptr) {
		return;
	}

	if (strstr(pNode->Stu_Choose_Class, Record1) != nullptr && strstr(pNode->Stu_Choose_Class, Record2) != nullptr) {		
		//情况1：如果删除的记录存储在节点上，将节点记录清空

		pNode->Stu_Choose_Class = ((std::string)pNode->Stu_Choose_Class + std::string(" 已删除")).c_str();
	}
	else {
		
		List* New_List = pNode->Next_Record;						
		List* New_List_Son = New_List->Next_Record;
		/*情况2：如果删除的记录存储在节点后面链表头结点上，
		删掉该链表节点*/
		if (strstr(New_List->Stu_Choose_Class, Record1) != nullptr && strstr(New_List->Stu_Choose_Class, Record2) != nullptr) {

			pNode->Next_Record = New_List->Next_Record;
			delete New_List;
		}
		/*情况3：如果删除的记录存储在节点后面链表非头结点上，删掉该链表节点*/
		else {
			if (New_List_Son == nullptr) {

				printf("删除失败，不存在该条选课记录！\n");
				return;
			}
			while (strstr(New_List_Son->Stu_Choose_Class, Record1) == nullptr || strstr(New_List_Son->Stu_Choose_Class, Record2) == nullptr) {
				
				New_List = New_List->Next_Record;
				New_List_Son = New_List_Son->Next_Record;
				if (New_List_Son == nullptr) {

					printf("删除失败，不存在该条选课记录！\n");
					return;
				}

			}
			New_List->Next_Record = New_List_Son->Next_Record;
			delete New_List_Son;
			printf("删除成功！\n");
		}
		

	}


}

void CBst::DelLeaf(Node* pNode)
{
	//删除叶子
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
	//删除左单亲
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
	//删除右单亲
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
	//删除双亲节点
	//左子树查找最大值
	Node* pLeftMax = pNode->m_pLeft;
	while (pLeftMax->m_pRight != nullptr) {

		pLeftMax = pLeftMax->m_pRight;
	}

	//交换
	char New_Sort_Key[100];
	char New_Stu_Choose_Class[100];
	strcpy_s(New_Sort_Key, 100, pLeftMax->Sort_Key);
	strcpy_s(New_Stu_Choose_Class, 100, pLeftMax->Stu_Choose_Class);

	pNode->Sort_Key = New_Sort_Key;
	pNode->Stu_Choose_Class = New_Stu_Choose_Class;
	pNode->Next_Record = pLeftMax->Next_Record;

	//删除左子树最大值
	if (pLeftMax->m_pLeft == nullptr && pLeftMax->m_pRight == nullptr) {		//叶节点

		DelLeaf(pLeftMax);
	}
	if (pLeftMax->m_pLeft != nullptr && pLeftMax->m_pRight == nullptr) {		//左单亲节点

		DelLSingle(pLeftMax);
	}
}

CBst::Node* CBst::FindNode(CMyString& Sort_Key)
{

	//根据Sort_Key来判断数据放在左子树还是右子树
	Node* pNode = m_pRoot;
	while (pNode != nullptr) {

		if (strcmp(Sort_Key, pNode->Sort_Key) < 0) {	//如果数据小，则往左子树找
			pNode = pNode->m_pLeft;
		}

		else if (strcmp(Sort_Key, pNode->Sort_Key) > 0) {	//如果数据大，则往右子树找
			pNode = pNode->m_pRight;
		}

		else {	//相等说明找到了

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

		//判断此节点是否平衡
		if (GetHeight(pParent->m_pRight) - GetHeight(pParent->m_pLeft) > 1) {
			Node* p500 = pParent;
			Node* p900 = p500->m_pRight;
			if (GetHeight(p900->m_pLeft) > GetHeight(p900->m_pRight)) {

				//右左
				RightRotate(p900);
				LeftRotate(p500);
				return;
			}
			else {

				//右右
				LeftRotate(p500);
				return;
			}
			
		}
		else if (GetHeight(pParent->m_pLeft) - GetHeight(pParent->m_pRight) > 1) {

			Node* p60 = pParent;
			Node* p20 = pParent->m_pLeft;
			if (GetHeight(p20->m_pLeft) > GetHeight(p20->m_pRight)) {

				RightRotate(p60);		//左左
				return;
			}
			else {
				//左右
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

		//根节点，提上来的节点作为新的根节点
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

		//根节点，提上来的节点作为新的根节点
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
