#include <iostream>
#include <mutex>
#include <thread>
#include <memory>

using namespace std;


// Example 2
// Double Checked Locking
// Thread Safe
// g++ SingletonDCL.cpp -std=c++14  -pthread

class SingletonEvenBetter {
public:
    
     
     /** delete copy and move constructors and assign operators */
     /** Copy construct */
     SingletonEvenBetter(SingletonEvenBetter const&) = delete;
     /** Move construct */
     SingletonEvenBetter(SingletonEvenBetter&&) = delete;
     /** Copy assign */
     SingletonEvenBetter& operator=(SingletonEvenBetter const&) = delete;
     /** Move assign */
     SingletonEvenBetter& operator=(SingletonEvenBetter &&) = delete;


    static SingletonEvenBetter& Instance()  {

        std::call_once(create, [&](){m_instance.reset(new SingletonEvenBetter);});
         return *m_instance.get();
    }
    
    void add() { num = num + 1;}
    void print() {std::cout << num << "\n"; }
   
      ~SingletonEvenBetter() {};
protected:
    static unique_ptr<SingletonEvenBetter> m_instance;
    static std::once_flag create;

private:
    int num ;
    explicit SingletonEvenBetter() : num(0) {};
 
};


unique_ptr<SingletonEvenBetter> SingletonEvenBetter::m_instance = nullptr;
std::once_flag SingletonEvenBetter::create;




void ThreadFoo(){
    // Following code emulates slow initialization.
    SingletonEvenBetter& a = SingletonEvenBetter::Instance();

    a.add();
    a.print();
}

void ThreadBar(){
    // Following code emulates slow initialization.
    SingletonEvenBetter& a = SingletonEvenBetter::Instance();

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