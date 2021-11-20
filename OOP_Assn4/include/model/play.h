#ifndef __AS4_MODEL_PLAY_H
#define __AS4_MODEL_PLAY_H

#include "model/song.h"
#include <QSoundEffect>
#include <QTimer>
#include <QEventLoop>

namespace as4::model
{
    class playmusic : public QObject{ //melody 와 drum을 재생하는 class의 base class이다.
        Q_OBJECT
    public:
        playmusic() { num = 0; } //constructor
        virtual ~playmusic() = default; //destructor
    public slots:
        void start(); //실제적인 재생을 담당하는 함수
    protected:
        std::vector<Note*> result; //재생할 Note목록을 Sort된 형태로 담는 vector
        ISeq* track; //재생할 note의 목록을 담고있는 ISeq포인터
        QEventLoop loop; //이벤트를 실행시켜주는 변수
        unsigned long long num; //재생할 노트의 개수
    };

    class playmelody : public playmusic
    {
        Q_OBJECT
    public:
        playmelody() //constructor
        {
            track = nullptr;
        }
        playmelody(VectorSeq* init) //constructor
        {
            track = new VectorSeq(*init);
        }
        ~playmelody() //destructor
        {
            delete track;
        }
    };

    class playdrum : public playmusic
    {
        Q_OBJECT
    public:
        playdrum() //constructor
        {
            track = nullptr;
        }
        playdrum(VectorSeq* init) //constructor
        {
            track = new VectorSeq(*init);
        }
        ~playdrum() //destructor
        {
            delete track;
        }
    };
}
#endif // __AS4_MODEL_PLAY_H
