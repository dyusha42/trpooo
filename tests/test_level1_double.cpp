#include <gtest/gtest.h>
#include <cblas.h>
#include <vector>
#include <cmath>
#include "test_utils.h"

class CBlasLevel1DoubleTest : public ::testing::Test {
protected:
    void SetUp() override {
        x = {1.0, 2.0, 3.0, 4.0, 5.0};
        y = {5.0, 4.0, 3.0, 2.0, 1.0};
        n = static_cast<int>(x.size());
    }

    std::vector<double> x, y;
    int n;
};


TEST_F(CBlasLevel1DoubleTest, DaxpyBasic) {
    double alpha = 2.0;
    std::vector<double> expected = {7.0, 8.0, 9.0, 10.0, 11.0};
    
    cblas_daxpy(n, alpha, x.data(), 1, y.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(y, expected));
}

TEST_F(CBlasLevel1DoubleTest, DaxpyZeroAlpha) {
    double alpha = 0.0;
    std::vector<double> expected = y;
    
    cblas_daxpy(n, alpha, x.data(), 1, y.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(y, expected));
}

TEST_F(CBlasLevel1DoubleTest, DaxpyNegativeAlpha) {
    double alpha = -1.0;
    std::vector<double> expected = {4.0, 2.0, 0.0, -2.0, -4.0};
    
    cblas_daxpy(n, alpha, x.data(), 1, y.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(y, expected));
}

TEST_F(CBlasLevel1DoubleTest, DaxpyWithIncrement) {
    std::vector<double> x_extended = {1.0, 99.0, 2.0, 99.0, 3.0};
    std::vector<double> y_test = {1.0, 2.0, 3.0};
    double alpha = 1.0;
    std::vector<double> expected = {2.0, 4.0, 6.0};
    
    cblas_daxpy(3, alpha, x_extended.data(), 2, y_test.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(y_test, expected));
}


TEST_F(CBlasLevel1DoubleTest, DdotBasic) {
    double result = cblas_ddot(n, x.data(), 1, y.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 35.0));
}

TEST_F(CBlasLevel1DoubleTest, DdotZeroVector) {
    std::vector<double> zeros(n, 0.0);
    double result = cblas_ddot(n, x.data(), 1, zeros.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 0.0));
}

TEST_F(CBlasLevel1DoubleTest, DdotOrthogonalVectors) {
    std::vector<double> x_test = {1.0, 0.0, 0.0};
    std::vector<double> y_test = {0.0, 1.0, 0.0};
    
    double result = cblas_ddot(3, x_test.data(), 1, y_test.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 0.0));
}


TEST_F(CBlasLevel1DoubleTest, Dnrm2Basic) {
    double result = cblas_dnrm2(n, x.data(), 1);
    double expected = std::sqrt(55.0);
    
    EXPECT_TRUE(almost_equal(result, expected));
}

TEST_F(CBlasLevel1DoubleTest, Dnrm2ZeroVector) {
    std::vector<double> zeros(n, 0.0);
    double result = cblas_dnrm2(n, zeros.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 0.0));
}

TEST_F(CBlasLevel1DoubleTest, Dnrm2UnitVector) {
    std::vector<double> unit = {1.0, 0.0, 0.0, 0.0, 0.0};
    double result = cblas_dnrm2(static_cast<int>(unit.size()), unit.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 1.0));
}


TEST_F(CBlasLevel1DoubleTest, DcopyBasic) {
    std::vector<double> dest(n);
    
    cblas_dcopy(n, x.data(), 1, dest.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(dest, x));
}

TEST_F(CBlasLevel1DoubleTest, DcopyWithIncrement) {
    std::vector<double> x_extended = {1.0, 99.0, 2.0, 99.0, 3.0};
    std::vector<double> dest(3);
    std::vector<double> expected = {1.0, 2.0, 3.0};
    
    cblas_dcopy(3, x_extended.data(), 2, dest.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(dest, expected));
}


TEST_F(CBlasLevel1DoubleTest, DscalBasic) {
    double alpha = 2.0;
    std::vector<double> expected = {2.0, 4.0, 6.0, 8.0, 10.0};
    
    cblas_dscal(n, alpha, x.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(x, expected));
}

TEST_F(CBlasLevel1DoubleTest, DscalZeroAlpha) {
    double alpha = 0.0;
    std::vector<double> expected(n, 0.0);
    
    cblas_dscal(n, alpha, x.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(x, expected));
}

TEST_F(CBlasLevel1DoubleTest, DscalFractionalAlpha) {
    double alpha = 0.5;
    std::vector<double> expected = {0.5, 1.0, 1.5, 2.0, 2.5};
    
    cblas_dscal(n, alpha, x.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(x, expected));
}


TEST_F(CBlasLevel1DoubleTest, DasumBasic) {
    double result = cblas_dasum(n, x.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 15.0));
}

TEST_F(CBlasLevel1DoubleTest, DasumMixedValues) {
    std::vector<double> mixed = {-1.0, 2.0, -3.0, 4.0, -5.0};
    double result = cblas_dasum(static_cast<int>(mixed.size()), mixed.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 15.0));
}


TEST_F(CBlasLevel1DoubleTest, IdamaxBasic) {
    CBLAS_INDEX result = cblas_idamax(n, x.data(), 1);
    
    EXPECT_EQ(result, 4);
}

TEST_F(CBlasLevel1DoubleTest, IdamaxNegativeValues) {
    std::vector<double> mixed = {1.0, -10.0, 3.0, 4.0, 5.0};
    CBLAS_INDEX result = cblas_idamax(static_cast<int>(mixed.size()), mixed.data(), 1);
    
    EXPECT_EQ(result, 1);
}

TEST_F(CBlasLevel1DoubleTest, IdamaxFirstElement) {
    std::vector<double> test = {10.0, 1.0, 2.0, 3.0};
    CBLAS_INDEX result = cblas_idamax(static_cast<int>(test.size()), test.data(), 1);
    
    EXPECT_EQ(result, 0);
}


TEST_F(CBlasLevel1DoubleTest, DswapBasic) {
    std::vector<double> x_orig = x;
    std::vector<double> y_orig = y;
    
    cblas_dswap(n, x.data(), 1, y.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(x, y_orig));
    EXPECT_TRUE(vectors_almost_equal(y, x_orig));
}


TEST_F(CBlasLevel1DoubleTest, DrotgBasic) {
    double a = 3.0;
    double b = 4.0;
    double c, s;
    
    cblas_drotg(&a, &b, &c, &s);
    
    EXPECT_TRUE(almost_equal(a, 5.0));
    EXPECT_TRUE(almost_equal(c*c + s*s, 1.0));
}


TEST_F(CBlasLevel1DoubleTest, DrotBasic) {
    std::vector<double> x_test = {1.0, 2.0, 3.0};
    std::vector<double> y_test = {4.0, 5.0, 6.0};
    double c = 1.0;
    double s = 0.0;
    
    std::vector<double> x_expected = x_test;
    std::vector<double> y_expected = y_test;
    
    cblas_drot(3, x_test.data(), 1, y_test.data(), 1, c, s);
    
    EXPECT_TRUE(vectors_almost_equal(x_test, x_expected));
    EXPECT_TRUE(vectors_almost_equal(y_test, y_expected));
}
