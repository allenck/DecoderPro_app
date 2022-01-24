#ifndef BEANTABLEITEM_H
#define BEANTABLEITEM_H

#include <QWidget>
#include "abstractaction.h"

class ActionListener;
class BeanEditItem;
class BeanItemPanel : public QWidget
{
public:
    BeanItemPanel(QWidget* parent = 0);
    ~BeanItemPanel();
    /*public*/ void saveItem();
    /*public*/ void resetField();
    /*public*/ void setSaveItem(AbstractAction *save);
    /*public*/ void setResetItem(AbstractAction *reset);
    /*public*/ void addItem(BeanEditItem* bei);
    /*public*/ QList<BeanEditItem*> getListOfItems();
    /*public*/ void setName(QString name);
    /*public*/ QString getName();

private:
    AbstractAction* save;
    AbstractAction* reset;

    QList<BeanEditItem*> items;// = new QList<BeanEditItem*>();
    QString name;

};

#endif // BEANTABLEITEM_H
