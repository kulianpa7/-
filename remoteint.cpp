#include "remoteint.h"
int remoteint::driver_id = -1;
remoteint::remoteint() {
}

void remoteint::save_id(int id) {
    driver_id = id;
}

int remoteint::return_id() {
    return driver_id;
}
