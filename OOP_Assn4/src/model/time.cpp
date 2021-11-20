#include <cmath>

#include "model/time.h"


namespace as4::model
{
    TimeConfig::TimeConfig(double bpm, uint64_t granuality) :
        m_bpm(bpm),
        m_granuality(granuality)
    {}

    double TimeConfig::Seconds(const TimeInterval &t) const
    {
        const auto beats = Beats(t);
        const auto minutes = beats / m_bpm;
        const auto seconds = minutes * 60.0;
        return seconds;
    }

    double TimeConfig::Beats(const TimeInterval &t) const
    {
        return static_cast<double>(t) / m_granuality;
    }

    TimeInterval TimeConfig::IntervalFromSeconds(double seconds) const
    {
        const auto minutes = seconds / 60.0;
        const auto beats = minutes * m_bpm;
        const auto interval = IntervalFromBeats(beats);
        return interval;
    }

    TimeInterval TimeConfig::IntervalFromBeats(double beats) const
    {
        return static_cast<TimeInterval>(std::lround(beats * m_granuality));
    }

    namespace time
    {
        TimeConfig DefaultConfig()
        {
            return TimeConfig(120, 4);
        }
    }
}