#ifndef SWINGCONFIGURATORINTERFACETESTACTIONACTION_H
#define SWINGCONFIGURATORINTERFACETESTACTIONACTION_H

#include "abstractaction.h"

class SwingConfiguratorInterfaceTestActionAction : public AbstractAction
{
    Q_OBJECT
public:
    explicit SwingConfiguratorInterfaceTestActionAction(QObject *parent = nullptr);
public slots:
 void actionPerformed();
private:
 static Logger* log;};

#endif // SWINGCONFIGURATORINTERFACETESTACTIONACTION_H
