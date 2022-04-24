
// Copyright Leatherman

#include <algorithm>
#include <string>

#include "textgen.h"

Prefix MarkovGenerator::ReadState(std::istream &in, const int npref) {
    std::string in_string;

    Prefix prefix;

    Prefix starting_prefix;

    for (int i = 0; i < npref; i++) {
        in >> in_string;

        prefix.push_back(std::move(in_string));
    }

    starting_prefix = prefix;

    while (in >> in_string) {
        addPrefix(prefix);
        addSuffixToPrefix(prefix, in_string);
        shiftPrefix(prefix, in_string);
    }

    return starting_prefix;
}

void MarkovGenerator::addPrefix(const Prefix& prefix) {
    statetab[prefix];
}

void MarkovGenerator::addSuffixToPrefix(const Prefix& prefix,
                                        const std::string& suffix) {
    addPrefix(prefix);

    std::vector<std::string> &vec = statetab[prefix];

    if (std::find(vec.begin(), vec.end(), suffix) == vec.end()) {
        vec.push_back(suffix);
    }
}

void shiftPrefix(Prefix &prefix, // NOLINT(runtime/references)
                 const std::string &new_suffix) {
    prefix.pop_front();
    prefix.push_back(new_suffix);
}

bool MarkovGenerator::hasPrefix(const Prefix & prefix) {
    return (statetab.find(prefix) != statetab.end());
}

std::tuple<std::string, bool>
MarkovGenerator::getNextSuffix(Prefix &prefix, unsigned int *state) {
    if (state == nullptr) throw std::invalid_argument("Nullptr passed");

    std::map<Prefix, std::vector<std::string>>::iterator it;

    it = statetab.find(prefix);

    std::string suffix;

    bool found = false;

    if (it != statetab.end()) {
        suffix = it->second[rand_r(state) % (it->second).size()];
        shiftPrefix(prefix, suffix);

        found = true;
    }

    return std::make_tuple(suffix, found);
}

void MarkovGenerator::write(std::ostream &out,
                            Prefix &starting_prefix,
                            unsigned *state,
                            unsigned len) {
    if (state == nullptr) throw std::invalid_argument("Nullptr passed");

    Prefix prefix = starting_prefix;

    for (auto& str : prefix) {
        out << str << " ";
    }

    for (int i = 0; i < len; i++) {
        auto [suffix, found] = getNextSuffix(prefix, state);

        if (found) {
            out << suffix << " ";
        } else {
            break;
        }
    }

    out << '\n';
}

std::vector<std::string>
MarkovGenerator::operator[](Prefix &prefix) { // NOLINT(runtime/references)
    if (hasPrefix(prefix)) {
        return statetab[prefix];
    } else {
        return std::vector<std::string>();
    }
}
