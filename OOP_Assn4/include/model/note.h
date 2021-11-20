#ifndef __AS4_MODEL_NOTE_H
#define __AS4_MODEL_NOTE_H

#include "model/time.h"
#include "model/pitch.h"

namespace as4::model
{
    /**
     * A class for repesenting a musical note
     */
    class Note
    {
        public:
            Note() {}
            Note(Timestamp start, TimeInterval duration, Pitch pitch);

            Timestamp GetStart() const;
            TimeInterval GetDuration() const;
            Pitch GetPitch() const;

            void SetStart(const Timestamp &timestamp);
            void SetDuration(const TimeInterval &interval);
            void SetPitch(const Pitch &pitch);

            bool operator==(const Note &other) const;
            bool operator!=(const Note &other) const;

        private:
            Timestamp m_start;
            TimeInterval m_duration;
            Pitch m_pitch;
    };
}

#endif

