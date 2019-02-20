#ifndef __BUS_IF_H__
#define __BUS_IF_H__

typedef unsigned short uint16;

class bus_if{
public:
	typedef enum {BUS_OK,BUS_ERROR} status_t;
	virtual status_t read(uint16 addr, uint16 &data) = 0;
	virtual status_t write(uint16 addr,uint16 data) = 0;
	bus_if(){}
	~bus_if(){}
};

#endif
