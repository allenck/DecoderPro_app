#ifndef ICONDIALOG_H
#define ICONDIALOG_H
#include <itemdialog.h>
#include "logger.h"
#include <QPushButton>

class JPanel;
class QLabel;
class ImagePanel;
class JTextField;
class CatalogPanel;
class NamedIcon;
class IconDialog : public ItemDialog
{
    Q_OBJECT
public:
    //explicit IconDialog(QWidget *parent = 0);
    /*public*/ IconDialog(QString type, QString family, FamilyItemPanel *parentPanel, QMap <QString, NamedIcon*>* iconMap , QWidget *parent=nullptr);
    /*public*/ QString getClassName();
signals:

public slots:

private:
    Logger* log;

protected:
    /*protected*/ FamilyItemPanel* _parent;
    /*protected*/ QString _family;
   /*protected*/ QMap <QString, NamedIcon*>*  _iconMap;
    /*protected*/ JPanel*       _iconPanel;
//    /*protected*/ ImagePanel*    _iconEditPanel;
    /*protected*/ CatalogPanel*  _catalog;
//    /*private*/ /*final*/ QLabel* _nameLabel;
//    /*protected*/ JTextField*    _familyName;

    // Only multiSensor adds and deletes icons
    /*protected*/ virtual void makeAddIconButtonPanel(JPanel* buttonPanel, QString addTip, QString deleteTip);
    /*protected*/ virtual bool doDoneAction();
    /*protected*/ JPanel* makeIconPanel(QMap<QString, NamedIcon*>* iconMap);
    /*protected*/ QMap<QString, NamedIcon *> *clone(QMap<QString, NamedIcon *> *map);
    /*protected*/ void makeDoneButtonPanel(JPanel* buttonPanel, QString text);
    /*protected*/ void sizeLocate();

protected slots:
//    /*protected*/ void renameFamily();

    friend class FamilyItemPanel;
    friend class MultiSensorItemPanel;
};

#endif // ICONDIALOG_H
