#include "binary_signal.h"
#include "gtest/gtest.h"

/********************************************
Run with g++ -o test *.cpp -lgtest -lpthread
*********************************************/

TEST(Constructor, Input) {
	Binary_Signal::Binary_Signal a;
	EXPECT_EQ(a.GetSizeNow(), 0);
	Binary_Signal::Binary_Signal b(1, 49, 167);
	EXPECT_EQ(b.GetSizeNow(), 167);
	Binary_Signal::Binary_Signal c("1502140417");
	EXPECT_EQ(c.GetSizeNow(), 5);
	try {
		Binary_Signal::Binary_Signal test1("vgqhbwnj325");
	} catch (std::invalid_argument) {
		std::cout << "Bad string" << std::endl;
	}
    Binary_Signal::Binary_Signal test2;
	EXPECT_THROW(test2.SetSignal("45r6tgyhuijokfh9238hg9tgegv9w9e"), std::invalid_argument);
}

TEST(Setters, Input) {
	Binary_Signal::Binary_Signal a("140315031407");
	EXPECT_EQ(a.GetSizeNow(), 6);
	EXPECT_EQ(a.GetFullSignalDuration(), 26);
	/*****************************/
	//SetSignal (const char* signal)
	/*****************************/
	Binary_Signal::Binary_Signal test2;
	EXPECT_THROW(test2.SetSignal("45r6tgyhuijokfh9238hg9tgegv9w9e"), std::invalid_argument);
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
	Binary_Signal::Binary_Signal t_set("140312");
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
    c = ~a;
    EXPECT_EQ(c, a);
}

TEST(OtherFunctions, Input) {
	Binary_Signal::Binary_Signal a("12180305");
	a.FreeClass();
	EXPECT_EQ(a.GetSizeNow(), 0);
	a.SetSignal("12180305");
	a.DeleteSignal(3, 56);
	Binary_Signal::Binary_Signal b("120305");
	EXPECT_EQ(a, b);
    Binary_Signal::Binary_Signal c(a, 2);
    Binary_Signal::Binary_Signal d(b, 3);
    c.SignalAddition(d);
    EXPECT_EQ(2*a + 3*b, c);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}