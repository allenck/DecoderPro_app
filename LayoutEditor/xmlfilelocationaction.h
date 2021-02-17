#ifndef XMLFILELOCATIONACTION_H
#define XMLFILELOCATIONACTION_H

#include "abstractaction.h"
class QTextBrowser;
class XmlFileLocationAction : public AbstractAction
{
    Q_OBJECT
public:
    XmlFileLocationAction(QObject* parent);
public slots:
    /*public*/ void actionPerformed(JActionEvent* ev = 0);
private:
    void addLogFiles(QTextBrowser* pane, QString logDir);

};

#endif // XMLFILELOCATIONACTION_H
