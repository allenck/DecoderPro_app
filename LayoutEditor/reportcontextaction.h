#ifndef REPORTCONTEXTACTION_H
#define REPORTCONTEXTACTION_H

#include "abstractaction.h"

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
 /*public*/ void actionPerformed(ActionEvent* ev = 0);
 void on_copyClicked();
 void on_closeClicked();
private:
 void common();
 QLabel* pane;
 JFrame* frame;
 void addString(QString val);
 void addProperty(QString prop);
};

#endif // REPORTCONTEXTACTION_H
