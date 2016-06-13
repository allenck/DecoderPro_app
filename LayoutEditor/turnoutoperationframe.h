#ifndef TURNOUTOPERATIONFRAME_H
#define TURNOUTOPERATIONFRAME_H

#include <QDialog>
#include "liblayouteditor_global.h"

class TurnoutOperation;
class PropertyChangeEvent;
class QTabWidget;
class TurnoutOperationConfig;
class LIBLAYOUTEDITORSHARED_EXPORT TurnoutOperationFrame : public QDialog
{
    Q_OBJECT
 public:
    explicit TurnoutOperationFrame(QWidget *parent = 0);

 signals:

 public slots:
    void propertyChange(PropertyChangeEvent*);
 private:
    TurnoutOperationFrame* self;// = this;
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
