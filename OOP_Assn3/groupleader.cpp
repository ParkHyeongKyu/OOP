# -*- coding: utf-8 -*-
#include "default.h"
#include "member.h"
#include "vote.h"
#include "group.h"
using namespace std;

extern void viewall(int loadMode, ofstream& inLogWrite, int nTokens, MemberCollection& mc, voteCollection& nvc, groupcollection& gc);

void groupleader::printmenu() //그룹 리더일 경우 메뉴 출력
{
	cout << "=======================" << endl; fflush(stdout);
	cout << "4.1 Logout" << endl; fflush(stdout);
	cout << "4.2 Delete Existing Vote Item" << endl; fflush(stdout);
	cout << "4.3 Add a Vote Item" << endl; fflush(stdout);
	cout << "4.4 List All Vote Items" << endl; fflush(stdout);
	cout << "4.5 Cast a Vote" << endl; fflush(stdout);
	cout << "4.6 List All Group Members" << endl; fflush(stdout);
	cout << "4.7 Ban a Member from Group" << endl; fflush(stdout);
	cout << "4.8 Program Exit" << endl; fflush(stdout);
	cout << "=======================" << endl; fflush(stdout);
}

void groupleader::printpos(Member*& plogin) //그룹 리더일 경우 현재 위치 출력
{
	cout << "[ID]: " << plogin->getID() << ", [Current Position]: ";  fflush(stdout);
	cout << "Group Leader" << ", [Joined Group]: " << plogin->getgroupname() << endl << "Select Menu: "; fflush(stdout);
}
//그룹 리더일 경우 switch-case문
void groupleader::doswitchcase(int& menu, int& loadMode, ofstream& inLogWrite, string* tokens, int& nTokens, bool& nowlogin, Member*& plogin, MemberCollection& mc, voteCollection& nvc, groupcollection& gc)
{
	switch (menu)
	{
	case 0:
	{
		viewall(loadMode, inLogWrite, nTokens, mc, nvc, gc); //현재 프로그램 내에 존재하는 모든 정보 출력
		break;
	}
	case 1:
	{
		nowlogin = Logout(loadMode, tokens, nTokens, plogin, inLogWrite, nowlogin); //로그아웃 해주는 함수 실행
		break;
	}
	case 2:
	{
		deletevoteitem(loadMode, inLogWrite, nTokens, tokens, nowlogin, nvc, gc); //투표를 삭제해주는 함수 실행
		break;
	}
	case 3:
	{
		addvoteitem(loadMode, inLogWrite, nTokens, tokens, nowlogin, nvc, gc); //투표를 추가해주는 함수 실행
		break;
	}
	case 4:
	{
		listallvote(loadMode, nTokens, tokens, nowlogin, inLogWrite, nvc, gc); //투표리스트를 출력하는 함수 실행
		break;
	}
	case 5:
	{
		castvote(loadMode, inLogWrite, nTokens, tokens, nowlogin, plogin, mc, nvc, gc); //투표를 하게 해주는 함수 실행
		break;
	}
	case 6:
	{
		listgroupmember(loadMode, inLogWrite, nTokens, gc);
		break;
	}
	case 7:
	{
		banmember(loadMode, inLogWrite, nTokens, tokens, mc, gc); //멤버 추방메뉴 실행
		break;
	}
	case 8:
	{
		delete plogin;
		inLogWrite.close(); //프로그램 종료
		exit(0);
	}
	default:
		cout << "Undefined menu selection" << endl; //1~7번 이외의 값 입력했을 경우
		if (!loadMode)
			inLogWrite << 4 << " " << menu << endl;
		break;

	}
	if (!loadMode && menu != 0 && menu != 1 && menu != 4 && menu != 6 && menu >= 0 && menu <= 8) { //입력값이 없는 0번, 1번, 4번, 6번을 제외한 경우에는 getchar을 통해 버퍼를 비워줌
		getchar();
	}
}

