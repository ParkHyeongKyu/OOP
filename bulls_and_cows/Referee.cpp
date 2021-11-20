#include "Referee.h"

Referee::Referee() : Difficulty(0), SetCount(0), Answer_array(nullptr), Return_value(nullptr)
{
}

Referee::~Referee()
{
    if(Answer_array != nullptr){
        delete Answer_array;
    }
}

bool Referee::PLAY_Solo()
{
    SetCount = 0;
    Array Guess_array(Difficulty);  // User's array. 
    bool result_flag = false;       // win <- true, lose <- false

    while(SetCount != 9){
    // 1 loop = 1 set of the game

        string guess;
        while(true){
            cout<<" >> Input your guess("<<Difficulty<<" numbers). 'help' to view help."<<endl;
            guess.clear(); // for "fflush"
            cout<<" >> "; cin >> guess;
            if(guess == "help"){
                ViewHelp();
            }
            else if(guess == "stop"){
                cout<<endl;
                return false;
            }
            else if(guess == "exit"){
                exit(1);
            }
            else if(guess.size() != Difficulty){
                cout<<" >> Please enter the correct number of your guess."<<endl;
            }
            else{
                if(Guess_array.SetArray(guess)){ // return false << the element was overlapping
                    break;
                    // if the "guess" was correct, then break and go to next step; check Answer_array
                }
            }
        }

        Return_value = Answer_array->Check(Guess_array);    
        if(Return_value->isOut()){
            cout<<" >> OUT. "<<endl;
        }
        else{
            if(Return_value->Strike() == Difficulty){ // user win
                result_flag = true;
                break;
            }
            cout<<" >> "<<Return_value->Strike()<<" STRIKE."<<endl;
            cout<<" >> "<<Return_value->Ball()<<" BALL."<<endl;
            Guess_array.clear();
        }
        SetCount++;
        cout<<endl;
        // one set is over
    }

    return result_flag;
}

bool Referee::PLAY_PVP()
{
    SetCount = 0;
    Array Guess_array(Difficulty);  // User's array.
	Array Guess_array2(Difficulty); //User2's array.
    bool result_flag = false;       // win <- true, lose <- false

	while (SetCount != 9) {
		// 1 loop = 1 set of the game

		string guess;
		while (true) {
			cout << "Player1's turn" << endl;
			cout << " >> Input your guess(" << Difficulty << " numbers). 'help' to view help." << endl;
			guess.clear(); // for "fflush"
			cout << " >> "; cin >> guess;
			if (guess == "help") {
				ViewHelp();
			}
			else if (guess == "stop") {
				cout << endl;
				return false;
			}
			else if (guess == "exit") {
				exit(1);
			}
			else if (guess.size() != Difficulty) {
				cout << " >> Please enter the correct number of your guess." << endl;
			}
			else {
				if (Guess_array.SetArray(guess)) { // return false << the element was overlapping
					break;
					// if the "guess" was correct, then break and go to next step; check Answer_array
				}
			}
		}

		Return_value = Answer_array->Check(Guess_array);
		if (Return_value->isOut()) {
			cout << " >> OUT. " << endl;
		}
		else {
			if (Return_value->Strike() == Difficulty) { // user win
				result_flag = true;
				cout << " >> Player 1 won!" << endl;
				break;
			}
			cout << " >> " << Return_value->Strike() << " STRIKE." << endl;
			cout << " >> " << Return_value->Ball() << " BALL." << endl;
			Guess_array.clear();
		}
		SetCount++;
		cout << endl;

		string guess2;
		while (true) {
			cout << "Player2's turn" << endl;
			cout << " >> Input your guess(" << Difficulty << " numbers). 'help' to view help." << endl;
			guess2.clear(); // for "fflush"
			cout << " >> "; cin >> guess2;
			if (guess2 == "help") {
				ViewHelp();
			}
			else if (guess2 == "stop") {
				cout << endl;
				return false;
			}
			else if (guess2 == "exit") {
				exit(1);
			}
			else if (guess2.size() != Difficulty) {
				cout << " >> Please enter the correct number of your guess." << endl;
			}
			else {
				if (Guess_array2.SetArray(guess2)) { // return false << the element was overlapping
					break;
					// if the "guess" was correct, then break and go to next step; check Answer_array
				}
			}
		}

		Return_value = Answer_array->Check(Guess_array2);
		if (Return_value->isOut()) {
			cout << " >> OUT. " << endl;
		}
		else {
			if (Return_value->Strike() == Difficulty) { // user win
				result_flag = true;
				cout << " >> Player 2 won!" << endl;
				break;
			}
			cout << " >> " << Return_value->Strike() << " STRIKE." << endl;
			cout << " >> " << Return_value->Ball() << " BALL." << endl;
			Guess_array2.clear();
		}
		SetCount++;
		cout << endl;
		// one set is over
	}

    return result_flag;
}

bool Referee::PLAY_Computer()
{
    SetCount = 0;
    Array Guess_array(Difficulty);  // User's array.
    bool result_flag = false;       // win <- true, lose <- false


    /* */

    return result_flag;
}

void Referee::MakeAnswerArray(int _difficulty)
{
    if(Answer_array != nullptr){ // delete previous Answer_array
        delete Answer_array;
    }
    Difficulty = _difficulty;
    Answer_array = new Answer(Difficulty);
}

void Referee::ViewHelp() const
{   
    cout<<endl;
    cout<<" >> 'stop' - Stop this game and go to main menu."<<endl;
    cout<<" >> 'exit' - Program exit."<<endl;
    cout<<endl;
}