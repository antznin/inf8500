#ifndef COPRO2_ADAPT_SLAVE_H
#define COPRO2_ADAPT_SLAVE_H

#include <systemc.h>

#include "simple_bus_types.h"
#include "simple_bus_slave_if.h"
#include "packet.h"

class copro2_adapt_slave
	: public simple_bus_slave_if,
	public sc_module
{
public:
	SC_HAS_PROCESS(copro2_adapt_slave);
	/* *******************************************************************
	// MODULE PORTS
	******************************************************************** */
	sc_in_clk clock;

	// Connexions entre adapteur et copro
	sc_fifo_out<Packet*> fifo_out;
	sc_in<bool> ack;
	sc_event received;
	

	/* *******************************************************************
	// MODULE METHODS
	******************************************************************** */
	// Attente du communicateur pr�t (METHOD)
	/* void access_time(void); */ 
	// thread de dispatch r�veill�e lorsqu'un paquet est pr�t (THREAD)
	/* void dispatch(void); */
	// Slave Interface (M�thodes de l'interface � impl�menter)
	simple_bus_status read(int *data, unsigned int address);
	simple_bus_status write(int *data, unsigned int address);
	bool direct_read(int *data, unsigned int address);
	bool direct_write(int *data, unsigned int address);
	unsigned int start_address() const;
	unsigned int end_address() const;

	void pkt_send2(void);


	/* *******************************************************************
	// MODULE CONSTRUCTOR
	******************************************************************** */
	copro2_adapt_slave(sc_module_name name_
		, unsigned int start_address
		, unsigned int end_address
		,unsigned int nr_wait_states)
		: sc_module(name_)
		, m_start_address(start_address)
		, m_end_address(end_address)
		, m_nr_wait_states(nr_wait_states)
		, packet_dispatched(1)
		, m_wait_count(-1)
		, compt(0)
	{
		/* SC_THREAD(dispatch); */
		//A COMPLETER
		/* SC_METHOD(access_time); */
		dont_initialize();
		//A COMPLETER
		SC_THREAD(pkt_send2);
		sensitive << ack << received; 


	}
	/* *******************************************************************
	// MODULE DESTRUCTOR
	******************************************************************** */
	~copro2_adapt_slave();
	/* *******************************************************************
	// LOCAL VARIABLES
	******************************************************************** */
private:
	sc_event start_dispatch;
	int packet_dispatched;
	Packet *packet;
	unsigned int *MEM;
	unsigned int m_start_address;
	unsigned int m_end_address;
	int m_wait_count;
	unsigned int m_nr_wait_states;
	int compt;
	unsigned int m_current_packet_start_address;
};

#endif