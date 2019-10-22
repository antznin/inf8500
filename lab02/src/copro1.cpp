
#include "copro1.h"
#include <string.h>


void copro1::pkt_display()
{
	while(true)
	{
		msg_valid = false; //Indique qu'il n'y a plus de paquets valides pour display et qu'il faut recommencer un cycle
		
		//Recupération du paquet généré par l'adaptateur
		ack = false; 
		cout << "COPRO1 : Attente paquet pret" << endl;
		wait(ready.posedge_event()); // Attendre ready == true
		cout << "COPRO1 : paquet pret" << endl;
		cout << "COPRO1 : Recuperation du paquet" << endl;
		pkt = *packet_in;
		cout << "COPRO1 : Acquittement" << endl;
		ack = true;

  unsigned int* ptr_int = pkt.getPacket();
  unsigned int  dir = pkt.getDir();
  unsigned  int iarray[16];
  for(int i = 0;i<17;i++)
   {
     iarray[i] = ptr_int[i+3]; //*(ptr_int+i*sizeof(unsigned int);
   }

// Code pour faire appel au tri
  cBubbleSort<unsigned int> cb(iarray, 16);
  std::cout<<"Passed Int Array "<<std::endl;
  cb.print();
  if (dir == 1) cb.doSort(true); else cb.doSort(false);
//  std::cout<<"Ascend(1)*/Desc(0)* Order "<<direction<<std::endl;
  cb.print();
  unsigned int* ptr_int_r;
  ptr_int_r = cb.get_pointer_to_sorted_array();

  pkt.putPacket(ptr_int_r);   // Display peut maintenant afficher le resultat du tri

		
		// Envoi du paquet au display
		msg_valid = true; //Indique qu'un nouveau paquet est disponible pour le display
		char message[100];
		output_pkt = &pkt;
		strcpy( message, "DISPLAY : Paquet en Provenance : " );
		strcat( message, name() );
		output_msg = message;

		// Indiquer au module display qu'il faut afficher un message
		cout << "COPRO1 : Envoi à copro1" << endl;
		cout << "COPRO1 : attente de copro1 ready" << endl;
		wait(display_ready.value_changed_event()); // attente du signal indiquant que le paquet a été lu par le display
		cout << "COPRO1 : Display a bien recu le message" << endl;

	}
}
