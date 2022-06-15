// HomeworkTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#include "CMyString.h"
#include "CBst.h"
#include <fstream>
#include <strstream>
#include <windows.h>
#include <string>
using namespace std;

CBst* CAvlTree_StuID = new CBst();								//实例化一个学生ID平衡二叉树
CBst* CAvlTree_StuName = new CBst();							//实例化一个学生姓名平衡二叉树
CBst* CAvlTree_ClassID = new CBst();							//实例化一个课程ID平衡二叉树
CBst* CAvlTree_ClassName = new CBst();							//实例化一个课程名平衡二叉树

void Read_To_Avl(fstream& fs);
void Start_Insert();
void Start_Delete();
void Start_Find();

int main() {

	fstream fs;
	fs.open("Choose_Class_Record1.txt");
	Read_To_Avl(fs);			//读取文件选课记录，存储到内存的4棵平衡二叉树中
	fs.close();					//关闭文件流

	do {

		int nChoose_Input = 0;		//根据用户输入来执行功能
		printf("初始化完毕，请选择功能：\n1.插入\n2.删除\n3.查询\n");
		scanf_s("%d", &nChoose_Input);
		switch (nChoose_Input) {

		case 1:
		{
			Start_Insert();
			break;
		}
		case 2:
		{
			Start_Delete();
			break;
		}
		case 3:
		{
			Start_Find();
			break;
		}


		}
	} while (TRUE);
	


	
	return 0;
}


//读取文件选课记录，存储到内存的4棵平衡二叉树中
void Read_To_Avl(fstream& fs) {
	int i = 0;
	string Stu_ID, Stu_Name, Class_ID, Class_Name, Class_Goal;		//存储选课记录的5个字符串
	printf("正在存储数据到二叉树中，请稍等......\n");
	while (fs >> Stu_ID >> Stu_Name >> Class_ID >> Class_Name >> Class_Goal) {

		CMyString* Sort_Key = new CMyString[4];
		CMyString* Stu_Choose_Class = new CMyString[2];

		//每读一行选课记录，将该记录存储在平衡二叉树中
		Stu_Choose_Class[0] = (Stu_ID + string(" ") + Stu_Name + string(" ") + Class_ID + string(" ")
			+ Class_Name + string(" ") + Class_Goal).c_str();
		Stu_Choose_Class[1] = (Stu_ID + string(" ") + Stu_Name + string(" ") + Class_ID + string(" ")
			+ Class_Name + string(" ") + Class_Goal).c_str();

		//存到以学生ID排序的AVL树
		Sort_Key[0] = Stu_ID.c_str();
		CAvlTree_StuID->Insert(Sort_Key[0], Stu_Choose_Class[0]);

		//存到以学生姓名排序的AVL树
		if (i % 10 == 0) {

			Sort_Key[1] = Stu_Name.c_str();
			Sort_Key[2] = Stu_ID.c_str();
			CAvlTree_StuName->Insert(Sort_Key[1], Sort_Key[2]);
		}
		

		//存到以课程ID排序的AVL树
		Sort_Key[3] = Class_ID.c_str();
		CAvlTree_ClassID->Insert(Sort_Key[3], Stu_Choose_Class[1]);

		printf("已存储数据：%d条\n", i);
		i++;

	}

	const char* szClass_Name[50] = { "语文","数学","英语","生物","化学","物理", "体育", "美术", "音乐", "C++",
	"PC汇编", "C语言", "数据结构", "MFC", "JAVA", "arm汇编", "数据库", "军事", "新闻", "渗透测试", "毛概", "近代史",
	"形势与政策", "原子弹", "氢弹", "导弹", "航空航天", "matlab", "英雄联盟", "绝地求生", "守望先锋", "魔兽争霸", "传奇",
	"QQ飞车", "跑跑卡丁车", "内卷", "拍马屁", "创新创业", "吹牛B", "逆向", "格斗", "隐身", "天马流星拳", "开飞机",
	"开坦克", "养猪", "种田", "吃饭", "睡觉", "打豆豆" };

	const char* szClass_ID[50] = { "0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19",
	"20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
	"40", "41", "42", "43", "44", "45", "46", "47", "48", "49" };
	//存到以课程名排序的AVL树
	for (int j = 0; j < 50; j++) {
		CMyString* Sort_Key = new CMyString;
		CMyString* ClassID = new CMyString;
		*Sort_Key = szClass_Name[j];
		*ClassID = szClass_ID[j];
		CAvlTree_ClassName->Insert(*Sort_Key, *ClassID);
	}

		
	

	
}

