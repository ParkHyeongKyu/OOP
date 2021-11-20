#include "model/song.h"

namespace as4::model
{
    const DefaultSeq *Song::GetMelodySeq() const
    {
        return &std::get<0>(m_seqs);
    }

    DefaultSeq *Song::GetMelodySeq()
    {
        return &std::get<0>(m_seqs);
    }

    const DefaultSeq *Song::GetDrumSeq() const
    {
        return &std::get<1>(m_seqs);
    }

    DefaultSeq *Song::GetDrumSeq()
    {
        return &std::get<1>(m_seqs);
    }
}
