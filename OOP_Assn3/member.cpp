# -*- coding: utf-8 -*-
#include "default.h"
#include "member.h"
#include "vote.h"
#include "group.h"
using namespace std;

//1. 회원가입
void MemberCollection::join(MemberCollection* mc, int loadMode, ofstream & inLogWrite, string *tokens, int nTokens, bool nowlogin)
{
	string RRN, ID, password;
	cout << "Selected Menu: 1.1 Register as a Member" << endl;
	if (!loadMode) //로그파일을 받아들이지 않았을경우 직접 정보를 입력받고 로그파일에 출력함
	{
		cout << "Resident Registration Number:"; fflush(stdout);
		cin >> RRN;
		cout << "ID:"; fflush(stdout);
		cin >> ID;
		cout << "Password:"; fflush(stdout);
		cin >> password;
		inLogWrite << "1 1 " << RRN << " " << ID << " " << password << " " << endl;
	}
	else { //로그파일을 받아들였을 경우 tokens를 통해 실행함
		if (nTokens != 5)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		RRN = tokens[2]; ID = tokens[3]; password = tokens[4];
		cout << "1.1 Resident Registration Number: " << RRN << endl;
		cout << "ID: " << ID << endl;
		cout << "Password:" << password << endl;
	}
	//검사시작
	if (mc->searchMember(RRN, ID) && !nowlogin) //로그인되어있고 주민번호와 ID가 겹치지 않을 경우 memberlist에 정보 추가
	{
		memberlist[mloc] = new Member;
		memberlist[mloc]->setRRN(RRN);
		memberlist[mloc]->setID(ID);
		memberlist[mloc++]->setpassword(password);
		membernum++;
		cout << "Registration Done!" << endl;
		return;
	}
	else
	{
		cout << "Registration Fail" << endl;
		return;
	}
}

bool MemberCollection::searchMember(string RRN, string ID) //RRN과 ID가 겹치는지 확인하여 true나 false로 값을 반환
{
	for (int i = 0; i < getmloc(); i++)
	{
			if (RRN == memberlist[i]->getRRN() || ID == memberlist[i]->getID())
				return false;
	}
	return true;
}
//회원 탈퇴
bool MemberCollection::unsubscribe(int loadMode, ofstream & inLogWrite, string *tokens, int nTokens, bool nowlogin, Member*& plogin, MemberCollection& mc, groupcollection& gc)
{
	string ID, password;
	cout << "Selected Menu: 2.2 Unsubscribe from System" << endl;
	if (!loadMode) //로그파일을 받아들이지 않았을 경우 정보를 직접 입력받고 로그 파일에 출력함
	{
		cout << "ID:"; fflush(stdout);
		cin >> ID;
		cout << "Password:"; fflush(stdout);
		cin >> password;
		inLogWrite << "2 2 " << ID << " " << password << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함.
		if (nTokens != 4)
		{
			cout << "invalid commandLog input format" << endl;
			return true;
		}
		ID = tokens[2]; password = tokens[3];
		cout << "ID: " << ID << endl;
		cout << "Password:" << password << endl;
	}

	int removeidx; //삭제할 memberlist의 index
	if (nowlogin && ID == plogin->getID() && password == plogin->getpassword()) //현재 로그인이 되어 있으며 ID와 password가 현재 로그인한 사람과 정보가 일치할 경우 실행
	{
		for (int i = 0; i < mloc; i++) //반복문을 돌며 입력한 ID와 memberlist에서 일치하는 ID를 찾음
		{
			if (ID == memberlist[i]->getID())
			{
				removeidx = i;
				break;
			}
		}
		memberlist[removeidx]->setID("\0"); 
		memberlist[removeidx]->setpassword("\0"); 
		memberlist[removeidx]->setRRN("\0"); //삭제할 memberlist의 정보를 모두 "\0"로 초기화시킴
		cout << "Unsubscribe Success" << endl;
		delete plogin;
		membernum--;
		return false;
	}
	else
	{
		cout << "Unsubscribe Failed" << endl;
		return true;
	}
}
//로그인
bool MemberCollection::Login(int loadMode, string *tokens, int nTokens, Member*& plogin, ofstream & inLogWrite, bool nowlogin)
{
	string ID, password, RRN;
	cout << "Selected Menu: 1.2 Login" << endl;
	if (!loadMode) //로그파일을 받아들이지 않았을 경우 직접 정보를 입력받고 로그파일에 출력함
	{
		cout << "ID:"; fflush(stdout);
		cin >> ID;
		cout << "Password:"; fflush(stdout);
		cin >> password;
		inLogWrite << "1 2 " << ID << " " << password << " " << endl;
	}
	else { //로그파일을 받아들였을 경우 tokens를 통하여 실행함
		if (nTokens != 4)
		{
			cout << "invalid commandLog input format" << endl;
			return false;
		}
		ID = tokens[2]; password = tokens[3];
		cout << "ID: " << ID << endl;
		cout << "Password:" << password << endl;
	}

	for (int i = 0; i < getmloc(); i++) //반복문을 돌면서 memberlist에 있는 ID와 password가 입력값과 일치하는 것이 있는지 찾음.
	{
		if (ID == memberlist[i]->getID() && password == memberlist[i]->getpassword())
		{
			RRN = memberlist[i]->getRRN();
			cout << "Login Success!" << endl;
			if (memberlist[i]->getgroupleader()) //memberlist[i] 객체가 가르키는 type에 따라 polymorphism을 이용한 동적할당을 진행함.
			{
				plogin = new groupleader(memberlist[i]);
			}
			else if (memberlist[i]->getgroup() && !memberlist[i]->getgroupleader())
			{
				plogin = new groupmember(memberlist[i]);
			}
			else
			{
				plogin = new Member(memberlist[i]);
			}
			return true;
		}
	}

	cout << "Login Failed" << endl;
	return false;
}