void Start_Insert()
{
	int nChoose_Input_Insert = 0;
	while (nChoose_Input_Insert != 4) {							//只要没返回主菜单，就一直停留在插入界面

		printf("请选择功能：\n1.新增学生(ID, 名字)\n2.新增课程(ID,名字)\n3.新增选课记录(学生ID, 课程ID, 分数)\n4.返回主菜单\n");
		scanf_s("%d", &nChoose_Input_Insert);
		switch (nChoose_Input_Insert) {

		case 1:
		{
			char szStu_ID[100];
			char szStu_Name[100];
			CMyString* Sort_Key = new CMyString[2];				//定义可变长字符串
			CMyString* Stu_ID = new CMyString;
			CMyString* Stu_Choose_Class = new CMyString;
			printf("请输入学生ID 学生姓名\n");
			scanf_s("%s %s", szStu_ID, 100, szStu_Name, 100);

			//将该学生ID+学生姓名存储在CAvlTree_StuName和CAvlTree_StuID中，因为他没有选课记录，暂时不用存储在别的树中
			Sort_Key[0] = szStu_Name;
			*Stu_ID = szStu_ID;
			CAvlTree_StuName->Insert(Sort_Key[0], *Stu_ID);		//存到CAvlTree_StuName

			//存到CAvlTree_StuID
			string szStu_Choose_Class;
			szStu_Choose_Class = (string)szStu_ID + string(" ") + (string)szStu_Name + string(" ") + string("NULL")
				+ string(" ") + string("NULL") + string(" ") + string("NULL");//确保成功插入，需要拼接一条空选课记录
			Sort_Key[1] = szStu_ID;
			*Stu_Choose_Class = szStu_Choose_Class.c_str();
			CAvlTree_StuID->Insert(Sort_Key[1], *Stu_Choose_Class);
			printf("插入成功！\n");
			break;


		}

		case 2:
		{
			char szClass_ID[100];
			char szClass_Name[100];
			CMyString* Sort_Key = new CMyString[2];		//定义可变长字符串
			CMyString* Class_ID = new CMyString;
			CMyString* Stu_Choose_Class = new CMyString;
			printf("请输入课程ID 课程名\n");
			scanf_s("%s %s", szClass_ID, 100, szClass_Name, 100);
			//将该课程ID+课程名存储在CAvlTree_ClassName和CAvlTree_ClassID中，因为该课程没人选，暂时不用存储在别的树中
			Sort_Key[0] = szClass_Name;
			*Class_ID = szClass_ID;
			CAvlTree_ClassName->Insert(Sort_Key[0], *Class_ID);

			string szStu_Choose_Class;
			szStu_Choose_Class = string("NULL") + string(" ") + string("NULL") + string(" ") + (string)szClass_ID
				+ string(" ") + (string)szClass_Name + string(" ") + string("NULL");
			Sort_Key[1] = szClass_ID;
			*Stu_Choose_Class = szStu_Choose_Class.c_str();
			CAvlTree_ClassID->Insert(Sort_Key[1], *Stu_Choose_Class);
			printf("插入成功！\n");
			break;


		}

		case 3:
		{
			char szStu_ID[100];
			char szClass_ID[100];
			char szGoal[100];
			CBst::Node* Find_Result = new CBst::Node();
			CMyString* Sort_Key = new CMyString[2];		//定义可变长字符串
			CMyString* Stu_Choose_Class = new CMyString[2];


			//首先根据学生ID找到学生姓名 Buf_Stu_Name
			printf("请输入学生ID 课程ID 成绩\n");
			scanf_s("%s %s %s", szStu_ID, 100, szClass_ID, 100, szGoal, 100);
			Sort_Key[0] = szStu_ID;
			Sort_Key[1] = szClass_ID;
			Find_Result = CAvlTree_StuID->FindNode(Sort_Key[0]);
			if (Find_Result == nullptr) {
				printf("插入失败！不存在该学生!\n");
				break;
			}
			istrstream istr1(Find_Result->Stu_Choose_Class);
			string Buf_Stu_ID1, Buf_Stu_Name1, Buf_Class_ID1, Buf_Class_Name1, Buf_Other1, Buf_Stu_Choose_Class;
			istr1 >> Buf_Stu_ID1 >> Buf_Stu_Name1 >> Buf_Other1;

			//然后根据课程ID找到课程名 Buf_Class_Name
			Find_Result = CAvlTree_ClassID->FindNode(Sort_Key[1]);
			if (Find_Result == nullptr) {
				printf("插入失败！不存在该课程!\n");
				break;
			}
			istrstream istr2(Find_Result->Stu_Choose_Class);
			string Buf_Stu_ID2, Buf_Stu_Name2, Buf_Class_ID2, Buf_Class_Name2, Buf_Other2;
			istr2 >> Buf_Stu_ID2 >> Buf_Stu_Name2 >> Buf_Class_ID2 >> Buf_Class_Name2 >> Buf_Other2;

			//拼接选课记录
			Buf_Stu_Choose_Class = (string)szStu_ID + string(" ") + Buf_Stu_Name1 + string(" ") + (string)szClass_ID
				+ string(" ") + Buf_Class_Name2 + string(" ") + (string)szGoal;

			Stu_Choose_Class[0] = Buf_Stu_Choose_Class.c_str();
			Stu_Choose_Class[1] = Buf_Stu_Choose_Class.c_str();
			//将该选课记录存储在CAvlTree_StuID和CAvlTree_ClassID中

			CAvlTree_StuID->Insert(Sort_Key[0], Stu_Choose_Class[0]);
			CAvlTree_ClassID->Insert(Sort_Key[1], Stu_Choose_Class[1]);
			printf("插入成功！\n");

			//及时更新到文件
			fstream fs;
			fs.open("Choose_Class_Record1.txt",ios::app);
			fs << endl << Buf_Stu_Choose_Class;
			fs.flush();
			fs.close();

			break;
		}

		case 4:
			break;


		}
	}
	

}

