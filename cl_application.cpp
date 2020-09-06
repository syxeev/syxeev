#include "cl_application.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

cl_application::cl_application() { set_object_name("root"); }

void cl_application::initial_output() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            get_stream() << '8';
        }
        if (i != 9)
            get_stream() << endl;
    }
}

void cl_application::bild_tree_objects() {
    p_ob_position = new cl_pos;
    p_ob_position->set_object_name("ob_position");
    p_ob_position->set_parent(this);

    p_ob_write = new cl_write;
    p_ob_write->set_object_name("ob_write");
    p_ob_write->set_parent(this);

    p_ob_console = new cl_con;
    p_ob_console->set_object_name("ob_console");
    p_ob_console->set_parent(this);
}

int cl_application::exec_app() {
    set_stream();
    initial_output();
    stringstream stream;
    int a, b;
    char c;
    cin >> a >> b >> c;
    stream.str("");
    stream << a << ' ' << b << ' ' << c;
    this->set_connect(SIGNAL_D(this->valid_input), p_ob_position, HENDLER_D(cl_pos::hendler_valid_input));
    p_ob_position->set_connect(SIGNAL_D(p_ob_position->position_secure), p_ob_write, HENDLER_D(cl_write::hendler_pos_secure));
    while (a != 0 && b != 0) {
        emit_signal(SIGNAL_D(valid_input), stream);
        cin >> a >> b >> c;
        stream.str("");
        stream << a << ' ' << b << ' ' << c;
    }
    p_ob_console->out_to_console();
    return 0;
}