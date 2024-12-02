#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename T>
class MyAllocator {
public:
    using value_type = T;

    constexpr T* allocate( std::size_t n ) {
        cout << "allocate n: " << n << endl;
        return static_cast<T*>(::operator new(sizeof(T) * n));
    }

    constexpr allocation_result<T*> allocate_at_least( std::size_t n ) {
        cout << "allocate_at_least n: " << n << endl;
        return {static_cast<T*>(::operator new(sizeof(T) * n)), n};
    }

    void deallocate( T* p, std::size_t n ) {
        cout << "deallocate n: " << n << endl;
        if (n > 0) {
            ::operator delete(p);
        }
    }

    template <typename U>
    bool operator==(const MyAllocator<U>&) const noexcept {
        cout << "operator==\n";
        return true;
    }
};

template <typename T>
class MYVector {
private:
    size_t _size = 0;
    size_t max_size = 1;
    int* data;
    T allocator;

public:
    MYVector() = default;
    ~MYVector() {
        if (max_size > 0) {
            allocator.deallocate(data, max_size);
        }
    }

    void push_back(int v) {
        if (_size + 1 >= max_size) {
            auto res = allocator.allocate_at_least(max_size * 2);
            auto new_data = res.ptr;

            for (size_t i = 0; i < _size; i++) {
                *(new_data + i) = *(data + i);
            }
            *(new_data + _size) = v;

            allocator.deallocate(data, _size);

            data = new_data;
            max_size = res.count;
            _size += 1;
        }
    }

    int operator[](size_t idx) {
        return *(data + idx);
    }

    size_t size() {
        return _size;
    }
};

int main()
{
    map<int, int, std::less<>, MyAllocator<std::pair<const int, int>>> myMap;

    for (int i = 0; i < 10; i++) {
        myMap[i] = i;
    }


    MYVector<MyAllocator<int>> myVec;
    for (int i = 0; i < 10; i++) {
        myVec.push_back(i + 1);
    }

    for (size_t i = 0; i < myVec.size(); i++) {
        cout << i << ": " << myVec[i] << endl;
    }

    return 0;
}