#ifndef IBAG151_TESTS_DRONE_FIXTURE_HPP
#define IBAG151_TESTS_DRONE_FIXTURE_HPP

#include <gtest/gtest.h>

#include "ibag151/drone_ibag151.hpp"

namespace ibag151::test {

/// Shared fixture: every test starts with a freshly constructed drone.
class DroneTest : public ::testing::Test {
protected:
    DroneIbag151 drone;
};

}  // namespace ibag151::test

#endif  // IBAG151_TESTS_DRONE_FIXTURE_HPP
