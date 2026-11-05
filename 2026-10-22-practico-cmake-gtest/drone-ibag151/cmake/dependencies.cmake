# Development-only dependencies.
#
# GoogleTest is fetched at configure time and cached in the build tree, so the
# solution does not depend on the professor's labs or on a system installation.
# The first configure requires network access; later builds reuse _deps/.

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

# We only need the gtest targets, not gmock.
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
