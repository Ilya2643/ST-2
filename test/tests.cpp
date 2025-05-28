// Copyright 2022 UNN-CS
#include <gtest/gtest.h>
#include <cstdint>
#include <cmath>
#include "../include/task.h"
#include "circle.h"

const double PI = 3.141592653589793;

TEST(CircleInitializationTest, DefaultConstructorValues) {
  Circle c(3.75);
  EXPECT_DOUBLE_EQ(c.GetRadius(), 3.75);
}

TEST(CirclePropertyTest, RadiusChangeEffects) {
  Circle c(2.25);
  c.SetRadius(6.5);
  EXPECT_DOUBLE_EQ(c.GetRadius(), 6.5);
  EXPECT_DOUBLE_EQ(c.GetFerence(), 2 * PI * 6.5);
  EXPECT_DOUBLE_EQ(c.GetArea(), PI * 6.5 * 6.5);
}

TEST(CirclePropertyTest, CircumferenceChangeEffects) {
  Circle c(1.8);
  c.SetFerence(2 * PI * 4.2);
  EXPECT_DOUBLE_EQ(c.GetRadius(), 4.2);
  EXPECT_DOUBLE_EQ(c.GetArea(), PI * 4.2 * 4.2);
}

TEST(CirclePropertyTest, AreaChangeEffects) {
  Circle c(3.0);
  c.SetArea(PI * 5.4 * 5.4);
  EXPECT_DOUBLE_EQ(c.GetRadius(), 5.4);
  EXPECT_DOUBLE_EQ(c.GetFerence(), 2 * PI * 5.4);
}

TEST(CircleEdgeCaseTest, ZeroRadiusProperties) {
  Circle c(0);
  EXPECT_DOUBLE_EQ(c.GetRadius(), 0);
  EXPECT_DOUBLE_EQ(c.GetFerence(), 0);
  EXPECT_DOUBLE_EQ(c.GetArea(), 0);
}

TEST(CircleEdgeCaseTest, LargeRadiusProperties) {
  Circle c(1.5e6);
  EXPECT_DOUBLE_EQ(c.GetFerence(), 2 * PI * 1.5e6);
  EXPECT_DOUBLE_EQ(c.GetArea(), PI * 1.5e6 * 1.5e6);
}

TEST(CirclePrecisionTest, HighPrecisionValues) {
  Circle c(1.234567);
  EXPECT_DOUBLE_EQ(c.GetRadius(), 1.234567);
  EXPECT_DOUBLE_EQ(c.GetFerence(), 2 * PI * 1.234567);
  EXPECT_DOUBLE_EQ(c.GetArea(), PI * 1.234567 * 1.234567);
}

TEST(CircleUpdateTest, MultiplePropertyUpdates) {
  Circle c(2.0);
  c.SetRadius(3.5);
  c.SetFerence(2 * PI * 4.8);
  c.SetArea(PI * 6.2 * 6.2);
  EXPECT_DOUBLE_EQ(c.GetRadius(), 6.2);
  EXPECT_DOUBLE_EQ(c.GetFerence(), 2 * PI * 6.2);
  EXPECT_DOUBLE_EQ(c.GetArea(), PI * 6.2 * 6.2);
}

TEST(EarthRopeTest, SmallLengthIncrease) {
  double gap = CalculateRopeGap(6375.0 * 1000, 2.0);
  EXPECT_NEAR(gap, 2.0 / (2 * PI), 1e-6);
}

TEST(EarthRopeTest, NoLengthIncrease) {
  double gap = CalculateRopeGap(6375.0 * 1000, 0);
  EXPECT_DOUBLE_EQ(gap, 0);
}

TEST(EarthRopeTest, LargeLengthIncrease) {
  double gap = CalculateRopeGap(6375.0 * 1000, 5000);
  EXPECT_NEAR(gap, 5000 / (2 * PI), 1e-6);
}

TEST(EarthRopeTest, ExactCircumferenceIncrease) {
  double gap = CalculateRopeGap(6375.0 * 1000, 2 * PI * 15);
  EXPECT_NEAR(gap, 15, 1e-6);
}

TEST(PoolCostTest, StandardPoolConfiguration) {
  double cost = CalculatePoolCost(3.5, 1.25, 1200, 2200);
  double expCost = (PI * (4.75 * 4.75 - 3.5 * 3.5) * 1200) + (2 * PI * 4.75 * 2200);
  EXPECT_NEAR(cost, expCost, 1e-6);
}

TEST(PoolCostTest, NoPathConfiguration) {
  double cost = CalculatePoolCost(2.8, 0, 1500, 2400);
  double expectedCost = 2 * PI * 2.8 * 2400;
  EXPECT_NEAR(cost, expectedCost, 1e-6);
}

TEST(PoolCostTest, LargePoolConfiguration) {
  double cost = CalculatePoolCost(45, 5.5, 800, 1850);
  double expCost = (PI * (50.5 * 50.5 - 45 * 45) * 800) + (2 * PI * 50.5 * 1850);
  EXPECT_NEAR(cost, expCost, 1e-6);
}

TEST(PoolCostTest, ZeroRadiusPool) {
  double cost = CalculatePoolCost(0, 2.5, 700, 1900);
  double expectedCost = (PI * 2.5 * 2.5 * 700) + (2 * PI * 2.5 * 1900);
  EXPECT_NEAR(cost, expectedCost, 1e-6);
}

TEST(PoolCostTest, MinimalPoolConfiguration) {
  double cost = CalculatePoolCost(0.8, 0.3, 300, 400);
  double r = 0.8 + 0.3;
  double expectedCost = (PI * (r * r - 0.8 * 0.8) * 300) + (2 * PI * r * 400);
  EXPECT_NEAR(cost, expectedCost, 1e-6);
}

TEST(PoolCostTest, FreeMaterialsCase) {
  double cost = CalculatePoolCost(2.0, 1.0, 0, 0);
  EXPECT_DOUBLE_EQ(cost, 0);
}

TEST(PoolCostTest, NoWaterCostCase) {
  double cost = CalculatePoolCost(3.0, 1.5, 0, 2000);
  double expectedCost = 2 * PI * (3.0 + 1.5) * 2000;
  EXPECT_NEAR(cost, expectedCost, 1e-6);
}
