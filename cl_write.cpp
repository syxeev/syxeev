#include "cl_write.h"
#include <sstream>

void cl_write::hendler_pos_secure(stringstream& stream) {
    char c;
    stream >> c;
    if ((c > 'a' && c < 'z') || (c > 'A' && c < 'Z')) {
        ((get_root())->get_stream()) << c;
    }
    else {
        (get_root()->get_stream()).seekp(0, ios_base::end);
        ((get_root())->get_stream()) << endl << "Not a letter of the Latin alphabet: " << c;
    }
}
