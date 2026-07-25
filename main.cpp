#include <iostream>
#include "resolver.hh"
#include <optional>
using namespace std;

void print_matrix_set(){

}

void test_case(){
    std::vector<std::vector<std::optional<int>>> test_mat(9, vector<optional<int>>(9));
    test_mat = {
        { 5 , 3 , nullopt ,   nullopt, 7 , nullopt,   nullopt, nullopt, nullopt},
        { 6 , nullopt, nullopt,   1 , 9 , 5 ,   nullopt, nullopt, nullopt},
        { nullopt, 9 , 8 ,   nullopt, nullopt, nullopt,   nullopt, 6 , nullopt},

        { 8 , nullopt, nullopt,   nullopt, 6 , nullopt,   nullopt, nullopt, 3 },
        { 4 , nullopt, nullopt,   8 , nullopt, 3 ,   nullopt, nullopt, 1 },
        { 7 , nullopt, nullopt,   nullopt, 2 , nullopt,   nullopt, nullopt, 6 },

        { nullopt, 6 , nullopt,   nullopt, nullopt, nullopt,   2 , 8 , nullopt},
        { nullopt, nullopt, nullopt,   4 , 1 , 9 ,   nullopt, nullopt, 5 },
        { nullopt, nullopt, nullopt,   nullopt, 8 , nullopt,   nullopt, 7 , 9 }};
    Resolver resolver(test_mat);
}
int main(){
    test_case();
}