#ifndef SAVEMENU_H
#define SAVEMENU_H

#include <QMenu>
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT SaveMenu : public QMenu
{
    Q_OBJECT
public:
    explicit SaveMenu(QWidget *parent = 0);
    /*public*/ SaveMenu(QString name, QWidget *parent = 0);

signals:

public slots:

};

#endif // SAVEMENU_H
