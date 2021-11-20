# -*- coding: utf-8 -*-
#include "default.h"
#include "member.h"
#include "vote.h"
#include "group.h"
using namespace std;

int printMenu1() //처음에 로그 파일의 포함 여부를 정하는 메뉴를 출력한다.
{
	string line;
	int loadMode;
	cout << "Load log file?(1:yes, 0:no (log will be deleted)):"; fflush(stdout);
	getline(cin, line);
	loadMode = atoi(line.c_str());
	return loadMode;
}

void printnum(int num) //몇번째 작업이 진행중인지 출력해줌
{
	cout << "\n\n=======================" << endl; fflush(stdout);
	cout << "Num:" << num << endl; fflush(stdout);
}

void printMenu2() //nonmember일 경우 메뉴 출력
{
	cout << "=======================" << endl; fflush(stdout);
	cout << "1.1 Register as a Member" << endl; fflush(stdout);
	cout << "1.2 Login" << endl; fflush(stdout);
	cout << "1.3 Program Exit" << endl; fflush(stdout);
	cout << "=======================" << endl; fflush(stdout);
}

void clearTokens(string * tokens) //Tokens를 비워주는 역할을 한다.
{
	for (int i = 0; i < 6; i++)
		tokens[i].clear();
}

void viewall(int loadMode, ofstream& inLogWrite, int nTokens, MemberCollection& mc, voteCollection& nvc, groupcollection& gc)
{
	if (!loadMode) //로그파일을 입력받지 않았을 경우 로그파일에 출력함.
	{
		inLogWrite << "0 0" << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함.
		if (nTokens != 2)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
	}

	cout << "<Member List>" << endl;
	for (int i = 0; i < mc.getmloc(); i++) //모든 멤버의 정보를 보여줌
	{
		if (mc.getMemberlist(i)->getID() != "")
		{
			cout << "[ID]: " << mc.getMemberlist(i)->getID();
			cout << ", [Joined  Group]: ";
			if (mc.getMemberlist(i)->getgroup())
				cout << mc.getMemberlist(i)->getgroupname();
			else
				cout << "None";
			cout << ", [Position]: ";
			if (!mc.getMemberlist(i)->getgroup())
				cout << "Member" << endl;
			else if (mc.getMemberlist(i)->getgroupleader())
				cout << "Group Leader" << endl;
			else
				cout << "Group Member" << endl;
		}
	}
	cout << "<Group List>" << endl;
	for (int i = 0; i < gc.getnum(); i++) //모든 그룹의 정보를 보여줌
	{
		if (gc.getgroup(i)->getname() == "")
			continue;
		cout << gc.getgroup(i)->getname() << " ";
	}
	if (gc.getnum() == 0)
		cout << "None" << endl;
	else
		cout << endl;

	cout << "<General Votes>" << endl;
	for (int i = 0; i < nvc.getloc(); i++) //모든 일반투표의 정보를 보여줌
	{
		if (nvc.getvotelist(i)->getsubject() == "")
			continue;
		cout << nvc.getvotelist(i)->getsubject() << " ";
	}
	if (nvc.getnsubject() == 0)
		cout << "None" << endl;
	else
		cout << endl;

	cout << "<Group Votes>" << endl;
	for (int i = 0; i < gc.getnum(); i++) //모든 그룹투표의 정보를 보여줌
	{
		cout << gc.getgroup(i)->getname() << ": ";
		for (int j = 0; j < gc.getgroup(i)->getvc().getloc(); j++)
		{
			if (gc.getgroup(i)->getname() == "")
				continue;
			cout << gc.getgroup(i)->getvc().getvotelist(j)->getsubject() << " ";
		}
		if (gc.getgroup(i)->getvc().getnsubject() == 0)
			cout << "None";
		cout << endl;
	}
	if (gc.getnum() == 0)
		cout << "None" << endl;
	else
		cout << endl;
}

