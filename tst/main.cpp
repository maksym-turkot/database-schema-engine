/**
 * Runs the googletest suite. IDE may indicate errors, please ignore them.
 * Software is compiled using CMake and runs correctly in the Terminal.
 * 
 * @author  Maksym Turkot
 * @version 11/06/2022
 */

#include "gtest/gtest.h"

/**
 * Runs the googletest suite.
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}