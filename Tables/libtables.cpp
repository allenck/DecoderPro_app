#include "libtables.h"


LibTables::LibTables()
{
 tableFrame = new TablesFrame();
 //tableFrame->show();
}
void LibTables::show()
{
 tableFrame->show();
 tableFrame->setVisible(true);
}
void LibTables::show(QString s)
{
 tableFrame->setupType(s);
 tableFrame->show();
}