bool groupleader::Logout(int loadMode, string *tokens, int nTokens, Member*& plogin, ofstream & inLogWrite, bool nowlogin)
{
	cout << "Selected Menu: 4.1 Logout" << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 로그파일에 출력함
	{
		inLogWrite << "4 1 " << " " << endl;
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

void groupleader::deletevoteitem(int loadMode, ofstream& inLogWrite, int nTokens, string* tokens, bool nowlogin, voteCollection& nvc, groupcollection& gc)
{
	string voteitem;
	group* g = NULL;
	int type;
	for (int i = 0; gc.getnum(); i++) //현재 위치하는 그룹 찾음
	{
		if (this->getgroupname() == gc.getgroup(i)->getname())
		{
			g = gc.getgroup(i);
			break;
		}
	}
	cout << "Selected Menu: 4.2 Delete Existing Vote" << endl;
	cout << "<General Votes>" << endl; //일반 투표 목록 출력
	for (int i = 0; i < nvc.getloc(); i++)
	{
		if (nvc.getvotelist(i)->getsubject() == "")
			continue;
		cout << nvc.getvotelist(i)->getsubject() << " ";
	}
	if (nvc.getnsubject() == 0)
		cout << "None" << endl;
	else
		cout << endl;
	cout << "<Group Votes>" << endl; //그룹 투표 목록 출력
	for (int i = 0; i < g->getvc().getloc(); i++)
	{
		if (g->getvc().getvotelist(i)->getsubject() == "")
			continue;
		cout << g->getvc().getvotelist(i)->getsubject() << " ";
	}
	if (g->getvc().getnsubject() == 0)
		cout << "None" << endl;
	else
		cout << endl;

	if (!loadMode) //로그파일을 입력받지 않았을 경우 정보를 입력받고 로그파일에 출력함
	{
		cout << "Select Vote Type(0: general, 1: group): ";  fflush(stdout);
		cin >> type;
		cout << "Vote Subject to Delete: "; fflush(stdout);
		cin >> voteitem;
		inLogWrite << "4 2 " << type << " " << voteitem << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함
		if (nTokens != 4)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		type = atoi(tokens[2].c_str()), voteitem = tokens[3];
		cout << "Select Vote Type(0: general, 1: group): " << type << endl;
		cout << "Vote Subject to Delete: " << voteitem << endl;
	}

	if (type == 1)
	{
		for (int i = 0; i < g->getvc().getloc(); i++) //반복문을 돌면서 입력받은 주제와 일치하는 주제가 votelist에 존재하는지 검사함
		{
			if (g->getvc().getvotelist(i)->getsubject() == voteitem)
			{
				g->getvc().getvotelist(i)->setsubject("\0");
				g->getvc().getvotelist(i)->setitemnum(0);
				g->getvc().minusnsubject();
				cout << "Vote Deleted!" << endl;
				return;
			}
		}
	}
	else
	{
		for (int i = 0; i < nvc.getloc(); i++) //반복문을 돌면서 입력받은 주제와 일치하는 주제가 votelist에 존재하는지 검사함
		{
			if (nvc.getvotelist(i)->getsubject() == voteitem)
			{
				nvc.getvotelist(i)->setsubject("\0");
				nvc.getvotelist(i)->setitemnum(0);
				nvc.minusnsubject();
				cout << "Vote Deleted!" << endl;
				return;
			}
		}
	}
	cout << "Vote Deleted Failed" << endl;
	return;
}

void groupleader::addvoteitem(int loadMode, ofstream& inLogWrite, int nTokens, string* tokens, bool nowlogin, voteCollection& nvc, groupcollection& gc)
{
	string voteitem;
	int votenum, type;
	group* g = NULL;
	for (int i = 0; gc.getnum(); i++) //현재 속한 그룹을 찾음
	{
		if (this->getgroupname() == gc.getgroup(i)->getname())
		{
			g = gc.getgroup(i);
			break;
		}
	}
	cout << "Selected Menu: 4.3 Add a New Vote Item" << endl;
	cout << "<General Votes>" << endl; //일반 투표 목록 출력
	for (int i = 0; i < nvc.getloc(); i++)
	{
		if (nvc.getvotelist(i)->getsubject() == "")
			continue;
		cout << nvc.getvotelist(i)->getsubject() << " ";
	}
	if (nvc.getnsubject() == 0)
		cout << "None" << endl;
	else
		cout << endl;

	cout << "<Group Votes>" << endl; //그룹 투표 목록 출력
	for (int i = 0; i < g->getvc().getloc(); i++)
	{
		if (g->getvc().getvotelist(i)->getsubject() == "")
			continue;
		cout << g->getvc().getvotelist(i)->getsubject() << " ";
	}
	if (g->getvc().getnsubject() == 0)
		cout << "None" << endl;
	else
		cout << endl;

	if (!loadMode) //로그파일을 입력받지 않았을 경우 정보를 입력받고 로그파일에 출력함
	{
		cout << "Select Vote Type(0: general, 1: group): ";
		cin >> type;
		cout << "Vote Subject: "; fflush(stdout);
		cin >> voteitem;
		cout << "Number of Vote Items: "; fflush(stdout);
		cin >> votenum;
		inLogWrite << "4 3 " << type << " " << voteitem << " " << votenum << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함.
		if (nTokens != 5)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		type = atoi(tokens[2].c_str()), voteitem = tokens[3], votenum = atoi(tokens[4].c_str());
		cout << "Select Vote Type(0: general, 1: group): " << type << endl;
		cout << "Vote Subject: " << voteitem << endl;
		cout << "Number of Vote Items: " << votenum << endl;
	}

	if (votenum < 3 || votenum > 10)
	{
		cout << "Vote added fail" << endl;
		return;
	}

	if (type == 1)
	{
		for (int i = 0; i < g->getvc().getloc(); i++) //반복문을 이용하여 일치하는 주제가 있는지 검사하고 있다면 실패했다는 문구를 출력함.
		{
			if (voteitem == g->getvc().getvotelist(i)->getsubject())
			{
				cout << "Vote added fail" << endl;
				return;
			}
		}
		//성공한 상태이므로 votelist에 주제를 추가하고 nsubject의 값을 하나 올리며 vote의 항목수도 votelist에 저장함.
		g->getvc().makevote(g->getvc().getloc());
		g->getvc().getvotelist(g->getvc().getloc())->setitemnum(votenum);
		g->getvc().getvotelist(g->getvc().getloc())->setsubject(voteitem);
		g->getvc().plusnsubject();
		g->getvc().plusloc();
		cout << "Vote Added!" << endl;
		return;
	}
	else
	{
		for (int i = 0; i < nvc.getloc(); i++) //반복문을 이용하여 일치하는 주제가 있는지 검사하고 있다면 실패했다는 문구를 출력함.
		{
			if (voteitem == nvc.getvotelist(i)->getsubject())
			{
				cout << "Vote added fail" << endl;
				return;
			}
		}
		//성공한 상태이므로 votelist에 주제를 추가하고 nsubject의 값을 하나 올리며 vote의 항목수도 votelist에 저장함.
		nvc.makevote(nvc.getloc());
		nvc.getvotelist(nvc.getloc())->setitemnum(votenum);
		nvc.getvotelist(nvc.getloc())->setsubject(voteitem);
		nvc.plusnsubject();
		nvc.plusloc();
		cout << "Vote Added!" << endl;
		return;
	}
}

void groupleader::listallvote(int loadMode, int nTokens, string* tokens, bool nowlogin, ofstream& inLogWrite, voteCollection& nvc, groupcollection& gc)
{
	group* g = NULL;
	for (int i = 0; gc.getnum(); i++) //현재 위치한 그룹 찾음
	{
		if (this->getgroupname() == gc.getgroup(i)->getname())
		{
			g = gc.getgroup(i);
			break;
		}
	}

	cout << "Selected Menu: 4.4 List All Vote Items" << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 로그파일에 출력함.
	{
		inLogWrite << "4 4" << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함.
		if (nTokens != 2)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
	}
	cout << "<General Vote List>" << endl; //일반 투표 목록 출력
	if (nvc.getnsubject() == 0)
		cout << "None" << endl;
	else
	{
		for (int i = 0; i < nvc.getloc(); i++) //반복문을 이용하여 출력함
		{
			if (nvc.getvotelist(i)->getsubject() == "") //subject의 처음이 비어있다는 것은 삭제되었거나 비어있다는 것이므로 무시하고 다음 반복문으로 넘어감
				continue;
			cout << "Vote Subject: " << nvc.getvotelist(i)->getsubject() << ", Vote Counts per Item - ";
			for (int j = 0; j < nvc.getvotelist(i)->getitemnum(); j++)
				cout << "item" << j + 1 << ": " << nvc.getvotelist(i)->getitem(j).at(0) << " ";
			cout << "\n";
		}
	}
	cout << "<Group Vote List>" << endl; //그룹 투표 목록 출력
	if (g->getvc().getnsubject() == 0)
		cout << "None" << endl;
	else
	{
		for (int i = 0; i < g->getvc().getloc(); i++) //반복문을 이용하여 출력함
		{
			if (g->getvc().getvotelist(i)->getsubject() == "") //subject의 처음이 비어있다는 것은 삭제되었거나 비어있다는 것이므로 무시하고 다음 반복문으로 넘어감
				continue;
			cout << "Vote Subject: " << g->getvc().getvotelist(i)->getsubject() << ", Vote Counts per Item - ";
			for (int j = 0; j < g->getvc().getvotelist(i)->getitemnum(); j++)
				cout << "item" << j + 1 << ": " << g->getvc().getvotelist(i)->getitem(j).at(0) << " ";
			cout << "\n";
		}
	}
	return;
}

void groupleader::castvote(int loadMode, ofstream& inLogWrite, int nTokens, string* tokens, bool nowlogin, Member*& plogin, MemberCollection& mc, voteCollection& nvc, groupcollection& gc)
{
	string subject;
	int num1, num2, type;
	group* g = NULL;
	for (int i = 0; gc.getnum(); i++) //현재 소속된 그룹 찾음
	{
		if (this->getgroupname() == gc.getgroup(i)->getname())
		{
			g = gc.getgroup(i);
			break;
		}
	}
	cout << "Selected Menu: 4.5 Cast a Vote" << endl;
	cout << "<General Votes>" << endl; //일반 투표 목록 출력
	for (int i = 0; i < nvc.getloc(); i++)
	{
		if (nvc.getvotelist(i)->getsubject() == "")
			continue;
		cout << nvc.getvotelist(i)->getsubject() << " ";
	}
	if (nvc.getnsubject() == 0)
		cout << "None" << endl;
	else
		cout << endl;

	cout << "<Group Votes>" << endl; //그룹 투표 목록 출력
	for (int i = 0; i < g->getvc().getloc(); i++)
	{
		if (g->getvc().getvotelist(i)->getsubject() == "")
			continue;
		cout << g->getvc().getvotelist(i)->getsubject() << " ";
	}
	if (g->getvc().getnsubject() == 0)
		cout << "None" << endl;
	else
		cout << endl;

	if (!loadMode) //로그파일을 입력받지 않았을 경우 직접 정보를 입력받고 이를 로그파일에 출력함.
	{
		cout << "Select Vote Type(0: general, 1: group): ";
		cin >> type;
		cout << "Vote Subject: "; fflush(stdout);
		cin >> subject;
		if (type == 1)
		{
			cout << "Vote for(select 2 items): "; fflush(stdout);
			cin >> num1 >> num2;
			inLogWrite << "4 5 " << type << " " << subject << " " << num1 << " " << num2 << " " << endl;
		}
		else
		{
			cout << "Vote for: "; fflush(stdout);
			cin >> num1;
			inLogWrite << "4 5 " << type << " " << subject << " " << num1 << " " << endl;
		}
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함
		if (nTokens != 6)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		type = atoi(tokens[2].c_str()), subject = tokens[3], num1 = atoi(tokens[4].c_str()), num2 = atoi(tokens[5].c_str());
		cout << "Select Vote Type(0: general, 1: group): " << type << endl;
		cout << "Vote Subject: " << subject << endl;
		cout << "Vote for(select 2 items): " << num1 << " " << num2 << endl;
	}

	if (type == 0) //일반 투표일 경우
	{
		for (int i = 0; i < nvc.getloc(); i++) //반복문을 통해 votelist에 있는 주제와 입력받은 주제가 일치하는 것이 있는지 확인함
		{
			if (subject == nvc.getvotelist(i)->getsubject()) //주제가 일치하는 것이 있는 경우
			{
				for (int j = 0; j < mc.getmloc(); j++) //반복문을 통해 탈퇴하고 동일한 주민번호로 재가입하여 투표하는 경우가 있는지 확인함
				{
					if (plogin->getRRN() == nvc.getvotelist(i)->getRRN(j) || plogin->getvotefor(i))
					{
						cout << "Request processed failed" << endl;
						return;
					}
				}
				nvc.getvotelist(i)->setitem(num1);
				nvc.getvotelist(i)->setRRNlist(plogin->getRRN());
				cout << "Request processed successfully!" << endl;
				return;
			}
		}
	}
	else //그룹 투표일 경우
	{
		for (int i = 0; i < g->getvc().getloc(); i++) //반복문을 통해 votelist에 있는 주제와 입력받은 주제가 일치하는 것이 있는지 확인함
		{
			if (subject == g->getvc().getvotelist(i)->getsubject()) //주제가 일치하는 것이 있는 경우
			{
				for (int j = 0; j < mc.getmloc(); j++) //반복문을 통해 탈퇴하고 동일한 주민번호로 재가입하여 투표하는 경우가 있는지 확인함
				{
					if (plogin->getRRN() == g->getvc().getvotelist(i)->getRRN(j) || plogin->getvotefor(i))
					{
						cout << "Request processed failed" << endl;
						return;
					}
				}
				g->getvc().getvotelist(i)->setitem(num1);
				g->getvc().getvotelist(i)->setitem(num2);
				g->getvc().getvotelist(i)->setRRNlist(plogin->getRRN());
				cout << "Request processed successfully!" << endl;
				return;
			}
		}
	}

	cout << "Request processed failed" << endl;
	return;
}

void groupleader::listgroupmember(int loadMode, ofstream& inLogWrite, int nTokens, groupcollection& gc)
{
	group* g = NULL;
	for (int i = 0; gc.getnum(); i++) //현재 소속된 그룹 찾음
	{
		if (this->getgroupname() == gc.getgroup(i)->getname())
		{
			g = gc.getgroup(i);
			break;
		}
	}

	cout << "Selected Menu: 4.6 List All Group Members" << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 로그파일에 출력함.
	{
		inLogWrite << "4 6" << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함.
		if (nTokens != 2)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
	}

	cout << "<Group Members>" << endl;
	for (int i = 0; i < g->getgloc(); i++)
	{
		if (g->getgroupmember(i)->getID() == "")
			continue;
		cout << g->getgroupmember(i)->getID() << " ";
	}
	return;
}

void groupleader::banmember(int loadMode, ofstream& inLogWrite, int nTokens, string* tokens, MemberCollection& mc, groupcollection& gc)
{
	string banid;
	group* g = NULL;
	Member* copy = NULL;
	for (int i = 0; gc.getnum(); i++) //현재 위치한 그룹 찾음
	{
		if (this->getgroupname() == gc.getgroup(i)->getname())
		{
			g = gc.getgroup(i);
			break;
		}
	}
	cout << "Selected Menu: 4.7 Ban a Group Member" << endl;
	if (!loadMode) //로그파일을 받아들이지 않았을 경우 직접 정보를 입력받고 로그파일에 출력함
	{
		cout << "Group Member's ID to Ban: "; fflush(stdout);
		cin >> banid;
		inLogWrite << "4 7 " << banid << endl;
	}
	else { //로그파일을 받아들였을 경우 tokens를 통하여 실행함
		if (nTokens != 3)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		banid = tokens[2];
		cout << "Group Member's ID to Ban: " << banid << endl;
	}

	for (int i = 0; i < mc.getmloc(); i++) //멤버리스트에서 위치 확인
	{
		if (mc.getMemberlist(i)->getID() == banid)
		{
			for (int j = 0; j < g->getnum(); j++) //그룹에 속해있는지 확인
			{
				if (banid == g->getgroupmember(j)->getID())
				{
					if (mc.getMemberlist(i)->getgroupleader()) //그룹 리더라면 ban 불가능
					{
						cout << "Ban Failed" << endl;
						return;
					}
					else //추방
					{
						g->deletegroupmember(j);
						g->downnum();
						mc.getMemberlist(j)->setgroup(false);
						copy = new Member(mc.getMemberlist(i));
						mc.deletemember(j);
						mc.setmember(j, copy);
						delete copy;
						cout << " Ban success" << endl;
						return;
					}
				}
			}
		}
	}

	cout << "Ban Failed" << endl;
	return;
}
