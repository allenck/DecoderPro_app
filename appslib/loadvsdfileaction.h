#ifndef LOADVSDFILEACTION_H
#define LOADVSDFILEACTION_H
#include "abstractaction.h"
#include "appslib_global.h"

class File;
class Logger;
class JFileChooser;
class APPSLIBSHARED_EXPORT LoadVSDFileAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit LoadVSDFileAction(QObject *parent = 0);
 /*public*/ LoadVSDFileAction(QString s, QObject *parent);
 /*public*/ static bool loadVSDFile(File* f);
 /*public*/ static bool loadVSDFile(QString fp);


signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);

private:
 JFileChooser* fileChooser;
 void common();
 static /*private*/ QString last_path;// = null;
 Logger* log;
};

#endif // LOADVSDFILEACTION_H
