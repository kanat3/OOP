#include "map.hpp"
#include "operands.hpp"
#include "file_access.hpp"
#include "assembler.hpp"
#include "gtest/gtest.h"

/********************************************
Run with g++ -o test *.cpp -lgtest -lpthread
*********************************************/

TEST (Operands, Setters_Getters) {
    Operator_Container a;
    a.SetLabel("TEST!!!");
    EXPECT_EQ(a.GetLabel(), "TEST!!!");
    a.SetLabel("HELP me");
    EXPECT_EQ(a.GetLabel(), "HELP me");
    Operator_Register b;
    b.SetLR(5);
    EXPECT_EQ(b.GetLR(), 5);
    b.SetLR(-32);
    EXPECT_EQ(b.GetLR(), -32);
    b.SetLR(3490);
    EXPECT_EQ(b.GetLR(), 3490);
    b.SetHR(5);
    EXPECT_EQ(b.GetHR(), 5);
    b.SetHR(-32);
    EXPECT_EQ(b.GetHR(), -32);
    b.SetHR(3490);
    EXPECT_EQ(b.GetHR(), 3490);
    Operator_RegisterMemory c;
    c.SetMemoryID("DATA_SEGMENT");
    EXPECT_EQ(c.GetMemoryID(), "DATA_SEGMENT");
    c.SetMemoryID("DATA_3456789");
    EXPECT_EQ(c.GetMemoryID(), "DATA_3456789");
    c.SetRegister(40);
    EXPECT_EQ(c.GetRegister(), 40);
    c.SetRegister(-456);
    EXPECT_EQ(c.GetRegister(), -456);
    Operator_Transition d;
    d.SetTransLabel("#LABEL");
    EXPECT_EQ(d.GetTransLabel(), "#LABEL");
    Operator_Typedef f;
    f.SetOperand("+");
    EXPECT_EQ(f.GetOperand(), "+");
}

TEST (Operands, Virtual_func) {
    Operator_Container a;
    Operator_Register b;
    Operator_RegisterMemory c;
    Operator_Transition t;
    Operator_Typedef d;
    EXPECT_EQ(a.getTypeofClass(), "Operator_Container");
    EXPECT_EQ(b.getTypeofClass(), "Operator_Register");
    EXPECT_EQ(c.getTypeofClass(), "Operator_RegisterMemory");
    EXPECT_EQ(t.getTypeofClass(), "Operator_Transition");
    EXPECT_EQ(d.getTypeofClass(), "Operator_Typedef");
}

TEST (Map, All_Func) {
    Table a;
    Operator_Container* a1 = new Operator_Container;
    a1->SetLabel("test operator #1");
    Operator_Container* a2 = new Operator_Container;
    a2->SetLabel("test operator #2");
    Operator_Container* a3 = new Operator_Container;
    a3->SetLabel("test operator #3");
    Operator_Container* a4 = new Operator_Container;
    a4->SetLabel("test operator #4");
    Operator_Container* a5 = new Operator_Container;
    a5->SetLabel("test operator #5");
    a.AddSymbol(10, a1);
    a.AddSymbol(20, a2);
    a.AddSymbol(30, a3);
    a.AddSymbol(40, a4);
    a.AddSymbol(50, a5);
    
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}