void doTask() //실질적인 역할을 수행하는 함수이다. 이 함수 안에서 대부분의 작업이 실행된다.
{
	//설명: 메인함수의 작업부분이다. 메뉴를 파싱하여 명령에 맞는 작업을 진행한다.
	// 메뉴 파싱을 위한 변수
	int menu1 = 0; //실행할 메뉴의 번호를 저장하는 변수이다.
	int menu2 = 0; //실행할 메뉴의 번호를 저장하는 변수이다.
	int num = 1; //수행 횟수를 저장하는 변수이다.
	int loadMode; //로그 파일의 로드 여부를 저장하는 변수이다. 1이면 로드 파일이 로드되고 0이면 로드되지 않는다.
	ofstream inLogWrite; //파일 입출력에서 로그 텍스트 파일로 출력해주는 역할을 한다.
	ifstream inLogRead; //파일 입출력에서 로그 텍스트 파일에서 입력을 받아들이는 역할을 한다.
	string tokens[6], line; //로그 파일에서 토큰을 저장하고 line을 받아들이는 역할을 한다.
	stringstream stream; //토큰을 얻을 수 있게 하는 역할을 한다.
	int nTokens=0; //number of tokens in string
	bool nowlogin = false; //현재 로그인 상태를 나타낸다.
	Member* plogin = NULL; //현재 로그인 되어있는 멤버의 정보를 저장한다.

	loadMode = printMenu1();

	MemberCollection mc; //전체 멤버를 관리하는 membercollection 변수이다.
	voteCollection nvc; //전체 일반 투표를 관리하는 votecollection 변수이다.
	groupcollection gc;

	if (!loadMode) { //로그 파일을 입력받지 않았을 경우 새롭게 로그 파일에 출력한다.
		inLogWrite.open(COMMAND_LOG_FILE_NAME, ios::out);
	}
	else { //로그 파일을 입력받았을 경우 로그 파일을 입력받고 그 뒤에 계속 이어서 달게 한다.
		inLogRead.open(COMMAND_LOG_FILE_NAME,ios::in); //read mode
		inLogWrite.open(COMMAND_LOG_FILE_NAME, ios::in|ios::app); //concat without truncation
	}

	// 종료 메뉴가 입력되기 전까지 반복함
	while (1)
	{
		//Menu Parsing
		printnum(num++); // 입력파일에서 메뉴 숫자 읽기

		if (!nowlogin) //로그인이 안되어있는 경우
		{
			printMenu2();
			cout << "[Current Position]: ";  fflush(stdout);
			cout << "Non Member" << endl << "Select Menu: ";  fflush(stdout);
		}
		else //로그인이 되어 있는 경우 다형성을 이용하여 menu와 pos를 출력한다.
		{
			plogin->printmenu();
			plogin->printpos(plogin);
		}

		if (loadMode == 1) //로그 파일을 입력 받았을 경우
		{
			getline(inLogRead, line);
			if (line == "")
			{
				//end of file with newline
				if (inLogRead.eof())
				{
					//stop reading from logfile 
					//stdin mode starts
					inLogRead.close();
					loadMode = 0;
					getline(cin, line);
					//when first stdin input was newline
					//continue without loggin input
					if (line == "")
					{
						cout << "Selected Menu: Undefined menu selection" << endl; fflush(stdout);
						continue;
					}
					stream.str(line);
					nTokens = 0;
					clearTokens(tokens);
					while (stream >> tokens[nTokens]) //한 줄에서 token들을 입력받아서 저장함
						nTokens++;
					stream.clear();
					menu1 = atoi(tokens[0].c_str());
					menu2 = atoi(tokens[1].c_str());
				}
				//middle of file with new line
				//continue without logging
				else
				{
					cout << "\nSelected Menu: Undefined menu selection" << endl; fflush(stdout);
					continue;
				}
			}

			//inputs != newline
			else
			{
				stream.str(line);
				nTokens = 0;
				clearTokens(tokens);
				//Read all tokens(seperated by " ")
				while (stream >> tokens[nTokens]) //한 줄에서 token들을 입력받아서 저장함
					nTokens++;
				stream.clear();
				menu1 = atoi(tokens[0].c_str());
				menu2 = atoi(tokens[1].c_str());
				cout << menu1 << " " << menu2 << endl; fflush(stdout);
			}


		}
		//stdin mode
		else
		{
			getline(cin, line);
			if (line == "")
			{
				cout << "Selected Menu: Undefined menu selection" << endl; fflush(stdout);
				continue;
			}
			stream.str(line);
			nTokens = 0;
			clearTokens(tokens);
			while (stream >> tokens[nTokens]) //한 줄에서 token들을 입력받아서 저장함
				nTokens++;
			stream.clear();
			menu1 = atoi(tokens[0].c_str());
			menu2 = atoi(tokens[1].c_str());
		}
		if (!nowlogin) //로그인이 안되어있는 경우
		{
			switch (menu2)
			{
			case 0:
			{
				viewall(loadMode, inLogWrite, nTokens, mc, nvc, gc);
				break;
			}
			case 1:
			{
				mc.join(&mc, loadMode, inLogWrite, tokens, nTokens, nowlogin); //회원가입 함수
				break;
			}
			case 2:
			{
				nowlogin = mc.Login(loadMode, tokens, nTokens, plogin, inLogWrite, nowlogin); //회원탈퇴 시켜주는 함수 실행
				break;
			}
			case 3:
			{
				inLogWrite.close(); //프로그램 종료
				return;
			}
			default:
				cout << "Undefined menu selection" << endl; //1~3번 이외의 값 입력했을 경우
				if (!loadMode)
					inLogWrite << menu1 << " " << menu2 << endl;
				break;

			}
			if (!loadMode && menu2 != 0 && menu2 >= 1 && menu2 <= 3) { //getchar을 통해 버퍼를 비워줌
				getchar();
			}
		}
		else
			plogin->doswitchcase(menu2, loadMode, inLogWrite, tokens, nTokens, nowlogin, plogin, mc, nvc, gc);
	}
	return;
}
