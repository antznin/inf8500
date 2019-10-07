#include "interconnexion.h"
#include "globals.h"
#include <string.h>

void interconnexion::pkt_dispatch(void){
	
	int addr;

	while (true)
	{

		packet_next = true;
		cout << "INT : attente packet_ready" << endl;
		wait(packet_ready.posedge_event()); // attendre packet_ready

		//Recupération du paquet
		pkt = *packet_in;

		//Lecture de l'adresse du paquet
		addr = pkt.getAddress();

		packet_next = false;

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
	
	cout << "INT : envoie paquet cop2" << endl;
	fifo_out.write(&pkt);
	cout << "INT : paquet cop2 envoye" << endl;
	wait(packet_next2.posedge_event());

}

void interconnexion::pkt_send3(void){
	
	packet_out3.write(&pkt);
	wait(packet_next3.posedge_event());
}
