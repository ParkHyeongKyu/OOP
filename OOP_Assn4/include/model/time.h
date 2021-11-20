#ifndef __AS4_MODEL_TIME_H
#define __AS4_MODEL_TIME_H

#include <cstdint>

/**
 * How time system works in our sequencer)
 *
 * A sequence consists of multiple 'beat's
 * Each 'beat' consists of multiple 'unit's
 *
 * The music plays according to current 'bpm'.
 * 'bpm' means number of beats played in a minute
 *
 * ----------------------- sequence--------------------------------------->
 * -----beat---->-----beat---->-----beat---->-----beat---->-----beat---->--
 * -unit->-unit->-unit->-unit->-unit->-unit->-unit->-unit->-unit->-unit->-u
 *
 * For simplicity, we excluded the notion of "bar".
 *
 * The meaning of a single beat is 'the basic unit of time in music theory'.
 * A beat can be split into multiple segments. We set granuality of this
 * segments by setting 'granuality' in TimeConfig.
 *
 * The reason we are not modifying floating point value for 'beat' directly is
 * , in general, people don't compose music with continuous units like
 * "0.333 beat" or "0.25867 beat". People almost always use discrete units like
 * "1/16 beat" or "1/8 beat". This discrete notation is more useful when
 * composing music.
 */
namespace as4::model
{

    // type alias (TimeInterval is replaced with uint64_t at compile time)
    // time length in number of units. The unit can have different meanings.
    using TimeInterval = uint64_t;

    // type alias
    // Timestamp is just a specialization of TimeInterval.
    // We can think of Timestamps as time intervals starting from 0.
    using Timestamp = TimeInterval;

    // The reason I used type alias instead of class definition)
    //
    // Time intervals will always be represented as a single integral value.
    // There is no need to declare a class that wraps this single value
    // and create corresponding getter and setter.
    //
    // 'using' is a way to make a type alias in C++
    // i.e.) if you declare "using A = B;", All 'A' types will be replaced
    //       with 'B' type at compile time. This is more useful after you
    //       learn templates in C++.

    /**
     * Abstract)
     * Time configuration
     *
     * Notes)
     * This object contains all the information needed to convert any
     * TimeInterval or Timestamp to actual clock time or beats.
     */
    class TimeConfig
    {
        public:
            /**
             * @param bpm           number of beats played per minute
             * @param granuality    number of units in a beat
             *                      i.e) if granuality is 2, 
             *                      TimeInterval value 1,2 corresponds to 0.5 beat, 1.0 beat.
             *                      similarly, 3,4 corresponds to 1.5 beat, 2.0 beat
             */
            TimeConfig(double bpm, uint64_t granuality);

            /**
             * Converts a TimeInterval to seconds
             */
            double Seconds(const TimeInterval &t) const;

            /**
             * Converts a TimeInterval to beats
             */
            double Beats(const TimeInterval &t) const;

            /**
             * Converts seconds to TimeInterval
             */
            TimeInterval IntervalFromSeconds(double seconds) const;

            /**
             * Converts beats to TimeInterval
             */
            TimeInterval IntervalFromBeats(double beats) const;

        private:
            double m_bpm; // number of beats per second
            uint64_t m_granuality; // maximum number of units in a beat
    };

    // Functions for convenience
    namespace time
    {
        /**
         * Get default time config with 120BPM and granuality of 4.
         * (Each beat consists of 4 units).
         */
        TimeConfig DefaultConfig();
    }
}

#endif
