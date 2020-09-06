#include "cl_pos.h"
#include <sstream>

void cl_pos::hendler_valid_input( stringstream& stream) {
    int a, b;
    stream >> a >> b;
    if ((a > 0 && a < 11) && (b > 0 && b < 11)) {
        ((get_root())->get_stream()).seekp((b - 1) + 12 * (a - 1), ios_base::beg);
        emit_signal(SIGNAL_D(position_secure), stream);
    }
    else {
        ((get_root())->get_stream()).seekp(0, ios_base::end);
        ((get_root())->get_stream())<<endl<<"Coordinate is wrong ( " << a << ", " << b << " )";
    }
}