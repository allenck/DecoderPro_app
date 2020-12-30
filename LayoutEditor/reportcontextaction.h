#ifndef REPORTCONTEXTACTION_H
#define REPORTCONTEXTACTION_H

#include "abstractaction.h"
#include <qzeroconf.h>

class JTextArea;
class JmriPanel;
class JFrame;
class QLabel;
class WindowInterface;
class ReportContextAction : public AbstractAction
{
 Q_OBJECT
public:
 /*public*/ ReportContextAction(QObject* parent);
 ReportContextAction(QString s, WindowInterface* wi);
 /*public*/ ReportContextAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ JmriPanel* makePanel();
public slots:
 /*public*/ void actionPerformed(JActionEvent* ev = 0)override;
 void on_copyClicked();
 void on_closeClicked();
private:
 void common();
 JTextArea* pane;
 JFrame* frame;
 QZeroConf* zeroConf;

 void addString(QString val);
 void addProperty(QString prop);
};

#endif // REPORTCONTEXTACTION_H