bool MemberCollection::Logout(int loadMode, string *tokens, int nTokens, Member*& plogin, ofstream & inLogWrite, bool nowlogin)
{
	cout << "Selected Menu: 2.1 Logout" << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 로그파일에 출력함
	{
		inLogWrite << "2 1 " << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함
		if (nTokens != 2)
		{
			cout << "invalid commandLog input format" << endl;
			return true;
		}
	}
		delete plogin;
		cout << "Logout Success" << endl; fflush(stdout);
		return false;
}

void MemberCollection::joingroup(int loadMode, string* tokens, int nTokens, Member*& plogin, ofstream& inLogWrite, groupcollection& gc)
{
	string gname;
	Member* copy = NULL;
	cout << "Selected Menu: 2.7 Join Group" << endl;

	cout << "<Group List>" << endl; //그룹리스트 목록을 출력함
	for (int i = 0; i < gc.getnum(); i++)
	{
		if (gc.getgroup(i)->getname() == "")
			continue;
		cout << gc.getgroup(i)->getname() << " ";
	}
	if (gc.getnum() == 0)
		cout << "None" << endl;
	else
		cout << endl;

	if (!loadMode) //로그파일을 받아들이지 않았을 경우 직접 정보를 입력받고 로그파일에 출력함
	{
		cout << "Group Name to Join:"; fflush(stdout);
		cin >> gname;
		inLogWrite << "2 7 " << gname << endl;
	}
	else { //로그파일을 받아들였을 경우 tokens를 통하여 실행함
		if (nTokens != 3)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		gname = tokens[2];
		cout << "Group Name to Join: " << gname << endl;
	}

	for (int i = 0; i < gc.getnum(); i++) //반복문을 통해 그룹명이 일치하는 그룹이 존재하는지 확인함
	{
		if (gname == gc.getgroup(i)->getname())
		{
			gc.getgroup(i)->plusgroupmember(plogin); //그룹의 member에 추가함
			gc.getgroup(i)->plusnum();
			gc.getgroup(i)->plusgloc();
			for (int j = 0; j < getmloc(); j++)
			{
				if (plogin->getID() == getMemberlist(j)->getID()) //plogin과 memberlist[j]를 다형성을 이용하여 다시 동적할당해줌
				{
					memberlist[j]->setgroup(true);
					memberlist[j]->setgroupname(gname);
					copy = new Member(memberlist[j]);
					delete memberlist[j];
					delete plogin;
					plogin = new groupmember(copy);
					memberlist[j] = new groupmember(copy);
					delete copy;
					memberlist[j]->setgroupname(gname);
				}
			}
			cout << "Group Join Success" << endl;
			return;
		}
	}

	cout << "Group Join Failed" << endl;
	return;
}

