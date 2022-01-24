#ifndef FIRSTTIMESTARTUPWIZARDACTION_H
#define FIRSTTIMESTARTUPWIZARDACTION_H
#include "jmriabstractaction.h"

class Apps3;
class JmriJFrame;
class JActionEvent;
class FirstTimeStartUpWizardAction : public JmriAbstractAction
{
 Q_OBJECT

public:
 /*public*/ FirstTimeStartUpWizardAction(QString s, WindowInterface* wi, QObject* parent);
 /*public*/ FirstTimeStartUpWizardAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ FirstTimeStartUpWizardAction(QString s, QObject* parent);
 /*public*/ JmriPanel* makePanel();
 /*public*/ void setApp(Apps3* app);


public slots:
 /*public*/ void actionPerformed(ActionEvent* e = nullptr);

private:
 void common();
 static JmriJFrame* f;
 Apps3* app;

};

#endif // FIRSTTIMESTARTUPWIZARDACTION_H
