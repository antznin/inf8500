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
	/* 
	à compléter 
	*/

	//////// Interface avec le coprocesseur 1 ////////
	// Sortie du paquet à transmettre au coprocesseur 1
	/* 
	à compléter 
	*/
	

	//////// Interface avec le corocesseur 2 ////////
	// Sortie du paquet à transmettre au coprocesseur 2
	/* 
	à compléter 
	*/

	//////// Interface avec le coprocesseur 3 ////////
	// Sortie du paquet à transmettre au coprocesseur 3
	/* 
	à compléter 
	*/


	/* *******************************************************************
	// LOCAL VARIABLES
	******************************************************************** */
	// Paquet local au module pkt_terminator
	Packet pkt;

	/* *******************************************************************
	// MODULE METHODS
	******************************************************************** */
	// Ce fonction reçoit un paquet du générateur et le dispatche à un des coprocesseurs
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
		SC_THREAD(generate);
		// generate est sensible à next_packet
		sensitive(packet_ready);		
	
		
	}

};

#endif

