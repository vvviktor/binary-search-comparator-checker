#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace bin_search_checker {

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

template <typename T, typename Ostream = std::basic_ostream<char>,
          typename Comp = Compare<T, Ostream>>
class BinSearchChecher {
   public:
    BinSearchChecher() = default;
    BinSearchChecher(Ostream& out) : out_(out) {}

    template <typename Container = std::vector<T>>
    void LowerBoundCheck(const Container& arr, const T& value) const {
        PrintArr(arr);
        auto it = std::lower_bound(arr.begin(), arr.end(), value, comp_);
        out_ << "Lower bound for value " << value << " is "
             << (it != arr.end() ? std::to_string(*it) : "end iterator")
             << '\n';
    }

    template <typename Container = std::vector<T>>
    void UpperBoundCheck(const Container& arr, const T& value) const {
        PrintArr<Container>(arr);
        auto it = std::upper_bound(arr.begin(), arr.end(), value, comp_);
        out_ << "Upper bound for value " << value << " is "
             << (it != arr.end() ? std::to_string(*it) : "end iterator")
             << '\n';
    }

   private:
    Ostream& out_ = std::cout;
    Comp comp_ = Comp(out_);

    template <typename Container>
    void PrintArr(const Container& arr) const {
        out_ << "arr == [";
        bool is_first = true;
        for (const T& val : arr) {
            if (is_first) {
                is_first = false;
            } else {
                out_ << ", ";
            }
            out_ << val;
        }
        out_ << "]\n";
    }
};

}  // namespace bin_search_checker

int main(int argc, char** argv) {
    std::ofstream out_file =
        argc > 1 ? std::ofstream(*++argv) : std::ofstream();
    std::ostream* out = argc > 1 ? &out_file : &std::cout;
    std::vector<int> arr{2, 3, 5, 7, 9, 12, 14};
    bin_search_checker::BinSearchChecher<int> checker(*out);
    checker.UpperBoundCheck(arr, 5);
    checker.LowerBoundCheck(arr, 5);
}
