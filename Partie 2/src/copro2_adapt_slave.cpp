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
  	    MEM[(address - m_start_address)/4] = *data;
		packet = new Packet(&MEM[(address - m_start_address)/4]);  
		received.notify();
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
		fifo_out.write(packet);
		wait(ack.posedge_event());
	}
}
