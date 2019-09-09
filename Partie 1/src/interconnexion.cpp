#include "interconnexion.h"
#include "globals.h"
#include <string.h>

void interconnexion::pkt_dispatch(void){
	
	int addr;

	while (true)
	{

		//Recupération du paquet
		/* 
		à compléter 
		*/

		//Lecture de l'adresse du paquet
		/* 
		à compléter 
		*/


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
	
	/* 
	à compléter 
	*/

}

void interconnexion::pkt_send2(void){
	
	/* 
	à compléter 
	*/

}

void interconnexion::pkt_send3(void){
	
	/* 
	à compléter 
	*/
}
