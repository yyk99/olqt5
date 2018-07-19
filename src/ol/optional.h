/*
 * Copyright (C) 2018
 * All rights reserved.
 *
 */

#ifndef OL_OPTIONAL_H
#define OL_OPTIONAL_H

#include <utility>
#include <stdexcept>

namespace ol {

template <typename T>
class optional : std::pair<T, bool> {
public:
    typedef std::pair<T, bool> papa_t;
    optional(T const &t) : papa_t(t, true) {};
    optional() : papa_t(T(), false) {}

    bool has_value() const { return second; }
    T const &value() const { 
        if (!has_value())
            throw std::runtime_error("bad_optional_access");
        return first; 
    }
    T &value() { 
        if (!has_value())
            throw std::runtime_error("bad_optional_access");
        return first; 
    }

    T const &value(T const &dflt) const {
        return has_value() ? first : dflt;
    }

    void reset () {
        first = T();
        second = false;
    }
};

}

#endif // OPTIONAL_H
