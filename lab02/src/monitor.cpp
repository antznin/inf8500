#include "monitor.h"
#include "Scoreboard.h"

monitor::~monitor()
{
	if (MEM) delete [] MEM;
  	MEM = (unsigned int *)0;
}

void monitor::wait_loop()
{
	if (m_wait_count >= 0) m_wait_count--;
}

simple_bus_status monitor::read(int *data, unsigned int address)
{
	//DO NOTHING (UNIMPLEMENTED)
	return SIMPLE_BUS_ERROR;
}

simple_bus_status monitor::write(int *data, unsigned int address)
{
	static int cpt_passage = 1;

  if (m_wait_count < 0) {
      
		m_wait_count = m_nr_wait_states;
		return SIMPLE_BUS_WAIT;
  }
  if (m_wait_count == 0) {
		
		MEM[(address - m_start_address)/4] = *data;
		
		if (cpt_passage == 19) {
			// Packet reçu au complet
			cpt_passage = 1;
			start_dispatch.notify();
		}
		else {
			if (cpt_passage == 1)
				m_current_packet_start_address = address;
			
			cpt_passage++;
		}
		
		return SIMPLE_BUS_OK;
	}

  return SIMPLE_BUS_WAIT;
}

void monitor::dispatch()
{
	while(1) 
	{	
		wait(); // Attente évènement start_dispatch
		cout << "COPRO1 : TEST event dispatch" << endl;
		pkt_copro = new Packet(&MEM[((m_current_packet_start_address - m_start_address) / 4)]);
		compare_pkt();
	}

}

unsigned int  monitor::start_address() const
{
	return m_start_address;
}

unsigned int  monitor::end_address() const
{
	return m_end_address;
}

void monitor::compare_pkt(void)
{
	ScoreBoard scb;
	// read the packet from packet_gen
	pkt_gen = packet_in_gen.read();
	//cout << "MONITOR : Received from packet_gen :" << endl;
	//cout << *pkt_gen << endl;
	//cout << "MONITOR : Received from copro :" << endl;
	//cout << *pkt_copro << endl;
	cout << "MONITOR : Comparing..." << endl;
	scb.check_int((int *)(*pkt_copro).getPacket(), (int *)(*pkt_gen).getPacket(), (*pkt_gen).getDir());
	

}



// Ajout Julien, sinon erreur à la compilation (comme dans l'exemple) :

bool monitor::direct_read(int *data, unsigned int address)
{
  return (read(data, address) == SIMPLE_BUS_OK);
}

bool monitor::direct_write(int *data, unsigned int address)
{
  return (write(data, address) == SIMPLE_BUS_OK);
}

