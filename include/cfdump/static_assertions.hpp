#ifndef CFDUMP_STATIC_ASSERTIONS_HPP
#define CFDUMP_STATIC_ASSERTIONS_HPP

#include<limits>

static_assert(std::numeric_limits<float>::is_iec559);
static_assert(std::numeric_limits<double>::is_iec559);

#endif