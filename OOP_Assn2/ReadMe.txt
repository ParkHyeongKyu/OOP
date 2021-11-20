default.h : 기본적으로 포함시킬 라이브러리들을 포함시키고 프로그램에서 사용할 상수들을 정의함.

member.h : 회원의 정보를 저장하고 수정할 수 있는 Member class와 전체 회원을 관리하는 작업을 하는 MemberCollection class를 정의함.

vote.h : 투표의 정보를 저장하고 각 투표에 대한 작업을 실행할 수 있는 vote class와 전체 투표를 관리하는 작업을 하는 voteCollection class를 정의함.

main.cpp : menuParser.cpp에 정의되어있는 doTask()함수를 실행시킴으로써 프로그램을 시작하게 함.

menuParser.cpp : 메뉴의 출력과 실행에 대한 함수가 있는 소스파일로 로그파일의 포함여부, 메뉴 번호의 선택, 메뉴 번호에 따른 함수 실행 등의 작업이 진행된다.

member.cpp : MemberCollection class에서 정의된 함수들을 선언한 곳으로 회원가입, 회원탈퇴, 로그인, 로그아웃의 작업이 실행된다.

vote.cpp : voteCollection class에서 정의된 함수들을 선언한 곳으로 투표 제거, 투표 추가, 투표 리스트 확인, 투표하기의 작업이 실행된다.