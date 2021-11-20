default.h : 기본적인 라이브러리를 include하고 필요한 상수들을 정의한 헤더파일

group.h : group class와 groupcollection class가 정의되어 있어 전체 그룹을 관리하거나 그룹 각각을 관리할 수 있음

member.h : Member class, groupmemebr class, groupleader class, groupcollection class가 정의되어 있음.
	   각각의 멤버를 관리하고, 멤버의 신분에 따라 실행할 수 있는 method들이 class별로 나눠져 있음.

vote.h : vote class, votecollection class가 정의되어 있음.
	 각각의 투표를 관리하고, 전체 투표도 관리 할 수 있는 기능을 수행 가능함

main.cpp : doTask() 함수를 호출하여 프로젝트를 시작하는 역할을 함

menuParser.cpp : 로그 파일의 로드 여부를 정하고 현재 사용자의 신분에 따른 메뉴를 출력함.
		 viewall() 함수가 정의되어 0 0을 입력하면 현재 프로그램 내의 모든 정보를 출력해줌.

member.cpp : MemberCollection class내의 public method들을 정의하였으며 Member class내에서
	     다형성을 이용하는 method들도 정의되어 있는 공간임

vote.cpp : voteCollection class내의 public method들을 정의한 공간임

groupmember.cpp : groupmember class내의 public method들을 정의한 공간임

groupleader.cpp : groupleader class내의 public method들을 정의한 공간임
