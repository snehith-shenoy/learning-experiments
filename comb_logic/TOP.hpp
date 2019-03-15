#pragma once
//#include "MONITOR.hpp"
#include "AND_GATE.hpp"
#include "NOT_GATE.hpp"
#include "OR_GATE.hpp"
#include "STIMULATOR.hpp"

class TOP: public sc_module

{
	public:
		TOP(sc_module_name nm): sc_module(nm),
		and1("AND_1"),
		and2("AND_2"),
		and3("AND_3"),
		and4("AND_4"),
		or1("OR_1"),
		or2("OR_2"),

		not1("NOT_1"),
		not2("NOT_2"),
		not3("NOT_3"),
		stim("Test_Vector_Generator")

	{

		//Stimuli
		//First level
		stim.m_A(sigA);
		stim.m_B(sigB);
		stim.m_C(sigC);
		stim.m_D(sigD);




		and1.m_in1(sigA);
		not1.m_in1(sigC);

		and2.m_in1(sigA);
		not2.m_in1(sigB);

		and3.m_in1(sigB);
		and3.m_in2(sigC);
		not3.m_in1(sigD);

		//Second level

		not1.m_op(w1); and1.m_in2(w1);
		not2.m_op(w2); and2.m_in2(w2);
		and3.m_op(w3); and4.m_in1(w3);
		not3.m_op(w4); and4.m_in2(w4);

		//Third level

		and1.m_op(w5); or1.m_in1(w5);
		and2.m_op(w6); or1.m_in2(w6);

		//Penultimate level

		or1.m_op(w7); or2.m_in1(w7);
		and4.m_op(w8); or2.m_in2(w8);

		// Ultimate level

		or2.m_op(buffout);

		stim.m_in1(buffout);

	}

		private:

		sc_buffer<bool> sigA, sigB, sigC, sigD;	
		sc_signal<bool> w1,w2,w3,w4,w5,w6,w7,w8;
		sc_signal<bool> buffout;
		AndGate and1,and2,and3,and4;
		OrGate or1,or2;
		NotGate not1,not2,not3;
		STIMULATOR stim;

};
