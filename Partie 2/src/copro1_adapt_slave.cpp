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
	  return SIMPLE_BUS_WAIT;
	}
	if (m_wait_count == 0)
	{
		
	  	MEM[(address - m_start_address)/4] = *data;
		packet = new Packet(&MEM[(address - m_start_address)/4]);  
		received.notify();
		
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
		ready = false;
		pkt_out = packet;
		ready = true;
		wait(ack.posedge_event());
	}
}
