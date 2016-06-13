#ifndef ROSTERMENU_H
#define ROSTERMENU_H

#include <QMenu>
#include "logger.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT RosterMenu : public QMenu
{
    Q_OBJECT
public:
    //explicit RosterMenu(QWidget *parent = 0);
    enum TYPE
    {
        /**
         * Ctor argument defining that the menu object will be
         * used as part of the main menu of the program, away from
         * any GUI that can select or use a RosterEntry.
         */
     MAINMENU = 1,
    /**
     * Ctor argument defining that the menu object will be
     * used as a menu on a GUI object that can select
     * a RosterEntry.
     */
    SELECTMENU =2,
    /**
     * Ctor argument defining that the menu object will
     * be used as a menu on a GUI object that is dealing with
     * a single RosterEntry.
     */ENTRYMENU = 3
    };
    /*public*/ RosterMenu(QString pMenuName, int pMenuType, QWidget* pWho);

signals:

public slots:

private:
 Logger* log;
};

#endif // ROSTERMENU_H
