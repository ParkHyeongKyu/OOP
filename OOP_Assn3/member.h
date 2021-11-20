# -*- coding: utf-8 -*-
#ifndef _MEMBER_H_
#define _MEMBER_H_

class MemberCollection;
class voteCollection;
class groupcollection;

class Member{
private:
	std::string RRN; //주민번호
	std::string ID;
	std::string password;
	std::string groupname;
	bool isgroup; //그룹에 속해있는지 여부
	bool isgroupleader; //그룹 리더 여부
	bool votefor[MAX_NUM_VOTEITEM]; //투표를 했는지 안했는지 여부를 저장함
public:
	Member() //default constructor
	{
		for (int i = 0; i < MAX_NUM_VOTEITEM; i++)
			votefor[i] = false;
		isgroup = false;
		isgroupleader = false;
	}
	Member(Member*& copy) //copy constructor
	{
		RRN = copy->RRN;
		ID = copy->ID;
		password = copy->password;
		groupname = copy->groupname;
		isgroup = copy->isgroup;
		isgroupleader = copy->isgroupleader;
		for(int i = 0; i < MAX_NUM_VOTEITEM; i++)
			votefor[i] = copy->votefor[i];
	}
	virtual void printmenu();
	virtual void printpos(Member*& plogin);
	virtual void doswitchcase(int& menu, int& loadMode, std::ofstream& inLogWrite, std::string* tokens, int& nTokens, bool& nowlogin, Member*& plogin, MemberCollection& mc, voteCollection& nvc, groupcollection& gc);
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
	void setgroupname(std::string name) //groupname설정
	{
		groupname = name;
	}
	std::string getgroupname() //groupname을 가져옴
	{
		return groupname;
	}
	bool getgroupleader() //groupleader여부를 가져옴
	{
		return isgroupleader;
	}
	void setgroupleader(bool a) //groupleader여부를 지정함
	{
		isgroupleader = a;
	}
	bool getgroup() //groupmember여부를 가져옴
	{
		return isgroup;
	}
	void setgroup(bool a) //groupmember여부를 지정함
	{
		isgroup = a;
	}
};

class groupmember : public Member { //Member class 상속
public :
	groupmember() {} //default constructor
	groupmember(Member*& copy) : Member(copy) {} //copy constructor
	virtual void printmenu();
	virtual void printpos(Member*& plogin);
	virtual void doswitchcase(int& menu, int& loadMode, std::ofstream& inLogWrite, std::string* tokens, int& nTokens, bool& nowlogin, Member*& plogin, MemberCollection& mc, voteCollection& nvc, groupcollection& gc);
	bool unsubscribe(int loadMode, std::ofstream & inLogWrite, std::string *tokens, int nTokens, bool nowlogin, Member*& plogin, MemberCollection& mc, groupcollection& gc); //회원탈퇴 함수
	virtual bool Logout(int loadMode, std::string *tokens, int nTokens, Member*& plogin, std::ofstream & inLogWrite, bool nowlogin); //로그아웃 함수
	virtual void deletevoteitem(int loadMode, std::ofstream& inLogWrite, int nTokens, std::string* tokens, bool nowlogin, voteCollection& nvc, groupcollection& gc); //투표를 삭제시키는 함수
	virtual void addvoteitem(int loadMode, std::ofstream& inLogWrite, int nTokens, std::string* tokens, bool nowlogin, voteCollection& nvc, groupcollection& gc); //투표를 추가하는 함수
	virtual void listallvote(int loadMode, int nTokens, std::string* tokens, bool nowlogin, std::ofstream& inLogWrite, voteCollection& nvc, groupcollection& gc); //전체 투표를 출력해주는 함수
	virtual void castvote(int loadMode, std::ofstream& inLogWrite, int nTokens, std::string* tokens, bool nowlogin, Member*& plogin, MemberCollection& mc, voteCollection& nvc, groupcollection& gc); //투표를 실행해주는 함수
	void unsubscribegroup(int loadMode, std::ofstream& inLogWrite, int nTokens, std::string* tokens, Member*& plogin, MemberCollection& mc, groupcollection& gc); //그룹 탈퇴 함수
private :

};

