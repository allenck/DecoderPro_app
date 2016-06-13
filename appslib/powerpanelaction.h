#ifndef POWERPANELACTION_H
#define POWERPANELACTION_H

#include "jmriabstractaction.h"
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT PowerPanelAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 explicit PowerPanelAction(QObject *parent = 0);
 ~PowerPanelAction() {}
 PowerPanelAction(const PowerPanelAction& other) : JmriAbstractAction(tr("Power Control"), (QObject*)other.parent()) {}
 /*public*/ PowerPanelAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
};
Q_DECLARE_METATYPE(PowerPanelAction)
#endif // POWERPANELACTION_H
