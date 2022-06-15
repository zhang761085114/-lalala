# StudentInfo
控制台版的学生信息管理系统，支持增删改查，查询时间复杂度为log(N)

​
要求：1.对100w条学生选课记录进行增删改查

2.不使用标准库里的存储类

3.不使用数据库存储

4.查询时间复杂度为O(logn)

虽然大学的时候做过这类项目，但是每次看到这个项目需求的时候，内心深处总是会产生恐惧和抵触，尤其是这4个要求，让我就更抓狂了。

1.100w条！也就是说程序跑起来都得一会儿，并且我从哪里搞到这100w条测试数据呢

2.不使用标准库里的存储类，也就是说我得自己写存储类，数组啊、二叉树啊、链表啥的，肝疼

3.不使用数据库存储，gg，增删改查就得自己来写了，还得判断数据重复、不合法等等，肝疼

4.查询时间复杂度为O(logn)，那就肯定不能用链表、数组存储了，只能用平衡二叉树

所以动手做项目前，这4点得先想清楚，脑子里有个明确的解决思路，千万别上来就int main，一定一定要先做好大致设计流程：

1.100w条数据，肯定不是一条一条手写，直接代码生成，用C++的文件流进行操作非常方便，

用50个常用汉字随机组成3个字的名字，就能有10w以上个学生姓名；自己写50个课程，每个学生选10门课，这样就有100w条数据了(按照学生ID 学生姓名 课程ID 课程名 成绩格式来生成，方便到时候以文件流的形式读进内存)，生成代码忘记保存了，不过也不难，花几个小时整一整就行了。



2.不使用标准库里的存储类，我们需要自己写一个存储类，以Key值作为排序依据，将选课记录存储在其中，对其中的数据进行增删改查~~增删改查思路这不就搞定啦！

3.不使用数据库存储，同2，自己设计能够增删改查的平衡二叉树

4.查询时间复杂度为O(logn)，能达到这个时间复杂度的，只有平衡二叉树了，所有我们需要自己写一个树，以Key值作为排序依据，将选课记录存储在其中，对结点进行增删改查~~增删改查思路这不就搞定啦！

总结起来，这其中真正的难点就是平衡二叉树类的设计及其增删改查功能，其他的交给时间就能完成。

平衡二叉树
以下是详细设计要注意的细节

1.总共要设计4课树，分别以学生ID、学生姓名、课程ID、课程名作为key排序，因为查询的时候，要根据这4个条件进行查询

2.键值对方式存储

3.一个学生ID对应一个学生，但是对应多个选课记录，一个树结点存不下，所以在结点后面附加一条链表（其他3棵树同理）



4.每次增加结点或删除结点时，要记得调整高度，进行左旋或右旋

5.删除分两种，结点删除和精准删除，比如删除某个学生ID，就是结点删除，这个学生都不存在了，所以直接把结点给删掉，他的选课记录也就全没了。。。比如删除某个选课记录，就是精准删除，你需要先找到结点，然后从结点往后面的附加链表查，当查到完全匹配的选课记录时，将那个数据给删掉


差不多就是这些，先上平衡二叉树类的代码 CBst.h和CBst.cpp

//二叉树类声明中，CMySting.h大家可以忽略，这个是我自己写的变长字符串类，嫌麻烦可以直接用c++库里的string


将平衡二叉树的功能、存储思路设计好后，后面的代码写起来就顺风顺水了

首先是以文件流的形式，一行一行读取学生选课记录，然后将其存储到4棵平衡二叉树中

​
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

​
插入
插入分3种：

新增学生（学生ID + 姓名） 
需要对CAvlTree_StuID树和CAvlTree_StuName树进行操作

CAvlTree_StuID树：通过学生ID进行排序，新增节点

CAvlTree_StuName树：通过学生姓名进行排序，新增节点

新增课程（课程ID + 课程名） 
需要对CAvlTree_ClassID树和CAvlTree_ClassName树进行操作

CAvlTree_ClassID树：通过课程ID进行排序，新增节点

CAvlTree_ClassName树：通过课程名进行排序，新增节点

新增选课记录（学生ID+课程ID+成绩）
需要对CAvlTree_StuID树、CAvlTree_ClassID树进行操作

CAvlTree_StuID树：首先通过学生ID找到相应节点，然后将新的选课记录存储在该节点的附加链表里面

CAvlTree_ClassID树：首先通过课程ID找到相应节点，然后将新的选课记录存储在该节点的附加链表里面

最后，每插入一条3.选课记录，需要将该记录同步更新到txt文件中，直接通过文件流插入到文件末尾即可。

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

删除
删除分3种：

1.删除学生（ID） 

需要对CAvlTree_StuID树、CAvlTree_StuName树、CAvlTree_ClassID树进行操作

CAvlTree_StuID树：通过学生ID找到对应节点，记录下学生姓名、课程ID，删掉该节点

CAvlTree_StuName树：通过记录的学生姓名找到对应节点，将节点及其附加链表的学生ID进行比对，删掉与学生ID匹配的数据，避免同名问题。

CAvlTree_ClassID树：通过记录的课程ID找到对应节点，如果节点及其附加链表里包含相匹配的学生ID、学生姓名的数据，删掉该数据

2.删除课程（ID） 

需要对CAvlTree_StuID树、CAvlTree_ClassID树、CAvlTree_ClassName树进行操作

CAvlTree_ClassID树：通过课程ID找到对应节点，记录下课程名、学生ID，删掉该节点

