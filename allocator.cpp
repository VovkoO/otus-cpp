#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <memory_resource>
#include <cstddef>
#include <unordered_set>

using namespace std;

template <typename T>
struct allocation_result {
    T ptr;
    std::size_t count;
};

template <class T>
class MyAllocator {
public:
    using value_type = T;

    T* allocate(size_t n) {
        cout << "allocate n: " << n << " ";

        if (n > free_size) {
            cout << "new \n";
            auto allocated = static_cast<T*>(::operator new(sizeof(T) * n * 10));
            need_to_free.insert(allocated);
            free_size = n * 9;
            free_mem = allocated + (n * sizeof(T));
            return allocated;
        } else {
            cout << "old \n";
            auto allocated = free_mem;
            free_size -= n;
            free_mem += n * sizeof(T);
            return allocated;
        }
    }

    allocation_result<T*> allocate_at_least( std::size_t n ) {
        cout << "allocate_at_least n: " << n << endl;
        auto allocated = static_cast<T*>(::operator new(sizeof(T) * n * 10));
        need_to_free.insert(allocated);
        return {allocated, n};
    }

    void deallocate( T* p, std::size_t n ) {
        cout << "deallocate n: " << n << endl;
        if (need_to_free.contains(p)) {
            ::operator delete(p);
            need_to_free.erase(p);
        }
    }

    template <typename U>
    bool operator==(const MyAllocator<U>&) const noexcept {
        cout << "operator==\n";
        return true;
    }

private:
    unordered_set<T*> need_to_free;
    T* free_mem;
    size_t free_size = 0;
};

template <typename Alloc>
class MYVector {
private:
    size_t _size = 0;
    size_t max_size = 0;
    int* data;
    Alloc allocator;


public:
    MYVector() = default;
    ~MYVector() {
        if (max_size > 0) {
            allocator.deallocate(data, max_size);
        }
    }

    void push_back(int v) {
        if (_size + 1 >= max_size) {
            size_t new_size = max_size * 2;
            if (new_size == 0) {
                new_size = 1;
            }
            auto res = allocator.allocate_at_least(new_size);
            auto new_data = res.ptr;

            for (size_t i = 0; i < _size; i++) {
                *(new_data + i) = *(data + i);
            }


            allocator.deallocate(data, max_size);

            data = new_data;
            max_size = res.count;
        }
        *(data + _size) = v;
        _size += 1;
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
    {
        cout << "MAP\n";
        map<int, int, std::less<>, MyAllocator<std::pair<const int, int>>> myMap;

        for (int i = 0; i < 20; i++) {
            myMap[i] = i;
        }
    }

    cout << "------------------------";

    {
        cout << "MY CONTAINER\n";
        MYVector<MyAllocator<int>> myVec;
        for (int i = 0; i < 10; i++) {
            myVec.push_back(i + 1);
        }

        for (size_t i = 0; i < myVec.size(); i++) {
            cout << i << ": " << myVec[i] << endl;
        }
    }

    return 0;
}