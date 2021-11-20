# -*- coding: utf-8 -*-
#include "default.h"
#include "vote.h"
#include "member.h"
#include "group.h"
using namespace std;

void voteCollection::deletevoteitem(int loadMode, ofstream& inLogWrite, int nTokens, string* tokens, bool nowlogin)
{
	string voteitem;
	cout << "Selected Menu: 2.3 Delete Existing Vote" << endl;
	cout << "<General Votes>" << endl; //일반 투표 목록 출력
	for (int i = 0; i < getloc(); i++)
	{
		if (votelist[i]->getsubject() == "")
			continue;
		cout << votelist[i]->getsubject() << " ";
	}
	if (getnsubject() == 0)
		cout << "None" << endl;
	else
		cout << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 정보를 입력받고 로그파일에 출력함
	{
		cout << "Vote Subject to Delete: "; fflush(stdout);
		cin >> voteitem;
		inLogWrite << "2 3 0 " << voteitem << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함
		if (nTokens != 4)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		voteitem = tokens[3];
		cout << "Vote Subject to Delete: " << voteitem << endl;
	}

	for (int i = 0; i < loc; i++) //반복문을 돌면서 입력받은 주제와 일치하는 주제가 votelist에 존재하는지 검사함
	{
		if (votelist[i]->getsubject() == voteitem)
		{
			if (nowlogin) //일치하는 주제를 찾고 현재 로그인된 상태라면 투표를 삭제시킴
			{
				votelist[i]->setsubject("\0");
				votelist[i]->setitemnum(0);
				cout << "Vote Deleted!" << endl;
				minusnsubject();
				return;
			}
		}
	}
	cout << "Vote Deleted Failed" << endl;
	return;
}

void voteCollection::addvoteitem(int loadMode, ofstream& inLogWrite, int nTokens, string* tokens, bool nowlogin)
{
	string voteitem;
	int votenum;
	cout << "Selected Menu: 2.4 Add a New Vote Item" << endl;
	cout << "<General Votes>" << endl; //일반투표 목록 출력
	for (int i = 0; i < getloc(); i++)
	{
		if (votelist[i]->getsubject() == "")
			continue;
		cout << votelist[i]->getsubject() << " ";
	}
	if (getnsubject() == 0)
		cout << "None" << endl;
	else
		cout << endl;

	if (!loadMode) //로그파일을 입력받지 않았을 경우 정보를 입력받고 로그파일에 출력함
	{
		cout << "Vote Subject: "; fflush(stdout);
		cin >> voteitem;
		cout << "Number of Vote Items: "; fflush(stdout);
		cin >> votenum;
		inLogWrite << "2 4 0 " << voteitem << " " << votenum << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함.
		if (nTokens != 5)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		voteitem = tokens[3], votenum = atoi(tokens[4].c_str());
		cout << "Vote Subject: " << voteitem << endl;
		cout << "Number of Vote Items: " << votenum << endl;
	}

	for (int i = 0; i < loc; i++) //반복문을 이용하여 일치하는 주제가 있는지 검사하고 있다면 실패했다는 문구를 출력함.
	{
		if (voteitem == votelist[i]->getsubject())
		{
			cout << "Vote added fail" << endl;
			return;
		}
	}
	if (votenum < 3 || votenum > 10) //현재 로그인되어있는 상태가 아니라면 vote를 add할 수 없음
	{
		cout << "Vote Added Failed" << endl;
		return;
	}
	else //성공한 상태이므로 votelist에 주제를 추가하고 nsubject의 값을 하나 올리며 vote의 항목수도 votelist에 저장함.
	{
		makevote(loc);
		votelist[loc]->setitemnum(votenum);
		votelist[loc++]->setsubject(voteitem);
		nsubject++;
		cout << "Vote Added!" << endl;
		return;
	}
}

void voteCollection::listallvote(int loadMode, int nTokens, string* tokens, bool nowlogin, ofstream& inLogWrite)
{
	cout << "Selected Menu: 2.5 List All Vote Items" << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 로그파일에 출력함.
	{
		inLogWrite << "2 5" << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함.
		if (nTokens != 2)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
	}
	cout << "<General Vote>" << endl;
	if (nsubject == 0)
		cout << "None" << endl;
	else
	{
		for (int i = 0; i < loc; i++) //반복문을 이용하여 출력함
		{
			if (votelist[i]->getsubject() == "") //subject의 처음이 비어있다는 것은 삭제되었거나 비어있다는 것이므로 무시하고 다음 반복문으로 넘어감
				continue;
			cout << "Vote Subject: " << votelist[i]->getsubject() << ", Vote Counts per Item - ";
			for (int j = 0; j < votelist[i]->getitemnum(); j++)
				cout << "item" << j + 1 << ": " << votelist[i]->getitem(j).at(0) << " ";
			cout << "\n";
		}
	}
	return;
}

void voteCollection::castvote(int loadMode, ofstream& inLogWrite, int nTokens, string* tokens, bool nowlogin, Member*& plogin, MemberCollection& mc)
{
	string subject;
	int num;
	cout << "Selected Menu: 2.6 Cast a Vote" << endl;
	cout << "<General Votes>" << endl; //일반 투표 목록 출력
	for (int i = 0; i < getloc(); i++)
	{
		if (votelist[i]->getsubject() == "")
			continue;
		cout << votelist[i]->getsubject() << " ";
	}
	if (getnsubject() == 0)
		cout << "None" << endl;
	else
		cout << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 직접 정보를 입력받고 이를 로그파일에 출력함.
	{
		cout << "Vote Subject: "; fflush(stdout);
		cin >> subject;
		cout << "Vote for(select 1 item): "; fflush(stdout);
		cin >> num;
		inLogWrite << "2 6 0 " << subject << " " << num << "  0" << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함
		if (nTokens != 6)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		subject = tokens[3], num = atoi(tokens[4].c_str());
		cout << "Vote Subject: " << subject << endl;
		cout << "Vote for(select 1 item): " << num << endl;
	}

	for (int i = 0; i < loc; i++) //반복문을 통해 votelist에 있는 주제와 입력받은 주제가 일치하는 것이 있는지 확인함
	{
		if (subject == votelist[i]->getsubject()) //주제가 일치하는 것이 있는 경우
		{
			if (nowlogin) //현재 로그인이 되어있는 상태인 경우
			{
				for (int j = 0; j < mc.getmloc(); j++) //반복문을 통해 탈퇴하고 동일한 주민번호로 재가입하여 투표하는 경우가 있는지 확인함
				{
					if (plogin->getRRN() == votelist[i]->getRRN(j) || plogin->getvotefor(i))
					{
						cout << "Request processed failed" << endl;
						return;
					}
				}
				votelist[i]->setitem(num);
				votelist[i]->setRRNlist(plogin->getRRN());
				cout << "Request processed successfully!" << endl;
				return;
			}
		}
	}
	cout << "Request processed failed" << endl;
	return;
}
