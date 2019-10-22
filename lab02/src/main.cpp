/*
 * main.cpp
 *
 *  Created on: 26-Dec-2014
 *      Author: Gaurav Maheshwari
 *      Modifié par Guy Bois en septembre 2019
 *      Ce fichier a servi a teste testcase.h
 */    
#include "include.h"
#include "BubbleSort.h"
#include "testcase.h"
#include "Scoreboard.h"
#include "assertlib.h"
//template <class TypeA> class cBubbleSort;
using namespace DS;


int main( int argc , char *argv[])
{
  unsigned int seed = atoi(argv[1]);
  crave::init("crave.cfg");
  std::cout<<"Guy Start "<<std::endl;
  crave::set_global_seed(seed);
  randv<int> x = NULL;
   
  int	iarray[MAX];
  int * ptr_int ;
  bool direction = true;

  ScoreBoard scb;
  string str = argv[2];
  int arg_val=argc;
  TestBase * test;
  test = new TestBase;
  test->chk_testcase(argc,str);
  ptr_int= test->p;
  direction = test->direction;
  for(int i = 0;i<MAX;i++)
   {
     iarray[i] = *(ptr_int+i);
   }
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////

  

	cBubbleSort<int> cb(iarray, MAX);
  std::cout<<"Passed Int Array "<<std::endl;
	cb.print();
  int *ptr_int_r;// = cb.get_pointer_to_sorted_array();
	cb.doSort(direction);
  std::cout<<"Ascend(1)*/Desc(0)* Order "<<direction<<std::endl;
	cb.print();
  ptr_int_r = cb.get_pointer_to_sorted_array();
  scb.check_int(ptr_int_r ,ptr_int,direction);

}



