#include "packet_gen_adapt_master.h"
#include "globals.h"
#include <string.h>

void packet_gen_adapt_master::pkt_dispatch(void){

	unsigned int addr;
	simple_bus_status status;
	unsigned int length = 0x20;
	Packet data[length];

	while (true)
	{
		
		cout << "GEN ADAPT: Attente paquet" << endl;
		wait();
		cout << "GEN ADAPT: Paquet recu" << endl;
		
		data = pkt_in; // pointeur sur le paquet
		pkt = *pkt_in;
		addr = pkt.getAddress();

		cout << "GEN ADAPT: Burst write" << endl;
		status = bus_port->burst_write(m_unique_priority, data, 
					     addr, length, m_lock);
		if (status == SIMPLE_BUS_ERROR)
		sb_fprintf(stdout, "%g %s : blocking-write failed at address %x\n",
			   sc_time_stamp().to_double(), name(), m_address);

		wait(m_timeout, SC_NS);
	}
}

