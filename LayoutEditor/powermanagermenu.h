#ifndef POWERMANAGERMENU_H
#define POWERMANAGERMENU_H

#include <QMenu>
#include <QList>
#include <QAction>

class PowerManager;
class PowerManagerMenu : public QMenu
{
    Q_OBJECT
public:
    explicit PowerManagerMenu(QWidget *parent = 0);
    /*public*/ PowerManager* getManager();
    /*public*/ PowerManager* get();

signals:

public slots:

private:
    QList<QAction*> items;// = new QList<QAction*>();
    void setDefault();

protected:
    virtual /*abstract*/ /*protected*/ void choiceChanged() {}

};

#endif // POWERMANAGERMENU_H
