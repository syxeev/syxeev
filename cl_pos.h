#ifndef CL_POS_H
#define CL_POS_H

#include "cl_base.h"

class cl_pos : public cl_base {
public:
	void hendler_valid_input(stringstream&);
	static void position_secure(stringstream&) {};
};

#endif