# -*- coding: utf-8 -*-
#include "default.h"
#include "vote.h"
using namespace std;

void voteCollection::deletevoteitem(int loadMode, ofstream& inLogWrite, int nTokens, string* tokens, bool nowlogin)
{
	string voteitem;
	cout << "Selected Menu: 5. Delete Existing Vote" << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 정보를 입력받고 로그파일에 출력함
	{
		cout << "Vote Subject to Delete: "; fflush(stdout);
		cin >> voteitem;
		inLogWrite << "5 " << voteitem << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함
		if (nTokens != 2)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		voteitem = tokens[1];
		cout << "Vote Subject to Delete: " << voteitem << endl;
	}

	for (int i = 0; i < nsubject; i++) //반복문을 돌면서 입력받은 주제와 일치하는 주제가 votelist에 존재하는지 검사함
	{
		if (votelist[i].getsubject() == voteitem)
		{
			if (nowlogin) //일치하는 주제를 찾고 현재 로그인된 상태라면 투표를 삭제시킴
			{
				votelist[i].setsubject("\0"), votelist[i].setitemnum(0);
				cout << "Vote Deleted!" << endl;
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
	cout << "Selected Menu: 6. Add a New Vote Item" << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 정보를 입력받고 로그파일에 출력함
	{
		cout << "Vote Subject: "; fflush(stdout);
		cin >> voteitem;
		cout << "Number of Vote Items: "; fflush(stdout);
		cin >> votenum;
		inLogWrite << "6 " << voteitem << " " << votenum << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함.
		if (nTokens != 3)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		voteitem = tokens[1], votenum = atoi(tokens[2].c_str());
		cout << "Vote Subject: " << voteitem << endl;
		cout << "Number of Vote Items: " << votenum << endl;
	}

	for (int i = 0; i < nsubject; i++) //반복문을 이용하여 일치하는 주제가 있는지 검사하고 있다면 실패했다는 문구를 출력함.
	{
		if (voteitem == votelist[i].getsubject())
		{
			cout << "Vote added fail" << endl;
			return;
		}
	}
	if (!nowlogin) //현재 로그인되어있는 상태가 아니라면 vote를 add할 수 없음
	{
		cout << "Vote Added Failed" << endl;
		return;
	}
	else //성공한 상태이므로 votelist에 주제를 추가하고 nsubject의 값을 하나 올리며 vote의 항목수도 votelist에 저장함.
	{
		votelist[nsubject].setitemnum(votenum), votelist[nsubject++].setsubject(voteitem);
		cout << "Vote Added!" << endl;
		return;
	}
}

void voteCollection::listallvote(int loadMode, int nTokens, string* tokens, bool nowlogin, ofstream& inLogWrite)
{
	cout << "Selected Menu: 7. List All Vote Items" << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 로그파일에 출력함.
	{
		inLogWrite << "7" << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함.
		if (nTokens != 1)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
	}
	if (nowlogin) //현재 로그인 되어있는 상태일 경우에만 votelist를 출력가능
	{
		for (int i = 0; i < nsubject; i++) //반복문을 이용하여 출력함
		{
			if (votelist[i].getsubject() == "") //subject의 처음이 비어있다는 것은 삭제되었거나 비어있다는 것이므로 무시하고 다음 반복문으로 넘어감
				continue;
			cout << "Vote Subject: " << votelist[i].getsubject() << ", Vote Counts per Item - ";
			for (int j = 0; j < votelist[i].getitemnum(); j++)
				cout << "item" << j + 1 << ": " << votelist[i].getitem(j).at(0) << " ";
			cout << "\n";
		}
	}
	else
	{
		cout << "List failed" << endl;
	}
	return;
}

void voteCollection::castvote(int loadMode, ofstream& inLogWrite, int nTokens, string* tokens, bool nowlogin, Member& plogin, MemberCollection& mc)
{
	string subject;
	int num;
	cout << "Selected Menu: 8. Cast a Vote" << endl;
	if (!loadMode) //로그파일을 입력받지 않았을 경우 직접 정보를 입력받고 이를 로그파일에 출력함.
	{
		cout << "Vote Subject: "; fflush(stdout);
		cin >> subject;
		cout << "Vote for: "; fflush(stdout);
		cin >> num;
		inLogWrite << "8 " << subject << " " << num << " " << endl;
	}
	else { //로그파일을 입력받았을 경우 tokens를 이용하여 실행함
		if (nTokens != 3)
		{
			cout << "invalid commandLog input format" << endl;
			return;
		}
		subject = tokens[1], num = atoi(tokens[2].c_str());
		cout << "Vote Subject: " << subject << endl;
		cout << "Vote for: " << num << endl;
	}

	for (int i = 0; i < nsubject; i++) //반복문을 통해 votelist에 있는 주제와 입력받은 주제가 일치하는 것이 있는지 확인함
	{
		if (subject == votelist[i].getsubject()) //주제가 일치하는 것이 있는 경우
		{
			if (nowlogin) //현재 로그인이 되어있는 상태인 경우
			{
				for (int j = 0; j < mc.getMembernum(); j++) //반복문을 통해 탈퇴하고 동일한 주민번호로 재가입하여 투표하는 경우가 있는지 확인함
				{
					if (plogin.getRRN() == votelist[i].getRRN(j) || plogin.getvotefor(i))
					{
						cout << "Request processed failed" << endl;
						return;
					}
				}
				votelist[i].setitem(num);
				votelist[i].setRRNlist(plogin.getRRN());
				cout << "Request processed successfully!" << endl;
				return;
			}
		}
	}
	cout << "Request processed failed" << endl;
	return;
}
