#include <iostream>
#include <string>
#include "Sequence.h"

int main() {
    
    Sequence<int, Array> s1;
    for(int i=1; i<=6; ++i) s1.append(i*10);
    
    std::cout << "Array Size: " << s1.size() << " Capacity: " << s1.capacity() << "\n";
    std::cout << "Contains 30: " << (s1.contains(30) ? "Yes" : "No") << "\n";
    s1.remove(30);
    std::cout << "After remove 30, size: " << s1.size() << "\n\n";

    Sequence<int, ForwardList> s2;
    for(int i=1; i<=6; ++i) s2.append(i*10);
    
    std::cout << "List Size: " << s2.size() << "\n";
    std::cout << "Contains 30: " << (s2.contains(30) ? "Yes" : "No") << "\n";
    s2.remove(30);
    std::cout << "After remove 30, size: " << s2.size() << "\n\n";

    Sequence<std::string, Array> s3;
    s3.append("Hello");
    std::cout << "String test: " << (s3.contains("Hello") ? "Found" : "Not found") << "\n";

    return 0;
}