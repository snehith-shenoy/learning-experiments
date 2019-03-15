#include "TOP.hpp"

int sc_main(int argc, char* argv[])
{
	TOP t("Testbench");
	std::cout<<"\nF = A (!C + !B) + B.C.(!D)\n\n";
	sc_start();
	return 0;
}
