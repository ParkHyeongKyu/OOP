#ifndef __AS4_SONG_H
#define __AS4_SONG_H

#include <tuple>

#include "model/seq.h"

namespace as4::model
{
    /**
     * Abstract)
     * A class that represents a song consisting of two tracks (DefaultSeq)
     *
     * Note)
     * We have a problem: This class can only use DefaultSeq as internal
     * representation.
     * We may resolve this problem after we learn templates later in the course.
     */
    class Song
    {
    public:
        // Don't delete pointers returned from these methods
        const DefaultSeq* GetMelodySeq() const;
        DefaultSeq* GetMelodySeq();
        const DefaultSeq* GetDrumSeq() const;
        DefaultSeq* GetDrumSeq();
    private:
        std::pair<DefaultSeq, DefaultSeq> m_seqs;
    };
}

#endif
