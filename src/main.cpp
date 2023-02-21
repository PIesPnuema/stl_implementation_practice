

/*
 *   Author:  Aaron Carroll
 *   Email:   arncarroll@gmail.com
 *   Date:    2022
 *   File:
 *
 *   Program output
 *   --------------
 *   - Contains all unitTests for Vector.h
 *   - Runs all tests for Vector.h at bottom of page inside int main() {}.
 *
 */

#include <iostream>

#include "./include/vector.h"
using namespace AaronCarroll;

#include "UnitTest++.h"
using namespace UnitTest;

#include "./include/constants.h"
using namespace VectorTestConstants;

TEST(Test1DefaultConstructor) {

    Vector<int> myVectorInt;
    CHECK_EQUAL(myVectorInt.getCapacity(), 2);
    CHECK_EQUAL(myVectorInt.getSize(), 0);

    Vector<std::string> myVectorStr;
    CHECK_EQUAL(myVectorStr.getCapacity(), 2);
    CHECK_EQUAL(myVectorStr.getSize(), 0);
}

TEST(test2allocateNSizeEmptyVector) {
    
    Vector<double> myVectorDouble(SIZE);
    CHECK_EQUAL(myVectorDouble.getCapacity(), SIZE);
    CHECK_EQUAL(myVectorDouble.getSize(), 0);
    
    //std::cout << "test2 double. Expected value = \" \": ";
    //myVectorDouble.print();
    //std::cout << "\n";
}

TEST(test3allocateNSizePlusValue) {
    
    Vector<double> myVectorDouble(SIZE, DOUBLEVALUE);
    CHECK_EQUAL(myVectorDouble.getCapacity(), SIZE);
    CHECK_EQUAL(myVectorDouble.getSize(), SIZE);
    CHECK_EQUAL(myVectorDouble[1], DOUBLEVALUE);
        
    //std::cout << "test3 double. Expected value = 3.14: ";
    //myVectorDouble.print();
    //std::cout << "\n";

    Vector<std::string> myVectorStr(SIZE, STRINGVALUE);
    CHECK_EQUAL(myVectorStr.getCapacity(), SIZE);
    CHECK_EQUAL(myVectorStr.getSize(), SIZE);
    CHECK(myVectorStr[SIZE-1].compare(STRINGVALUE) == 0);

    //std::cout << "test3 string. Expected value = \"Hello World\": ";
    //myVectorStr.print();
    //std::cout << "\n";
}

TEST(testPushBack) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    CHECK_EQUAL(myVec[0], INTVALUE);
}

TEST(testPopBack) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    myVec.pushBack(INTVALUE);
    myVec.popBack();
    CHECK_EQUAL(myVec.getSize(), 1);

    Vector<std::string> myVecStr;
    myVecStr.pushBack(STRINGVALUE);
    myVecStr.pushBack(STRINGVALUE);
    myVecStr.popBack();
    CHECK_EQUAL(myVecStr.getSize(), 1);
}

TEST(testFront) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    myVec.pushBack(INTVALUE + 2);
    myVec.pushBack(INTVALUE + 3);
    CHECK_EQUAL(myVec.front(), INTVALUE);
}

TEST(testBack) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    myVec.pushBack(INTVALUE + 2);
    myVec.pushBack(INTVALUE + 3);
    CHECK_EQUAL(myVec.back(), INTVALUE + 3);
}

TEST(testSubScript) {
    Vector<int> myVec;
    myVec.pushBack(INTVALUE);
    myVec.pushBack(INTVALUE + 2);
    myVec.pushBack(INTVALUE + 3);
    CHECK(myVec[0] == INTVALUE && myVec[1] == INTVALUE + 2 && 
            myVec[2] == INTVALUE + 3);
}
/*
TEST(test) {

}

TEST(test) {

}
TEST(test) {

}

TEST(test) {

}

*/


int main(int argc, char *argv[]) {
    
    return UnitTest::RunAllTests();
}