CAvlTree_ClassName树：通过记录下的课程名找到对应节点，删除该节点（不用考虑课程同名问题）

CAvlTree_StuID树:通过记录下的学生ID找到对应节点，如果节点及其附加链表包含相匹配的课程ID和课程名，删除相应数据

3.删除选课记录（学生ID+课程ID）

需要对CAvlTree_StuID树、CAvlTree_ClassID树进行操作

先从这两棵树中找到学生ID对应的姓名，课程ID对应的课程名，记录下来。

CAvlTree_StuID树：首先通过学生ID找到相应节点，如果节点及其附加链表包含相匹配的课程ID和课程名，删除相应数据

CAvlTree_ClassID树：首先通过课程ID找到相应节点，如果节点及其附加链表里包含相匹配的学生ID、学生姓名的数据，删掉该数据

最后，每删除一条记录，首先要将原txt数据全部拷贝到新的txt文件中（除了要删除的数据），然后再将新的txt文件内容写入原txt文件，达到删除效果。

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

查询
查询分6种：

但实际上相当于4种，通过学生ID、学生姓名、课程ID、课程名4种条件进行查询

（6）实现过程：通过学生ID，从CAvlTree_StuID树找到相应节点，将里面的信息打印出来
实现过程：通过学生姓名，从CAvlTree_StuName树找到相应节点，将里面的信息打印出来
（5）实现过程：通过课程ID，从CAvlTree_ClassID树找到相应节点，将里面的信息打印出来
实现过程：通过课程名，从CAvlTree_ClassName树找到相应节点，将里面的信息打印出来
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
			string Buf_Stu_ID, Buf_Stu_Name, Buf_Class_ID, Buf_Class_Name, Buf_Goal, Stu_Choose_Class[100], Buf_Other1, Buf_Other2;
			istr >> Buf_Stu_ID >> Buf_Stu_Name >> Buf_Class_ID >> Buf_Class_Name >> Buf_Goal >> Buf_Other1;
			Stu_Choose_Class[nStu_Choose_Class_Num] = Buf_Stu_ID + string(" ") + Buf_Stu_Name + string(" ") +
				Buf_Class_ID + string(" ") + Buf_Class_Name + string(" ") + Buf_Goal + string(" ") + Buf_Other1;

			if (Find_Result->Next_Record != nullptr) {			//有多条选课记录，从链表里找
				CBst::List* New_List = Find_Result->Next_Record;
				while (New_List != nullptr) {
					nStu_Choose_Class_Num++;
					istrstream istr(New_List->Stu_Choose_Class);
					istr >> Buf_Stu_ID >> Buf_Stu_Name >> Buf_Class_ID >> Buf_Class_Name >> Buf_Goal >> Buf_Other2;
					Stu_Choose_Class[nStu_Choose_Class_Num] = Buf_Stu_ID + string(" ") + Buf_Stu_Name + string(" ") +
						Buf_Class_ID + string(" ") + Buf_Class_Name + string(" ") + Buf_Goal + string(" ") + Buf_Other2;
					New_List = New_List->Next_Record;
				}
			}

			cout << "**********************" << endl << "ID对应选课记录有：" << endl;
			cout << "(学生ID " << "学生姓名 " << "课程ID " << "课程名 " << "成绩)" << endl << endl;
			for (int i = 0; i <= nStu_Choose_Class_Num; i++) {
				if (strstr(Stu_Choose_Class[i].c_str(), "已删除") == nullptr && strstr(Stu_Choose_Class[i].c_str(), "NULL") == nullptr) {
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

最后就是运行效果了：

运行程序，根据控制台指示，对学生信息进行管理

![image](https://user-images.githubusercontent.com/41890243/173800168-d3ea0e6b-6b9a-4038-aa62-41d6e0895ed3.png)

功能1：插入
输入1，按回车，进入插入功能页面

![image](https://user-images.githubusercontent.com/41890243/173800222-05b69c2c-cec9-4616-b7b6-e5808ccaf22f.png)


例如我们要新增一条选课记录，输入3，按回车，然后根据提示输入学生ID、课程ID、分数，即可插入

![image](https://user-images.githubusercontent.com/41890243/173800294-acd2ad44-4de1-4c3d-9119-293130e0158b.png)


输入4，按回车，可以返回主菜单

功能2：删除
输入2，按回车，进入删除功能页面

![image](https://user-images.githubusercontent.com/41890243/173800333-09b98964-578e-405a-a52c-668c4cc2212c.png)


例如我们要删除刚才插入的数据：学生ID--1 课程ID--40

输入3，按回车，输入1  40，显示删除成功！

![image](https://user-images.githubusercontent.com/41890243/173800367-745edf46-b0d2-4a82-a1c0-a8978a00b7a7.png)


此时我们如果再删一次刚才的数据，就会报错！

![image](https://user-images.githubusercontent.com/41890243/173800397-387a53f7-d7f6-4022-af75-d490dd17d8ad.png)


功能3：查询
输入3，按回车，进入查询功能页面

![image](https://user-images.githubusercontent.com/41890243/173800430-a46f0850-ab38-4592-ad08-bbb70c8530cd.png)


例如我们要查ID号为10的学生的选课记录，我们可以输入5，按回车，然后根据提示输入学生ID进行查询

![image](https://user-images.githubusercontent.com/41890243/173800454-ab24a56a-a61a-43fa-8b63-86fbab784193.png)






