#ifndef LOADXMLUSERACTION_H
#define LOADXMLUSERACTION_H
#include "loadxmlconfigaction.h"

class JActionEvent;
class File;
class LoadXmlUserAction : public LoadXmlConfigAction
{
 Q_OBJECT
public:
 explicit LoadXmlUserAction(QObject *parent = 0);
 /*public*/ LoadXmlUserAction(QString s,  QObject *parent);
 /*public*/ static File* getCurrentFile();

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0) override;

private:
 static File* currentFile;// = null;
 void common();
 Logger* log;

};

#endif // LOADXMLUSERACTION_H
