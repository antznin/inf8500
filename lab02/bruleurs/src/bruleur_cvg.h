/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
  more contributor license agreements.  See the NOTICE file distributed
  with this work for additional information regarding copyright ownership.
  Accellera licenses this file to you under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with the
  License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
  implied.  See the License for the specific language governing
  permissions and limitations under the License.

 *****************************************************************************/

/*****************************************************************************
 
  stimulus.h -- 
 
  Original Author: Rocco Jonack, Synopsys, Inc.
 
 *****************************************************************************/

 /*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here. 
      Name, Affiliation: Teodor Vasilache and Dragos Dospinescu,
                         AMIQ Consulting s.r.l. (contributors@amiq.com)
                   Date: 2018-Feb-20

  Description of Modification: Included the FC4SC library, created and 
  instantiated a covergroup for collecting stimulus data coverage.

  	  	  	  	   Date: 2018-Sep-24

  Description of Modification: Updated the instantiation of the coverpoints
  to use the new COVERPOINT macro.
            
 *****************************************************************************/

/*****************************************************************************
 
  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.
 
      Name, Affiliation, Date:
  Description of Modification:
    
 *****************************************************************************/

#include "fc4sc.hpp"

//SC_MODULE(m_coverture_bruleur) {
//
//  sc_out<bool> thermostat;
//  sc_out<bool> bruleur;   
//  sc_out<int>  valve;
//  sc_out<int>  nb_de_cov;  
//  sc_in<int> CLK;

  class fcov_bruleur : public covergroup {

  public:

    int thermostat = 0;
    int bruleur = 0;
    int valve = 0;
    int nb_de_cov = 0;

    // Must call parent constructor somewhere register a new cvg
    CG_CONS(fcov_bruleur) {
    }

    void  sample(int thermostat, int bruleur , int valve) {

      this->thermostat = thermostat;
      this->bruleur = bruleur;
      this->valve = valve;
      covergroup::sample();
      nb_de_cov += 1;

    }

    COVERPOINT(int, thermostat_cvp, thermostat) {
        bin<int>("200 deg", 200),
        bin<int>("300 deg", 300),
        bin<int>("400 deg", 400),
        bin<int>("500 deg", 500),
        bin<int>("600 deg", 600),
        bin<int>("700 deg", 700),
        bin<int>("800 deg", 800),
    };

    COVERPOINT(int, bruleur_cvp, bruleur) {
        bin<int>("3 brul", 3),
        bin<int>("4 brul", 4),
        bin<int>("5 brul", 5),
        bin<int>("6 brul", 6),
    };

    COVERPOINT(int, valve_cvp, valve) {
        bin<int>("valve ouverte", 1),
        bin<int>("valve fermee", 0)
    };

    cross<int, int, int> reset_valid_cross = cross<int, int, int> (this, "croissement de 3 parametres",
        &valve_cvp,
        &bruleur_cvp,
        &thermostat_cvp
    );

  };

 // fcov_bruleur cg_bruleur;

 // SC_CTOR(m_coverture_bruleur)
 // {
 //     SC_METHOD(entry);
 //     dont_initialize();
 //     sensitive << CLK.pos();
 // }  
//};

