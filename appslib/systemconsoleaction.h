#ifndef SYSTEMCONSOLEACTION_H
#define SYSTEMCONSOLEACTION_H

#include <QAction>
#include "appslib_global.h"

class WindowInterface;
class APPSLIBSHARED_EXPORT SystemConsoleAction : public QAction
{
 Q_OBJECT
public:
 explicit SystemConsoleAction(QObject *parent = 0);
 /*public*/  SystemConsoleAction(QString s, WindowInterface* wi);
 /*public*/  SystemConsoleAction(QString s, QIcon i, WindowInterface* wi);

signals:

public slots:
 /*public*/  void actionPerformed(ActionEvent* e = 0);

private:
 void common();
};

#endif // SYSTEMCONSOLEACTION_H
