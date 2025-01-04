#ifndef REMOTEINT_H
#define REMOTEINT_H

class remoteint
{
public:
    remoteint();

    static int driver_id;

    static void save_id(int id);
    static int return_id();
};

#endif // REMOTEINT_H
