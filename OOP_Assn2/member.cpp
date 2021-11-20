# -*- coding: utf-8 -*-
#include "default.h"
#include "member.h"
using namespace std;

//1. 회원가입
void MemberCollection::join(MemberCollection* mc, int loadMode, ofstream & inLogWrite, string *tokens, int nTokens, bool nowlogin)
{
	string RRN, ID, password;
	cout << "Selected Menu: 1. Register as a Member" << endl;
	if (!loadMode) //로그파일을 받아들이지 않았을경우 직접 정보를 입력받고 로그파일에 출력함
	{
		cout << "Resident Registration Number:"; fflush(stdout);
		cin >> RRN;
		cout << "ID:"; fflush(stdout);
		cin >> ID;
		cout << "Password:"; fflush(stdout);
		cin >> password;
		inLogWrite << "1 " << RRN << " " << ID << " " << password << " " << endl;
	}
	else { //로그파일을 받아들였을 경우 tokens를 통해 실행함
		if (nTokens != 4)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		RRN = tokens[1]; ID = tokens[2]; password = tokens[3];
		cout << "1. Resident Registration Number: " << RRN << endl;
		cout << "ID: " << ID << endl;
		cout << "Password:" << password << endl;
	}
	//검사시작
	if (mc->searchMember(RRN, ID) && !nowlogin) //로그인되어있고 주민번호와 ID가 겹치지 않을 경우 memberlist에 정보 추가
	{
		memberlist[membernum].setRRN(RRN);
		memberlist[membernum].setID(ID);
		memberlist[membernum].setpassword(password);
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
	for (int i = 0; i < getMembernum(); i++)
	{
		if (RRN == memberlist[i].getRRN() || ID == memberlist[i].getID())
			return false;
	}
	return true;
}
//회원 탈퇴
bool MemberCollection::unsubscribe(int loadMode, ofstream & inLogWrite, string *tokens, int nTokens, bool nowlogin, Member& plogin)
{
	string ID, password;
	cout << "Selected Menu: 2. Unsubscribe from System" << endl;
	if (!loadMode) //로그파일을 받아들이지 않았을 경우 정보를 직접 입력받고 로그 파일에 출력함
	{
		cout << "ID:"; fflush(stdout);
		cin >> ID;
		cout << "Password:"; fflush(stdout);
		cin >> password;
		inLogWrite << "2 " << ID << " " << password << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함.
		if (nTokens != 3)
		{
			cout << "invalid commandLog input format" << endl;
			return true;
		}
		ID = tokens[1]; password = tokens[2];
		cout << "ID: " << ID << endl;
		cout << "Password:" << password << endl;
	}

	int removeidx; //삭제할 memberlist의 index
	if (nowlogin && ID == plogin.getID() && password == plogin.getpassword()) //현재 로그인이 되어 있으며 ID와 password가 현재 로그인한 사람과 정보가 일치할 경우 실행
	{
		for (int i = 0; i < membernum; i++) //반복문을 돌며 입력한 ID와 memberlist에서 일치하는 ID를 찾음
		{
			if (ID == memberlist[i].getID())
			{
				removeidx = i;
				break;
			}
		}
		memberlist[removeidx].setID("\0"), memberlist[removeidx].setpassword("\0"), memberlist[removeidx].setRRN("\0"); //삭제할 memberlist의 정보를 모두 "\0"로 초기화시킴
		cout << "Unsubscribe Success" << endl;
		return false;
	}
	else if(!nowlogin) //로그인이 안된 상태에서 시도했을때
	{
		cout << "Unsubscribe Failed" << endl;
		return false;
	}
	else
	{
		cout << "Unsubscribe Failed" << endl;
		return true;
	}
}
//로그인
bool MemberCollection::Login(int loadMode, string *tokens, int nTokens, Member& plogin, ofstream & inLogWrite, bool nowlogin)
{
	string ID, password, RRN;
	cout << "Selected Menu: 3. Login" << endl;
	if (!loadMode) //로그파일을 받아들이지 않았을 경우 직접 정보를 입력받고 로그파일에 출력함
	{
		cout << "ID:"; fflush(stdout);
		cin >> ID;
		cout << "Password:"; fflush(stdout);
		cin >> password;
		inLogWrite << "3 " << ID << " " << password << " " << endl;
	}
	else { //로그파일을 받아들였을 경우 tokens를 통하여 실행함
		if (nTokens != 3)
		{
			cout << "invalid commandLog input format" << endl;
			return false;
		}
		ID = tokens[1]; password = tokens[2];
		cout << "ID: " << ID << endl;
		cout << "Password:" << password << endl;
	}

	if (nowlogin) //현재 로그인 중이라면 이 함수를 종료시킨다.
	{
		cout << "Login Failed" << endl;
		return true;
	}

	for (int i = 0; i < getMembernum(); i++) //반복문을 돌면서 memberlist에 있는 ID와 password가 입력값과 일치하는 것이 있는지 찾음.
	{
		if (ID == memberlist[i].getID() && password == memberlist[i].getpassword())
		{
			RRN = memberlist[i].getRRN();
			cout << "Login Success!" << endl;
			plogin.setID(ID); //일치하는 것이 있다면 현재 로그인한 멤버의 정보를 plogin에 저장함
			plogin.setpassword(password);
			plogin.setRRN(RRN);
			return true;
		}
	}

	cout << "Login Failed" << endl;
	return false;
}

bool MemberCollection::Logout(int loadMode, string *tokens, int nTokens, Member& plogin, ofstream & inLogWrite, bool nowlogin)
{
	cout << "Selected Menu: 4. Logout" << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 로그파일에 출력함
	{
		inLogWrite << "4" << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함
		if (nTokens != 1)
		{
			cout << "invalid commandLog input format" << endl;
			return true;
		}
	}

	if (nowlogin) //현재 로그인 되어있는 상태일 경우
	{
		plogin.setID("\0"); //로그아웃 되었으므로 plogin을 "\0"으로 초기화함
		plogin.setpassword("\0");
		cout << "Logout Success" << endl; fflush(stdout);
		return false;
	}
	else
	{
		cout << "Logout failed" << endl; fflush(stdout);
		return false;
	}
}