class groupleader : public groupmember { //groupmember class 상속
public :
	groupleader() {} //default constructor
	groupleader(Member*& copy) : groupmember(copy) {} //copy constructor
	virtual void printmenu();
	virtual void printpos(Member*& plogin);
	virtual void doswitchcase(int& menu, int& loadMode, std::ofstream& inLogWrite, std::string* tokens, int& nTokens, bool& nowlogin, Member*& plogin, MemberCollection& mc, voteCollection& nvc, groupcollection& gc);
	virtual bool Logout(int loadMode, std::string *tokens, int nTokens, Member*& plogin, std::ofstream & inLogWrite, bool nowlogin); //로그아웃 함수
	virtual void deletevoteitem(int loadMode, std::ofstream& inLogWrite, int nTokens, std::string* tokens, bool nowlogin, voteCollection& nvc, groupcollection& gc); //투표를 삭제시키는 함수
	virtual void addvoteitem(int loadMode, std::ofstream& inLogWrite, int nTokens, std::string* tokens, bool nowlogin, voteCollection& nvc, groupcollection& gc); //투표를 추가하는 함수
	virtual void listallvote(int loadMode, int nTokens, std::string* tokens, bool nowlogin, std::ofstream& inLogWrite, voteCollection& nvc, groupcollection& gc); //전체 투표를 출력해주는 함수
	virtual void castvote(int loadMode, std::ofstream& inLogWrite, int nTokens, std::string* tokens, bool nowlogin, Member*& plogin, MemberCollection& mc, voteCollection& nvc, groupcollection& gc); //투표를 실행해주는 함수
	void banmember(int loadMode, std::ofstream& inLogWrite, int nTokens, std::string* tokens, MemberCollection& mc, groupcollection& gc); //멤버 추방 함수
	void listgroupmember(int loadMode, std::ofstream& inLogWrite, int nTokens, groupcollection& gc); //그룹 멤버 보여주는 함수
private :
	using groupmember::unsubscribegroup; //groupmember의 unsubscribegroup 구현 못함
};

class MemberCollection {
private:
	Member* memberlist[MAX_NUM_MEMBER]; //멤버의 정보를 저장하는 리스트
	int membernum; //전체 멤버 수
	int mloc; //memberlist배열 중 가장 마지막 배열 index + 1
public:
	MemberCollection() //constructor
	{
		/*for (int i = 0; i < MAX_NUM_MEMBER; i++)
		{
			memberlist[i] = new Member;
		}*/
		membernum = 0;
		mloc = 0;
	}
	~MemberCollection() //destructor
	{
		delete[] &memberlist;
	}
	void join(MemberCollection* mc, int loadMode, std::ofstream & inLogWrite, std::string *tokens, int nTokens, bool nowlogin); //회원가입 함수
	bool searchMember(std::string RRN, std::string ID); //멤버의 중복 여부를 확인하는 함수
	int getmloc()
	{
		return mloc;
	}
	void minusmembernum()
	{
		membernum--;
	}
	void plusmloc()
	{
		mloc++;
	}
	int getMembernum() //멤버수를 얻어옴
	{
		return membernum;
	}
	Member*& getMemberlist(int i) //멤버의 정보를 얻어옴
	{
		return memberlist[i];
	}
	void deletemember(int i)
	{
		delete memberlist[i];
	}
	void setmember(int i, Member*& copy)
	{
		memberlist[i] = new Member(copy);
	}
	virtual bool unsubscribe(int loadMode, std::ofstream & inLogWrite, std::string *tokens, int nTokens, bool nowlogin, Member*& plogin, MemberCollection& mc, groupcollection& gc); //회원탈퇴 함수
	bool Login(int loadMode, std::string *tokens, int nTokens, Member*& plogin, std::ofstream & inLogWrite, bool nowlogin); //로그인 함수
	virtual bool Logout(int loadMode, std::string *tokens, int nTokens, Member*& plogin, std::ofstream & inLogWrite, bool nowlogin); //로그아웃 함수
	void joingroup(int loadMode, std::string* tokens, int nTokens, Member*& plogin, std::ofstream& inLogWrite, groupcollection& gc); //그룹 가입 함수
	void creategroup(int loadMode, std::string* tokens, int nTokens, Member*& plogin, std::ofstream& inLogWrite, groupcollection& gc); //그룹 생성 함수
};

#endif
