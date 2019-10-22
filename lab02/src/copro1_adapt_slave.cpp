#include "copro1_adapt_slave.h"

copro1_adapt_slave::~copro1_adapt_slave()
{
	if (MEM) delete [] MEM;
  	MEM = (unsigned int *)0;
}

void copro1_adapt_slave::wait_loop()
{
	if (m_wait_count >= 0) m_wait_count--;
}

simple_bus_status copro1_adapt_slave::read(int *data, unsigned int address)
{
	//DO NOTHING (UNIMPLEMENTED)
	return SIMPLE_BUS_ERROR;
}

simple_bus_status copro1_adapt_slave::write(int *data, unsigned int address)
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

void copro1_adapt_slave::dispatch()
{
	while(1) 
	{	
		wait(); // Attente évènement start_dispatch
		cout << "COPRO1_ADAPT : TEST event dispatch" << endl;
		packet = new Packet(&MEM[((m_current_packet_start_address - m_start_address) / 4)]);

		pkt_send1();
	}

}

unsigned int  copro1_adapt_slave::start_address() const
{
	return m_start_address;
}

unsigned int  copro1_adapt_slave::end_address() const
{
	return m_end_address;
}

void copro1_adapt_slave::pkt_send1(void)
{
	packet_out.write(packet);
	valid.write(true);
	wait(next.posedge_event());
	valid.write(false);
}


void copro1_adapt_slave::to_monitor(void)
{
	simple_bus_status status;
	int addr = 0x300, packet_size = 19;
	while(1) 
	{
		cout << "COPRO1_ADAPT : Attente paquet trie" << endl;
		pkt = *packet_in.read(); // Attendre la lecture bloquante
		cout << "COPRO1_ADAPT : Recuperation du paquet trie" << endl;
		// write du paquet au moniteur
		cout << "COPRO1_ADAPT : Envoi burst_write" << endl;
		status = bus_port->burst_write(1, (int*)pkt.getPacket(), addr, packet_size, false);
		cout << pkt;
	}
}

// Ajout Julien, sinon erreur à la compilation (comme dans l'exemple) :

bool copro1_adapt_slave::direct_read(int *data, unsigned int address)
{
  return (read(data, address) == SIMPLE_BUS_OK);
}

bool copro1_adapt_slave::direct_write(int *data, unsigned int address)
{
  return (write(data, address) == SIMPLE_BUS_OK);
}
