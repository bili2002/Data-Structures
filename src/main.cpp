#include "SharedPointer.h"
#include <iostream> 
#include <vector> 

using namespace std;

int main() {
    int* a = new int(2);
    SharedPointer<int> sh = SharedPointer<int>(a);
    SharedPointer<int> sh2 = SharedPointer<int>(sh);
    shared_ptr<int> sh = shared_ptr<int>(new int(2)); 
    cout<<(*sh)<<endl;
    cout<<(*a)<<endl;
    
    sh.~SharedPointer();    
    cout<<(*sh2)<<endl;

    cout<<(*a)<<endl;

    vector<SharedPointer<int>> v;
    v.push_back(sh2);
    sh2.~SharedPointer();    
    cout<<(*a)<<endl;

    v.pop_back();
    cout<<(*a)<<endl;
    return 0;
}