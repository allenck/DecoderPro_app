#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include "jdialog.h"

class ItemPanel;
class FamilyItemPanel;
class ItemDialog : public JDialog
{
    Q_OBJECT
public:
    //explicit ItemDialog(QWidget *parent = 0);
    /*public*/ ItemDialog(QString type, QString family, QString title, FamilyItemPanel *parent, bool mode);
 /*public*/ void dispose();

signals:

public slots:
protected:
    /*protected*/ FamilyItemPanel* _parent;
    /*protected*/ QString    _type;
    /*protected*/ QString    _family;
    /*protected*/ void sizeLocate();
    /*protected*/ QString getDialogType();
    /*protected*/ virtual void closeDialogs();

friend class FamilyItemPanel;
friend class MultiSensorItemPanel;
};

#endif // ITEMDIALOG_H
