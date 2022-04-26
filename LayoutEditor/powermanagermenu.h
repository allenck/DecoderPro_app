#ifndef POWERMANAGERMENU_H
#define POWERMANAGERMENU_H

#include <QMenu>
#include <QList>
#include <QAction>

class AbstractPowerManager;
class PowerManagerMenu : public QMenu
{
    Q_OBJECT
public:
    explicit PowerManagerMenu(QWidget *parent = 0);
    /*public*/ AbstractPowerManager* getManager();
    /*public*/ AbstractPowerManager* get();

signals:

public slots:

private:
    QList<QAction*> items;// = new QList<QAction*>();
    void setDefault();

protected:
    virtual /*abstract*/ /*protected*/ void choiceChanged() {}

};

#endif // POWERMANAGERMENU_H
