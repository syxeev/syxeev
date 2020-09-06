#ifndef CL_APPLICATION_H
#define CL_APPLICATION_H

#include "cl_con.h"
#include "cl_pos.h"
#include "cl_write.h"

using namespace std;

class cl_application : public cl_base {
public:
	cl_application();
	//   ~cl_application ( );

	void bild_tree_objects();
	void initial_output();
	int exec_app();
	static void valid_input(stringstream&) {};

private:
	cl_pos* p_ob_position;
	cl_write* p_ob_write;
	cl_con* p_ob_console;
};

#endif // CL_APPLICATION_H