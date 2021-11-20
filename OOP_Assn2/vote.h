# -*- coding: utf-8 -*-
#include "member.h"
#ifndef _VOTE_H_
#define _VOTE_H_

class vote {
private:
	std::string subject; //주제
	int itemnum; //투표 항목수 저장
	std::string item[MAX_NUM_VOTEITEM]; //투표 항목에 투표수를 저장하는 리스트
	std::string RRNlist[MAX_NUM_MEMBER]; //중복 투표 여부를 검사하기 위한 주민번호 검사 리스트
public:
	vote() //constructor
	{
		for (int i = 0; i < MAX_NUM_VOTEITEM; i++) //반복문을 통하여 전체 투표 항목의 투표수를 0으로 저장
		{
			item[i] = "0";
		}
		itemnum = 0;
	}
	std::string getsubject() //주제를 불러옴
	{
		return subject;
	}
	int getitemnum() //투표 항목수를 불러옴
	{
		return itemnum;
	}
	std::string getitem(int i) //투표 항목의 투표수를 불러옴
	{
		return item[i];
	}
	std::string getRRN(int i) //중복 투표 여부를 검사하기 위한 주민번호를 불러옴
	{
		return RRNlist[i];
	}
	void setsubject(std::string nsubject) //주제를 설정함
	{
		subject = nsubject;
	}
	void setitemnum(char nitemnum) //투표 항목수를 설정함
	{
		itemnum = nitemnum;
	}
	void setitem(int i) //투표 항목의 투표수를 증가시킴
	{
		item[i - 1].at(0)++;
	}
	int how = 0;
	void setRRNlist(std::string RRN) //중복 투표 여부를 검사하기 위한 주민번호를 저장함
	{
		RRNlist[how++] = RRN;
	}
};

class voteCollection {
private:
	vote votelist[MAX_NUM_VOTE]; //전체 투표 리스트를 저장함.
	int nsubject; //전체 투표의 개수
public:
	voteCollection() //constructor
	{
		nsubject = 0;
	}
	void deletevoteitem(int loadMode, std::ofstream& inLogWrite, int nTokens, std::string* tokens, bool nowlogin); //투표를 삭제시키는 함수
	void addvoteitem(int loadMode, std::ofstream& inLogWrite, int nTokens, std::string* tokens, bool nowlogin); //투표를 추가하는 함수
	void listallvote(int loadMode, int nTokens, std::string* tokens, bool nowlogin, std::ofstream& inLogWrite); //전체 투표를 출력해주는 함수
	void castvote(int loadMode, std::ofstream& inLogWrite, int nTokens, std::string* tokens, bool nowlogin, Member& plogin, MemberCollection& mc); //투표를 실행해주는 함수
};

#endif
