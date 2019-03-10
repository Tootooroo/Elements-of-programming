#include <iostream>
#include "IntSub.h"

using std::cout;
using std::endl;
using std::ostream;

template<typename Domain>
using relation = bool (*)(const Domain& a, const Domain& b);

template<typename Domain, typename R>
const Domain& select_0_2(const Domain& a, const Domain& b, R r) {
    if (r(b, a)) return b;
    return a;
}

template<typename Domain, typename R>
const Domain& select_1_2(const Domain& a, const Domain& b, R r) {
    if (r(b, a)) return a;
    return b;
}

template<typename Domain, typename R>
const Domain& select_0_3(const Domain& a, const Domain& b, const Domain& c, R r) {
    return select_0_2(select_0_2(a, b, r), c, r);
}

template<typename Domain, typename R>
const Domain& select_1_3(const Domain& a, const Domain& b, const Domain& c, R r) {
    return select_0_2(select_1_2(a, b, r), c, r);
}

template<typename Domain, typename R>
const Domain& select_2_3(const Domain &a, const Domain &b, const Domain &c, R r) {
    return select_1_2(select_1_2(a, b, r), c, r);
}

template<typename Domain, typename R>
const Domain& select_1_4_ab_cd(const Domain &a, const Domain &b, const Domain &c, const Domain &d, R r) {
    if (r(c, a)) return select_0_2(a, d, r);    
    return select_0_2(b, c, r);
}

template<typename Domain, typename R>
const Domain& select_1_4_ab(const Domain &a, const Domain &b, const Domain &c, const Domain &d, R r) {
    if (r(d, c)) return select_1_4_ab_cd(a, b, d, c, r);
    return select_1_4_ab_cd(a, b, c, d, r);
}

template<typename Domain, typename R>
const Domain& select_1_4(const Domain &a, const Domain &b, const Domain &c, const Domain &d, R r) {
    if (r(b, a)) return select_1_4_ab(b, a, c, d, r);
    return select_1_4_ab(a, b, c, d, r);
}

template<typename Domain, typename R>
const Domain & select_2_5_ab_cd(const Domain &a, const Domain &b, const Domain &c, const Domain &d, const Domain &e, R r) {
    if (r(c, a)) return select_1_4(a, b, d, e, r);
    return select_1_4(c, b, d, e, r);
}

template<typename Domain, typename R>
const Domain & select_2_5_ab(const Domain &a, const Domain &b, const Domain &c, const Domain &d, const Domain &e, R r) {
    if (r(d, c)) return select_2_5_ab_cd(a, b, d, c, e, r);
    return select_2_5_ab_cd(a, b, c, d, e, r);
}

template<typename Domain, typename R>
const Domain & select_2_5(const Domain &a, const Domain &b, const Domain &c, const Domain &d, const Domain &e, R r) {
    if (r(b, a)) return select_2_5_ab(b, a, c, d, e, r);
    return select_2_5_ab(a, b, c, d, e, r);
}

/* With stability indices */
#define infoPrint_4() \
    cout << ia << " " << ib << " " << ic << " " << id << " -- " \
        << a << " " << b << " " << c << " " << d << endl; 
#define infoPrint_5() \
    cout << ia << " " << ib << " " << ic << " " << id << " " << ie << " -- " \
        << a << " " << b << " " << c << " " << d << " " << e << endl; 

template<typename Domain_R, typename R, int ia, int ib>
struct compare_strict_or_reflexive {
    bool operator()(const Domain_R &a, const Domain_R &b, R r) {
        if (ia < ib)
            return r(a, b); 
        else 
            return !r(b, a);
    }
};

template<typename Domain_R, typename R, int ia, int ib>
const Domain_R & select_0_2_stability(const Domain_R &a, const Domain_R &b, R r) {
    compare_strict_or_reflexive<Domain_R, R, ia, ib> cmp;
    
    if (cmp(b, a, r)) return b;
    return a;
         
}

template<typename Domain_R, typename R, int ia, int ib, int ic, int id>
const Domain_R & select_1_4_ab_cd_stability(const Domain_R &a, const Domain_R &b, const Domain_R &c, const Domain_R &d, R r) {
    compare_strict_or_reflexive<Domain_R, R, ia, ic> cmp; 

    infoPrint_4();

    if (cmp(c, a, r)) return select_0_2_stability<Domain_R, R, ia, id>(a, d, r);
    return select_0_2_stability<Domain_R, R, ib, ic>(b, c, r);
}


