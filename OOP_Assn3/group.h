# -*- coding: utf-8 -*-
#ifndef _GROUP_H_
#define _GROUP_H_

class Member;
class voteCollection;
class groupmember;

class group {
private:
	std::string name; //그룹 이름
	Member* groupmember[MAX_GROUP_NUM]; //그룹에 속한 멤버리스트
	Member leader; //그룹 리더
	int num; //그룹 멤버 수
	int gloc; //그룹 멤버리스트 마지막 index + 1
	voteCollection gvc; //그룹내 투표리스트
public:
	group() //default constructor
	{
		for (int i = 0; i < MAX_GROUP_NUM; i++)
		{
			groupmember[i] = new ::groupmember;
		}
	}
	group(Member& nleader, std::string nname) : name(nname), leader(nleader), num(1)  //default constructor
	{
		groupmember[MAX_GROUP_NUM] = new Member;
	}
	~group() //destructor
	{
		delete[] &groupmember;
	}
	Member* getgroupmember(int i)
	{
		return this->groupmember[i];
	}
	Member getleader()
	{
		return this->leader;
	}
	void plusgroupmember(Member*& nmember)
	{
		groupmember[gloc] = new Member(nmember);
		return;
	}
	void deletegroupmember(int i)
	{
		groupmember[i]->setgroupname("\0");
		groupmember[i]->setID("\0");
		groupmember[i]->setpassword("\0");
		groupmember[i]->setRRN("\0");
		groupmember[i]->setvotefor(0);
	}
	std::string getname()
	{
		return name;
	}
	int getnum()
	{
		return num;
	}
	void downnum()
	{
		num--;
	}
	void plusnum()
	{
		num++;
	}
	void setname(std::string nname)
	{
		name = nname;
	}
	void setleader(Member*& nleader)
	{
		leader = nleader;
	}
	void setnum()
	{
		num = 0;
	}
	void setgloc()
	{
		gloc = 0;
	}
	void plusgloc()
	{
		gloc++;
	}
	int getgloc()
	{
		return gloc;
	}
	voteCollection& getvc()
	{
		return gvc;
	}
};

class groupcollection {
private:
	group* grouplist[MAX_GROUP]; //모든 그룹을 담고있는 배열
	int num; //그룹의 개수
public:
	groupcollection() : num(0) {} //default constructor
	~groupcollection() //destructor
	{
		delete[] &grouplist;
 	}
	group* getgroup(int i)
	{
		return grouplist[i];
	}
	int getnum()
	{
		return num;
	}
	void makegroup()
	{
		grouplist[num] = new group;
	}
	void plusnum()
	{
		num++;
	}
};

#endif
