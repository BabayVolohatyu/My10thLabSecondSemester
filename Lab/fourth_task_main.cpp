#include <iostream>
#include <vector>

int main() {
    std::string expression{"exp fugvk glui y"};
    std::vector<std::string> words;
    auto it = expression.begin();
    auto pbi = [](std::vector<std::string> &v,int i,char &c){v[i].push_back(c);};
    int number_of_word = 0;
    while (it != expression.end()) {
        if (*it == ' ') number_of_word++;
        else {
            if (number_of_word >= words.size()) words.emplace_back("");
            pbi(words,number_of_word, *it);
        }
        it++;
    }
    std::vector<std::string> reverse_words;
    auto it2 = words.end();
    it2--;
    do {
        reverse_words.push_back(*it2);
        it2--;
    } while (it2 != words.begin() - 1);
    for (auto &s: reverse_words) std::cout << s << " ";
}
