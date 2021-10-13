#include "Lemniscata.h"
#include "gtest/gtest.h"

using namespace Lemniscata_Bernoulli;

TEST(Constructor, PositiveInput) {
	Lemniscata a;
	EXPECT_EQ(a.GetDistance(), 80);
	Lemniscata b(66);
	EXPECT_EQ(b.GetDistance(), 66);
	Lemniscata e(3.45678);
	EXPECT_EQ(e.GetDistance(), 3.45678);
	Lemniscata r(24345.7);
	EXPECT_EQ(r.GetDistance(), 24345.7);
}

TEST(Constructor, NegativeInput) {
	EXPECT_ANY_THROW(Lemniscata a(-5));
	EXPECT_ANY_THROW(Lemniscata b(0));
	EXPECT_ANY_THROW(Lemniscata c(-35.4747));
}

TEST(Distance_Setter, PositiveInput) {
	Lemniscata a;
	a.SetDistance(3.4656);
	EXPECT_EQ(a.GetDistance(), 3.4656);
	a.SetDistance(463737);
	EXPECT_EQ(a.GetDistance(), 463737);
	a.SetDistance(0.45678);
	EXPECT_EQ(a.GetDistance(), 0.45678);
	a.SetDistance(3111);
	EXPECT_EQ(a.GetDistance(), 3111);
	a.SetDistance(99999.0);
	EXPECT_EQ(a.GetDistance(), 99999.0);
	a.SetDistance(3);
	EXPECT_EQ(a.GetDistance(), 3);
}

TEST(Distance_Setter, NegativeInput) {
	Lemniscata a;
	EXPECT_ANY_THROW(a.SetDistance(-3.4656));
	EXPECT_ANY_THROW(a.SetDistance(0));
	EXPECT_ANY_THROW(a.SetDistance(-345678));
	EXPECT_ANY_THROW(a.SetDistance(-357.23456));
}

TEST(DistanceToTheCenter, Input) {
	Lemniscata a;
	a.SetDistance(160);
	EXPECT_EQ(a.DistanceToTheCenter(0), 226.2741699796952162);
	a.SetDistance(20);
	EXPECT_EQ(a.DistanceToTheCenter(0), 28.2842712474619020);
	a.SetDistance(5);
	EXPECT_EQ(a.DistanceToTheCenter(0), 7.0710678118654755);
}

TEST(RadiusOfCurvature_ByAngle, Input) {
	Lemniscata a(59);
	Lemniscata b(180);
	Lemniscata c(30);
	double abs_error = 0.001;
	EXPECT_NEAR(a.RadiusOfCurvature_ByAngle(0), 27.8129, abs_error);
	EXPECT_NEAR(b.RadiusOfCurvature_ByAngle(20), 427.865, abs_error);
	EXPECT_NEAR(c.RadiusOfCurvature_ByAngle(46), 14.6775, abs_error);
}

TEST(RadiusOfCurvature_ByLength, Input) {
	Lemniscata a;
	double abs_error = 0.001;
	EXPECT_NEAR(a.RadiusOfCurvature_ByLength(100), 42.6666, abs_error);
	EXPECT_NEAR(a.RadiusOfCurvature_ByLength(40), 106.6666, abs_error);
	EXPECT_NEAR(a.RadiusOfCurvature_ByLength(17), 250.9803,abs_error);
}

TEST(RadiusOfCurvature_ByLength, ErrorInput) {
	Lemniscata a;
	EXPECT_ANY_THROW(a.RadiusOfCurvature_ByLength(999));
	EXPECT_ANY_THROW(a.RadiusOfCurvature_ByLength(-35.236));
	EXPECT_ANY_THROW(a.RadiusOfCurvature_ByLength(-0));
}

TEST(AreaOfTheSector, Input) {
	Lemniscata a;
	double abs_error = 0.01;
	EXPECT_NEAR(a.AreaOfTheSector(10), 2217.8, abs_error);
	EXPECT_NEAR(a.AreaOfTheSector(69), 1729.88, abs_error);
}

TEST(Area, Input) {
	Lemniscata a(50);
	EXPECT_EQ(a.Area(), 5000);
	Lemniscata b(160);
	EXPECT_EQ(b.Area(), 51200);
	Lemniscata c(70);
	EXPECT_EQ(c.Area(), 9800);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}