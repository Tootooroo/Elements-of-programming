/* IntSub.h */

#ifndef _INT_SUB_H_
#define _INT_SUB_H_ value

#include <iostream>

class IntSub {
    public:
        IntSub();
        IntSub(int idx, int sub);
        bool operator<(const IntSub &intSub) const;
        friend std::ostream & operator<<(std::ostream &os, const IntSub &intSub);
    private:
        int idx;
        int subscript;
};

#endif /* ifndef _INT_SUB_H_ */


