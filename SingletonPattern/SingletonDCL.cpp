#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>

using namespace std;


// Example 2
// Double Checked Locking
// Thread Safe
// g++ SingletonDCL.cpp -std=c++14  -pthread

class SingletonDCL {
public:
    
     
     /** delete copy and move constructors and assign operators */
     /** Copy construct */
     SingletonDCL(SingletonDCL const&) = delete;
     /** Move construct */
     SingletonDCL(SingletonDCL&&) = delete;
     /** Copy assign */
     SingletonDCL& operator=(SingletonDCL const&) = delete;
     /** Move assign */
     SingletonDCL& operator=(SingletonDCL &&) = delete;



    static SingletonDCL* Instance() {
       
        if(m_instance==nullptr){
            lock_guard<mutex> lock(m_lock);
            if(m_instance==nullptr){
                m_instance = new SingletonDCL();
            }
        }
         return m_instance;
    }
    
    void add() { num = num + 1;}
    void print() {std::cout << num << "\n"; }
   
protected:
    static atomic<SingletonDCL*> m_instance;
    static mutex m_lock;

private:
    int num ;
    explicit SingletonDCL() : num(0) {};
    ~SingletonDCL() {};
};

atomic<SingletonDCL*> SingletonDCL::m_instance { nullptr };
std::mutex SingletonDCL::m_lock;










void ThreadFoo(){
    // Following code emulates slow initialization.
    SingletonDCL* a = SingletonDCL::Instance();

    a->add();
    a->print();

}

void ThreadBar(){
    // Following code emulates slow initialization.
    SingletonDCL* a = SingletonDCL::Instance();

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