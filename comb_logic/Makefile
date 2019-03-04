# Directory where SystemC in installed
SYSTEMC_HOME=/home/vayavya/systemc-2.3.3
SYSTEMC_ARCH=linux64

# List of source files
CSRCS=
CPPSRCS= $(wildcard *.cpp)
# Name of the executable
EXE= comb_logic


#------ DONT EDIT BELOW ----------------------------
CXX=g++
CC=gcc
LD=g++
COBJS=$(patsubst %.c,%.o,$(CSRCS))
CPPOBJS=$(patsubst %.cpp,%.o,$(CPPSRCS))
CC_FLAGS=-Wall -std=c++11 -g -o0 
ifeq ($(DEBUGPRINT), "")
  #define D_PRINT 1
else
  #define D_PRINT 0
endif


SYSTEMC_INC=$(SYSTEMC_HOME)/include
SYSTEMC_LIB=$(SYSTEMC_HOME)/lib-$(SYSTEMC_ARCH)

SYSTEMC_LIBS=-lsystemc -lm

%.o:%.cpp
	$(CXX) $(CC_FLAGS) -I $(SYSTEMC_INC) -I. -c $^ -o $@

%.o:%.c
	$(CC) $(CC_FLAGS) -I. -c $^ -o $@

$(EXE): $(COBJS) $(CPPOBJS)
	$(LD) $(LD_FLAGS) $(COBJS) $(CPPOBJS) -L $(SYSTEMC_LIB) $(SYSTEMC_LIBS) -o $@

clean:
	rm -f $(EXE) $(COBJS) $(CPPOBJS)
