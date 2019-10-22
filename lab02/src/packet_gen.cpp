#include <systemc.h>
#include "packet_gen.h"
#include "my_rand_obj.h"

// SC_THREAD(generate)
// sensitive(next_packet)
void packet_gen::generate( void )
{  
	int i=0;
 	int nba; 
	int copro_numero;
	int offset_copro;
	my_rand_obj rand_addr;

	while (i < 8)
	{
 		packet_ready = false;
		cout << "GEN : attente du bus pret" << endl;
		wait(); // Attendre l'assertion de next_packet
		
		wait(50, SC_NS);
		
		/* // Choix copro 0, 1 ou 2 */
		/* copro_numero = rand() % 3; */

		/* offset_copro = (rand() % 46) * 4; */	
		/* nba = (copro_numero * 256) + offset_copro; */

		CHECK(rand_addr.next());
		cout << rand_addr << endl;
		
		nba = rand_addr.address;
		nba = nba - (nba % 4); 

		// G�n�rer un nouveau paquet et l'envoyer au coprocesseur
		// dont le num�ro a �t� g�n�r� al�atoirement
		pkt = new Packet(nba, 1 + i);
		//affichage du paquet envoy�
		cout << "GEN : Un paquet a ete envoye a l'adresse 0x" << hex << nba << endl;
		cout << *pkt;
		cout << "GEN : Ecriture non bloquante au monitor :" << endl;
		packet_monitor.nb_write(pkt);
		packet_out = pkt;
		cout << "GEN : Envoi du paquet au bus" << endl;
		packet_ready = true;
		
		cout << "GEN : Attente paquet recu" << endl;
		wait(); // Attendre la d�sassertion de next_packet
		packet_ready = false;
		
		delete pkt;
		i++;
	}
	
}
