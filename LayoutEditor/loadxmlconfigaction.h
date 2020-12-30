#ifndef LOADXMLCONFIGACTION_H
#define LOADXMLCONFIGACTION_H
#include "loadstorebaseaction.h"

class Logger;
class File;
class JFileChooser;
class LoadXmlConfigAction : public LoadStoreBaseAction
{
 Q_OBJECT
public:
 explicit LoadXmlConfigAction(QObject *parent = 0);
 /*public*/ LoadXmlConfigAction(QString s,QObject *parent);
 ~LoadXmlConfigAction() {}
 LoadXmlConfigAction(const LoadXmlConfigAction&) : LoadStoreBaseAction() {}
 static /*public*/ File* getFile(JFileChooser* fileChooser);
 static /*public*/ File* getFileCustom(JFileChooser* fileChooser);
 static /*public*/ QString currentFile;
signals:

public slots:
 /*public*/ virtual void actionPerformed(JActionEvent* e = 0);

private:
 void common();
 static Logger* log;
protected:
 /*protected*/ bool loadFile(JFileChooser* fileChooser);

};
Q_DECLARE_METATYPE(LoadXmlConfigAction)
#endif // LOADXMLCONFIGACTION_H
