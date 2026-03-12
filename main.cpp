#include <iostream>
#include <cstring>
#include <string>

class String {
private:
    char* data;
    size_t len;

public:
    
    String(const char* str = "") {
        len = std::strlen(str);
        data = new char[len + 1];
        std::strcpy(data, str);
    }

    String(const std::string& str) {
        len = str.length();
        data = new char[len + 1];
        std::strcpy(data, str.c_str());
    }

    ~String() {
        delete[] data;
    }

    String(const String& other) {
        len = other.len;
        data = new char[len + 1];
        std::strcpy(data, other.data);
    }

    String(String&& other) {
        len = other.len;
        data = other.data; 
        
        other.data = nullptr;
        other.len = 0;
    }

    String& operator=(const String& other) {
        
        if (this != &other) {
            delete[] data; 
            
            len = other.len;
            data = new char[len + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }

    String& operator=(String&& other) {
        if (this != &other) {
            delete[] data; 
            
            len = other.len;
            data = other.data;
            
            other.data = nullptr;
            other.len = 0;
        }
        return *this;
    }

    String& operator+=(const String& other) {
        size_t new_len = len + other.len;
        char* new_data = new char[new_len + 1];
        
        std::strcpy(new_data, data);
        std::strcat(new_data, other.data);
        
        delete[] data; 
        data = new_data; 
        len = new_len;
        
        return *this;
    }

    char& operator[](size_t index) {
        return data[index];
    }
    
    const char& operator[](size_t index) const {
        return data[index];
    }

    explicit operator const char*() const {
        return data;
    }
};

String operator+(const String& lhs, const String& rhs) {
    String result(lhs); 
    result += rhs;      
    return result;      
}

bool operator==(const String& lhs, const String& rhs) {
    return std::strcmp((const char*)lhs, (const char*)rhs) == 0;
}

bool operator!=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}

int main() {
    String s1 = "Code";
    std::string s2 = " STL";
    const char* p = " C-string";

    String r1 = s1 + s2;
    String r2 = s2 + s1;
    String r3 = p + s1;
    String r4 = s1 + p;

    std::cout << "s1+s2: " << (const char*)r1 << '\n';
    std::cout << "s2+s1: " << (const char*)r2 << '\n';
    std::cout << "p+s1:  " << (const char*)r3 << '\n';
    std::cout << "s1+p:  " << (const char*)r4 << '\n';

    s1 += " Program";
    std::cout << "s1 +=: " << (const char*)s1 << '\n';
    std::cout << "s1[0]: " << s1[0] << '\n';
    std::cout << "s1 != r1: " << (s1 != r1) << '\n';

    return 0;
}