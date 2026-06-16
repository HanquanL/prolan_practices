#include <iostream>
#include <stdlib.h>

class Myclass{
    int _mymember;

    public:
        Myclass(){
            std::cout << "constructor is called\n";
        }

        ~Myclass(){
            std::cout << "destructor is called\n";
        }

        void *operator new(size_t size){
            std::cout << "new: allocating " << size << "bytes of memory" << std::endl;
            void *p = malloc(size);

            return p;
        }

        void operator delete(void *p){
            std::cout << "delete: Memory is freed again " << std::endl;
            free(p);
        }
};

int main(){
    Myclass *p = new Myclass();
    delete p;
}