void MemberCollection::creategroup(int loadMode, string* tokens, int nTokens, Member*& plogin, ofstream& inLogWrite, groupcollection& gc)
{
	string gname;
	Member* copy;
	cout << "Selected Menu: 2.8 Create Group" << endl;

	cout << "<Group List>" << endl; // 그룹 목록 생성
	for (int i = 0; i < gc.getnum(); i++)
	{
		if (gc.getgroup(i)->getname() == "")
			continue;
		cout << gc.getgroup(i)->getname() << " ";
	}
	if (gc.getnum() == 0)
		cout << "None" << endl;
	else
		cout << endl;

	if (!loadMode) //로그파일을 받아들이지 않았을 경우 직접 정보를 입력받고 로그파일에 출력함
	{
		cout << "Group Name to Create:"; fflush(stdout);
		cin >> gname;
		inLogWrite << "2 8 " << gname << endl;
	}
	else { //로그파일을 받아들였을 경우 tokens를 통하여 실행함
		if (nTokens != 3)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		gname = tokens[2];
		cout << "Group Name to Create: " << gname << endl;
	}

	for (int i = 0; i < gc.getnum(); i++) //동일한 그룹명을 가진 그룹이 존재한다면 실패한다.
	{
		if (gname == gc.getgroup(i)->getname())
		{
			cout << "Group create Failed" << endl;
			return;
		}
	}
	
	for (int j = 0; j < getmloc(); j++)
	{
		if (plogin->getID() == getMemberlist(j)->getID()) //그룹을 만든 리더의 memberlist위치를 찾는다.
		{
			plogin->setgroup(true);
			plogin->setgroupleader(true);
			plogin->setgroupname(gname);
			copy = new Member(plogin);
			delete memberlist[j];
			delete plogin;
			plogin = new groupleader(copy);
			memberlist[j] = new groupleader(copy); //다형성을 이용한 동적할당을 진행한다.
			gc.makegroup();
			gc.getgroup(gc.getnum())->setname(gname);
			gc.getgroup(gc.getnum())->setleader(copy);
			gc.getgroup(gc.getnum())->setnum();
			gc.getgroup(gc.getnum())->setgloc();
			gc.getgroup(gc.getnum())->plusgroupmember(plogin);
			gc.getgroup(gc.getnum())->plusnum();
			gc.getgroup(gc.getnum())->plusgloc();
			gc.plusnum();
			delete copy;
		}
	}
	cout << "Group Created Success" << endl;
	return;
}

void Member::printmenu() //일반회원일 경우 출력 메뉴
{
	cout << "=======================" << endl; fflush(stdout);
	cout << "2.1 Logout" << endl; fflush(stdout);
	cout << "2.2 Unsubscribe from System" << endl; fflush(stdout);
	cout << "2.3 Delete Existing Vote Item" << endl; fflush(stdout);
	cout << "2.4 Add a Vote Item" << endl; fflush(stdout);
	cout << "2.5 List All Vote Items" << endl; fflush(stdout);
	cout << "2.6 Cast a Vote" << endl; fflush(stdout);
	cout << "2.7 Join Group" << endl; fflush(stdout);
	cout << "2.8 Create a Group" << endl; fflush(stdout);
	cout << "2.9 Program Exit" << endl; fflush(stdout);
	cout << "=======================" << endl; fflush(stdout);
}

void Member::printpos(Member*& plogin) //일반회원일 경우 현재 위치 출력
{
	cout << "[ID]: " << plogin->getID() << ", [Current Position]: ";  fflush(stdout);
	cout << "Member" << endl << "Select Menu: "; fflush(stdout);
}
//일반회원일 경우의 switch-case문
void Member::doswitchcase(int& menu, int& loadMode, ofstream& inLogWrite, string* tokens, int& nTokens, bool& nowlogin, Member*& plogin, MemberCollection& mc, voteCollection& nvc, groupcollection& gc)
{
	switch (menu)
	{
	case 1:
	{
		nowlogin = mc.Logout(loadMode, tokens, nTokens, plogin, inLogWrite, nowlogin); //로그아웃 해주는 함수 실행
		break;
	}
	case 2:
	{
		nowlogin = mc.unsubscribe(loadMode, inLogWrite, tokens, nTokens, nowlogin, plogin, mc, gc); //회원탈퇴 시켜주는 함수 실행
		break;
	}
	case 3:
	{
		nvc.deletevoteitem(loadMode, inLogWrite, nTokens, tokens, nowlogin); //투표를 삭제해주는 함수 실행
		break;
	}
	case 4:
	{
		nvc.addvoteitem(loadMode, inLogWrite, nTokens, tokens, nowlogin); //투표를 추가해주는 함수 실행
		break;
	}
	case 5:
	{
		nvc.listallvote(loadMode, nTokens, tokens, nowlogin, inLogWrite); //투표리스트를 출력하는 함수 실행
		break;
	}
	case 6:
	{
		nvc.castvote(loadMode, inLogWrite, nTokens, tokens, nowlogin, plogin, mc); //투표를 하게 해주는 함수 실행
		break;
	}
	case 7:
	{
		mc.joingroup(loadMode, tokens, nTokens, plogin, inLogWrite, gc); //그룹에 join하게 해주는 함수 실행
		break;
	}
	case 8:
	{
		mc.creategroup(loadMode, tokens, nTokens, plogin, inLogWrite, gc); //그룹을 만들어주는 함수 실행
		break;
	}
	case 9:
	{
		delete plogin;
		inLogWrite.close(); //프로그램 종료
		exit(0);
	}
	default:
		cout << "Undefined menu selection" << endl; //1~9번 이외의 값 입력했을 경우
		if (!loadMode)
			inLogWrite << 2 << " " << menu << endl;
		break;

	}
	if (!loadMode && menu != 1 && menu != 5 && menu >= 1 && menu <= 9) { //입력값이 없는 1번과 5번을 제외한 경우에는 getchar을 통해 버퍼를 비워줌
		getchar();
	}
}
