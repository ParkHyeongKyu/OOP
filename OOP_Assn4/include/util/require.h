#ifndef __AS4_UTIL_REQUIRE_H
#define __AS4_UTIL_REQUIRE_H

/**
 * Convenience macros for error checking
 */
#define AS4_REQUIRE(__p__) as4::util::_require(__p__, #__p__, __FILE__, __LINE__)

namespace as4::util
{
    /**
     * If val is false, throws a std::runtime_exception
     */
    void _require(bool val, std::string cand, std::string file, int line);
}

#endif
