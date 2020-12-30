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
    /*public*/ void on_openUserFilesButton(JActionEvent* event = 0);
    /*public*/ void on_openRosterButton(JActionEvent* event = 0);
    /*public*/ void on_openProfileButton(JActionEvent* event = 0);
    /*public*/ void on_openSettingsButton(JActionEvent* event = 0);
    /*public*/ void on_openScriptsButton(JActionEvent* event = 0);
    /*public*/ void on_openProgramButton(JActionEvent* event = 0);
    /*public*/ void on_openLogFilesButton(JActionEvent* event = 0);
private:
    void addLogFiles(QTextBrowser* pane, QString logDir);

};

#endif // XMLFILELOCATIONACTION_H
