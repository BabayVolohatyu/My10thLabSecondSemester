#include <iostream>
#include "set"
int main(){
    const int n = 3,m =4;
    int a[n] = {0,0,8};
    int b[m] = {0,8,8,8};
    std::multiset<int> multiset;
    std::set<int> set;
    for(int i : a){
        multiset.insert(i);
    }
    for(int i : b){
        multiset.insert(i);
    }
    for(int i:multiset){
        set.insert(i);
    }
    int med = *multiset.begin();
    for(int i:set){
        if(multiset.count(i) > multiset.count(med))med = i;
    }
    std::cout << med;
}