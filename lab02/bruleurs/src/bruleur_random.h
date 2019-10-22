#include <crave/ConstrainedRandom.hpp>

#include <iostream>

using std::ostream;

using crave::rand_obj;
using crave::randv;
using crave::if_then_else;
using crave::if_then;
using crave::inside;
using crave::range;
using crave::weighted_range;
using crave::dist;
using crave::distribution;

// Requis:
// Bruleurs		Thermostat  		Valve				Nombre de points
//   3 a 4		200 & 300		ouverte (valeur 1)		4 points a couvrir
//   3 a 4		400			fermee ou ouverte		4 points a couvrir
//   5			500			fermee ou ouverte		2 points a couvrir
//   6			600			fermee ou ouverte		2 points a couvrir
//   6			700 & 800		fermee 	(valeur 0)		2 points a couvrir
//										total:14 points de couverture requises
//										14 points sur 56 points possibles = 25%

class my_rand_obj : public rand_obj {
 public:
  randv<int> 		bruleur;
  randv<int> 		thermostat;
  randv<int> 		valve;
	
  my_rand_obj(rand_obj* parent = 0) : rand_obj(parent), bruleur(this), thermostat(this), valve(this) {
	int bruleurs [] = { 3, 4, 5, 6 };
	constraint(inside(bruleur(), bruleurs));
	int thermostats [] = { 200, 300, 400, 500, 600, 700, 800 };
	constraint(inside(thermostat(), thermostats));
	int valves [] = { 0, 1 };	
	constraint(inside(valve(), valves));
    	constraint( if_then(thermostat() == 200 || thermostat() == 300, valve() != 0 && bruleur() < 5)); 
	constraint( if_then(thermostat() == 400, bruleur() < 5));
	constraint( if_then(thermostat() == 500, 4 < bruleur() && bruleur() < 6));
	constraint( if_then(thermostat() == 600, bruleur() > 5));
	constraint( if_then(thermostat() == 700 || thermostat() == 800, valve() != 1  && bruleur() > 5));
  };

  unsigned int thermo_value() { 
      return (thermostat);
  };
  
  unsigned int bruleur_value() { 
      return (bruleur);
  };
  
  unsigned int valve_value() { 
      return (valve);
  };


  friend ostream& operator<<(ostream& os, my_rand_obj& obj) {

    os << " ";
    os << obj.thermostat;
	
	os << " ";
    os << obj.bruleur;
	
	os << " ";
    os << obj.valve;
	
    return os;
	
  }
};

// Le main a servi pour faire le test du code
//int main(int argc, char* argv[]) {
//  crave::init("crave.cfg");
//  my_rand_obj obj;
//  for (int i = 0; i < 50; i++) {
//    CHECK(obj.next());
//    std::cout << obj << std::endl;
//  };
//
//  return 0;
//}
