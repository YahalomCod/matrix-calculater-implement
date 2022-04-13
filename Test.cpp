#include "doctest.h"
#include "sources/Matrix.hpp"
#include "doctest.h"
using namespace zich;

#include <string>
#include <algorithm>
using namespace std;

vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
vector<double> zero = {0, 0, 0, 0, 0, 0, 0, 0, 0};
vector<double> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
vector<double> arr2 = {1.1, 2.2, 3.3};
vector<double> arr3 = {2.2, 4.4, 6.6};
Matrix I{identity, 3, 3};
Matrix Z{zero, 3, 3};
Matrix mat1{arr1, 3, 3};
Matrix mat2{arr2, 3, 1};
Matrix mat3{arr3, 3, 1};

TEST_CASE("Good input")
{
    CHECK_EQ(mat1 * I == mat1,true);
    CHECK_EQ(mat1 * Z == Z,true);
    CHECK_EQ(Z * I == Z,true);
    CHECK_EQ(I * mat2 == mat2,true);
    CHECK_EQ(mat1 * I == mat1,true);
    CHECK_EQ(mat1 + Z == mat1,true);
    CHECK_EQ(Z - mat1 == -mat1,true);
    CHECK_EQ(mat1 < mat1 * mat1,true);
    CHECK_EQ(mat2 + 1 == ++mat2,true);
    CHECK_EQ(mat2 * 2 == mat3, true);
    CHECK_EQ(mat1 * 0 == Z, true);
    CHECK_NE(mat2 != mat2,true);
    CHECK_NE(Z > I,true);
}

TEST_CASE("Bad input")
{
    CHECK_THROWS(mat1 * mat2);
    CHECK_THROWS(mat1 + mat2);
    CHECK_THROWS(mat1 - mat2);
    CHECK_THROWS(bool check = mat1 > mat2);
    CHECK_THROWS(bool check = mat1 >= mat2);
    CHECK_THROWS(bool check = mat1 < mat2);
    CHECK_THROWS(bool check = mat1 <= mat2);
    CHECK_THROWS(bool check = mat1 != mat2);
    CHECK_THROWS(bool check = mat1 == mat2);

}