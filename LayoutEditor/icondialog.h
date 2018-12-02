#ifndef ICONDIALOG_H
#define ICONDIALOG_H
#include <itemdialog.h>
#include "logger.h"

class JTextField;
class CatalogPanel;
class NamedIcon;
class IconDialog : public ItemDialog
{
    Q_OBJECT
public:
    //explicit IconDialog(QWidget *parent = 0);
    /*public*/ IconDialog(QString type, QString family, ItemPanel* parent, QMap <QString, NamedIcon*>* iconMap );

signals:

public slots:
    void doneAction();
    void addFamilyButtonAction();
    void deleteButtonAction();

private:
    /*private*/ bool		_newIconSet;// = false;
    Logger* log;
protected:
    /*protected*/ QMap <QString, NamedIcon*>*  _iconMap;
    /*protected*/ QWidget*       _iconPanel;
    /*protected*/ CatalogPanel*  _catalog;
    /*protected*/ JTextField*    _familyName;
    /*protected*/ QPushButton*   _addFamilyButton;
    /*protected*/ QPushButton*   _deleteButton;
    /*protected*/ void makeAddSetButtonPanel(QWidget* buttonPanel);
    // Only multiSensor adds and deletes icons
    /*protected*/ void makeAddIconButtonPanel(QWidget* buttonPanel, QString addTip, QString deleteTip);
    /*protected*/ bool doDoneAction();
    /*protected*/ void addFamilySet();
    /*protected*/ void deleteFamilySet();
    /*protected*/ void makeDoneButtonPanel(QWidget* buttonPanel);
//    /*protected*/ void makeCreateButtonPanel(QWidget* buttonPanel);
    /*protected*/ QWidget* makeIconPanel(QMap<QString, NamedIcon *> *iconMap);
    void checkIconSizes();
    /*protected*/ QMap<QString, NamedIcon *> *clone(QMap<QString, NamedIcon *> *map);
};

#endif // ICONDIALOG_H
