#ifndef PICKSINGLEPANEL_H
#define PICKSINGLEPANEL_H

#include <QWidget>
#include "jtextfield.h"
#include "jtable.h"
#include "picklistmodel.h"
#include "actionlistener.h"

//template<class T>
class PickSinglePanel : public QWidget
{
 Q_OBJECT
public:
 explicit PickSinglePanel(PickListModel* model, QWidget *parent = nullptr);
 /*public*/ NamedBeanHandle<NamedBean*>* getSelectedBeanHandle();
 /*public*/ JTable* getTable();
signals:

public slots:
private:
 /*private*/ int ROW_HEIGHT;

 //PickListModel<T> _model;
 PickListModel* _model;

 QWidget* _addPanel;
 QWidget* _cantAddPanel;
 JTextField* _sysNametext;
 JTextField* _userNametext;
 JTable* _table;
 //JScrollPane _scroll;
 /*private*/ QWidget* makeAddToTablePanel();
 void addToTable();

 friend class PSPOkListener;
 friend class PSPCancelListener;
};
class PSPOkListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 PickSinglePanel* panel;
public:
 PSPOkListener(PickSinglePanel* panel);
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)override;
};

class PSPCancelListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 PickSinglePanel* panel;
public:
 PSPCancelListener(PickSinglePanel* panel);
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)override;
};

#endif // PICKSINGLEPANEL_H
