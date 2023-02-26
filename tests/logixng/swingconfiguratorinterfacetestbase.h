#ifndef SWINGCONFIGURATORINTERFACETESTBASE_H
#define SWINGCONFIGURATORINTERFACETESTBASE_H

#include <QObject>
#include "junitutil.h"

class JDialogOperator;
class DefaultConditionalNG;
class SwingConfiguratorInterfaceTestBase : public QObject
{
    Q_OBJECT
public:
    explicit SwingConfiguratorInterfaceTestBase(QObject *parent = nullptr);

signals:

protected:
    /*protected*/ JDialogOperator* editItem(
            DefaultConditionalNG* conditionalNG,
            QString title1, QString title2, int row);

};

#endif // SWINGCONFIGURATORINTERFACETESTBASE_H
