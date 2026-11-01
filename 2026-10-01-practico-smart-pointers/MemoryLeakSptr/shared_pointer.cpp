// TOPiC: Shared Pointer

//NOTES:
//0. shared_ptr is a Class template, is a smart pointer can share ownership of object (managed object).
//1. Several shared ptr can point to the same object (managed object).
//2. it keep a reference count to maintein and how many shared ptr are pointing to the same object.
//   and once last shared_ptr goes out of scope then the managed object gets deelted.
//3. shared_ptr is "threads safe" and not thread safe, whas is this?
//   a. Control block is thread safe
//   b. managed object not.
//4. There are three ways shared_ptr will distroy managed object.
//   a. if the last shared_ptr goes out of scope
//   b. if you initialize shared_ptr with some other shared_ptr
//   c. if you reset the shared_ptr
//5. Reference cout doesn´t work when we use reference or pointer of shared_ptr




//PRoGRAM.

#include <iostream>
#include <memory>
using namespace std;

class Foo{
int x;
public:
   explicit Foo(int x): x{x} {}
   int getX(){return x;}
   ~Foo(){cout << "call destructor!" << endl;}
};


int main(){

// 1. Forma Tradicional
//Foo *f = new Foo(18);
//cout << f->getX() << endl;
//delete f;


// 2. use Shared_Ptr
std::shared_ptr <Foo> sp(new Foo(100));
cout << sp->getX() << endl;
cout << sp.use_count() << endl;
// 3 . shared other shared_ptr
std::shared_ptr<Foo> sp1 = sp ;

// 4. now by Reference & and call Destructor
// Make copy by value and do not increment the cout of reference.
//std::shared_ptr<Foo> *sp1 = &sp ;
cout << sp.use_count() << endl;
cout << sp1.use_count() << endl;
cout << sp1->getX() << endl;

return 0;
}