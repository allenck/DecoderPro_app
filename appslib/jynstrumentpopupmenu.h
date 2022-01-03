#ifndef JYNSTRUMENTPOPUPMENU_H
#define JYNSTRUMENTPOPUPMENU_H
#include "menu.h"
#include "jynstrument.h"

class JynstrumentPopupMenu : public Menu
{
    Q_OBJECT
public:
 /*public*/ JynstrumentPopupMenu(Jynstrument* it);


private:
 Jynstrument* jynstrument; // The jynstrument itself
 /*private*/ void initMenu();

};

#endif // JYNSTRUMENTPOPUPMENU_H
