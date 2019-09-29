#include "packet_gen_adapt_master.h"
#include "globals.h"
#include <string.h>

void packet_gen_adapt_master::pkt_dispatch(void){

	unsigned int addr;
	simple_bus_status status;
	unsigned int length = 6; // 6 words = 24 bytes
	unsigned int data[length];

	while (true)
	{
		
		cout << "GEN ADAPT: Attente paquet" << endl;
		next_packet = true;
		wait(packet_ready.posedge_event());
		cout << "GEN ADAPT: Paquet recu" << endl;
		
		pkt = *pkt_in;
		addr = pkt.getAddress();
		memcpy(data, pkt.getPacket(), 24);
		/* Packet * pkt_tmp = new Packet(data); */
		/* cout << *pkt_in << endl; */
		/* cout << *pkt_tmp << endl; */
		cout << "GEN ADAPT: addr : " << addr << endl;

		cout << "GEN ADAPT: Burst write" << endl;
		status = bus_port->burst_write(m_unique_priority, (int *)data, 
					     addr, length, m_lock);
		if (status == SIMPLE_BUS_ERROR)
		sb_fprintf(stdout, "%g %s : blocking-write failed at address %x\n",
			   sc_time_stamp().to_double(), name(), m_address);

		cout << "GEN ADAPT: Post-Burst write" << endl;
		next_packet = false;
		wait(m_timeout, SC_NS);
	}
}

