#include "pch.h"

// Include headers from Bulls trainer 2023
#include "../src/maths_functions.h"

using namespace cpv;

//////////////////////////////////
// 
// Test the reciprocate function
//
///////////////////////////////////

TEST(MathsFunction, reciprocate_heading_case_1) {
    EXPECT_EQ(reciprocate_heading(90), 270);
}

TEST(MathsFunction, reciprocate_heading_case_2) {
    EXPECT_EQ(reciprocate_heading(0), 180);
}

TEST(MathsFunction, reciprocate_heading_case_3) {
    EXPECT_EQ(reciprocate_heading(10), 190);
}

TEST(MathsFunction, reciprocate_heading_case_4) {
    EXPECT_EQ(reciprocate_heading(180), 0);
}

TEST(MathsFunction, reciprocate_heading_case_5) {
    EXPECT_EQ(reciprocate_heading(270), 90);
}

TEST(MathsFunction, reciprocate_heading_case_6) {
    EXPECT_EQ(reciprocate_heading(225), 45);
}

// Test for accidental use of a floating number
TEST(MathsFunction, reciprocate_heading_case_7) {
    EXPECT_EQ(reciprocate_heading(137.8), 317);
}


//////////////////////////////////////////////////
// 
// Test the pixels_between_point_a_and_b function
// 
// https://www.omnicalculator.com/math/pythagorean-theorem 
//
//////////////////////////////////////////////////


// The aircraft from which most measurements will be made is positioned at screen coordinates 363,667 so use this
// as the first co-ordinate in initial tests. 

TEST(MathsFunction, pixels_between_point_a_and_b_case_5) {
    EXPECT_DOUBLE_EQ(pixels_between_point_a_and_b(Coordinate(363, 667), Coordinate(363, 667)), 0.0);
}

TEST(MathsFunction, pixels_between_point_a_and_b_case_1) {
    EXPECT_DOUBLE_EQ(pixels_between_point_a_and_b(Coordinate(363, 667), Coordinate(363, 567)), 100.0);
}

TEST(MathsFunction, pixels_between_point_a_and_b_case_2) {
    EXPECT_DOUBLE_EQ(pixels_between_point_a_and_b(Coordinate(363, 667), Coordinate(463, 667)), 100.0);
}

TEST(MathsFunction, pixels_between_point_a_and_b_case_3) {
    EXPECT_DOUBLE_EQ(pixels_between_point_a_and_b(Coordinate(363, 667), Coordinate(363, 767)), 100.0);
}

TEST(MathsFunction, pixels_between_point_a_and_b_case_4) {
    EXPECT_DOUBLE_EQ(pixels_between_point_a_and_b(Coordinate(363, 667), Coordinate(263, 667)), 100.0);
}


// Use float check as there are too many digits for a double comparison and it doesn't need to be that accurate
TEST(MathsFunction, pixels_between_point_a_and_b_case_6) {
    EXPECT_FLOAT_EQ(pixels_between_point_a_and_b(Coordinate(363, 667), Coordinate(463, 567)), 141.4214);
}

TEST(MathsFunction, pixels_between_point_a_and_b_case_7) {
    EXPECT_FLOAT_EQ(pixels_between_point_a_and_b(Coordinate(363, 667), Coordinate(463, 767)), 141.4214);
}

TEST(MathsFunction, pixels_between_point_a_and_b_case_8) {
    EXPECT_FLOAT_EQ(pixels_between_point_a_and_b(Coordinate(363, 667), Coordinate(263, 767)), 141.4214);
}

TEST(MathsFunction, pixels_between_point_a_and_b_case_9) {
    EXPECT_FLOAT_EQ(pixels_between_point_a_and_b(Coordinate(363, 667), Coordinate(263, 567)), 141.4214);
}

//////////////////////////////////////////////////
// 
// Test the angle_between_point_a_and_b function
//
// Testing the angle from the aircraft in the center of the screen to a point around it
// 
//////////////////////////////////////////////////


// The aircraft from which most measurements will be made is positioned at screen coordinates 363,667 so use this
// as the first co-ordinate in initial tests. 


// First test the cardinal points
TEST(MathsFunction, angle_between_point_a_and_b_case_1) {
    EXPECT_EQ(angle_between_point_a_and_b(Coordinate(363, 667), Coordinate(363, 567)), 0);
}

TEST(MathsFunction, angle_between_point_a_and_b_case_2) {
    EXPECT_EQ(angle_between_point_a_and_b(Coordinate(363, 667), Coordinate(463, 667)), 90);
}

TEST(MathsFunction, angle_between_point_a_and_b_case_3) {
    EXPECT_EQ(angle_between_point_a_and_b(Coordinate(363, 667), Coordinate(363, 767)), 180);
}

TEST(MathsFunction, angle_between_point_a_and_b_case_4) {
    EXPECT_EQ(angle_between_point_a_and_b(Coordinate(363, 667), Coordinate(263,667)), 270);
}

// Second test between the cardinal points
TEST(MathsFunction, angle_between_point_a_and_b_case_5) {
    EXPECT_EQ(angle_between_point_a_and_b(Coordinate(363, 667), Coordinate(463, 567)), 45);
}

TEST(MathsFunction, angle_between_point_a_and_b_case_6) {
    EXPECT_EQ(angle_between_point_a_and_b(Coordinate(363, 667), Coordinate(463, 767)), 135);
}

TEST(MathsFunction, angle_between_point_a_and_b_case_7) {
    EXPECT_EQ(angle_between_point_a_and_b(Coordinate(363, 667), Coordinate(263, 767)), 225);
}

TEST(MathsFunction, angle_between_point_a_and_b_case_8) {
    EXPECT_EQ(angle_between_point_a_and_b(Coordinate(363, 667), Coordinate(263, 567)), 315);
}


//////////////////////////////////////////////////
// 
// Test the calc_endpoint_given_start_bearing_and_range function
// 
//////////////////////////////////////////////////


// The aircraft from which most measurements will be made is positioned at screen coordinates 363,667 so use this
// as the first co-ordinate in initial tests. 

TEST(MathsFunction, calc_endpoint_given_start_bearing_and_range_case_1) {
//    EXPECT_EQ(calc_endpoint_given_start_bearing_and_range(Coordinate(363, 667), 0, 0, 30, 0.5), Coordinate(363, 667));
}