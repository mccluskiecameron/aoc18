
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>

std::vector<uint16_t> digit_list {3u, 7u};
const std::vector<uint16_t> match_pattern {5u, 8u, 0u, 7u, 4u, 1u};
std::deque<uint16_t> last_n_digits(match_pattern.size());

struct elf {
    uint32_t current_index = 0u;
    void step() {
        current_index += digit_list[current_index];
        ++current_index;
        current_index %= digit_list.size();
    }
};

elf elf1{0u}, elf2{1u};
uint32_t match_index = 0u; 
bool match_index_lock = false;

void matchQueueCheck() {
    if (match_index_lock) {
        return;
    }
    uint16_t idx_ctr = 0u;
    bool r = true;
    for (uint16_t u : last_n_digits) {
        r &= (match_pattern[idx_ctr] == u);
        ++idx_ctr;
    }
    if (r) {
        match_index = digit_list.size();
        match_index_lock = true;
    }
}

void createNewRecipes() {
    uint32_t sum = 
        digit_list[elf1.current_index] +
        digit_list[elf2.current_index];
    if (sum >= 10) {
        last_n_digits.pop_front();
        digit_list.push_back(sum / 10);
        last_n_digits.push_back(sum / 10);
        matchQueueCheck();
        last_n_digits.pop_front();
        digit_list.push_back(sum % 10); 
        last_n_digits.push_back(sum % 10);
        matchQueueCheck();
    } else {
        last_n_digits.pop_front();
        digit_list.push_back(sum);
        last_n_digits.push_back(sum);
        matchQueueCheck();
    }
}

int main(int argc, char* argv[]) {
    uint32_t init_size = digit_list.size();
    uint32_t desired = 580741u; //desired offset
    while (digit_list.size() < (desired + init_size + 10u)) {
        createNewRecipes();
        elf1.step();
        elf2.step();
    }
    while (!match_index) {
        createNewRecipes();
        elf1.step();
        elf2.step();
    }
    std::cout << "Part1: \n";
    std::for_each(
        digit_list.begin() + desired,
        digit_list.begin() + desired + 10u,
        [&](uint16_t u){
        std::cout << static_cast<uint16_t>(u);
    });
    std::cout << '\n';
    std::cout << "Part2: \n";
    std::cout << match_index - match_pattern.size() << '\n';
    return 0;
}
