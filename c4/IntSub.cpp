#include "IntSub.h"


IntSub::IntSub(int idx, int sub) {
    this->idx = idx;  
    this->subscript = sub;
}

bool IntSub::operator<(const IntSub &intSub) const {
    return idx < intSub.idx;
}

std::ostream & operator<<(std::ostream &os, const IntSub &intSub) {
    os << intSub.idx << "." << intSub.subscript;
    return os;
}

