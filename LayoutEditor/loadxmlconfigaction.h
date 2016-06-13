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
 explicit LoadXmlConfigAction(QObject *parent);
 /*public*/ LoadXmlConfigAction(QString s,QObject *parent);
 static /*public*/ File* getFile(JFileChooser* fileChooser);
 static /*public*/ File* getFileCustom(JFileChooser* fileChooser);

signals:

public slots:
 /*public*/ virtual void actionPerformed(ActionEvent* e = 0);

private:
 void common();
 Logger* log;
protected:
 /*protected*/ bool loadFile(JFileChooser* fileChooser);

};

#endif // LOADXMLCONFIGACTION_H
