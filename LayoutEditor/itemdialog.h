#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include "jmrijframe.h"

class ItemPanel;
class FamilyItemPanel;
class ItemDialog : public JmriJFrame
{
    Q_OBJECT
public:
    //explicit ItemDialog(QWidget *parent = 0);
    /*public*/ ItemDialog(QString type, QString title);
 /*public*/ void dispose();
 /*public*/ QString getClassName();
signals:

public slots:
private:
 /*private*/ static ItemDialog* _instance;// = null;		// only let one dialog at a time

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
