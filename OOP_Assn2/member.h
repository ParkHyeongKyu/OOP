# -*- coding: utf-8 -*-
#ifndef _MEMBER_H_
#define _MEMBER_H_

class Member {
private:
	std::string RRN; //주민번호
	std::string ID;
	std::string password;
	bool votefor[MAX_NUM_VOTEITEM] = { false }; //투표를 했는지 안했는지 여부를 저장함
public:
	std::string getRRN() //RRN값을 가져옴
	{
		return RRN;
	}
	std::string getID() //ID값을 가져옴
	{
		return ID;
	}
	std::string getpassword() //password값을 가져옴
	{
		return password;
	}
	bool getvotefor(int i) //투표 여부를 index에 따라 가져옴
	{
		return votefor[i];
	}
	void setRRN(std::string nRRN) //RRN값을 설정함
	{
		RRN = nRRN;
	}
	void setID(std::string nID) //ID값을 설정함
	{
		ID = nID;
	}
	void setpassword(std::string npassword) //password값을 설정함
	{
		password = npassword;
	}
	void setvotefor(int i) //투표 여부를 설정함
	{
		votefor[i] = true;
	}
};

class MemberCollection {
private:
	Member memberlist[MAX_NUM_MEMBER]; //멤버의 정보를 저장하는 리스트
	int membernum; //전체 멤버 수
public:
	MemberCollection() //constructor
	{
		membernum = 0;
	}
	void join(MemberCollection* mc, int loadMode, std::ofstream & inLogWrite, std::string *tokens, int nTokens, bool nowlogin); //회원가입 함수
	bool searchMember(std::string RRN, std::string ID); //멤버의 중복 여부를 확인하는 함수
	int getMembernum() //멤버수를 얻어옴
	{
		return membernum;
	}
	Member getMember(int i) //멤버의 정보를 얻어옴
	{
		return memberlist[i];
	}
	bool unsubscribe(int loadMode, std::ofstream & inLogWrite, std::string *tokens, int nTokens, bool nowlogin, Member& plogin); //회원탈퇴 함수
	bool Login(int loadMode, std::string *tokens, int nTokens, Member& plogin, std::ofstream & inLogWrite, bool nowlogin); //로그인 함수
	bool Logout(int loadMode, std::string *tokens, int nTokens, Member& plogin, std::ofstream & inLogWrite, bool nowlogin); //로그아웃 함수
};

#endif
