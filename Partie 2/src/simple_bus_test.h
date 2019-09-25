/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2014 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.accellera.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

  *****************************************************************************/

/*****************************************************************************

  simple_bus_test.h : The test bench.

  Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11

  *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

  Name, Affiliation, Date:
  Description of Modification:

  *****************************************************************************/

#ifndef __simple_bus_test_h
#define __simple_bus_test_h

#include <systemc.h>

#include "simple_bus.h"
#include "simple_bus_arbiter.h"
#include "packet.h"
#include "copro1.h"
#include "copro2.h"
#include "copro3.h"
#include "copro1_adapt_slave.h"
#include "copro2_adapt_slave.h"
#include "copro3_adapt_slave.h"
#include "packet_gen.h"
#include "packet_gen_adapt_master.h"
#include "display.h"


SC_MODULE(simple_bus_test)
{

	Packet packet_init1, packet_init2;
	char display_buffer[1024];

	// channels
	sc_clock C1;

	// Signaux entre Gen et Routeur
	sc_signal<bool> next_packet;
	sc_signal<bool> packet_ready;
	sc_signal<Packet*> pkt_RS;

	// Signaux entre adaptateur de coprocesseur 1 et coprocesseur 1
	//A COMPLETER
	sc_signal<Packet*> pkt_RS1;
	sc_signal<bool> ack1;
	sc_signal<bool> ready1;

	// Signaux entre adaptateur de coprocesseur 2 et coprocesseur 2
	sc_fifo<Packet*> fifo;
	sc_signal<bool> ack2;

	// Signaux entre adaptateur de coprocesseur 3 et coprocesseur 3
	//A COMPLETER
	sc_buffer<Packet*> buff3;
	sc_signal<bool> ack3;
	

	// Signaux entre Display et coprocesseurs
	sc_signal<bool, sc_core::SC_MANY_WRITERS> msg_valid;
	sc_signal<char*, sc_core::SC_MANY_WRITERS> display_message;
	sc_signal<Packet*, sc_core::SC_MANY_WRITERS> display_packet;
	sc_signal<bool> display_ready;



	// module instances
	packet_gen              *gen;
	packet_gen_adapt_master *master;
	simple_bus              *bus;
	simple_bus_arbiter      *arbiter;
	copro1                  *mcopro1;
	copro1_adapt_slave      *slave1;
	copro2                  *mcopro2;
	copro2_adapt_slave      *slave2;
	copro3                  *mcopro3;
	copro3_adapt_slave      *slave3;
	display                 *dply;

	//A COMPLETER

	// constructor
	SC_CTOR(simple_bus_test)
		: C1("C1")
	{
		// Espaces tampons (buffers) entre les modules
		display_packet = &packet_init2;
		display_message = display_buffer;
		display_buffer[0] = 0;

		// create instances
		//bus     = new simple_bus("bus",true); // verbose output
		//arbiter = new simple_bus_arbiter("arbiter",true); // verbose output
		bus       = new simple_bus("bus");
		arbiter   = new simple_bus_arbiter("arbiter");
		gen       = new packet_gen("packet_gen");
		mcopro1   = new copro1("copro1");
		mcopro2   = new copro2("copro2");
		dply      = new display("display");

		//A COMPLETER
		master = new packet_gen_adapt_master("master", 1, 0, false, 300);
		slave1 = new copro1_adapt_slave("slave1", 0, 95, 1);
		slave2 = new copro2_adapt_slave("slave2", 96, 191, 1);
		slave3 = new copro3_adapt_slave("slave3", 192, 287, 1);

		// connect instances
		
		bus->clock(C1);
		bus->arbiter_port(*arbiter);

		gen->packet_ready(packet_ready);
		gen->next_packet(next_packet);
		gen->packet_out(pkt_RS);

		master->clock(C1);
		master->pkt_in(pkt_RS);
		master->packet_ready(packet_ready);
		master->next_packet(next_packet);

		mcopro1->packet_out(pkt_RS1);
		mcopro1->ready(ready1);
		mcopro1->ack(ack1);
		mcopro1->msg_valid(msg_valid);
		mcopro1->output_msg(display_message);
		mcopro1->output_pkt(display_packet);
		mcopro1->display_ready(display_ready);

		slave1->clock(C1);
		slave1->pkt_out(pkt_RS1);
		slave1->ready(ready1);
		slave1->ack(ack1);

		mcopro2->fifo_in(fifo);
		mcopro2->ack(ack2);
		mcopro2->msg_valid(msg_valid);
		mcopro2->output_msg(display_message);
		mcopro2->output_pkt(display_packet);
		mcopro2->display_ready(display_ready);

		slave2->clock(C1);
		slave2->fifo_out(fifo);
		slave2->ack(ack2);

		mcopro3->ack(ack3);
		mcopro3->packet_in(buff3);
		mcopro3->msg_valid(msg_valid);
		mcopro3->output_msg(display_message);
		mcopro3->output_pkt(display_packet);
		mcopro3->display_ready(display_ready);

		slave3->clock(C1);
		slave3->pkt_out(buff3);
		slave3->ack(ack3);
		
		dply->msg_valid(msg_valid);
		dply->input_message(display_message);
		dply->input_packet(display_packet);
		dply->display_ready(display_ready);
		

		//A COMPLETER



	}

	// destructor
	~simple_bus_test()
	{
		if (bus) { delete bus; bus = 0; }
		if (arbiter) { delete arbiter; arbiter = 0; }
		if(dply) { delete dply; dply = 0; }
		if (gen) { delete gen; gen = 0; }
		//A COMPLETER
		
	}

}; // end class simple_bus_test

#endif
