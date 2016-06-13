#ifndef DUALDECODERTOOLACTION_H
#define DUALDECODERTOOLACTION_H

#include "jmriabstractaction.h"
#include "appslib_global.h"


class WindowInterface;
class APPSLIBSHARED_EXPORT DualDecoderToolAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 explicit DualDecoderToolAction(QObject *parent = 0);
 ~DualDecoderToolAction() {}
 DualDecoderToolAction(const DualDecoderToolAction& other) : JmriAbstractAction(other.text(), (QObject*)other.parent()) {}
 /*public*/ DualDecoderToolAction(QString s, WindowInterface* wi);
 /*public*/ DualDecoderToolAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ DualDecoderToolAction(QString s,QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
};
Q_DECLARE_METATYPE(DualDecoderToolAction)
#endif // DUALDECODERTOOLACTION_H
