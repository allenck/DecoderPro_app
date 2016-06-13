#ifndef UPDATEDECODERDEFINITIONACTION_H
#define UPDATEDECODERDEFINITIONACTION_H
#include "jmriabstractaction.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT UpdateDecoderDefinitionAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 explicit UpdateDecoderDefinitionAction(QObject *parent = 0);
 ~UpdateDecoderDefinitionAction() {}
 UpdateDecoderDefinitionAction(const UpdateDecoderDefinitionAction& other) : JmriAbstractAction(other.text(), other.icon(), (WindowInterface*)other.parent()) {}
 /*public*/ UpdateDecoderDefinitionAction(QString s, WindowInterface* wi, QObject *parent);
 /*public*/ UpdateDecoderDefinitionAction(QString s, QIcon i, WindowInterface* wi, QObject *parent) ;
 /*public*/ UpdateDecoderDefinitionAction(QString s, QObject *parent);
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 void common();
 Logger* log;
};
Q_DECLARE_METATYPE(UpdateDecoderDefinitionAction)
#endif // UPDATEDECODERDEFINITIONACTION_H
