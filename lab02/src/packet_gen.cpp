#include <systemc.h>
#include "packet_gen.h"
#include "my_rand_obj.h"
#include "input_cvg.h"
#include "testcase.h"

// SC_THREAD(generate)
// sensitive(next_packet)
void packet_gen::generate(void)
{
	int i = 0;
	int nba;
	int copro_numero;
	int offset_copro;
	my_rand_obj rand_addr;
	input_cvg cvg;
	TestBase test;
	std::string order;

	while (cvg.get_inst_coverage() < 100)
	{
		cout << "COVERAGE : " << cvg.get_inst_coverage() << endl;
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
		cout << "GEN : " << rand_addr.data_order_value() << endl; 

		switch (rand_addr.data_order_value()) {
			case 0: order = "Random_Dsc";
				break;
			case 1: order = "Random_Asc";
				break;
			case 2: order = "Full_Random";
				break;
			case 3: order = "Continues_Asc";
				break;
			case 4: order = "Continues_Desc";
				break;
		}
		cout << "PACKET_GEN : order = " << order << endl;
		test.chk_testcase(order);

		cvg.sample(rand_addr.copro_value(), rand_addr.data_order_value(), rand_addr.sort_dir_value());

		nba = rand_addr.address;
		nba = nba - (nba % 4);

		// G�n�rer un nouveau paquet et l'envoyer au coprocesseur
		// dont le num�ro a �t� g�n�r� al�atoirement
		pkt = new Packet(nba, 1 + i);
		//affichage du paquet envoy�

		// On met les donnees generees par le testcase dans le payload du pkt 
		unsigned int * newPayload; 
		newPayload = (unsigned int *)calloc(16, sizeof(unsigned int));
		int k;
		for (k = 0; k < 16; k++)
			newPayload[k] = (unsigned int)test.p[k];
		(*pkt).putPacket(newPayload);


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

	fc4sc::global::coverage_save("coverage_results.xml");
	std::cout << "nombre d'execution requise pour 100%: " << dec << cvg.nb_de_cov << std::endl;
	exit(0);
}
