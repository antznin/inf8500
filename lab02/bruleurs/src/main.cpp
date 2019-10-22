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
 
  main.cpp -- 
 
  Original Author: Rocco Jonack, Synopsys, Inc.
 
 *****************************************************************************/

/*****************************************************************************
 
  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.
 
      Name, Affiliation, Date:
  Description of Modification:
    
 *****************************************************************************/

#include <systemc.h>
#include "bruleur_random.h"
#include "bruleur_cvg.h"

int sc_main (int, char *[]) {
//  sc_clock         clock;

  crave::init("crave.cfg");
  my_rand_obj obj1;
  fcov_bruleur obj2;

  crave::set_global_seed(12345);

//  for (int i = 0; i < 50; i++) {
 while(obj2.get_inst_coverage() < 81.25) {  // (100% de thermostat + 100% bruleurs + 100 valve + 25% de cross)/4 = 81.25
  CHECK(obj1.next());
    obj2.sample(obj1.thermo_value(), obj1.bruleur_value(), obj1.valve_value());
    std::cout << obj1 << std::endl;
  };

  fc4sc::global::coverage_save("coverage_results.xml");
  std::cout << "nombre d'execution requise pour 81.25%: " <<  obj2.nb_de_cov << std::endl;
  
  return 0;
}

