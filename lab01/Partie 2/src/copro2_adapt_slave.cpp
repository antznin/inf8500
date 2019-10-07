#include "copro2_adapt_slave.h"

copro2_adapt_slave::~copro2_adapt_slave()
{
	if (MEM) delete [] MEM;
	MEM = (unsigned int *)0;
}

/* void copro2_adapt_slave::access_time() */
/* { */
/* 	//A COMPLETER */
/* 	return; */
/* } */

bool copro2_adapt_slave::direct_read(int *data, unsigned int address)
{
  return true;
}

bool copro2_adapt_slave::direct_write(int *data, unsigned int address)
{
  return true;
}

simple_bus_status copro2_adapt_slave::read(int *data, unsigned int address)
{
	//DO NOTHING (UNIMPLEMENTED)
	return SIMPLE_BUS_ERROR;
}
simple_bus_status copro2_adapt_slave::write(int *data, unsigned int address)
{
	//A COMPLETER
	// accept a new call if m_wait_count < 0)
	if (m_wait_count < 0)
	{
		m_wait_count = m_nr_wait_states;
		return SIMPLE_BUS_WAIT;
	}
	if (m_wait_count == 0)
	{
		
		if (compt == 0) {
			m_current_packet_start_address = address - m_start_address;
			MEM = (unsigned int *)malloc((m_end_address - m_start_address) * sizeof(unsigned int));
			cout << "ADAPT_SLAVE 2 : compt est a zero " << endl;
		}

		cout << "ADAPT_SLAVE 2 : address " << address << endl;
		cout << "ADAPT_SLAVE 2 : address de MEM " << address - m_start_address << endl;
	  	MEM[(address - m_start_address)/4] = *data;
		cout << "ADAPT_SLAVE 2 : contenu de data " << std::bitset<32>(*data) << " " << hex << *data << endl;
		compt = compt + 1;
		cout << "ADAPT_SLAVE 2 : compt = " << compt << endl;

		if (compt == 6) {
			compt = 0;
			packet = new Packet(&(MEM[(m_current_packet_start_address)/4]));  
			cout << "ADAPT_SLAVE 2 : Packet créé, addr =" << (*packet).getAddress() << endl;
			cout << "ADAPT_SLAVE 2 : Notifying via received" << endl;
			received.notify();
		}
		
	  	return SIMPLE_BUS_OK;
	}
	return SIMPLE_BUS_WAIT;
}
/* void copro2_adapt_slave::dispatch() */
/* { */
/* 	//A COMPLETER */
/* 	return; */
/* } */
unsigned int  copro2_adapt_slave::start_address() const
{
	return m_start_address;
}
unsigned int  copro2_adapt_slave::end_address() const
{
	return m_end_address;
}
void copro2_adapt_slave::pkt_send2(void){
	while (true) {
		wait(received);
		cout << "ADAPT_SLAVE 2 : Notified via received" << endl;
		fifo_out.write(packet);
		wait(ack.posedge_event());
	}
}
