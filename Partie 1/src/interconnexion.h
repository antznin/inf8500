#include <systemc.h>
#include "packet.h"		// importation du type Packet

#ifndef INTERCONNEXION_H
#define INTERCOONEXION_H

SC_MODULE(interconnexion)
{
	/* *******************************************************************
	// MODULE PORTS
	******************************************************************** */
	//////// Interface avec la g�n�ration de paquets ////////
	/* 
	� compl�ter 
	*/

	//////// Interface avec le coprocesseur 1 ////////
	// Sortie du paquet � transmettre au coprocesseur 1
	/* 
	� compl�ter 
	*/
	

	//////// Interface avec le corocesseur 2 ////////
	// Sortie du paquet � transmettre au coprocesseur 2
	/* 
	� compl�ter 
	*/

	//////// Interface avec le coprocesseur 3 ////////
	// Sortie du paquet � transmettre au coprocesseur 3
	/* 
	� compl�ter 
	*/


	/* *******************************************************************
	// LOCAL VARIABLES
	******************************************************************** */
	// Paquet local au module pkt_terminator
	Packet pkt;

	/* *******************************************************************
	// MODULE METHODS
	******************************************************************** */
	// Ce fonction re�oit un paquet du g�n�rateur et le dispatche � un des coprocesseurs
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
		// generate est sensible � next_packet
		sensitive(packet_ready);		
	
		
	}

};

#endif

