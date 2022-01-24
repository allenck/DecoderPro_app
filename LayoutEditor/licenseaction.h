#ifndef LICENSEACTION_H
#define LICENSEACTION_H

#include "jmriabstractaction.h"

class LicenseAction : public JmriAbstractAction
{
 public:
  /*public*/ LicenseAction(QObject* parent);
  /*public*/ LicenseAction(QString s, QIcon i, WindowInterface* w);
  /*public*/ LicenseAction(QString s, WindowInterface* w);
  /*public*/ JmriPanel* makePanel() override;

};

#endif // LICENSEACTION_H
