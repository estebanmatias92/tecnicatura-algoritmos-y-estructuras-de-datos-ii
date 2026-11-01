#include <iostream>
#include <memory>
using namespace std;

struct Son;
struct Daughter;
struct Mother;

struct Mother{
  ~Mother(){
  	std::cout << "Mother is Gone!" << std::endl;
  }
 void setSon(const std::shared_ptr<Son> s){
  mySon=s;
}

void setDaughter(const std::shared_ptr<Daughter> d){
  myDaughter=d;
}
std::weak_ptr<Son> mySon;
std::weak_ptr<Daughter> myDaughter;
};


struct Son{
	Son(std::shared_ptr<Mother> m):myMother(m){}
	~Son(){
		std::cout << "Son gone!" << std::endl; 
	}
	std::shared_ptr<const Mother> myMother;
};


struct  Daughter{

	Daughter(std::shared_ptr<Mother> m):myMother(m){}
	~Daughter(){
		std::cout << "Daughter gone!" << std::endl; 
	}
	std::shared_ptr<const Mother> myMother;
};




int main(int argc, char const *argv[])
{
	std::cout << std::endl;
	{

		std::shared_ptr<Mother> mother= std::shared_ptr<Mother>(new Mother);
		std::shared_ptr<Son> son = std::shared_ptr<Son>(new Son(mother));
		std::shared_ptr<Daughter> daughter= std::shared_ptr<Daughter>(new Daughter(mother));
		mother->setSon(son);
		mother->setDaughter(daughter);
	}
	std::cout << std::endl;

	return 0;
}