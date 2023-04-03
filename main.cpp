//
//  main.cpp
//  think-cell
//
//  Created by Ivan Kotikov on 20.02.2023.
//

#include <iostream>
#include <map>

template<typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K,V> m_map;
public:
    // constructor associates whole range of K with val
//    interval_map(V const& val)
//    : m_valBegin(val)
//    {}
    interval_map( V const& val) {
          m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        if (!(keyBegin < keyEnd)) {
            return;
        }
        
        auto intEnd = m_map.find(keyEnd);

        auto nearestRightValue = m_map.lower_bound(keyEnd);
        if (intEnd != m_map.end()) {
            intEnd -> second = nearestRightValue -> second;
        } else {
            --nearestRightValue;
            intEnd = m_map.insert(m_map.end(), std::make_pair(keyEnd, nearestRightValue -> second));
        }

        auto intBegin = m_map.insert_or_assign(keyBegin, val).first;

        m_map.erase(std::next(intBegin), intEnd);
        
        if (intBegin != m_map.begin()) {
            intBegin = std::prev(intBegin);
        }

        for (auto it = intEnd; it != intBegin; --it) {
            if (it -> second == intEnd -> second) {
                it = m_map.erase(it);
            }
        }
        
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        auto it=m_map.upper_bound(key);
        if(it==m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }
    
    void print ( ) {
        for (const auto& [key, val] : m_map) {
            std::cout << "[" << key << ", " << val << "]" << std::endl;
        }
        std::cout << std::endl;
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.


int main(int argc, const char * argv[]) {
    interval_map<int, char> intmap{'a'};
    intmap.print();
    
    
    intmap.assign(0, 10, 'a');
    intmap.print(); // [-2147483648:a][10:f][18:a]

    intmap.assign(11, 20, 'a');
    intmap.print(); // [-2147483648:a]

    intmap.assign(21, 30, 'a');
    intmap.print(); // [-2147483648:a]
    
    
    
//    intmap.assign(3, 5, 'b');
//    intmap.print();
//
//    intmap.assign(2, 3, 'c');
//    intmap.print(); // [-2147483648:a][2:c][3:b][5:a]
//
//    intmap.assign(2, 3, 'd');
//    intmap.print(); // [-2147483648:a][2:d][3:b][5:a]
//
//    intmap.assign(2, 4, 'e');
//    intmap.print(); // [-2147483648:a][2:e][4:b][5:a]
//
//    intmap.assign(4, 18, 'f');
//    intmap.print(); // [-2147483648:a][2:e][4:f][18:a]
//
//    intmap.assign(2, 8, 'g');
//    intmap.print(); // [-2147483648:a][2:g][8:f][18:a]
//
//    intmap.assign(0, 10, 'a');
//    intmap.print(); // [-2147483648:a][10:f][18:a]
//
//    intmap.assign(0, 20, 'a');
//    intmap.print(); // [-2147483648:a]
//
//    intmap.assign(0, 30, 'a');
//    intmap.print(); // [-2147483648:a]
    
}
