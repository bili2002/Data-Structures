#include "utility.h"
#include "shared_pointer.h"
#include <iostream> 
#include <vector> 

using namespace std;

int main() {
    int* a = new int(2);
    {
    WeakPointer_<int> wk;

    {
    SharedPointer_<int> sh = SharedPointer_<int>(a);
    {
    SharedPointer_<int> sh2 = SharedPointer_<int>(sh);
    cout<<(*sh)<<endl;
    cout<<(*a)<<endl;
    
    cout<<sh._get_count()<<endl;

    }
    cout<<(*sh)<<endl;

    cout<<(*a)<<endl;

    {
    vector<SharedPointer_<int>> v;
    v.push_back(sh);
    cout<<(*a)<<endl;
    v.pop_back();

    }

    wk = WeakPointer_(sh);
    cout<<wk.expired()<<endl;
    SharedPointer_<int> sh5 = wk.lock();
    }    
    cout<<wk.expired()<<endl;
    }


    cout<<(*a)<<endl;
    return 0;
}