#include <algorithm>
#include <iostream>
#include <vector>

template <typename T, typename Ostream>
class Compare {
   public:
    Compare(Ostream& out) : out_(out) {}
    constexpr bool operator()(const T& lhs, const T& rhs) const {
        out_ << "Result of comparison "
             << "(lhs == " << lhs << ") < (rhs == " << rhs << ") is "
             << (lhs < rhs ? "True\n" : "False\n");
        return lhs < rhs;
    }

   private:
    Ostream& out_;
};

template <typename T, typename Container = std::vector<T>,
          typename Ostream = std::basic_ostream<char>,
          typename Comp = Compare<T, Ostream>>
class BinSearchChecher {
   public:
    BinSearchChecher() = default;
    BinSearchChecher(Ostream& out) : out_(out) {}
    void LowerBoundCheck(const Container& arr, const T& value) const {
        auto it = std::lower_bound(arr.begin(), arr.end(), value, comp_);
        out_ << "Lower bound for value " << value << " is " << *it << '\n';
    }
    void UpperBoundCheck(const Container& arr, const T& value) const {
        auto it = std::upper_bound(arr.begin(), arr.end(), value, comp_);
        out_ << "Upper bound for value " << value << " is " << *it << '\n';
    }

   private:
    Ostream& out_ = std::cout;
    Comp comp_ = Comp(out_);
};

int main(int, char**) {
    std::vector<int> arr{2, 3, 5, 7, 9, 12, 14};
    BinSearchChecher<int> checker;
    checker.UpperBoundCheck(arr, 5);
    checker.LowerBoundCheck(arr, 5);
}