template<typename Domain_R, typename R, int ia, int ib, int ic, int id>
const Domain_R & select_1_4_ab_stability(const Domain_R &a, const Domain_R &b, const Domain_R &c, const Domain_R &d, R r) {
    compare_strict_or_reflexive<Domain_R, R, ic, id> cmp;

    infoPrint_4();

    if (cmp(d, c, r)) return select_1_4_ab_cd_stability<Domain_R, R, ia, ib, id, ic>(a, b, d, c, r);
    return select_1_4_ab_cd_stability<Domain_R, R, ia, ib, ic, id>(a, b, c, d, r);
}


template<typename Domain_R, typename R, int ia, int ib, int ic, int id>
const Domain_R & select_1_4_stability(const Domain_R &a, const Domain_R &b, const Domain_R &c, const Domain_R &d, R r) {
    compare_strict_or_reflexive<Domain_R, R, ia, ib> cmp;

    infoPrint_4();

    if (cmp(b, a, r)) return select_1_4_ab_stability<Domain_R, R, ib, ia, ic, id>(b, a, c, d, r);
    return select_1_4_ab_stability<Domain_R, R, ia, ib, ic, id>(a, b, c, d, r);
}


template<typename Domain_R, typename R, int ia, int ib, int ic, int id, int ie>
const Domain_R & select_2_5_ab_cd_stability(const Domain_R &a, const Domain_R &b, const Domain_R &c, const Domain_R &d, const Domain_R &e, R r) {
    compare_strict_or_reflexive<Domain_R, R, ia, ic> cmp;
    
    infoPrint_5();

    if (cmp(c, a, r)) return select_1_4_stability<Domain_R, R, ia, ib, id, ie>(a, b, d, e, r);
    return select_1_4_stability<Domain_R, R, ic, ib, id, ie>(c, b, d, e, r);
}


template<typename Domain_R, typename R, int ia, int ib, int ic, int id, int ie>
const Domain_R & select_2_5_ab_stability(const Domain_R &a, const Domain_R &b, const Domain_R &c, const Domain_R &d, const Domain_R &e, R r) {
    compare_strict_or_reflexive<Domain_R, R, ic, id> cmp;

    infoPrint_5();

    if (cmp(d, c, r)) return select_2_5_ab_cd_stability<Domain_R, R, ia, ib, id, ic, ie>(a, b, d, c, e, r);
    return select_2_5_ab_cd_stability<Domain_R, R, ia, ib, ic, id, ie>(a, b, c, d, e, r);
}


template<typename Domain_R, typename R, int ia, int ib, int ic, int id, int ie>
const Domain_R & select_2_5_stability(const Domain_R &a, const Domain_R &b, const Domain_R &c, const Domain_R &d, const Domain_R &e, R r) {
    compare_strict_or_reflexive<Domain_R, R, ia, ib> cmp;
    
    infoPrint_5();

    if (cmp(b, a, r)) return select_2_5_ab_stability<Domain_R, R, ib, ia, ic, id, ie>(b, a, c, d, e, r);
    return select_2_5_ab_stability<Domain_R, R, ia, ib, ic, id, ie>(a, b, c, d, e, r);
}

template<typename Domain>
bool lessThan(const Domain& a, const Domain& b) {
    return a < b;
}

int main() {
    IntSub a = IntSub(1, 1);
    IntSub b = IntSub(2, 2); 
    IntSub c = IntSub(2, 3);
    IntSub d = IntSub(3, 4);
    IntSub e = IntSub(4, 5);
    
    cout << "select_1_4: " << select_1_4(c, d, b, e, lessThan<IntSub>) << endl;
    cout << "select_2_5: " << select_2_5(a, b, c, d, e, lessThan<IntSub>) << endl;
    
    IntSub ret = select_2_5_ab_stability<IntSub, relation<IntSub>, 0, 1, 2, 3, 4>(a, b, c, d, e, lessThan<IntSub>);
    cout << "select_2_5(stable): " << ret << endl;

    return 0;
}


