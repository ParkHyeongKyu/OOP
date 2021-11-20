#ifndef __AS4_SONGIO_H
#define __AS4_SONGIO_H

#include <istream>
#include <ostream>

#include "model/song.h"

namespace as4::io
{
    namespace operators
    {
        /* Put your code here */
        std::ofstream& operator<<(std::ofstream& fout, as4::model::Song& song); //operator<<을 overload하기 위한 정의이다.
        std::ifstream& operator>>(std::ifstream& fin, as4::model::Song& song_recon); //operator>>을 overload하기 위한 정의이다.
    }
    bool operator==(const as4::model::Song s1, const as4::model::Song s2); //operator==을 overload하기 위한 정의이다.
}

#endif
