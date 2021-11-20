# -*- coding: utf-8 -*-
#include "default.h"
#include "member.h"
#include "vote.h"
using namespace std;

int printMenu1() //처음에 로그 파일의 포함 여부를 정하는 메뉴를 출력한다.
{
	string line;
	int loadMode;
	cout << "Load log file?(1:yes, 0:no (log will be deleted)):"; fflush(stdout);
	getline(cin, line);
	loadMode = atoi(line.c_str());
	return loadMode;
}

void printMenu2(int num)
{
	cout << "\n\n=======================" << endl; fflush(stdout);
	cout << "Num:" << num << endl; fflush(stdout);
	cout << "n=======================" << endl; fflush(stdout);
	cout << "1. Register as a Member" << endl; fflush(stdout);
	cout << "2. Unsubscribe from System" << endl; fflush(stdout);
	cout << "3. Login" << endl; fflush(stdout);
	cout << "4. Logout" << endl; fflush(stdout);
	cout << "5. Delete Existing Vote Item" << endl; fflush(stdout);
	cout << "6. Add a New Vote Item" << endl; fflush(stdout);
	cout << "7. List All Vote Items" << endl; fflush(stdout);
	cout << "8. Cast a Vote" << endl; fflush(stdout);
	cout << "9. Program Exit" << endl; fflush(stdout);
	cout << "=======================" << endl; fflush(stdout);
	cout << "Select Menu:"; fflush(stdout);
}

void clearTokens(string * tokens) //Tokens를 비워주는 역할을 한다.
{
	for (int i = 0; i < 4; i++)
		tokens[i].clear();
}

void doTask() //실질적인 역할을 수행하는 함수이다. 이 함수 안에서 대부분의 작업이 실행된다.
{
	//설명: 메인함수의 작업부분이다. 메뉴를 파싱하여 명령에 맞는 작업을 진행한다.
	// 메뉴 파싱을 위한 변수
	int menu = 0; //실행할 메뉴의 번호를 저장하는 변수이다.
	int num = 1; //수행 횟수를 저장하는 변수이다.
	int loadMode; //로그 파일의 로드 여부를 저장하는 변수이다. 1이면 로드 파일이 로드되고 0이면 로드되지 않는다.
	ofstream inLogWrite; //파일 입출력에서 로그 텍스트 파일로 출력해주는 역할을 한다.
	ifstream inLogRead; //파일 입출력에서 로그 텍스트 파일에서 입력을 받아들이는 역할을 한다.
	string tokens[4], line; //로그 파일에서 토큰을 저장하고 line을 받아들이는 역할을 한다.
	stringstream stream; //토큰을 얻을 수 있게 하는 역할을 한다.
	int nTokens=0; //number of tokens in string
	bool nowlogin = false; //현재 로그인 상태를 나타낸다.
	Member plogin; //현재 로그인 되어있는 멤버의 정보를 저장한다.

	loadMode = printMenu1();

	MemberCollection mc; //전체 멤버를 관리하는 membercollection 변수이다.
	voteCollection vc; //전체 투표를 관리하는 votecollection 변수이다.

	if (!loadMode) { //로그 파일을 입력받지 않았을 경우 새롭게 로그 파일에 출력한다.
		inLogWrite.open(COMMAND_LOG_FILE_NAME, ios::out);
	}
	else { //로그 파일을 입력받았을 경우 로그 파일을 입력받고 그 뒤에 계속 이어서 달게 한다.
		inLogRead.open(COMMAND_LOG_FILE_NAME,ios::in); //read mode
		inLogWrite.open(COMMAND_LOG_FILE_NAME, ios::in|ios::app); //concat without truncation
	}

	// 종료 메뉴(9)가 입력되기 전까지 반복함
	while (1)
	{
		//Menu Parsing
		printMenu2(num++); // 입력파일에서 메뉴 숫자 읽기
		if (loadMode == 1) //로그 파일을 입력 받았을 경우
		{
			getline(inLogRead, line);
			if (line == "")
			{
				//end of file with newline
				if (inLogRead.eof())
				{
					//stop reading from logfile 
					//stdin mode starts
					inLogRead.close();
					loadMode = 0;
					getline(cin, line);
					//when first stdin input was newline
					//continue without loggin input
					if (line == "")
					{
						cout << "Selected Menu: Undefined menu selection" << endl; fflush(stdout);
						continue;
					}
					menu = atoi(line.c_str());
				}
				//middle of file with new line
				//continue without logging
				else
				{
					cout << "\nSelected Menu: Undefined menu selection" << endl; fflush(stdout);
					continue;
				}
			}

			//inputs != newline
			else
			{
				stream.str(line);
				nTokens = 0;
				clearTokens(tokens);
				//Read all tokens(seperated by " ")
				while (stream >> tokens[nTokens]) //한 줄에서 token들을 입력받아서 저장함
					nTokens++;
				stream.clear();
				menu = atoi(tokens[0].c_str());
				cout << menu << endl; fflush(stdout);
			}


		}
		//stdin mode
		else
		{
			getline(cin, line);
			if (line == "")
			{
				cout << "Selected Menu: Undefined menu selection" << endl; fflush(stdout);
				continue;
			}
			menu = atoi(line.c_str());
		}

		// 메뉴 구분 및 해당 연산 수행
		switch (menu)
		{
		case 1:
		{	
			mc.join(&mc, loadMode, inLogWrite,tokens,nTokens, nowlogin); //회원가입 시켜주는 함수 실행
			break;
		}
		case 2:
		{
			nowlogin = mc.unsubscribe(loadMode, inLogWrite, tokens, nTokens, nowlogin, plogin); //회원탈퇴 시켜주는 함수 실행
			break;
		}
		case 3:
		{
			nowlogin = mc.Login(loadMode, tokens, nTokens, plogin, inLogWrite, nowlogin); //로그인해주는 함수 실행
			break;
		}
		case 4:
		{
			nowlogin = mc.Logout(loadMode, tokens, nTokens, plogin, inLogWrite, nowlogin); //로그아웃 해주는 함수 실행
			break;
		}
		case 5:
		{
			vc.deletevoteitem(loadMode, inLogWrite, nTokens, tokens, nowlogin); //투표를 삭제해주는 함수 실행
			break;
		}
		case 6:
		{
			vc.addvoteitem(loadMode, inLogWrite, nTokens, tokens, nowlogin); //투표를 추가해주는 함수 실행
			break;
		}
		case 7: //enter 필요
		{
			vc.listallvote(loadMode, nTokens, tokens, nowlogin, inLogWrite); //투표리스트를 출력하는 함수 실행
			break;
		}
		case 8:
		{
			vc.castvote(loadMode, inLogWrite, nTokens, tokens, nowlogin, plogin, mc); //투표를 하게 해주는 함수 실행
			break;
		}
		case 9:
		{
			inLogWrite.close(); //프로그램 종료
			return;
		}
		default:
			cout << "Undefined menu selection" << endl; //1~9번 이외의 값 입력했을 경우
			if(!loadMode)
				inLogWrite << menu << " " << endl;
			break;
			
		}
		if (!loadMode && menu != 4 && menu != 7 && menu >= 1 && menu < 10) { //입력값이 없는 4번과 7번을 제외한 경우에는 getchar을 통해 버퍼를 비워줌
			getchar();
		}
	}
	return;
}
