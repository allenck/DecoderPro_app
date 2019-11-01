#ifndef OPERATIONSMENU_H
#define OPERATIONSMENU_H

#include <QMenu>
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT OperationsMenu : public QMenu
{
    Q_OBJECT
public:
    explicit OperationsMenu(QWidget *parent = 0);
    /*public*/ OperationsMenu(QString name,QWidget *parent = 0);

signals:

public slots:

private:
    void common();
};

#endif // OPERATIONSMENU_H