void Start_Delete(){
	int nChoose_Input_Delete = 0;
	while (nChoose_Input_Delete != 4) {							//只要没返回主菜单，就一直停留在删除界面

		printf("请选择功能：\n1.删除学生(ID)\n2.删除课程(ID)\n3.删除选课记录(学生ID, 课程ID)\n4.返回主菜单\n");
		scanf_s("%d", &nChoose_Input_Delete);
		switch (nChoose_Input_Delete) {
		case 1:
		{
			//删除学生，需要删除CAvlTree_StuID、CAvlTree_StuName、CAvlTree_ClassID三棵树上的相关记录
			//1.CAvlTree_StuID的删除操作
			char szStu_ID[100];
			CBst::Node* Find_Result = new CBst::Node();
			CMyString* Sort_Key = new CMyString[3];				//定义可变长字符串

			printf("请输入要删除的学生ID\n");
			scanf_s("%s", szStu_ID, 100);
			Sort_Key[0] = szStu_ID;
			Find_Result = CAvlTree_StuID->FindNode(Sort_Key[0]);
			if (Find_Result == nullptr) {

				printf("删除失败！不存在该学生!\n");
				break;
			}

			int nClass_ID = 0;									//这里主要是获取学生姓名、课程ID，用来操作删除另外两棵树
			istrstream istr(Find_Result->Stu_Choose_Class);	
			string Buf_Stu_ID, Buf_Stu_Name, Buf_Class_ID[50], Buf_Class_Name, Buf_Other;
			istr >> Buf_Stu_ID >> Buf_Stu_Name >> Buf_Class_ID[nClass_ID] >> Buf_Class_Name >> Buf_Other;
			CBst::List* Next_List = Find_Result->Next_Record;
			while (Next_List != nullptr) {
				nClass_ID++;
				istrstream istr(Next_List->Stu_Choose_Class);
				istr >> Buf_Other >> Buf_Other >> Buf_Class_ID[nClass_ID] >> Buf_Other;
				Next_List = Next_List->Next_Record;
			}
			

			CAvlTree_StuID->Delete(Sort_Key[0]);

			//2.CAvlTree_StuName的删除操作
			Sort_Key[1] = Buf_Stu_Name.c_str();
			CAvlTree_StuName->Delete(Sort_Key[1], Sort_Key[0], Sort_Key[0]);	//防止重名

			//3.CAvlTree_ClassID的删除操作
			for (int Class_ID_Num = 0; Class_ID_Num <= nClass_ID; Class_ID_Num++) {

				Sort_Key[2] = Buf_Class_ID[Class_ID_Num].c_str();
				CAvlTree_ClassID->Delete(Sort_Key[2], Sort_Key[0], Sort_Key[1]);

			}
			
			//将原文件里的所有内容写到tmp文件里（除了要删除的内容），然后再写回原文件
			fstream fs;
			fstream fs_tmp;
			fs.open("Choose_Class_Record1.txt", ios::in);
			fs_tmp.open("Choose_Class_Record1_tmp.txt", ios::out);
			string estr;
			while (getline(fs, estr)){		//得到test.txt中一行的内容
	
				if (strstr(estr.c_str(), Buf_Stu_ID.c_str()) != nullptr &&
					strstr(estr.c_str(), Buf_Stu_Name.c_str()) != nullptr) {

					continue;
					}
				fs_tmp << estr << endl;

			}
			fs_tmp.close();
			fs.close();

			fstream fs1;
			fstream fs_tmp1;
			fs1.open("Choose_Class_Record1.txt", ios::out);
			fs_tmp1.open("Choose_Class_Record1_tmp.txt", ios::in);

			while (getline(fs_tmp1, estr)) //将temp.txt的内容写到test.txt
			{
				fs1 << estr << endl;
			}
			fs1.close();
			fs_tmp1.close();
			remove("Choose_Class_Record1_tmp.txt");

			printf("删除成功！\n");
			break;
		}

		case 2:
		{
			//删除课程，需要删除CAvlTree_StuID、CAvlTree_ClassID、CAvlTree_ClassName三棵树上的相关记录
			//1.CAvlTree_ClassID的删除操作
			char szClass_ID[100];
			CBst::Node* Find_Result = new CBst::Node();
			CMyString* Sort_Key = new CMyString[3];				//定义可变长字符串

			printf("请输入要删除的课程ID\n");
			scanf_s("%s", szClass_ID, 100);
			Sort_Key[0] = szClass_ID;
			Find_Result = CAvlTree_ClassID->FindNode(Sort_Key[0]);
			if (Find_Result == nullptr) {

				printf("删除失败！不存在该课程!\n");
				break;
			}

			int nStu_ID = 0;									//这里主要是获取课程名、学生ID，用来操作删除另外两棵树
			istrstream istr(Find_Result->Stu_Choose_Class);
			string Buf_Stu_ID[10000], Buf_Stu_Name, Buf_Class_ID, Buf_Class_Name, Buf_Other;
			istr >> Buf_Stu_ID[nStu_ID] >> Buf_Stu_Name >> Buf_Class_ID >> Buf_Class_Name >> Buf_Other;
			CBst::List* Next_List = Find_Result->Next_Record;
			while (Next_List != nullptr) {
				nStu_ID++;
				istrstream istr(Next_List->Stu_Choose_Class);
				istr >> Buf_Stu_ID[nStu_ID] >> Buf_Other;
				Next_List = Next_List->Next_Record;
			}


			CAvlTree_ClassID->Delete(Sort_Key[0]);

			//2.CAvlTree_ClassName的删除操作
			Sort_Key[1] = Buf_Class_Name.c_str();
			CAvlTree_ClassName->Delete(Sort_Key[1]);

			//3.CAvlTree_StuID的删除操作
			for (int Stu_ID_Num = 0; Stu_ID_Num <= nStu_ID; Stu_ID_Num++) {

				Sort_Key[2] = Buf_Stu_ID[Stu_ID_Num].c_str();
				CAvlTree_StuID->Delete(Sort_Key[2], Sort_Key[0], Sort_Key[1]);

			}

			//将原文件里的所有内容写到tmp文件里（除了要删除的内容），然后再写回原文件
			fstream fs;
			fstream fs_tmp;
			fs.open("Choose_Class_Record1.txt", ios::in);
			fs_tmp.open("Choose_Class_Record1_tmp.txt", ios::out);
			string estr;
			while (getline(fs, estr)) {		//得到test.txt中一行的内容

				if (strstr(estr.c_str(), Buf_Class_ID.c_str()) != nullptr &&
					strstr(estr.c_str(), Buf_Class_Name.c_str()) != nullptr) {

					continue;
				}
				fs_tmp << estr << endl;

			}
			fs_tmp.close();
			fs.close();

			fstream fs1;
			fstream fs_tmp1;
			fs1.open("Choose_Class_Record1.txt", ios::out);
			fs_tmp1.open("Choose_Class_Record1_tmp.txt", ios::in);

			while (getline(fs_tmp1, estr)) //将temp.txt的内容写到test.txt
			{
				fs1 << estr << endl;
			}
			fs1.close();
			fs_tmp1.close();
			remove("Choose_Class_Record1_tmp.txt");
			printf("删除成功！\n");
			break;

		}

		case 3:
		{
			//删除选课记录，需要删除CAvlTree_StuID、CAvlTree_ClassID两棵树上的相关记录
			//1.CAvlTree_StuID的删除操作
			char szStu_ID[100];
			char szClass_ID[100];

			CBst::Node* Find_Result = new CBst::Node();
			CMyString* Sort_Key = new CMyString[4];				//定义可变长字符串

			printf("请输入要删除的学生ID + 课程ID\n");
			scanf_s("%s %s", szStu_ID, 100, szClass_ID, 100);
			Sort_Key[0] = szStu_ID;
			Sort_Key[1] = szClass_ID;
			Find_Result = CAvlTree_StuID->FindNode(Sort_Key[0]);
			if (Find_Result == nullptr) {

				printf("删除失败！不存在该学生!\n");
				break;
			}

			//这里主要是获取课程名、学生姓名，用来操作删除两棵树
			istrstream istr1(Find_Result->Stu_Choose_Class);
			string Buf_Stu_ID1, Buf_Stu_Name1, Buf_Class_ID1, Buf_Class_Name1, Buf_Other1;
			istr1 >> Buf_Stu_ID1 >> Buf_Stu_Name1 >> Buf_Class_ID1 >> Buf_Class_Name1 >> Buf_Other1;
			Sort_Key[2] = Buf_Stu_Name1.c_str();

			Find_Result = CAvlTree_ClassID->FindNode(Sort_Key[1]);
			if (Find_Result == nullptr) {

				printf("删除失败！不存在该课程!\n");
				break;
			}
			istrstream istr2(Find_Result->Stu_Choose_Class);
			string Buf_Stu_ID2, Buf_Stu_Name2, Buf_Class_ID2, Buf_Class_Name2, Buf_Other2;
			istr2 >> Buf_Stu_ID2 >> Buf_Stu_Name2 >> Buf_Class_ID2 >> Buf_Class_Name2 >> Buf_Other2;
			Sort_Key[3] = Buf_Class_Name2.c_str();

			//删除两棵树上的记录
			CAvlTree_StuID->Delete(Sort_Key[0], Sort_Key[1], Sort_Key[3]);
			CAvlTree_ClassID->Delete(Sort_Key[1], Sort_Key[0], Sort_Key[2]);


			//将原文件里的所有内容写到tmp文件里（除了要删除的内容），然后再写回原文件
			fstream fs;
			fstream fs_tmp;
			fs.open("Choose_Class_Record1.txt", ios::in);
			fs_tmp.open("Choose_Class_Record1_tmp.txt", ios::out);
			string estr;
			while (getline(fs, estr)) {		//得到test.txt中一行的内容

				if (strstr(estr.c_str(), Buf_Stu_ID1.c_str()) != nullptr &&
					strstr(estr.c_str(), Buf_Stu_Name1.c_str()) != nullptr &&
					strstr(estr.c_str(), Buf_Class_ID2.c_str()) != nullptr &&
					strstr(estr.c_str(), Buf_Class_Name2.c_str()) != nullptr) {

					continue;
				}
				fs_tmp << estr << endl;

			}
			fs_tmp.close();
			fs.close();

			fstream fs1;
			fstream fs_tmp1;
			fs1.open("Choose_Class_Record1.txt", ios::out);
			fs_tmp1.open("Choose_Class_Record1_tmp.txt", ios::in);

			while (getline(fs_tmp1, estr)) //将temp.txt的内容写到test.txt
			{
				fs1 << estr << endl;
			}
			fs1.close();
			fs_tmp1.close();
			remove("Choose_Class_Record1_tmp.txt");
			break;

		}

		case 4:
			break;


		}

	}
}

