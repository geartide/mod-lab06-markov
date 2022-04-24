
// Copyright Leatherman

#pragma once

#include <ostream>
#include <istream>
#include <string>
#include <vector>
#include <deque>
#include <tuple>
#include <map>

const int NPREF = 2;
const int MAXGEN = 1000;

typedef std::deque<std::string> Prefix;

class MarkovGenerator {
 private:
    std::map<Prefix, std::vector<std::string>> statetab;

 public:
    Prefix ReadState(std::istream &in, const int npref = NPREF);

    void addPrefix(const Prefix& prefix);
    void addSuffixToPrefix(const Prefix& prefix, const std::string& suffix);

    bool hasPrefix(const Prefix & prefix);

    std::tuple<std::string, bool>
    getNextSuffix(Prefix &prefix, // NOLINT(runtime/references)
                  unsigned int *state);

    void write(std::ostream &out,
               Prefix &starting_prefix, // NOLINT(runtime/references)
               unsigned *state,
               unsigned len = MAXGEN);

    std::vector<std::string>
    operator[](Prefix &prefix); // NOLINT(runtime/references)
};

void shiftPrefix(Prefix &prefix, // NOLINT(runtime/references)
                 const std::string &new_suffix);
