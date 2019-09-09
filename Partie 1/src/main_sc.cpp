#include <systemc.h>

// D�finitions globales
#include "globals.h"

// D�finitions des modules
#include "display.h"
#include "packet_gen.h"
#include "copro1.h"
#include "copro2.h"
#include "copro3.h"
#include "interconnexion.h"


// D�finitions des classes
#include "packet.h"

// Fonction principale
int sc_main( int argc, char* argv[] )
{
	
	Packet packet_init1,packet_init2;
	char display_buffer[1024];
	display_buffer[0] = 0;
	
	// Connexions entre packet_gen et interconnexion 
	/* 
	� compl�ter 
	*/

	// Connexions entre interconnexion et copro1 
	/* 
	� compl�ter 
	*/

	// Connexions entre interconnexion et copro2 
	/* 
	� compl�ter 
	*/	

	// Connexions entre interconnexion et copro3 
	/* 
	� compl�ter 
	*/

	// Connexions entre Display et coprocesseurs 
	sc_signal<bool,sc_core::SC_MANY_WRITERS> msg_valid;
	sc_signal<char*, sc_core::SC_MANY_WRITERS> display_message;
	sc_signal<Packet*, sc_core::SC_MANY_WRITERS> display_packet;
	sc_signal<bool> display_ready;


	// Espaces tampons (buffers) entre les modules
	display_packet = &packet_init2;
	display_message = display_buffer;

	//------------------------------------------
	// Instanciation
	//------------------------------------------

	packet_gen the_pkt_gen("the_pkt_gen");
	interconnexion interconnexion ("interconexion");
	/* 
	� compl�ter 
	*/
	display monitor("monitor");

	//------------------------------------------
	// Connexions entre les ports
	//------------------------------------------

	the_pkt_gen(next_packet, packet_ready, packet_GR);
	interconnexion(packet_GR, packet_ready, next_packet, packet_RS, ack_RS, ready_RS, packet_RS2, packet_RS3, ack_RS3);
	/* 
	� compl�ter 
	*/
	monitor(msg_valid, display_message, display_packet, display_ready);

	//------------------------------------------
	// D�marrer la simulation
	//------------------------------------------
      
	sc_start(100, SC_SEC);


	printf("fin de la simulation");
	
	return 0;
}
