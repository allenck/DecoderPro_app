#ifndef PRINTROSTERACTION_H
#define PRINTROSTERACTION_H
#include "jmriabstractaction.h"
#include "libPr3_global.h"

class JmriJFrame;
class LIBPR3SHARED_EXPORT PrintRosterAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit PrintRosterAction(QObject *parent = 0);
 /*public*/ Q_INVOKABLE PrintRosterAction(QString s, WindowInterface* wi);
 /*public*/ Q_INVOKABLE PrintRosterAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ Q_INVOKABLE PrintRosterAction(QString actionName, JmriJFrame* frame, bool preview,QObject *parent);
 ~PrintRosterAction(){}
 PrintRosterAction(const PrintRosterAction& other) : JmriAbstractAction(other.text(), other.icon(), (WindowInterface*)other.parent()) {}
 /*public*/ void setPreview(bool preview);
 /*public*/ JmriPanel* makePanel() ;
 /*public*/ Q_INVOKABLE void setParameter(QString parameter, QString value);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 void common();
 /**
  * Variable to set whether this is to be printed or previewed
  */
 bool isPreview;
 /**
  * Frame hosting the printing
  */
 JmriJFrame* mFrame;// = new Frame();
 Logger* log;
};
Q_DECLARE_METATYPE(PrintRosterAction)
#endif // PRINTROSTERACTION_H
