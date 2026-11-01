// TOPiC: Shared Pointer

//NOTES:
//0. shared_ptr is a Class template, is a smart pointer can share ownership of object (managed object).
//1. Several shared ptr can point to the same object (managed object).
//2. it keep a reference count to maintein and how many shared ptr are pointing to the same object.
//   and once last shared_ptr goes out of scope then the managed object gets deelted.
//3. shared_ptr is "threads safe" and not thread sabe, whas is this?
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
#include<thread>
#include<mutex>
using namespace std;

class Foo{
int x;
public:
   explicit Foo(int x): x{x} {}
   int getX(){return x;}
   ~Foo(){cout << "call destructor!" << endl;}
};


void fun(std::shared_ptr<Foo> sp, int count){
  static std::mutex m1;
  std::lock_guard<std::mutex> loc(m1);
  cout << "Thread: " << count << " Count SP: " << sp.use_count() << endl;
}

int main(){

std::shared_ptr<Foo> sp(new Foo(100));
thread t1(fun,sp,1), t2(fun,sp,2), t3(fun,sp,3);
cout << "Main:" << sp.use_count() << endl;
t1.join();t2.join();t3.join();

return 0;
}