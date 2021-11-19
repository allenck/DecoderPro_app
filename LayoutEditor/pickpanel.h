#ifndef PICKPANEL_H
#define PICKPANEL_H

#include <QWidget>
#include <QTabWidget>
#include "actionlistener.h"
#include <QModelIndex>
#include "liblayouteditor_global.h"

class JActionEvent;
class ListSelectionEvent;
class ChangeEvent;
class PickListModel;
class JTextField;
class LIBLAYOUTEDITORSHARED_EXPORT PickPanel : public QWidget
{
    Q_OBJECT
public:
    //explicit PickPanel(QWidget *parent = 0);
    /*public*/ PickPanel(QList<PickListModel*> models, QWidget *parent = 0);
    /*public*/ void stateChanged(ChangeEvent* e);
//    /*public*/ void valueChanged(ListSelectionEvent* e);

signals:

public slots:
    void onRowClicked(QModelIndex index);

private:
    /*private*/ int ROW_HEIGHT;

    QList<PickListModel*> _models;
    QTabWidget* _tabPane;

    QWidget*      _addPanel;
    QWidget*      _cantAddPanel;
    JTextField*  _sysNametext;
    JTextField*  _userNametext;
    /*private*/ QWidget* makeAddToTablePanel();

    void addToTable();
protected:
//    void dragEnterEvent(QDragEnterEvent *);
//    void dragMoveEvent(QDragMoveEvent *);
 friend class ItActionListener;
};

class ItActionListener : public QObject, public ActionListener
{
  PickPanel* self;
  Q_OBJECT
  Q_INTERFACES(ActionListener)
public:
  ItActionListener(PickPanel* self);
public slots:
  /*public*/ void actionPerformed(JActionEvent* a = 0) ;
};

class PPCancelListener : public QObject, public ActionListener
{
  PickPanel* self;
  Q_OBJECT
  Q_INTERFACES(ActionListener)
public:
  PPCancelListener(PickPanel* self);
public slots:
  /*public*/ void actionPerformed(JActionEvent *) ;
};

#endif // PICKPANEL_H
