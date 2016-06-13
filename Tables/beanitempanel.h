#ifndef BEANTABLEITEM_H
#define BEANTABLEITEM_H

#include <QWidget>

class ActionListener;
class BeanEditItem;
class BeanItemPanel : public QWidget
{
public:
    BeanItemPanel(QWidget* parent = 0);
    ~BeanItemPanel();
    /*public*/ void saveItem();
    /*public*/ void resetField();
    /*public*/ void setSaveItem(ActionListener* save);
    /*public*/ void setResetItem(ActionListener* reset);
    /*public*/ void addItem(BeanEditItem* bei);
    /*public*/ QList<BeanEditItem*> getListOfItems();
    /*public*/ void setName(QString name);
    /*public*/ QString getName();

private:
    ActionListener* save;
    ActionListener* reset;

    QList<BeanEditItem*> items;// = new QList<BeanEditItem*>();
    QString name;

};

#endif // BEANTABLEITEM_H
