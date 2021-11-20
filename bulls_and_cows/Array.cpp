#include "Array.h"

PresentInfo::PresentInfo(int strike, int ball)
{
    #ifdef DEBUG_MODE
    cout<<" # PresentInfo Construct!"<<endl;
    cout<<" #   Strike : "<<Number[1]<<endl;
    cout<<" #   Ball : "<<Number[2]<<endl;
    #endif
    Number[1] = strike;
    Number[2] = ball;
    if(Number[1] == 0 && Number[2] == 0){
        Number[0] = 1;  // Out
    }
    else{
        Number[0] = 0;  // no Out
    }
}

PresentInfo::PresentInfo(PresentInfo& cpy)
{
    for(int i=0; i<3; i++){
        Number[i] = cpy.Number[i];
    }
}

bool PresentInfo::isOut() const
{
    if(Number[0] == 1){
        return true;
    }
    else{
        return false;
    }
}

int PresentInfo::Strike() const
{
    return Number[1];
}

int PresentInfo::Ball() const
{
    return Number[2];
}

Array::Array(int Difficulty) : ElemNum(Difficulty), Info(nullptr)
{

}

Array::~Array()
{
    if(Info != nullptr){
        delete Info;
    }
}

int& Array::operator[](int idx)
{
    if(idx < 0 || idx >= ElemNum){
        cout<<"SYSTEM : Array Boundary error! Return vector[0]"<<endl;
        return arr[idx];
    }
    return arr[idx];
}

PresentInfo* Array::Check(Array& Present)
{
    if(Info != nullptr){ // delete previous PresentInfo
        delete Info;
    }

    int strike_num = 0;
    int ball_num = 0;
    
    for(int i=0; i<ElemNum; i++){
        for(int j=i; j<ElemNum; j++){
            if(i==j && arr[i] == Present[i]){
                #ifdef DEBUG_MODE
                cout<<" # Strike ++!"<<endl;
                #endif
                strike_num++;
            }
            else if(i!=j && arr[i] == Present[j]){
                #ifdef DEBUG_MODE
                cout<<" # Ball ++!"<<endl;
                #endif
                ball_num++;
            }
        }
    }
    Info = new PresentInfo(strike_num, ball_num);
    return Info;
}

bool Array::SetArray(string& Numbers)
{
    arr.clear();
    for(int i=0; i<ElemNum; i++){
        #ifdef DEBUG_MODE
        cout<<" # Input string["<<i<<"] : "<<Numbers[i]<<endl;
        #endif
        int int_num = Numbers[i]-48; // operating ASCII code
        if(!this->push_back(int_num)){
            arr.clear();
            return false;
        }
    }
    return true;
}

void Array::clear()
{
    arr.clear();
}

bool Array::push_back(int elem)
{
    if(arr.size() == ElemNum){
        cout<<"SYSTEM : Vector is full!"<<endl;
        return false;
    }
    else{
        for(int i=0; i<arr.size(); i++){
            if(arr[i] == elem){
                cout<<" >> Two or more same number exist. Please enter again."<<endl;
                return false;
            }
        }
        arr.push_back(elem);
        return true;
    }
}

Answer::Answer(int Difficulty) : Array(Difficulty)
{
    SetRandomNumber();
    if(ElemNum == 3){
        cout<<" >> EASY MODE"<<endl;
    }
    else if(ElemNum == 4){
        cout<<" >> NORMAL MODE"<<endl;
    }
    else if(ElemNum == 5){
        cout<<" >> HARD MODE"<<endl;
    }
    else{
        cout<<"Difficulty : "<<Difficulty<<endl;
        cout<<"SYSTEM : Invalid Difficulty. Program exit."<<endl;
        exit(1);
    }
}

void Answer::SetRandomNumber()
{
    vector<int*> MemoryCollector;
    const int lowest = 0;
    const int highest = 9;
    const int range = (highest - lowest) + 1;

    while(arr.size() != ElemNum){
        int* random = new int(rand()%10);
        MemoryCollector.push_back(random);
        this->push_back(*random);
    }

    #ifdef DEBUG_MODE
    for(int i=0; i<arr.size(); i++){
        cout<<"answer : "<<arr[i]<<endl;
    }
    #endif

    while(MemoryCollector.size() != 0){
        delete MemoryCollector.back();
        MemoryCollector.pop_back();
    }
}

bool Answer::push_back(int randomNum)
{
    if(arr.size() == 0){
        arr.push_back(randomNum);
    }
    for(int i=0; i<arr.size(); i++){ // Overlap check
        if(arr[i] == randomNum){
            return false;
        }
    }
    arr.push_back(randomNum);
    return true;
}