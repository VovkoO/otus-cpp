#include <iostream>
#include <map>
#include <tuple>
#include <cassert>

using namespace std;

template<typename T, T DefaultValue>
class Matrix
{
    class Proxy1 {
        class Proxy2 {
        private:
            pair<int, int> idx;
            Matrix& m;

        public:
            Proxy2(size_t idx1, size_t idx2, Matrix& m): idx(idx1, idx2), m(m) {};

            Proxy2& operator= (T val) {
                if (m.data.contains(idx) && val == DefaultValue) {
                    m.data.erase(idx);
                } else {
                    m.data[idx] = val;
                }
                return *this;
            }

            operator T() {
                if (m.data.contains(idx)) {
                    return m.data[idx];
                }
                return DefaultValue;
            }
        };

    private:
        size_t idx;
        Matrix& m;

    public:
        Proxy1(size_t idx, Matrix& m): idx(idx), m(m) {};

        Proxy2 operator[] (int idx2) {
            return Proxy2(idx, idx2, m);
        }
    };

private:
    map<pair<int, int>, T> data;

public:
    class iterator {
        using inner_iterator = typename map<pair<int, int>, T>::const_iterator;

    private:
        inner_iterator ii;

    public:
        iterator(const inner_iterator& ii): ii(ii) {};

        bool operator!= (const iterator& other) {
            return ii != other.ii;
        }

        iterator& operator++() {
            ii++;
            return *this;
        }

        auto operator* () const{
            return std::make_tuple(ii->first.first, ii->first.second, ii->second);
        }
    };

    Proxy1 operator[] (int idx) {
       return Proxy1(idx, *this);
    }

    size_t size() {
        return data.size();
    }

    iterator begin() const {
         return iterator(data.begin());
    }

    iterator end() const {
        return iterator(data.end());
    }

};

// Пример использования
int main()
{
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0); // все ячейки свободны
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);
    // выведется одна строка
    // 100100314
    for(auto c: matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
    return 0;
}