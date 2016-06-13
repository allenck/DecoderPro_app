#ifndef PANELPROACTION_H
#define PANELPROACTION_H
#include "jmriabstractaction.h"
#include "appslib_global.h"

class AppsLaunchFrame;
class APPSLIBSHARED_EXPORT PanelProAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit PanelProAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE PanelProAction(QString s, WindowInterface* wi) ;
 /*public*/ Q_INVOKABLE PanelProAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Q_INVOKABLE PanelProAction(QString s, QObject* parent);
 ~PanelProAction() {}
 PanelProAction(const PanelProAction&) : JmriAbstractAction() {}
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 AppsLaunchFrame* frame;// = null;
 void common();
};
Q_DECLARE_METATYPE(PanelProAction)
#endif // PANELPROACTION_H
