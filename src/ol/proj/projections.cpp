/*
 * Copyright (C) 2018
 * All rights reserved.
 *
 */

#include "projections.h"

using namespace ol::proj;

std::map<std::string, ProjectionP> 
projections::cache;

void projections::clear()
{
    cache.clear();
}

ProjectionP projections::get(std::string const &code)
{
    return cache[code];
}

void projections::add(std::string const &code, ProjectionP projection)
{
    cache[code] = projection;
}
