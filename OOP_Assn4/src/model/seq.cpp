#include <algorithm>

#include "model/seq.h"

namespace as4::model
{
    VectorSeq::~VectorSeq()
    {
        for(size_t i=0; i<m_notes.size(); i++)
        {
            delete m_notes[i];
        }
    }

    VectorSeq::VectorSeq(const VectorSeq &other)
    {
        for(size_t i=0; i<other.m_notes.size(); i++)
        {
            m_notes.push_back(new Note(*other.m_notes[i]));
        }
    }

    VectorSeq &VectorSeq::operator=(const VectorSeq &other)
    {
        for(size_t i=0; i<m_notes.size(); i++)
        {
            delete m_notes[i];
        }
        m_notes.clear();

        for(size_t i=0; i<other.m_notes.size(); i++)
        {
            m_notes.push_back(new Note(*other.m_notes[i]));
        }

        return *this;
    }

    void VectorSeq::Put(const Note &note)
    {
        m_notes.push_back(new Note(note));
        // Since we use a simple vector,
        // we must sort the vector everytime we modify m_notes
        Sort(m_notes);
    }

    std::vector<Note*> VectorSeq::Get(const Timestamp &pos_seeker) //pos_seeker상태에서 연주중이거나 연주 시작되는 Note를 result에 담아 반환
    {
        std::vector<Note*> result;
        for(size_t i=0; i<m_notes.size(); i++)
        {
            Timestamp start = m_notes[i]->GetStart();
            Timestamp end = start+m_notes[i]->GetDuration();
            if (start <= pos_seeker && end > pos_seeker)
            {
                result.push_back(m_notes[i]);
            }
        }

        return result;
    }

    std::vector<Note*> VectorSeq::GetStart(const Timestamp& pos_seeker) //posseeker에서 시작하는 Note들의 vector을 return함
    {
        std::vector<Note*> result;
        for(size_t i = 0; i < m_notes.size(); i++)
        {
            Timestamp start = m_notes[i]->GetStart();
            if(start == pos_seeker)
            {
                result.push_back(m_notes[i]);
                Sort(result);
            }
        }

        return result;
    }

    bool VectorSeq::Remove(const Note *note)
    {
        const auto target =
                std::find(std::begin(m_notes), std::end(m_notes), note);
        if(std::end(m_notes) != target) // remove target found
        {
            m_notes.erase(target);
            // Since we use a simple vector,
            // we must sort the vector everytime we modify m_notes
            Sort(m_notes);
            return true;
        }
        else { // not found
            return false;
        }
    }

    const std::vector<Note*> VectorSeq::GetOrdered() const
    {
        // Just copy notes directly since they are already ordered
        return m_notes;
    }

    TimeInterval VectorSeq::GetSeqTimeLength() const
    {
        if(0 == m_notes.size())
        {
            return 0;
        }
        else {
            return m_notes.back()->GetStart() +
                    m_notes.back()->GetDuration();
        }
    }

    void VectorSeq::Sort(std::vector<Note*> svec)
    {
        // sort m_notes according to start time of each note
        std::sort(std::begin(svec), std::end(svec),
                [](const Note *a, const Note *b){
            return a->GetStart() < b->GetStart(); });
    }
}