void Start_Find()
{
	int nChoose_Input_Find = 0;
	while (nChoose_Input_Find != 7) {							//只要没返回主菜单，就一直停留在删除界面

		printf("请选择功能：\n1.学生ID查姓名\n2.学生姓名查ID\n3.课程ID查课程名\n4.课程名查课程ID\n5.学生ID查选课信息\n6.课程ID查选课信息\n7.返回主菜单\n");
		scanf_s("%d", &nChoose_Input_Find);
		switch (nChoose_Input_Find) {
		case 1:
		{
			char szStu_ID[100];
			CBst::Node* Find_Result = new CBst::Node();
			CMyString* Sort_Key = new CMyString;				//定义可变长字符串

			//从CAvlTree_StuID树里查学生姓名
			printf("请输入学生ID\n");
			scanf_s("%s", szStu_ID, 100);
			*Sort_Key = szStu_ID;
			Find_Result = CAvlTree_StuID->FindNode(*Sort_Key);
			if (Find_Result == nullptr) {

				printf("查询失败！不存在该学生!\n");
				break;
			}

			//找到学生姓名Buf_Stu_Name
			istrstream istr(Find_Result->Stu_Choose_Class);
			string Buf_Stu_ID, Buf_Stu_Name, Buf_Class_ID, Buf_Class_Name, Buf_Other;
			istr >> Buf_Stu_ID >> Buf_Stu_Name >> Buf_Class_ID >> Buf_Class_Name >> Buf_Other;
			cout << "**********************" << endl << "ID对应学生姓名为：" << Buf_Stu_Name << endl << "**********************" << endl;
			break;
		}

		case 2:
		{
			char szStu_Name[100];
			CBst::Node* Find_Result = new CBst::Node();
			CMyString* Sort_Key = new CMyString;				//定义可变长字符串

			//从CAvlTree_StuName树里查学生ID
			printf("请输入学生姓名\n");
			scanf_s("%s", szStu_Name, 100);
			*Sort_Key = szStu_Name;
			Find_Result = CAvlTree_StuName->FindNode(*Sort_Key);
			if (Find_Result == nullptr || strstr(Find_Result->Stu_Choose_Class, "已删除") != nullptr) {

				printf("查询失败！不存在该学生!\n");
				break;
			}

			//找到学生ID Buf_Stu_ID			
			istrstream istr(Find_Result->Stu_Choose_Class);
			int nStuID = 0;
			string Buf_Stu_ID[100];
			istr >> Buf_Stu_ID[nStuID];

			if (Find_Result->Next_Record != nullptr) {			//可能有重名的，还要往链表里查找
				CBst::List* New_List = Find_Result->Next_Record;
				while (New_List != nullptr) {
					nStuID++;
					istrstream istr(New_List->Stu_Choose_Class);
					istr >> Buf_Stu_ID[nStuID];
					New_List = New_List->Next_Record;
				}
			}
			cout << "**********************" << endl << "学生姓名对应ID为：";
			for (int i = 0; i <= nStuID; i++) {

				cout << Buf_Stu_ID[i] << "  ";
			}
			cout << endl << "**********************" << endl;
			break;

		}

		case 3:
		{
			char szClass_ID[100];
			CBst::Node* Find_Result = new CBst::Node();
			CMyString* Sort_Key = new CMyString;				//定义可变长字符串

			//从CAvlTree_ClassID树里查课程名
			printf("请输入课程ID\n");
			scanf_s("%s", szClass_ID, 100);
			*Sort_Key = szClass_ID;
			Find_Result = CAvlTree_ClassID->FindNode(*Sort_Key);
			if (Find_Result == nullptr) {

				printf("查询失败！不存在该课程!\n");
				break;
			}

			//找到课程名Buf_Class_Name
			istrstream istr(Find_Result->Stu_Choose_Class);
			string Buf_Stu_ID, Buf_Stu_Name, Buf_Class_ID, Buf_Class_Name, Buf_Other;
			istr >> Buf_Stu_ID >> Buf_Stu_Name >> Buf_Class_ID >> Buf_Class_Name >> Buf_Other;
			cout << "**********************" << endl << "ID对应课程名为：" << Buf_Class_Name << endl << "**********************" << endl;
			break;
		}

		case 4:
		{
			char szClass_Name[100];
			CBst::Node* Find_Result = new CBst::Node();
			CMyString* Sort_Key = new CMyString;				//定义可变长字符串

			//从CAvlTree_ClassName树里查课程ID
			printf("请输入课程名\n");
			scanf_s("%s", szClass_Name, 100);
			*Sort_Key = szClass_Name;
			Find_Result = CAvlTree_ClassName->FindNode(*Sort_Key);
			if (Find_Result == nullptr) {

				printf("查询失败！不存在该课程!\n");
				break;
			}

			//找到课程ID Buf_Class_ID			课程是不会重名的，所以不需要查节点链表
			istrstream istr(Find_Result->Stu_Choose_Class);
			string Buf_Class_ID;
			istr >> Buf_Class_ID;
			cout << "**********************" << endl << "课程名对应ID为：" << Buf_Class_ID << endl << "**********************" << endl;
			break;
		}

		case 5:
		{
			char szStu_ID[100];
			CBst::Node* Find_Result = new CBst::Node();
			CMyString* Sort_Key = new CMyString;				//定义可变长字符串

			//从CAvlTree_StuID树里查学生选课记录
			printf("请输入学生ID\n");
			scanf_s("%s", szStu_ID, 100);
			*Sort_Key = szStu_ID;
			Find_Result = CAvlTree_StuID->FindNode(*Sort_Key);
			if (Find_Result == nullptr) {

				printf("查询失败！不存在该学生!\n");
				break;
			}

			//找到学生选课记录
			istrstream istr(Find_Result->Stu_Choose_Class);
			int nStu_Choose_Class_Num = 0;
			string Buf_Stu_ID, Buf_Stu_Name, Buf_Class_ID, Buf_Class_Name, Buf_Goal, Stu_Choose_Class[100];
			istr >> Buf_Stu_ID >> Buf_Stu_Name >> Buf_Class_ID >> Buf_Class_Name >> Buf_Goal;
			Stu_Choose_Class[nStu_Choose_Class_Num] = Buf_Stu_ID + string(" ") + Buf_Stu_Name + string(" ") +
				Buf_Class_ID + string(" ") + Buf_Class_Name + string(" ") + Buf_Goal;

			if (Find_Result->Next_Record != nullptr) {			//有多条选课记录，从链表里找
				CBst::List* New_List = Find_Result->Next_Record;
				while (New_List != nullptr) {
					nStu_Choose_Class_Num++;
					istrstream istr(New_List->Stu_Choose_Class);
					istr >> Buf_Stu_ID >> Buf_Stu_Name >> Buf_Class_ID >> Buf_Class_Name >> Buf_Goal;
					Stu_Choose_Class[nStu_Choose_Class_Num] = Buf_Stu_ID + string(" ") + Buf_Stu_Name + string(" ") +
						Buf_Class_ID + string(" ") + Buf_Class_Name + string(" ") + Buf_Goal;
					New_List = New_List->Next_Record;
				}
			}

			cout << "**********************" << endl << "ID对应选课记录有：" << endl;
			cout << "(学生ID " << "学生姓名 " << "课程ID " << "课程名 " << "成绩)" << endl << endl;
			for (int i = 0; i <= nStu_Choose_Class_Num; i++) {
				if (strstr(Stu_Choose_Class[i].c_str(), "NULL") == nullptr && strstr(Stu_Choose_Class[i].c_str(), "已删除") == nullptr) {
					cout << Stu_Choose_Class[i] << endl;
				}
				
			}
			cout << endl << "**********************" << endl;
			break;
		}

		case 6:
		{
			char szClass_ID[100];
			CBst::Node* Find_Result = new CBst::Node();
			CMyString* Sort_Key = new CMyString;				//定义可变长字符串

			//从CAvlTree_ClassID树里查选课记录
			printf("请输入课程ID\n");
			scanf_s("%s", szClass_ID, 100);
			*Sort_Key = szClass_ID;
			Find_Result = CAvlTree_ClassID->FindNode(*Sort_Key);
			if (Find_Result == nullptr) {

				printf("查询失败！不存在该课程!\n");
				break;
			}

			//找到选课记录
			istrstream istr(Find_Result->Stu_Choose_Class);
			string Buf_Stu_ID, Buf_Stu_Name, Buf_Class_ID, Buf_Class_Name, Buf_Goal, Stu_Choose_Class;
			istr >> Buf_Stu_ID >> Buf_Stu_Name >> Buf_Class_ID >> Buf_Class_Name >> Buf_Goal;
			Stu_Choose_Class = Buf_Stu_ID + string(" ") + Buf_Stu_Name + string(" ") +
				Buf_Class_ID + string(" ") + Buf_Class_Name + string(" ") + Buf_Goal;
			cout << "**********************" << endl << "ID对应选课记录有：" << endl;
			cout << "(学生ID " << "学生姓名 " << "课程ID " << "课程名 " << "成绩)" << endl << endl;
			cout << Stu_Choose_Class << endl;
			//一个课程会有多个学生选，因此要查链表
			if (Find_Result->Next_Record != nullptr) {			//有多条选课记录，从链表里找
				CBst::List* New_List = Find_Result->Next_Record;
				while (New_List != nullptr) {
					istrstream istr(New_List->Stu_Choose_Class);
					istr >> Buf_Stu_ID >> Buf_Stu_Name >> Buf_Class_ID >> Buf_Class_Name >> Buf_Goal;
					Stu_Choose_Class = Buf_Stu_ID + string(" ") + Buf_Stu_Name + string(" ") +
						Buf_Class_ID + string(" ") + Buf_Class_Name + string(" ") + Buf_Goal;
					New_List = New_List->Next_Record;
					if (strstr(Stu_Choose_Class.c_str(), "NULL") == nullptr && strstr(Stu_Choose_Class.c_str(), "已删除") == nullptr) {
						cout << Stu_Choose_Class << endl;
					}
				}
			}

			cout << endl << "**********************" << endl;
			break;
		}

		case 7:
			break;


		}
	}

}
