#include "copro1_adapt_slave.h"

copro1_adapt_slave::~copro1_adapt_slave()
{
	//A COMPLETER
	if (MEM) delete [] MEM;
  	MEM = (unsigned int *)0;
}

/* void copro1_adapt_slave::access_time() */
/* { */
/* 	//A COMPLETER */
/* 	return; */
/* } */
bool copro1_adapt_slave::direct_read(int *data, unsigned int address)
{
  return true;
}

bool copro1_adapt_slave::direct_write(int *data, unsigned int address)
{
  return true;
}

simple_bus_status copro1_adapt_slave::read(int *data, unsigned int address)
{
	//DO NOTHING (UNIMPLEMENTED)
	return SIMPLE_BUS_ERROR;
}
simple_bus_status copro1_adapt_slave::write(int *data, unsigned int address)
{
	//A COMPLETER
	// accept a new call if m_wait_count < 0)
	if (m_wait_count < 0)
	{
		m_wait_count = m_nr_wait_states;
		cout << "ADAPT_SLAVE 1 : test" << endl;
		return SIMPLE_BUS_WAIT;
	}
	if (m_wait_count == 0)
	{
		
		if (compt == 0) {
			m_current_packet_start_address = address - m_start_address;
			MEM = (unsigned int *)malloc((m_end_address - m_start_address) * sizeof(unsigned int));
			cout << "ADAPT_SLAVE 1 : compt est a zero " << endl;
		}

		cout << "ADAPT_SLAVE 1 : address " << address << endl;
		/* cout << "ADAPT_SLAVE 1 : address de MEM " << address - m_start_address << endl; */
	  	MEM[(address - m_start_address)/4] = *data;
		cout << "ADAPT_SLAVE 1 : contenu de data " << std::bitset<32>(*data) << " " << hex << *data << endl;
		compt = compt + 1;
		cout << "ADAPT_SLAVE 1 : compt = " << compt << endl;

		if (compt == 6) {
			compt = 0;
			packet = new Packet(&(MEM[(m_current_packet_start_address)/4]));  
			cout << "ADAPT_SLAVE 1 : Packet créé, addr =" << (*packet).getAddress() << endl;
			cout << "ADAPT_SLAVE 1 : Notifying via received" << endl;
			received.notify();
		}
		
	  	return SIMPLE_BUS_OK;
	}
	return SIMPLE_BUS_WAIT;
}

/* void copro1_adapt_slave::dispatch() */
/* { */
/* 	//A COMPLETER */
/* 	return; */
/* } */
unsigned int  copro1_adapt_slave::start_address() const
{
	//A COMPLETER
	return m_start_address;
}
unsigned int  copro1_adapt_slave::end_address() const
{
	//A COMPLETER
	return m_end_address;
}
void copro1_adapt_slave::pkt_send1(void){
	//A COMPLETER
	while (true) {
		wait(received);
		cout << "ADAPT_SLAVE 1 : Notified via received" << endl;
		ready = false;
		pkt_out = packet;
		ready = true;
		wait(ack.posedge_event());
	}
}
