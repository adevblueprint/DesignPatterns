#include <iostream>
#include <mutex>
#include <thread>
#include <memory>

using namespace std;


// Example 2
// Double Checked Locking
// Thread Safe
// g++ SingletonBest.cpp -std=c++14  -pthread

class SingletonBest {
public:
    
     
     /** delete copy and move constructors and assign operators */
     /** Copy construct */
     SingletonBest(SingletonBest const&) = delete;
     /** Move construct */
     SingletonBest(SingletonBest&&) = delete;
     /** Copy assign */
     SingletonBest& operator=(SingletonBest const&) = delete;
     /** Move assign */
     SingletonBest& operator=(SingletonBest &&) = delete;


    static SingletonBest& Instance()  {
        static SingletonBest singleton;
        return singleton;
    }
    
    void add() { num = num + 1;}
    void print() {std::cout << num << "\n"; }
   
      ~SingletonBest() {};

private:
    int num ;
    explicit SingletonBest() : num(0) {};
 
};



void ThreadFoo(){
    // Following code emulates slow initialization.
    SingletonBest& a = SingletonBest::Instance();

    a.add();
    a.print();
}

void ThreadBar(){
    // Following code emulates slow initialization.
    SingletonBest& a = SingletonBest::Instance();

    a.add();
    a.print();

}


int main()
{
    std::cout <<"If you see the diffent value, then singleton was reused (yay!\n" <<
                "If you see same values, then 2 singletons were created (no!!)\n\n" <<
                "RESULT:\n";   
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();

    return 0;
}