

#ifndef MONITOR_H
#define MONITOR_H

#include <systemc.h>
#include "packet.h"		// importation du type Packet
#include "simple_bus_types.h"
#include "simple_bus_slave_if.h"


class monitor:
	public simple_bus_slave_if,
	public sc_module
{
public:
	SC_HAS_PROCESS(monitor);

	/* *******************************************************************
	// MODULE PORTS
	******************************************************************** */
	sc_in_clk clock;

	sc_fifo_in<Packet*> packet_in_gen;


	/* *******************************************************************
	// LOCAL VARIABLES
	******************************************************************** */

	/* *******************************************************************
	// MODULE METHODS
	******************************************************************** */
	void compare_pkt(void);
	void dispatch(void);
	void wait_loop(void); 
	simple_bus_status read(int *data, unsigned int address);
	simple_bus_status write(int *data, unsigned int address);
	unsigned int start_address() const;
	unsigned int end_address() const;

	bool direct_read(int *data, unsigned int address);
	bool direct_write(int *data, unsigned int address);

	/* *******************************************************************
	// MODULE CONSTRUCTOR
	******************************************************************** */
	monitor(sc_module_name name_
		, unsigned int start_address
		, unsigned int end_address
		,unsigned int nr_wait_states)
		: sc_module(name_)
		, m_start_address(start_address)
		, m_end_address(end_address)
		, m_nr_wait_states(nr_wait_states)
		, packet_dispatched(1)
		, m_wait_count(-1)
	{
		SC_THREAD(dispatch);	// On aurait pu utiliser une méthode aussi mais j'ai laissé SC_THREAD avec boucle infinie
		sensitive << start_dispatch;

		SC_METHOD(wait_loop);
		dont_initialize();	// wait_loop ne sera pas appelé une première fois
		sensitive << clock.pos();

		sc_assert(m_start_address <= m_end_address);
		sc_assert((m_end_address-m_start_address+1)%4 == 0);
		unsigned int size = (m_end_address-m_start_address+1)/4;
		MEM = new unsigned int [size];
		for (unsigned int i = 0; i < size; i++) {
			MEM[i] = 0;
		}
	}
	/* *******************************************************************
	// MODULE DESTRUCTOR
	******************************************************************** */
	~monitor();
	/* *******************************************************************
	// LOCAL VARIABLES
	******************************************************************** */
private:
	sc_event start_dispatch;
	int packet_dispatched;
	Packet *pkt_gen;
	Packet *pkt_copro;
	unsigned int *MEM;
	unsigned int m_start_address;
	unsigned int m_end_address;
	unsigned int m_current_packet_start_address;
	int m_wait_count;
	unsigned int m_nr_wait_states;
};

#endif

