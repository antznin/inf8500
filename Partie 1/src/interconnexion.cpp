#include "interconnexion.h"
#include "globals.h"
#include <string.h>

void interconnexion::pkt_dispatch(void){
	
	int addr;

	while (true)
	{

		wait(packet_ready.posedge_event()); // attendre packet_ready

		//Recupération du paquet
		pkt = *packet_in;

		//Lecture de l'adresse du paquet
		addr = pkt.getAddress();


		//Utiliser la bonne méthode d'envoi selon l'adresse
		switch (addr){
		case PACKET_OUT1:
			pkt_send1();
			break;
		case PACKET_OUT2:
			pkt_send2();
			break;
		case PACKET_OUT3:
			pkt_send3();
			break;
		}
		// Message de sortie pour le module display
	}
}

void interconnexion::pkt_send1(void){
	
	packet_out1 = &pkt;
	ready1 = true;
	wait(packet_next1.posedge_event());
	ready1 = false;
}

void interconnexion::pkt_send2(void){
	
	fifo_out.write(&pkt);

}

void interconnexion::pkt_send3(void){
	
	packet_out3.write(&pkt);
	wait(packet_next3.posedge_event());
}
