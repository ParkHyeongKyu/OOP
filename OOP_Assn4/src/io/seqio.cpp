#include "io/seqio.h"
#include "fstream" //추가
#include "sstream"

namespace as4::io
{
    namespace operators
    {
        /* Put your code here */
        std::ofstream& operator<<(std::ofstream& fout, as4::model::ISeq& seq1)
        {
            for(unsigned long long i = 0; i < seq1.GetOrdered().size(); i++) //start, duration, pitchclass, octave를 차례대로 fout시킨다.
            {
                fout << seq1.GetOrdered().operator[](i)->GetStart() << " ";
                fout << seq1.GetOrdered().operator[](i)->GetDuration() << " ";
                fout << seq1.GetOrdered().operator[](i)->GetPitch().GetPitchClass() << " ";
                fout << seq1.GetOrdered().operator[](i)->GetPitch().GetOctave() << " " << std::endl;
            }
            return fout;
        }
        std::ifstream& operator>>(std::ifstream& fin, as4::model::ISeq& seq2)
        {
            std::string tokens[4], line; //토큰을 저장하는 배열과 라인을 받아들이는 string이다.
            int nTokens; //토큰의 개수
            std::stringstream stream; //stream
            as4::model::Timestamp nstart;
            as4::model::TimeInterval ndur;
            int noct, npc;
            while(1) {
            std::getline(fin, line); //한 라인을 line에 받아옴
            if(line == "") //라인이 비었을 경우 while문을 빠져나감, 즉 파일의 마지막 부분을 의미함
                break;
            stream.str(line); //stream에 line을 담음
            nTokens = 0;
            for (int i = 0; i < 4; i++) //토큰을 저장하는 배열을 clear해줌
                tokens[i].clear();
            while (stream >> tokens[nTokens]) //stream에서 token들을 받아오며 nToken의 개수를 셈
                nTokens++;
            stream.clear(); //stream을 clear시킴

            nstart = atoi(tokens[0].c_str()); //atoi함수를 이용하여 각 토큰을 알맞은 변수에 집어넣음
            ndur = atoi(tokens[1].c_str());
            npc = atoi(tokens[2].c_str());
            noct = atoi(tokens[3].c_str());

            as4::model::Pitch np(npc, noct); //pitchclass와 octave를 합쳐 pitch를 만듬
            as4::model::Note n(nstart, ndur, np); //노트를 생성함
            seq2.Put(n); //seq2에 생성한 노트를 삽입함
            }
            return fin;
        }
    }
    bool operator==(const as4::model::ISeq& c1, const as4::model::ISeq& c2)
    {
        if(c1.GetOrdered().size() == c2.GetOrdered().size()) //c1과 c2의 size가 같을 경우
        {
            for(unsigned long long i = 0; i < c1.GetOrdered().size(); i++) //for문을 돌면서 모든 member가 같은지 비교함, 중간에 다른게 있으면 바로 0을 return함
            {
                if(c1.GetOrdered().operator[](i)->GetStart() != c2.GetOrdered().operator[](i)->GetStart())
                    return 0;
                else if(c1.GetOrdered().operator[](i)->GetDuration() != c2.GetOrdered().operator[](i)->GetDuration())
                    return 0;
                else if(c1.GetOrdered().operator[](i)->GetPitch().GetOctave() != c2.GetOrdered().operator[](i)->GetPitch().GetOctave())
                    return 0;
                else if(c1.GetOrdered().operator[](i)->GetPitch().GetPitchClass() != c2.GetOrdered().operator[](i)->GetPitch().GetPitchClass())
                    return 0;
            }
            return 1; //모두 같다면 1을 return함
        }
        else {
            return 0; //size가 같지 않은 경우 c1과 c2가 다른 것이므로 0을 return함
        }
    }
    bool operator==(as4::model::VectorSeq c1, as4::model::VectorSeq c2)
    {
        if(c1.GetOrdered().size() == c2.GetOrdered().size()) //c1과 c2의 size가 같을 경우
        {
            for(unsigned long long i = 0; i < c1.GetOrdered().size(); i++) //for문을 돌면서 모든 member가 같은지 비교함, 중간에 다른게 있으면 바로 0을 return함
            {
                if(c1.GetOrdered().operator[](i)->GetStart() != c2.GetOrdered().operator[](i)->GetStart())
                    return 0;
                else if(c1.GetOrdered().operator[](i)->GetDuration() != c2.GetOrdered().operator[](i)->GetDuration())
                    return 0;
                else if(c1.GetOrdered().operator[](i)->GetPitch().GetOctave() != c2.GetOrdered().operator[](i)->GetPitch().GetOctave())
                    return 0;
                else if(c1.GetOrdered().operator[](i)->GetPitch().GetPitchClass() != c2.GetOrdered().operator[](i)->GetPitch().GetPitchClass())
                    return 0;
            }
            return 1; //모두 같다면 1을 return함
        }
        else {
            return 0; //size가 같지 않은 경우 c1과 c2가 다른 것이므로 0을 return함
        }
    }
}
