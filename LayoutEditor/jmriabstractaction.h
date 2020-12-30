#ifndef JMRIABSTRACTACTION_H
#define JMRIABSTRACTACTION_H

#include "abstractaction.h"
#include "windowinterface.h"
#include "liblayouteditor_global.h"
#include "jmripanel.h"

class LIBLAYOUTEDITORSHARED_EXPORT JmriAbstractAction : public AbstractAction
{
 Q_OBJECT
public:
 //explicit JmriAbstractAction();
 JmriAbstractAction(QObject *parent = nullptr);
 /*public*/  JmriAbstractAction(QString s, WindowInterface* wi);
 /*public*/  JmriAbstractAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/  void setContext(QObject* context);
 /*public*/  JmriAbstractAction(QString s, QObject *parent);
 /*public*/  void setWindowInterface(WindowInterface* wi);
 /*public*/  void setName(QString name);
 ///*public*/  JmriAbstractAction* setHint(WindowInterface::Hint hint);
 /*public*/  void dispose();
 /*public*/  virtual JmriPanel* makePanel();
 /*public*/  virtual void setParameter(QString parameter, QString value) ;
 /*public*/  virtual void setParameter(QString parameter, QObject* value);

signals:

public slots:
 /*public*/  virtual void actionPerformed(JActionEvent* e = 0);

private:
 //private static final long serialVersionUID = 373576744806206486L;
 void common();
 JmriPanel* cache;// = NULL;

protected:
 ///*protected*/ WindowInterface::Hint hint;// = WindowInterface::Hint.DEFAULT;
 /*protected*/ WindowInterface* wi;
 /*protected*/ QObject* context;// = null;

};

#endif // JMRIABSTRACTACTION_H
