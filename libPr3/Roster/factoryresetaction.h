#ifndef FACTORYRESETACTION_H
#define FACTORYRESETACTION_H

#include <QAction>
#include "libPr3_global.h"
#include "logger.h"

class JFrame;
class ResetTableModel;
class LIBPR3SHARED_EXPORT FactoryResetAction : public QAction
{
    Q_OBJECT

public:
    FactoryResetAction(QString actionName, ResetTableModel* rpModel, QWidget *parent);

    ~FactoryResetAction() {}

private:
    ResetTableModel* rModel;
    QWidget* mParent ;
    Logger* log;
public slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);
};

#endif // FACTORYRESETACTION_H
