#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

template <typename T>
class Array {
private:
    T* data;           
    size_t m_size;     
    size_t m_capacity; 

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity]; 
        for (size_t i = 0; i < m_size; ++i) {
            new_data[i] = data[i];         
        }
        delete[] data;                     
        data = new_data;                   
        m_capacity = new_capacity;
    }

public:

    T* get_raw_ptr() const { return data; } // 2.
    
    Array() : data(nullptr), m_size(0), m_capacity(0) {}

    ~Array() {
        delete[] data;
    }

    Array(const Array& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        data = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            data[i] = other.data[i];
        }
    }

    Array(Array&& other) noexcept : data(other.data), m_size(other.m_size), m_capacity(other.m_capacity) {
        other.data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Array& operator=(const Array& other) {
        if (this != &other) { 
            delete[] data;    
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            data = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data; 
            data = other.data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    size_t size() const { return m_size; }
    
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    void insert_at(size_t index, const T& value) {
        if (m_size == m_capacity) { 
            reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        
        for (size_t i = m_size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++m_size;
    }

    void remove_at(size_t index) {
        for (size_t i = index; i < m_size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --m_size;
    }
};

template <typename T>
class Dictionary {
private:
    Array<T> arr; 

public:

    // ________________ TASK 2 START ________________

    class Iterator {
    private:
        T* ptr; 
    public:
        Iterator(T* p) : ptr(p) {}

        T& operator*() { 
            return *ptr; 
        }
        
        Iterator& operator++() { 
            ptr++; 
            return *this; 
        }
        
        bool operator!=(const Iterator& other) const { 
            return ptr != other.ptr; 
        }
    };

    Iterator begin() { 
        return Iterator(arr.get_raw_ptr()); 
    }
    
    Iterator end() { 
        return Iterator(arr.get_raw_ptr() + arr.size()); 
    }

    bool operator==(const Dictionary& other) const {
        if (arr.size() != other.arr.size()) {
            return false;
        }
        for (size_t i = 0; i < arr.size(); ++i) {
            if (!(arr[i] == other.arr[i])) {
                return false;
            }
        }
        return true;
    }
    
    // ________________ TASK 2 END ________________

    Dictionary() = default;
    Dictionary(const Dictionary& other) : arr(other.arr) {}
    Dictionary(Dictionary&& other) noexcept : arr(std::move(other.arr)) {}
    Dictionary& operator=(const Dictionary& other) { arr = other.arr; return *this; }
    Dictionary& operator=(Dictionary&& other) noexcept { arr = std::move(other.arr); return *this; }
    ~Dictionary() = default;

    bool contain(const T& value) const {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == value) {
                return true;
            }
        }
        return false;
    }

    void insert(const T& value) {
        if (contain(value)) {
            return; 
        }

        size_t pos = 0;
        while (pos < arr.size() && arr[pos] < value) {
            pos++; 
        }
        
        arr.insert_at(pos, value); 
    }

    void remove(const T& value) {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == value) {
                arr.remove_at(i);
                return; 
            }
        }
    }

    void print() const {
        std::cout << "[ ";
        for (size_t i = 0; i < arr.size(); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "]\n";
    }

    // ________________ TASK 3 START ________________

    Dictionary operator+(const Dictionary& other) const {
        Dictionary result;
        
        for (size_t i = 0; i < arr.size(); ++i) {
            result.insert(arr[i]); 
        }
        
        for (size_t i = 0; i < other.arr.size(); ++i) {
            result.insert(other.arr[i]);
        }
        
        return result;
    }

    Dictionary operator*(const Dictionary& other) const {
        Dictionary result;
        
        for (size_t i = 0; i < arr.size(); ++i) {

            if (other.contain(arr[i])) {
                result.insert(arr[i]);
            }
        }
        
        return result;
    }

    // ________________ TASK 3 END ________________
    
    size_t size() const { return arr.size(); }

};

// ________________ TASK 4 START ________________

template <typename T>
void copy(Dictionary<T>& dst, const Dictionary<T>& src) {
    dst = src; 
}

template <typename T>
void merge_into(Dictionary<T>& dst, Dictionary<T>&& src) {
    
    dst = dst + src;
    src = Dictionary<T>(); 
}

// ________________ TASK 4 END ________________

// ________________ TASK 7 START ________________

template <std::size_t N>
class Word {
private:
    char buffer[N];

public:
    
    Word() {
        buffer[0] = '\0';
    }

    Word(const std::string& str) {
        std::strncpy(buffer, str.c_str(), N - 1);
        buffer[N - 1] = '\0'; 
    }

    Word(const char* str) {
        std::strncpy(buffer, str, N - 1);
        buffer[N - 1] = '\0';
    }

    bool operator==(const Word& other) const {
        return std::strcmp(buffer, other.buffer) == 0;
    }

    bool operator<(const Word& other) const {
        return std::strcmp(buffer, other.buffer) < 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Word& w) {
        os << w.buffer;
        return os;
    }
};

// ________________ TASK 7 END ________________


int main() {
    
    // 1. ________________________

    std::cout << "\n___ Task 1 ___\n";

    Dictionary<int> dict;
    
    dict.insert(10);
    dict.insert(5);
    dict.insert(20);
    dict.insert(1);
    
    std::cout << "After insertion (should be sorted): ";
    dict.print(); // [ 1 5 10 20 ]

    dict.insert(10); 
    dict.insert(5);
    std::cout << "After attempting to duplicate: ";
    dict.print(); // [ 1 5 10 20 ]

    dict.remove(5);
    std::cout << "After removing 5: ";
    dict.print(); // [ 1 10 20 ]

    std::cout << "10? " << (dict.contain(10) ? "Yes" : "No") << "\n";
    std::cout << "5? " << (dict.contain(5) ? "Yes" : "No") << "\n";

    // 2. ________________________

    std::cout << "\n___ Task 2 ___\n";

    Dictionary<int> dict1;
    Dictionary<int> dict2;

    dict1.insert(10);
    dict1.insert(5);
    dict1.insert(20);

    dict2.insert(20);
    dict2.insert(5);
    dict2.insert(10);

    
    std::cout << "Elements in dict1: ";
    for (Dictionary<int>::Iterator it = dict1.begin(); it != dict1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    
    if (dict1 == dict2) {
        std::cout << "Comparison: dict1 and dict2 are EQUAL\n";
    } else {
        std::cout << "Comparison: dict1 and dict2 are NOT EQUAL\n";
    }

    dict2.remove(10);
    
    if (dict1 == dict2) {
        std::cout << "After remove: dict1 and dict2 are EQUAL\n";
    } else {
        std::cout << "After remove: dict1 and dict2 are NOT EQUAL\n";
    }

    // 3. ________________________

    std::cout << "\n___ Task 3 ___\n";
    
    Dictionary<int> dict3;
    Dictionary<int> dict4;

    dict3.insert(1); 
    dict3.insert(2); 
    dict3.insert(3);
    
    dict4.insert(2); 
    dict4.insert(3); 
    dict4.insert(4);

    std::cout << "dict3: ";
    for (Dictionary<int>::Iterator it = dict3.begin(); it != dict3.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "dict4: ";
    for (Dictionary<int>::Iterator it = dict4.begin(); it != dict4.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    // [ 1, 2, 3, 4 ]
    Dictionary<int> dict_Union = dict3 + dict4;
    std::cout << "Union (+): ";
    for (Dictionary<int>::Iterator it = dict_Union.begin(); it != dict_Union.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // [ 2, 3 ]
    Dictionary<int> dict_Intersection = dict3 * dict4;
    std::cout << "Intersection (*): ";
    for (Dictionary<int>::Iterator it = dict_Intersection.begin(); it != dict_Intersection.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // 4. ________________________

    std::cout << "\n___ Task 4 ___\n";
    
    Dictionary<int> dict5;
    dict5.insert(100);
    dict5.insert(200);

    Dictionary<int> dict6; 
    
    copy(dict6, dict5); 
    
    std::cout << "After copy(dict6, dict5), dict6 contains: ";
    for (Dictionary<int>::Iterator it = dict6.begin(); it != dict6.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    Dictionary<int> dict7;
    dict7.insert(1);
    dict7.insert(2);

    Dictionary<int> dict8;
    dict8.insert(2);
    dict8.insert(3);

    std::cout << "Before merge_into:\n";
    std::cout << "dict7 (dst): ";
    for (Dictionary<int>::Iterator it = dict7.begin(); it != dict7.end(); ++it) std::cout << *it << " ";
    std::cout << "\ndict8 (src): ";
    for (Dictionary<int>::Iterator it = dict8.begin(); it != dict8.end(); ++it) std::cout << *it << " ";
    std::cout << "\n";

    merge_into(dict7, std::move(dict8));

    std::cout << "\nAfter merge_into(dict7, std::move(dict8)):\n";
    std::cout << "dict7 (dst): ";
    for (Dictionary<int>::Iterator it = dict7.begin(); it != dict7.end(); ++it) std::cout << *it << " ";
    std::cout << "\ndict8 (src): ";
    for (Dictionary<int>::Iterator it = dict8.begin(); it != dict8.end(); ++it) std::cout << *it << " ";
    std::cout << "<- (should be completely empty)\n";

    // 5. ________________________

    std::cout << "\n___ Task 5 ___\n";

    std::string text = "Lorem ipsum dolor sit amet consectetuer adipiscing elit Maecenas porttitor congue massa Fusce posuere magna sed pulvinar ultricies purus lectus malesuada libero sit amet commodo magna eros quis urna Nunc viverra imperdiet enim Fusce est Vivamus a tellus Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas Proin pharetra nonummy pede Mauris et orci Aenean nec lorem In porttitor Donec laoreet nonummy augu Suspendisse dui purus scelerisque at vulputate vitae pretium mattis nunc Mauris eget neque at sem venenatis eleifend Ut nonummy Fusce aliquet pede non pede Suspendisse dapibus lorem pellentesque magna Integer nulla Donec blandit ";

    Dictionary<std::string> string_Dict;

    std::stringstream ss(text);
    std::string word;
    int word_Count = 0; 

    while (ss >> word) {
        string_Dict.insert(word); 
        word_Count++;
    }

    std::cout << "Words processed from text: " << word_Count << "\n";
    std::cout << "Unique words saved in Dictionary: " << string_Dict.size() << " (duplicates were ignored)\n\n";
    
    std::cout << "Dictionary contents (alphabetically sorted):\n";
    for (Dictionary<std::string>::Iterator it = string_Dict.begin(); it != string_Dict.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";


    // 6. ________________________

    std::cout << "\n___ Task 6 ___\n";

    Dictionary<std::string> string_Src;
    string_Src.insert("sheep");
    string_Src.insert("cat");
    string_Src.insert("hamster");

    Dictionary<std::string> string_Dst_Copy;

    copy(string_Dst_Copy, string_Src);
    
    std::cout << "After copy(string_Dst_Copy, string_Src):\n";
    std::cout << "string_Dst_Copy contains: ";
    for (Dictionary<std::string>::Iterator it = string_Dst_Copy.begin(); it != string_Dst_Copy.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "(should be alphabetically sorted)\n\n";

    Dictionary<std::string> string_Dst_merge;
    string_Dst_merge.insert("horse");
    string_Dst_merge.insert("puppy");

    std::cout << "Before merge_into:\n";
    std::cout << "string_Dst_merge: ";
    for (Dictionary<std::string>::Iterator it = string_Dst_merge.begin(); it != string_Dst_merge.end(); ++it) std::cout << *it << " ";
    
    std::cout << "\nstring_Src: ";
    for (Dictionary<std::string>::Iterator it = string_Src.begin(); it != string_Src.end(); ++it) std::cout << *it << " ";
    std::cout << "\n";

    merge_into(string_Dst_merge, std::move(string_Src));

    std::cout << "\nAfter merge_into(string_Dst_merge, std::move(string_Src)):\n";
    std::cout << "string_Dst_merge contains: ";
    for (Dictionary<std::string>::Iterator it = string_Dst_merge.begin(); it != string_Dst_merge.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    std::cout << "string_Src size is now: " << string_Src.size() << " (must be 0)\n";


    // 7. ________________________

    std::cout << "\n___ Task 7 ___\n";

    const std::size_t N = 16; 

    Word<N> w1("sheep");
    Word<N> w2("horse");
    Word<N> w3("sheep");
    
    Word<N> wLong("this_is_veryyyyyy_long_word"); 

    std::cout << "Word 1: " << w1 << "\n";
    std::cout << "Word 2: " << w2 << "\n";
    std::cout << "Shortened: " << wLong << "\n";

    std::cout << "w1 == w3? " << (w1 == w3 ? "Yes" : "No") << " (should be Yes, both are sheep)\n";
    std::cout << "w1 < w2?  " << (w1 < w2 ? "Yes" : "No") << " (should be No, 's' is after 'h')\n";

    // 8. ________________________

    std::cout << "\n___ Task 8 ___\n";

    Dictionary<std::string> dict_Task8;
    dict_Task8.insert("object");
    dict_Task8.insert("oriented");
    dict_Task8.insert("programming");

    Dictionary<Word<16>> edict;

    for (Dictionary<std::string>::Iterator it = dict_Task8.begin(); it != dict_Task8.end(); ++it) {
        edict.insert(Word<16>(*it));
    }

    std::cout << "Original dict_Task8 (std::string): ";
    for (Dictionary<std::string>::Iterator it = dict_Task8.begin(); it != dict_Task8.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "Transported edict (Word<16>): ";
    for (Dictionary<Word<16>>::Iterator it = edict.begin(); it != edict.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // 9. ________________________

    std::cout << "\n___ Task 9 ___\n";

    edict.insert(Word<16>("hello"));
    edict.insert(Word<16>("world"));
    
    Dictionary<Word<16>> edict1; 
    Dictionary<Word<16>> edict2; 

    int position = 1; 
    
    for (Dictionary<Word<16>>::Iterator it = edict.begin(); it != edict.end(); ++it) {
        if (position % 2 != 0) {
            edict1.insert(*it); 
        } else {
            edict2.insert(*it); 
        }
        position++;
    }

    std::cout << "Full edict: ";
    for (Dictionary<Word<16>>::Iterator it = edict.begin(); it != edict.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "edict1 (odd positions): ";
    for (Dictionary<Word<16>>::Iterator it = edict1.begin(); it != edict1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "edict2 (even positions): ";
    for (Dictionary<Word<16>>::Iterator it = edict2.begin(); it != edict2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    if ((edict1 + edict2) == edict) {
        std::cout << "Result: SUCCESS!\n";
    } else {
        std::cout << "Result: FAILED!\n";
    }
    
    // 10. ________________________

    std::cout << "\n___ Task 10 ___\n";

    {
        Dictionary<Word<16>> edict;
        
        edict.insert(Word<16>("horse"));      
        edict.insert(Word<16>("dog"));     
        edict.insert(Word<16>("cat"));     
        edict.insert(Word<16>("sheep"));       
        edict.insert(Word<16>("hamster")); 
        edict.insert(Word<16>("pig"));        
        edict.insert(Word<16>("duck"));      

        Dictionary<Word<16>> edict2; 
        Dictionary<Word<16>> edict3; 
        Dictionary<Word<16>> edict6; 

        int pos = 1;
        for (Dictionary<Word<16>>::Iterator it = edict.begin(); it != edict.end(); ++it) {
            if (pos % 2 == 0) edict2.insert(*it); 
            if (pos % 3 == 0) edict3.insert(*it); 
            if (pos % 6 == 0) edict6.insert(*it); 
            pos++;
        }

        std::cout << "edict2 (pos 2,4,6): ";
        for (Dictionary<Word<16>>::Iterator it = edict2.begin(); it != edict2.end(); ++it) std::cout << *it << " ";
        std::cout << "\n";

        std::cout << "edict3 (pos 3,6):   ";
        for (Dictionary<Word<16>>::Iterator it = edict3.begin(); it != edict3.end(); ++it) std::cout << *it << " ";
        std::cout << "\n";

        std::cout << "edict6 (pos 6):     ";
        for (Dictionary<Word<16>>::Iterator it = edict6.begin(); it != edict6.end(); ++it) std::cout << *it << " ";
        std::cout << "\n";

        Dictionary<Word<16>> intersection = edict2 * edict3;
        std::cout << "Intersection (edict2 * edict3): ";
        for (Dictionary<Word<16>>::Iterator it = intersection.begin(); it != intersection.end(); ++it) std::cout << *it << " ";
        std::cout << "\n";

        if ((edict2 * edict3) == edict6) {
            std::cout << "Result: SUCCESS!\n";
        } else {
            std::cout << "Result: FAILED!\n";
        }
    }
    

    return 0;

}