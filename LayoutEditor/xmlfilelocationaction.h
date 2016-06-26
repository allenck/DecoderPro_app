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
    /*public*/ void actionPerformed(ActionEvent* ev = 0);
    /*public*/ void on_openUserFilesButton(ActionEvent* event = 0);
    /*public*/ void on_openRosterButton(ActionEvent* event = 0);
    /*public*/ void on_openProfileButton(ActionEvent* event = 0);
    /*public*/ void on_openSettingsButton(ActionEvent* event = 0);
    /*public*/ void on_openScriptsButton(ActionEvent* event = 0);
    /*public*/ void on_openProgramButton(ActionEvent* event = 0);
    /*public*/ void on_openLogFilesButton(ActionEvent* event = 0);
private:
    void addLogFiles(QTextBrowser* pane, QString logDir);

};

#endif // XMLFILELOCATIONACTION_H
