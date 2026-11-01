#include <iostream>
#include <memory>


class Mother{

std::weak_ptr<class Son> mySon;
std::weak_ptr<class Daughter> myDaughter;

public:
  ~Mother(){
  	std::cout << "Mother is Gone!" << std::endl;
  }
 void setSon(const std::shared_ptr<Son> s){
  mySon=s;
}

void setDaughter(const std::shared_ptr<Daughter> d){
  myDaughter=d;
}


};

class Son{
	public:
	Son(std::shared_ptr<Mother> m):myMother(m){}
	~Son(){
		std::cout << "Son gone!" << std::endl; 
	}
	std::shared_ptr<const Mother> myMother;
};


class  Daughter{
	public:
	Daughter(std::shared_ptr<Mother> m):myMother(m){}
	~Daughter(){
		std::cout << "Daughter gone!" << std::endl; 
	}
	std::shared_ptr<const Mother> myMother;
};


main(int argc, char const *argv[])
{
	std::cout << std::endl;
	{

		//std::shared_ptr<Mother> mother= std::shared_ptr<Mother>(new Mother);
		// No more New/Delete/Raw Pointer Modern c++
		std::shared_ptr<Mother> mother= std::make_shared<Mother>();
		std::shared_ptr<int> foo = std::make_shared<int> (10);
		std::shared_ptr<Son> son = std::shared_ptr<Son>(new Son(mother));
		std::shared_ptr<Daughter> daughter= std::shared_ptr<Daughter>(new Daughter(mother));
		mother->setSon(son);
		mother->setDaughter(daughter);
		std::cout << "*foo: " << *foo << '\n';
	}
	std::cout << std::endl;

  
	return 0;
}