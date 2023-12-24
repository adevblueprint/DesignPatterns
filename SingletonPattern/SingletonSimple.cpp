#include <iostream>
#include <thread>
using namespace std;


// Example 1
// Not Thread Safe
// g++ SingletonSimple.cpp -std=c++14  -pthread

class SingletonSimple {
public:
    
     
     /** delete copy and move constructors and assign operators */
     /** Copy construct */
     SingletonSimple(SingletonSimple const&) = delete;
     /** Move construct */
     SingletonSimple(SingletonSimple&&) = delete;
     /** Copy assign */
     SingletonSimple& operator=(SingletonSimple const&) = delete;
     /** Move assign */
     SingletonSimple& operator=(SingletonSimple &&) = delete;



    static SingletonSimple* Instance() {
       
        if(m_instance==nullptr){
            m_instance = new SingletonSimple();
        }
         return m_instance;
    }
    
    void add() { num = num + 1;}
    void print() {std::cout << num << "\n"; }
   
protected:
    static SingletonSimple* m_instance;

private:
    int num ;

    explicit SingletonSimple() : num(0) {};
    ~SingletonSimple() {};
};

SingletonSimple* SingletonSimple::m_instance= nullptr;










void ThreadFoo(){
    // Following code emulates slow initialization.
SingletonSimple* a = SingletonSimple::Instance();

       a->add();
       a->print();

}

void ThreadBar(){
    // Following code emulates slow initialization.
SingletonSimple* a = SingletonSimple::Instance();

       a->add();
       a->print();

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