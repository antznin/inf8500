#include <systemc.h>
#include "packet.h"		// importation du type Packet

#ifndef INTERCONNEXION_H
#define INTERCOONEXION_H

SC_MODULE(interconnexion)
{
	/* *******************************************************************
	// MODULE PORTS
	******************************************************************** */
	//////// Interface avec la génération de paquets ////////
	sc_in<bool> packet_ready;
	sc_in<Packet*> packet_in;
	sc_out<bool> packet_next;

	//////// Interface avec le coprocesseur 1 ////////
	// Sortie du paquet à transmettre au coprocesseur 1
	sc_out<Packet*> packet_out1;
	sc_out<bool> ready1;
	sc_in<bool> packet_next1;
	

	//////// Interface avec le corocesseur 2 ////////
	// Sortie du paquet à transmettre au coprocesseur 2
	sc_fifo_out<Packet*> fifo_out;

	//////// Interface avec le coprocesseur 3 ////////
	// Sortie du paquet à transmettre au coprocesseur 3
	sc_buffer<Packet*> packet_out;
	sc_in<bool> packet_next3;


	/* *******************************************************************
	// LOCAL VARIABLES
	******************************************************************** */
	// Paquet local au module pkt_terminator
	Packet pkt;

	/* *******************************************************************
	// MODULE METHODS
	******************************************************************** */
	// Cette fonction reçoit un paquet du générateur et le dispatche à un des coprocesseurs
	void pkt_dispatch(void); //THREAD
	void pkt_send1(void);
	void pkt_send2(void);
	void pkt_send3(void);

	/* *******************************************************************
	// MODULE CONSTRUCTOR
	******************************************************************** */
	SC_CTOR(interconnexion)
	{
		
		// generate est un thread
		SC_THREAD(pkt_dispatch);
		// generate est sensible à next_packet
		sensitive << packet_ready << packet_next1;		
	
		
	}

};

#endif

