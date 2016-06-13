#ifndef LIBTABLES_H
#define LIBTABLES_H

#include "libtables_global.h"
#include "tablesframe.h"
#include "turnoutwidget.h"
#include "turnouttablewidget.h"

class LIBTABLESSHARED_EXPORT LibTables
{
    
public:
    LibTables();
    void show();
    void show(QString);
private:
 TablesFrame* tableFrame;
};

#endif // LIBTABLES_H
