#include "Manager.h"

void Manager::Menu()
{
    int choice;

    while(1){
        cout<<endl;
        cout<<"====================="<<endl;
        cout<<" >> 1. Game Start"<<endl;
        cout<<" >> 2. Program exit"<<endl;
        cout<<" >> ";
        cin>>choice;

        if(cin.fail()){ // to prevent infinite loop when getting string in "choice"
            cin.clear();
            cin.ignore(256, '\n');
        }

        if(choice == 1){
            // Select game mode
            cout<<endl;
            Menu_SelectModeAndPlay();
        }
        else if(choice == 2){
            cout<<" >> Program exit."<<endl;
            break;
        }
        else{
            cout<<" >> Invalid choice. Please enter again."<<endl;
            cout<<endl;
        }
    }
    // exit the program when break this loop
}

void Manager::Play(int GameMode)
{
    Game.MakeAnswerArray(Difficulty);
    if(GameMode == 1){
        if(Game.PLAY_Solo()){
            cout<<" >> You won!"<<endl;
        }
        else{
            cout<<" >> You lose!"<<endl;
        }
    }
    else if(GameMode == 2){
        if(Game.PLAY_PVP()){
            cout<<" >> Player 1 won!"<<endl;
        }
        else{
            cout<<" >> Player 2 won!"<<endl;
        }
    }
    else if(GameMode == 3){
        if(Game.PLAY_Computer()){
            cout<<" >> You won!"<<endl;
        }
        else{
            cout<<" >> You lose!"<<endl;
        }
    }
    else{
        cout<<"SYSTEM : Invalid game mode. Program exit."<<endl;
        exit(1);
    }
}

void Manager::Menu_SelectModeAndPlay()
{
    int choice;
    while(true){
        cout<<" >> Select Game Mode"<<endl;
        cout<<" >> 1. Solo Play"<<endl;
        cout<<" >> 2. 2 Players"<<endl;
        cout<<" >> 3. Play with computer"<<endl;
        cout<<" >> "; cin>>choice;
        if(choice != 1 && choice != 2 && choice != 3){
            cout<<" >> Invalid Mode. Please enter again."<<endl;
        }
        else break;
    }
    Menu_SelectDifficulty();
    Play(choice);
    GameCount++;
}

void Manager::Menu_SelectDifficulty()
{
    Difficulty = 0;
    int diff;
    while(true){
        cout<<" >> Select difficulty (easy: 1 / normal: 2 / hard: 3)"<<endl;
        cout<<" >> "; cin >> diff;

        if(cin.fail()){ // to prevent infinite loop when getting string in "choice"
            cin.clear();
            cin.ignore(256, '\n');
        }

        if(diff!=1 && diff!=2 && diff!=3){
            cout<<" >> Invalid Difficulty. Input again."<<endl;
        }
        else break;
    }
    Difficulty = diff + 2;
}