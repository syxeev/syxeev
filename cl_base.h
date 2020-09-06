#ifndef CL_BASE_H
#define CL_BASE_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
class cl_base;
typedef void (*TYPE_SIGNAL)(stringstream&);
typedef void (cl_base::* TYPE_HANDLER)(stringstream&);
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&(signal_f))
#define HENDLER_D(hendler_f)(TYPE_HANDLER)(&hendler_f)

class cl_base {
public:
    cl_base(cl_base* p_parent = 0);
    void set_connect(TYPE_SIGNAL, cl_base*, TYPE_HANDLER);
    void emit_signal(TYPE_SIGNAL, stringstream&);
    void set_object_name(string s_object_name);
    string get_object_name();
    fstream& get_stream();
    void set_stream();
    void set_parent(cl_base* p_parent);
    void add_child(cl_base* p_child);
    void delete_child(string s_object_name);
    string get_item(string, int);
    cl_base* get_root();
    cl_base* get_object(string);
    cl_base* take_child(string s_object_name);
    cl_base* get_child(string s_object_name);
    void set_state(int i_state);
    int get_state();
    void show_object_state();
    void output(cl_base*, int);
    cl_base* get_object_root();
private:
    struct o_sh {
        cl_base* p_cl_base;
        TYPE_HANDLER p_hendler;
    };
    multimap<TYPE_SIGNAL, o_sh*> connects;
    multimap<TYPE_SIGNAL, o_sh*>::iterator it_connects;
    vector<cl_base*> children;
    vector<cl_base*>::iterator it_child;

    fstream file;
    string object_name;
    cl_base* p_parent;
    int i_state;
   
    void show_state_next(cl_base* ob_parent);
};

#endif // CL_BASE_H