#ifndef SS_H
#define SS_H
#include "gg.h"
class ss{
private:
	int D, Q;
public:
	void input(int a, int b);
	friend int func(gg &, ss &);
};
#endif
