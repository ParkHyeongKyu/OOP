#ifndef __AS4_MODEL_PITCH_H
#define __AS4_MODEL_PITCH_H

#include <string>
#include <vector>

namespace as4::model
{
    /**
     * A class for repesenting pitch of a note
     */
    class Pitch
    {
        public:
            Pitch() {}
            Pitch(int pitch_class, int octave);

            /**
             * Abstract)
             * Get pitch class of this pitch
             * 
             * Note)
             * 0 -> C
             * 1 -> C#
             * 2 -> D
             * 3 -> D#
             * ...
             * 11 -> B
             * (>=12 or negative) -> undefined
             */
            int GetPitchClass() const;

            /**
             * Abstract)
             * Get octave of this pitch
             *
             * Note)
             * i.e) 440Hz tone is 'A' note of octave '4'
             */
            int GetOctave() const;

            bool operator==(const Pitch &other) const;
            bool operator!=(const Pitch &other) const;

        private:
            int m_pitch_class;
            int m_octave;
    };

    // Convenience class and functions for pitch
    namespace pitch
    {
        class StandardPitchStringfier
        {
            public:
                /**
                 * Abstract)
                 * Create pitch from string
                 * 
                 * Note)
                 * String pitch code is constructed as follows
                 *
                 *     <pitch class in alphabet><octave>
                 *
                 * Example)
                 * 
                 * "A4" -> Pitch('A', '4')
                 * "C#4" -> Pitch('C#', '4')
                 *
                 * you can't use 'b' (flat). Only '#' (sharp) is allowed
                 * "Bb4" -> error
                 */
                Pitch FromString(const std::string &code);

                /**
                 * Abstract)
                 * Create string code from pitch object
                 */
                std::string ToString(const Pitch &pitch);
        };
    }
}

#endif
