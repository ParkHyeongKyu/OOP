#include <stdexcept>

#include "util/require.h"

namespace as4::util
{
    void _require(bool val, std::string cand, std::string file, int line)
    {
        if(!val)
        {
            throw std::runtime_error(
                    std::string() + "Requirement is not met : " +
                    "AS4_REQUIRE(" + cand + ") " + "in " + 
                    file + ":" + std::to_string(line));
        }
    }
}
