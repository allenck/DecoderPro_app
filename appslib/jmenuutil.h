#ifndef JMENUUTIL_H
#define JMENUUTIL_H
#include <guiutilbase.h>
#include "rosterframe.h"
#include "appslib_global.h"


class QMenu;
class WindowInterface;
class APPSLIBSHARED_EXPORT JMenuUtil : public GuiUtilBase
{
 Q_OBJECT
public:
 //explicit JMenuUtil(QObject *parent = 0);
 static /*public*/  QList<QMenu*> loadMenu(QString path, WindowInterface* wi, QObject* context);

signals:

public slots:
private:
 static QMenu* jMenuFromElement(QDomElement main, WindowInterface* wi, QObject* context);
 static QMenu* createMenuGroupFromElement(QDomElement main, WindowInterface* wi, QObject* context);
 static void setMenuItemInterAction(QObject* context, /*final*/ QString ref, /*final*/ QAction* menuItem);
 static int convertStringToKeyEvent(QString st);
 QHash<QString, NoParm>* slotTable;// = (RosterFrame*)wi;
};

#endif // JMENUUTIL_H
