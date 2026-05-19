#include <gtest/gtest.h>
#include <cblas.h>
#include <vector>
#include <cmath>
#include "test_utils.h"

class CBlasLevel1FloatTest : public ::testing::Test {
protected:
    void SetUp() override {
        x = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        y = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
        n = static_cast<int>(x.size());
    }

    std::vector<float> x, y;
    int n;
};


TEST_F(CBlasLevel1FloatTest, SaxpyBasic) {
    float alpha = 2.0f;
    std::vector<float> expected = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    
    cblas_saxpy(n, alpha, x.data(), 1, y.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(y, expected));
}

TEST_F(CBlasLevel1FloatTest, SaxpyZeroAlpha) {
    float alpha = 0.0f;
    std::vector<float> expected = y;
    cblas_saxpy(n, alpha, x.data(), 1, y.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(y, expected));
}

TEST_F(CBlasLevel1FloatTest, SaxpyNegativeAlpha) {
    float alpha = -1.0f;
    std::vector<float> expected = {4.0f, 2.0f, 0.0f, -2.0f, -4.0f};
    
    cblas_saxpy(n, alpha, x.data(), 1, y.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(y, expected));
}

TEST_F(CBlasLevel1FloatTest, SaxpyWithIncrement) {
    std::vector<float> x_extended = {1.0f, 99.0f, 2.0f, 99.0f, 3.0f};
    std::vector<float> y_test = {1.0f, 2.0f, 3.0f};
    float alpha = 1.0f;
    std::vector<float> expected = {2.0f, 4.0f, 6.0f};
    
    cblas_saxpy(3, alpha, x_extended.data(), 2, y_test.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(y_test, expected));
}


TEST_F(CBlasLevel1FloatTest, SdotBasic) {
    float result = cblas_sdot(n, x.data(), 1, y.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 35.0f));
}

TEST_F(CBlasLevel1FloatTest, SdotZeroVector) {
    std::vector<float> zeros(n, 0.0f);
    float result = cblas_sdot(n, x.data(), 1, zeros.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 0.0f));
}

TEST_F(CBlasLevel1FloatTest, SdotWithIncrement) {
    std::vector<float> x_extended = {1.0f, 99.0f, 2.0f, 99.0f, 3.0f};
    std::vector<float> y_test = {1.0f, 2.0f, 3.0f};
    
    float result = cblas_sdot(3, x_extended.data(), 2, y_test.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 14.0f));
}


TEST_F(CBlasLevel1FloatTest, Snrm2Basic) {
    float result = cblas_snrm2(n, x.data(), 1);
    float expected = std::sqrt(55.0f);
    
    EXPECT_TRUE(almost_equal(result, expected));
}

TEST_F(CBlasLevel1FloatTest, Snrm2ZeroVector) {
    std::vector<float> zeros(n, 0.0f);
    float result = cblas_snrm2(n, zeros.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 0.0f));
}

TEST_F(CBlasLevel1FloatTest, Snrm2UnitVector) {
    std::vector<float> unit = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float result = cblas_snrm2(static_cast<int>(unit.size()), unit.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 1.0f));
}


TEST_F(CBlasLevel1FloatTest, ScopyBasic) {
    std::vector<float> dest(n);
    
    cblas_scopy(n, x.data(), 1, dest.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(dest, x));
}

TEST_F(CBlasLevel1FloatTest, ScopyWithIncrement) {
    std::vector<float> x_extended = {1.0f, 99.0f, 2.0f, 99.0f, 3.0f};
    std::vector<float> dest(3);
    std::vector<float> expected = {1.0f, 2.0f, 3.0f};
    
    cblas_scopy(3, x_extended.data(), 2, dest.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(dest, expected));
}


TEST_F(CBlasLevel1FloatTest, SscalBasic) {
    float alpha = 2.0f;
    std::vector<float> expected = {2.0f, 4.0f, 6.0f, 8.0f, 10.0f};
    
    cblas_sscal(n, alpha, x.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(x, expected));
}

TEST_F(CBlasLevel1FloatTest, SscalZeroAlpha) {
    float alpha = 0.0f;
    std::vector<float> expected(n, 0.0f);
    
    cblas_sscal(n, alpha, x.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(x, expected));
}

TEST_F(CBlasLevel1FloatTest, SscalNegativeAlpha) {
    float alpha = -1.0f;
    std::vector<float> expected = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f};
    
    cblas_sscal(n, alpha, x.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(x, expected));
}


TEST_F(CBlasLevel1FloatTest, SasumBasic) {
    float result = cblas_sasum(n, x.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 15.0f));
}

TEST_F(CBlasLevel1FloatTest, SasumNegativeValues) {
    std::vector<float> neg = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f};
    float result = cblas_sasum(n, neg.data(), 1);
    
    EXPECT_TRUE(almost_equal(result, 15.0f));
}


TEST_F(CBlasLevel1FloatTest, IsamaxBasic) {
    CBLAS_INDEX result = cblas_isamax(n, x.data(), 1);
    
    EXPECT_EQ(result, 4);
}

TEST_F(CBlasLevel1FloatTest, IsamaxNegativeValues) {
    std::vector<float> mixed = {1.0f, -10.0f, 3.0f, 4.0f, 5.0f};
    CBLAS_INDEX result = cblas_isamax(static_cast<int>(mixed.size()), mixed.data(), 1);
    
    EXPECT_EQ(result, 1);
}


TEST_F(CBlasLevel1FloatTest, SswapBasic) {
    std::vector<float> x_orig = x;
    std::vector<float> y_orig = y;
    
    cblas_sswap(n, x.data(), 1, y.data(), 1);
    
    EXPECT_TRUE(vectors_almost_equal(x, y_orig));
    EXPECT_TRUE(vectors_almost_equal(y, x_orig));
}
