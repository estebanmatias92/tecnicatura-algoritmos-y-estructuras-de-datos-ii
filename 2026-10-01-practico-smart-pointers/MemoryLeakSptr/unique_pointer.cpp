// TOPiC: Unique Pointer

//NOTES:
//0. unique_ptr is a Class template
//1. unique_ptr in one of the smart pointer provided by c++11 to prevent memory leacks.
//2. unique_ptr wraps a raw pointre in it, and de-alocates the raw pointer.
//   when unique_ptr obect goes out fo scope
//3. similar to actual pointers we can use -> and * on the object of unique_ptr,
//   because it is overloaded in unique_ptr class.
//4. when exception comes then also it will de-allocate the memoryhence no memory leck.
//5. Not only object we can create array of object of unique_ptr

// OPERATION// release, reset, swap, get, get_deleter

//PRoGRAM.

#include <iostream>
#include <memory>
using namespace std;

class Foo{
int x;
public:
    explicit Foo(int x): x{x} {cout << "call explicit constructor!" << endl;}
    
    int getX(){return x;}
   //Foo(){cout << "call constructor!" << endl;}
   ~Foo(){cout << "call destructor!" << endl;}
};


int main(){

// 1. Simple Class
//Foo *f = new Foo(18);
//cout << f->getX() << endl;
//delete f;

// 2. unique_ptr in action
//std::unique_ptr<Foo> p(new Foo(218));
//cout << p->getX() << endl;	

// 3. unique_ptr copy

	std::unique_ptr<Foo> p1(new Foo(18));
	
	std::unique_ptr<Foo> p2 = make_unique<Foo>(20);	
    // make_unique teaches users "never say new/delete and new[]/delete[]" without disclaimers.
    // make_unique is carefully implemented for exception safety 
    //and is recommended over directly calling unique_ptr constructors.
    cout << p1->getX() << endl; 
    cout << (*p2).getX() << endl; 
    p1 = p3 ;  //Fail not copy ownership
    
    unique_ptr<Foo> p3= std::move(p1);
    Foo* p = p3.get();
    // get() Returns a pointer to the managed object or nullptr if no object is owned.
    cout << "Release P3" << endl;
    Foo* p4 = p3.release();
    // Releases ownership of its stored pointer
    //release is used to release ownership of the managed object without deleting it:
    cout << "Reset P2" << endl;
    p2.reset(p4);
    // To delete the object, use reset.
    cout << p2->getX() << endl;


return 0;

}

// Run time
// 
// std::unique_ptr::reset
// If p is a null pointer (such as a default-initialized pointer), 
// the unique_ptr becomes empty, managing no object after the call. 
// To release the ownership of the stored pointer without destroying
// it, use member function release instead.

// std::unique_ptr::release
// Releases ownership of its stored pointer, by returning its value 
// and replacing it with a null pointer. This call does not destroy 
// the managed object, but the unique_ptr object is released from 
// the responsibility of deleting the object.


