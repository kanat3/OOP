#include "binary_signal.h"
#include "gtest/gtest.h"

/********************************************
Run with g++ -o test *.cpp -lgtest -lpthread
*********************************************/

TEST(Constructor, PositiveInput) {
	Binary_Signal::Binary_Signal a;
	EXPECT_EQ(a.GetSizeNow(), 0);
	Binary_Signal::Binary_Signal b(1);
	EXPECT_EQ(b.GetSizeNow(), Binary_Signal::SIZE);
	Binary_Signal::Binary_Signal c("1502140417");
	EXPECT_EQ(c.GetSizeNow(), 5);
}


TEST(Setters, Input) {
	Binary_Signal::Binary_Signal a("140315031407");
	EXPECT_EQ(a.GetSizeNow(), 6);
	EXPECT_EQ(a.GetFullSignalDuration(), 26);
	/*****************************/
	//SetSignal (const char* signal)
	/*****************************/
	Binary_Signal::Binary_Signal b;
	b.SetSignal("1202");
	Binary_Signal::Binary_Signal c("1202");
	EXPECT_EQ(b, c);
	/*****************************/
	//SetSignal (const int bin_level = 0, const char signal_duration = 49)
	/*****************************/
	Binary_Signal::Binary_Signal d;
	d.SetSignal(1, 50);
	Binary_Signal::Binary_Signal r("12");
	EXPECT_EQ(d, r);
	/*****************************/
	//SetSignalInTime (const int time, const Binary_Signal& to_add)
	/*****************************/
	a.SetSignalInTime(6, d);
	Binary_Signal::Binary_Signal t_set("1412");
	EXPECT_EQ(a, t_set);
}

TEST(Inversion, Input) {
	Binary_Signal::Binary_Signal a("14150307190216");
	Binary_Signal::Binary_Signal b("04051317091206");
	a.SignalInversion();
	EXPECT_EQ(a, b);
}

TEST(Overloads, Input) {
	Binary_Signal::Binary_Signal a("12031405");
	Binary_Signal::Binary_Signal b("1204");
	Binary_Signal::Binary_Signal c;
	Binary_Signal::Binary_Signal d("120314051204");
	c = a;
	EXPECT_EQ(c, a);
	c = a + b;
	EXPECT_EQ(c, d);
}

TEST(OtherFunctions, Input) {
	Binary_Signal::Binary_Signal a("12180305");
	a.FreeClass();
	EXPECT_EQ(a.GetSizeNow(), 0);
	a.SetSignal("12180305");
	a.DeleteSignal(3, 56);
	Binary_Signal::Binary_Signal b("120305");
	EXPECT_EQ(a, b);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}