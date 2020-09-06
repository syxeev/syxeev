#include "cl_con.h"
void cl_con::out_to_console() {
    ((get_root())->get_stream()).close();
    ((get_root())->get_stream()).open("field.txt", ios_base::in);
    string str;
    while (!((get_root())->get_stream()).eof()) {
        getline(((get_root())->get_stream()), str);
        cout << endl << str;
    }
}