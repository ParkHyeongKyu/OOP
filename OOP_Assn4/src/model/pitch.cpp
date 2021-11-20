#include <string>
#include <cstring>
#include <map>
#include <algorithm>
#include <cctype>
#include <vector>

#include "model/pitch.h"
#include "util/require.h"

namespace as4::model
{
    Pitch::Pitch(int pitch_class, int octave) : m_pitch_class(pitch_class), m_octave(octave)
    {
        AS4_REQUIRE(0 < octave);
        AS4_REQUIRE(0 <= pitch_class && 12 > pitch_class);
    }

    int Pitch::GetPitchClass() const
    {
        return m_pitch_class;
    }

    int Pitch::GetOctave() const
    {
        return m_octave;
    }

    bool Pitch::operator==(const Pitch &other) const
    {
        return m_pitch_class == other.m_pitch_class &&
                m_octave == other.m_octave;
    }

    bool Pitch::operator!=(const Pitch &other) const
    {
        return !(*this == other);
    }
}

namespace as4::model::pitch
{
    namespace // unexposed inner helper functions
    {
        // An ordered list of pitch class c_strings
        const char *pitch_class_strs[] = {
            "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
        // An ordered list of pitch class alphabet characters
        const char pitch_class_alphabets[] = {
            'C', 'D', 'E', 'F', 'G', 'A', 'B'};

        // Converts pitch class string to pitch class index
        int string_to_index(const std::string &code)
        {
            return std::distance(
                std::begin(pitch_class_strs), 
                std::find_if(
                    std::begin(pitch_class_strs), 
                    std::end(pitch_class_strs), 
                    [&code](const char *str) { 
                        return 0 == 
                        std::strncmp(code.c_str(), str, code.size()); }));
        }
    }

    Pitch StandardPitchStringfier::FromString(const std::string &code)
    {
        // A wrapper around std::digit. We do this because 
        // std::isdigit has type int->int
        const auto is_digit = [](char c) -> bool {
            return std::isdigit(c);
        };

        // input sanity check
        AS4_REQUIRE(2 <= code.size());
        AS4_REQUIRE(
                std::end(pitch_class_alphabets) != 
                std::find(std::begin(pitch_class_alphabets), 
                std::end(pitch_class_alphabets), 
                code[0]));

        const auto sharp_exists = '#' == code[1];

        AS4_REQUIRE(sharp_exists || 1 < code.size());
        AS4_REQUIRE((!sharp_exists) || 2 < code.size());
        AS4_REQUIRE(sharp_exists || 
                std::all_of(code.begin()+1, code.end(), is_digit));
        AS4_REQUIRE((!sharp_exists) || 
                std::all_of(code.begin()+2, code.end(), is_digit));

        const auto pitch_class_string = 
            sharp_exists ? code.substr(0,2) : code.substr(0,1);
        const auto octave_string = 
            sharp_exists ? code.substr(2) : code.substr(1);

        const auto pitch_class = string_to_index(pitch_class_string);
        const auto octave = std::stoi(octave_string);

        return Pitch(pitch_class, octave);
    }

    std::string StandardPitchStringfier::ToString(const Pitch &pitch)
    {
        const auto pitch_class = pitch.GetPitchClass();
        AS4_REQUIRE(0 <= pitch_class && 
                static_cast<int>(sizeof(pitch_class_strs)) > pitch_class);

        const auto octave = pitch.GetOctave();

        return std::string(pitch_class_strs[pitch_class]) + 
        std::to_string(octave);
    }
}

