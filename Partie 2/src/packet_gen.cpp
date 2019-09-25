#include <systemc.h>
#include "packet_gen.h"
/* #include <crave/ConstrainedRandom.hpp> */

/* using crave::randv; */
/* using crave::Generator; */

// SC_THREAD(generate)
// sensitive(next_packet)
void packet_gen::generate( void )
{  

	/* crave::init("crave.cfg"); */
	/* randv<unsigned int> nba(NULL); */
	/* Generator gen; */
	/* gen((nba() >= 0 && nba() <= 72) || (nba() >= 96 && nba() <= 168) || (nba() >= 192 && nba() <= 264)); */

	int nba;
	int i=0;
	while (i < 8)
	{
 		packet_ready = false;
		cout << "GEN : attente du bus pret" << endl;
		wait(); // Attendre l'assertion de next_packet
		
		wait(50, SC_NS);

		// Générer un nombre aléatoire entre 0 et 255.
		/* CHECK(gen.next()); */
		nba =  (rand() % 95)*3;
		if (nba > 72 && nba < 96)
			nba = 72;
		if (nba > 168 && nba < 192)
			nba = 168;
		if (nba > 264 && nba < 288)
			nba = 264;
		nba = 0;
		cout << "GEN : Random address : " << nba << endl;
		
		// Générer un nouveau paquet et l'envoyer au coprocesseur
		// dont le numéro a été généré aléatoirement
		pkt = new Packet(nba, 1 + i);
		//affichage du paquet envoyé
		cout << "GEN : Un paquet a ete envoye e l'adresse 0x" << hex << nba << endl;
		cout << *pkt;
		packet_out = pkt;
		cout << "GEN : Envoi du paquet au bus" << endl;
		packet_ready = true;

		
		cout << "GEN : Attente paquet recu" << endl;
		wait(next_packet.negedge_event()); // Attendre la désassertion de next_packet
		cout << "GEN : next_packet deasserte" << endl;
		packet_ready = false;
		
		delete pkt;
		i++;
	}
	
}
