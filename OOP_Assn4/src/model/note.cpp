#include "model/note.h"

namespace as4::model
{
    Note::Note(Timestamp start, TimeInterval duration, Pitch pitch) :
        m_start(start),
        m_duration(duration),
        m_pitch(pitch) {}
    

    Timestamp Note::GetStart() const
    {
        return m_start;
    }

    TimeInterval Note::GetDuration() const
    {
        return m_duration;
    }
    
    Pitch Note::GetPitch() const
    {
        return m_pitch;
    }

    void Note::SetStart(const Timestamp &timestamp)
    {
        m_start = timestamp;
    }

    void Note::SetDuration(const TimeInterval &interval)
    {
        m_duration = interval;
    }

    void Note::SetPitch(const Pitch &pitch)
    {
        m_pitch = pitch;
    }

    bool Note::operator==(const Note &other) const
    {
        return m_start == other.m_start &&
                m_duration == other.m_duration &&
                m_pitch == other.m_pitch;
    }

    bool Note::operator!=(const Note &other) const
    {
        return !(*this == other);
    }
}
