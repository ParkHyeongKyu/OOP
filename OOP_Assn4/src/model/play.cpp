#include "model/play.h"
#include "model/seq.h"
#include "model/time.h"
#include <QString>

namespace as4::model
{
    void playmusic::start()
    {
        result = track->GetOrdered(); //result에 track의 note들을 ordered해서 받아온다.
        num = result.size(); //num을 result의 size로 지정한다.
        std::string s[num]; //재생할 소리들의 Url을 String형태로 저장하는 배열이다.
        QString qs[num]; //재생할 소리들의 Url을 QString형태로 저장하는 배열이다.
        QTimer* timer[2][num]; //소리를 알맞은 시간에 재생할 수 있도록 해주는 타이머이다.
        QSoundEffect se[num]; //소리를 재생할 수 있게 해주는 배열이다.
        QTimer* f_timer = new QTimer; //loop를 종료시키는 타이머 역할을 한다.

        for(int i = 0; i < 2; i++) //타이머를 동적할당 시킨다.
        {
            for(int j = 0; j < num; j++)
            {
                timer[i][j] = new QTimer;
            }
        }
        for(int i = 0; i < num; i++)
        {
            if(typeid(*this) == typeid(playmelody)) //this포인터가 playmelody객체일 경우 Url을 지정
            {
                s[i] = ":/melody/melody/" + std::to_string(result[i]->GetPitch().GetPitchClass()) + "_" + std::to_string(result[i]->GetPitch().GetOctave()) + ".wav";
            }
            else { //this포인터가 playdrum 객체일 경우 Url을 지정
                s[i] = ":/drum/drum/" + std::to_string(result[i]->GetPitch().GetPitchClass()) + "_" + std::to_string(result[i]->GetPitch().GetOctave()) + ".wav";
            }
            qs[i] = QString::fromStdString(s[i]); //String형태의 Url을 QString형태로 바꾼다.
            se[i].setSource(QUrl::fromLocalFile(qs[i])); //재생할 Source를 지정한다.
        }
        if(typeid(*this) == typeid(playmelody)) //this포인터가 playmelody 객체인 경우(클래스 상속관계를 이용함)
        {
            for(int i = 0; i < num; i++)
            {
                timer[0][i]->singleShot(result[i]->GetStart() * 125, &se[i], SLOT(play())); //120bpm의 속도로 재생되는 경우 각 unit마다 0.125초동안 재생되므로 singleshot을 이용하여 재생되는 시간에 맞춰 play시킨다.
                timer[1][i]->singleShot(result[i]->GetStart() * 125 + 500, &se[i], SLOT(stop())); //1beat(0.5초) 재생 이후 음원이 멈춰야 하므로 재생시작 후 0.5초 이후에 음원을 멈춘다.
            }
        }
        else { //this포인터가 playdrum 객체인 경우(클래스 상속관계를 이용함)
            for(int i = 0; i < num; i++)
            {
                timer[0][i]->singleShot(result[i]->GetStart() * 125, &se[i], SLOT(play())); //120bpm의 속도로 재생되는 경우 각 unit마다 0.125초동안 재생되므로 singleshot을 이용하여 재생되는 시간에 맞춰 play시킨다.
            }
        }
        f_timer->singleShot(5000, &loop, SLOT(exit())); //5초(10beat)가 지나면 loop를 종료해주는 exit()을 호출한다.
        loop.exec(); //이벤트 루프를 시작한다. 즉, 재생을 시작한다.
    }
}
