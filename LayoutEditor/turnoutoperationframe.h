#ifndef TURNOUTOPERATIONFRAME_H
#define TURNOUTOPERATIONFRAME_H

#include <QDialog>
#include "liblayouteditor_global.h"
#include "propertychangelistener.h"

class TurnoutOperation;
class PropertyChangeEvent;
class QTabWidget;
class TurnoutOperationConfig;
class LIBLAYOUTEDITORSHARED_EXPORT TurnoutOperationFrame : public QDialog, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 public:
    explicit TurnoutOperationFrame(QWidget *parent = 0);
  QObject* pself() override {return (QObject*)this;}

 signals:

 public slots:
    void propertyChange(PropertyChangeEvent*) override;
 private:
    TurnoutOperationFrame* _self;// = this;
    TurnoutOperationConfig* currentConfig;// = null;
    TurnoutOperation* currentOperation;// = null;
    QString previousSelectionName;// = "";
    QTabWidget* tabPane;
    /*private*/ void populateTabs();
    /*private*/ void changeTab();

 private slots:
    /*private*/ void doOK();
    /*private*/ void doDelete();

};

#endif // TURNOUTOPERATIONFRAME_H
