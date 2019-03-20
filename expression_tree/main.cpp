
#include "Tree.h"

int main(int argc, char * argv[])
{

	Tree T1(new OpPlus, new Tree(new Num(1)) , new Tree(new OpMul, new Tree(new Var("xyz")) , new Tree(new Num(3)))); 
	Tree T2(new OpMul, new Tree(new Num(1)), new Tree(new Var("abc"))); 
	Tree T3(new OpPlus, new Tree(new Num(1)), new Tree(new OpDiv, new Tree(new Num(6)), new Tree(new Num(2))));
	Tree T4(new OpPlus , new Tree(new Var("a")), new Tree(new OpPlus,
				new Tree(new Num(1)), new Tree(new OpPlus, new Tree (new Num(2)),
					new Tree(new OpMinus, new Tree (new OpMul,
							new Tree (new Var("b")), new Tree(new OpMul, new Tree (new Num(2)),
								new Tree (new Num(3)))), new Tree(new Var("b"))))));  

	cout<<"#### Expressions constructed using default constructor:\n\n";
	cout << T1 << endl<<endl;
	cout << T2 << endl<<endl;
	cout << T3 << endl<<endl;
	cout << T4 << endl<<endl;
	T1.evaluate();
	T2.evaluate();
	T3.evaluate();
	T4.evaluate();
	cout << "#### After Evaluation\n\n";
	cout << T1 << endl<<endl;
	cout << T2 << endl<<endl;
	cout << T3 << endl<<endl;
	cout << T4 << endl << endl;

	cout<<"#### Expressions constructed using vector of nodes:\n\n";

	std::vector<Node *>  expr1{ 
		new OpMinus,
		    new OpPlus,
		    new OpMul,
		    new Num(2),
		    new Var("varA"),
		    new OpMul,
		    new Num(3),
		    new Num(3),
		    new Num(4)
	};

	std::vector<Node *>  expr2{
		new OpPlus,
		    new OpMul,
		    new Var("count"),
		    new Num(2),
		    new OpDiv,				
		    new Num(2),
		    new Num(10),
	};


	Tree VT1(expr1);
	Tree VT2(expr2);
	cout << VT1 << endl <<endl;
	cout << VT2 << endl <<endl;
	VT1.evaluate();
	VT2.evaluate();
	cout << "#### After Evaluation\n\n";
	cout << VT1 << endl<<endl;
	cout << VT2 << endl<<endl;
	return 0;
}
