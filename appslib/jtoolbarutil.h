#ifndef JTOOLBARUTIL_H
#define JTOOLBARUTIL_H
#include "guiutilbase.h"
#include "appslib_global.h"

class QToolBar;
class WindowInterface;
class APPSLIBSHARED_EXPORT JToolBarUtil : public GuiUtilBase
{
 Q_OBJECT
public:
 explicit JToolBarUtil(QObject *parent = 0);
 static /*public*/  QToolBar* loadToolBar(QString name);
 static /*public*/  QToolBar* loadToolBar(QString name, WindowInterface* wi, QObject* context);

signals:

public slots:

};

#endif // JTOOLBARUTIL_H
