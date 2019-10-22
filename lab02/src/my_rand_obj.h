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

enum copro_enum { copro1, copro2, copro3 };
CRAVE_ENUM(copro_enum, (copro1)(copro2)(copro3));

enum sort_dir_enum { down, up };
CRAVE_ENUM(sort_dir_enum, (down)(up));

enum data_order_enum { random_desc, random_asc, random_full, continues_asc, continues_desc};
CRAVE_ENUM(data_order_enum, (random_desc)(random_asc)(random_full) (continues_asc) (continues_desc));

class my_rand_obj : public rand_obj {
 public:
  randv<copro_enum> 		copro;
  randv<sort_dir_enum> 		sort_dir;
  randv<data_order_enum> 	data_order;
  randv<unsigned int> 		address;
  int 				offset=19*4+1;  // nombre d'octets dans un mot+ 1		

  my_rand_obj(rand_obj* parent = 0) : rand_obj(parent), copro(this), sort_dir(this), data_order(this), address(this) {
    constraint( if_then(copro() == copro1 , address() >= 0 && address() <= 255-offset));
    constraint(if_then(copro() == copro2 , address() >= 256 && address() <= 511-offset));
    constraint(if_then(copro() == copro3 , address() >= 512 && address() <= 767-offset));
    constraint(dist(address(), distribution <unsigned int>::create(weighted_range<unsigned int>(0, 255-offset,50))
			             (weighted_range<unsigned int>(256, 511-offset,25))
		                     (weighted_range<unsigned int>(512, 767-offset,25)))); 
  }


  friend ostream& operator<<(ostream& os, my_rand_obj& obj) {
    switch (obj.copro) {
      case copro1:
        os << "copro1";
        break;
      case copro2:
        os << "copro2";
        break;
      case copro3:
        os << "copro3";
        break;
      default:
        os << "UNKNOWN(" << obj.copro << ")";
    }
	
	    os << " ";
    switch (obj.sort_dir) {
      case down:
        os << "down";
        break;
      case up:
        os << "up";
        break;
      default:
        os << "UNKNOWN(" << obj.sort_dir << ")";
    }
	
    os << " ";
    switch (obj.data_order) {
      case random_desc:
        os << "random_desc";
        break;
      case random_asc:
        os << "random_asc";
        break;
      case random_full:
        os << "random_full";
        break;
      case continues_asc:
        os << "continues_asc";
        break;
     case continues_desc:
        os << "continues_desc";
        break;
      default:
        os << "UNKNOWN(" << obj.data_order << ")";
    }

    os << " ";
    os << obj.address;
    return os;
  }
};

// Le main a servi pour faire le test du code
int main(int argc, char* argv[]) {
  crave::init("crave.cfg");
  my_rand_obj obj;
  for (int i = 0; i < 50; i++) {
    CHECK(obj.next());
    std::cout << obj << std::endl;
  };

  return 0;
}