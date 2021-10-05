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
	Lemniscata q(325, 90);
	EXPECT_EQ(q.GetDistance(), 325);
	EXPECT_EQ(q.GetRadAngle(), 90);
	Lemniscata t(2345.436, 180);
	EXPECT_EQ(t.GetRadAngle(), 180);
	EXPECT_EQ(t.GetDistance(), 2345.436);
	Lemniscata v(2, 0);
	EXPECT_EQ(v.GetRadAngle(), 0);
	EXPECT_EQ(v.GetDistance(), 2);
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

TEST(Angle_Setter, PositiveInput) {
	Lemniscata a;
	a.SetAngle(90);
	EXPECT_EQ(a.GetRadAngle(), 90);
	a.SetAngle(0);
	EXPECT_EQ(a.GetRadAngle(), 0);
	a.SetAngle(180);
	EXPECT_EQ(a.GetRadAngle(), 180);
}

TEST(Angle_Setter, NegativeInput) {
	Lemniscata a;
	a.SetAngle(-90);
	EXPECT_EQ(a.GetRadAngle(), -90);
	a.SetAngle(-0);
	EXPECT_EQ(a.GetRadAngle(), -0);
	a.SetAngle(-180);
	EXPECT_EQ(a.GetRadAngle(), -180);
}

TEST(DistanceToTheCenter, Input) {
	Lemniscata a;
	a.SetDistance(160);
	EXPECT_EQ(a.DistanceToTheCenter(a.GetAngle()), 226.2741699796952162);
	a.SetDistance(20);
	EXPECT_EQ(a.DistanceToTheCenter(a.GetAngle()), 28.2842712474619020);
	a.SetDistance(5);
	EXPECT_EQ(a.DistanceToTheCenter(a.GetAngle()), 7.0710678118654755);
}

TEST(RadiusOfCurvature_ByAngle, Input) {
	Lemniscata a(59, 10);
	Lemniscata b(180, 179);
	Lemniscata c(30, 360);
	EXPECT_EQ(a.RadiusOfCurvature_ByAngle(a.GetAngle()), 28.69147308866308066);
	EXPECT_EQ(b.RadiusOfCurvature_ByAngle(b.GetAngle()), 84.87867057719222430);
	EXPECT_EQ(c.RadiusOfCurvature_ByAngle(c.GetAngle()), 14.14213562373094923);
}

TEST(RadiusOfCurvature_ByLength, Input) {
	Lemniscata a;
	EXPECT_EQ(a.RadiusOfCurvature_ByLength(100), 42.66666666666666430);
	EXPECT_EQ(a.RadiusOfCurvature_ByLength(40), 106.66666666666667140);
	EXPECT_EQ(a.RadiusOfCurvature_ByLength(17), 250.98039215686273451);
}

TEST(RadiusOfCurvature_ByLength, ErrorInput) {
	Lemniscata a;
	EXPECT_ANY_THROW(a.RadiusOfCurvature_ByLength(999));
	EXPECT_ANY_THROW(a.RadiusOfCurvature_ByLength(-35.236));
	EXPECT_ANY_THROW(a.RadiusOfCurvature_ByLength(-0));
}

TEST(AreaOfTheSector, Input) {
	Lemniscata a;
	a.SetAngle(30);
	EXPECT_EQ(a.AreaOfTheSector(a.GetAngle()), 2771.28129211020359435);
	a.SetAngle(12);
	EXPECT_EQ(a.AreaOfTheSector(a.GetAngle()), 1301.55725784256037514);
	a.SetAngle(69);
	EXPECT_EQ(a.AreaOfTheSector(a.GetAngle()), 2141.21794034834692866);
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