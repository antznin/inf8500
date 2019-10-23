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

class input_cvg : public covergroup
{

public:
  int copro;
  int data_order;
  int sort_dir;
  int nb_de_cov = 0;
  //rand enum {random_desc, random_asc, random_full, continues_asc, continues_desc} data_order;
  //rand enum {up, down} sort_dir;

  // Must call parent constructor somewhere register a new cvg
  CG_CONS(input_cvg)
  {
  }

  void sample(int copro, int data_order, int sort_dir)
  {

    this->copro = copro;
    this->data_order = data_order;
    this->sort_dir = sort_dir;
    covergroup::sample();
    nb_de_cov += 1;
  }

  COVERPOINT(int, copro_cvp, copro){
      bin<int>("copro 1", 0),
      bin<int>("copro 2", 1),
      bin<int>("copro 3", 2),
  };

  COVERPOINT(int, data_order_cvp, data_order){
      bin<int>("random_desc", 0),
      bin<int>("random_asc", 1),
      bin<int>("random_full", 2),
      bin<int>("continues_asc", 3),
      bin<int>("continues_desc", 4),
  };

  COVERPOINT(int, sort_dir_cvp, sort_dir){
      bin<int>("up", 1),
      bin<int>("down", 0)};

  cross<int, int, int> reset_valid_cross = cross<int, int, int>(this, "Croisement des 3 parametres",
                                                                &copro_cvp,
                                                                &data_order_cvp,
                                                                &sort_dir_cvp);
};

// fcov_bruleur cg_bruleur;

// SC_CTOR(m_coverture_bruleur)
// {
//     SC_METHOD(entry);
//     dont_initialize();
//     sensitive << CLK.pos();
// }
//};
