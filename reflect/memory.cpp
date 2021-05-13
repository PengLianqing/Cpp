#include <iostream>
#include <memory>

using namespace std;

void test(){
    void* p1 = allocator<int>().allocate(5);
    allocator<int>().deallocate((int*)p1, 5);
}

int main(){
    test();
}