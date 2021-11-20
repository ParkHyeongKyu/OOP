#ifndef __AS4_IO_SEQ_H
#define __AS4_IO_SEQ_H

#include <istream>
#include <ostream>

#include "model/seq.h"

/**
 * Abstract)
 * IO functions for note seqences
 *
 * Notes)
 * These namespace specifications(as4::io) are not mendatory for our code 
 * to work. However, it helps the users of this code not to mix many 
 * function/classes with identical names.
 */
namespace as4::io
{
    namespace operators
    {
        /* Put your code here */
        std::ofstream& operator<<(std::ofstream& fout, as4::model::ISeq& seq1); //opeartor<<을 overload하기 위한 정의이다.
        std::ifstream& operator>>(std::ifstream& fin, as4::model::ISeq& seq2); //operator>>을 overload하기 위한 정의이다.
    }
    bool operator==(const as4::model::ISeq& c1, const as4::model::ISeq& c2); //operator==을 ISeq형태의 parameter를 가질 때 overload하기 위한 정의이다.
    bool operator==(const as4::model::VectorSeq c1, const as4::model::VectorSeq c2); //operator==을 VectorSeq형태의 parameter를 가질 때 overload하기 위한 정의이다.
}

#endif
