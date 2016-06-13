#ifndef RUNJYTHONSCRIPT_H
#define RUNJYTHONSCRIPT_H

#include "jmriabstractaction.h"
#include "liblayouteditor_global.h"

class QWidget;
class Logger;
class JFileChooser;
class File;
class LIBLAYOUTEDITORSHARED_EXPORT RunJythonScript : public JmriAbstractAction
{
 Q_OBJECT
public:
 explicit RunJythonScript(QObject *parent = 0);
 /*public*/ RunJythonScript(QString s, QWidget* wi);
 /*public*/ RunJythonScript(QString s, QIcon i, QWidget* wi);
 /*public*/ RunJythonScript(QString name);
 /*public*/ RunJythonScript(QString name, QObject *parent);
 /*public*/ RunJythonScript(QString name, File* file, QObject *parent );
 ~RunJythonScript() {}
 RunJythonScript(const RunJythonScript& other) : JmriAbstractAction(other.text(), other.parent()) {}
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
 void On_stdErr(const QString& s);

private:
 File* configuredFile;
 /**
  * We always use the same file chooser in this class, so that the user's
  * last-accessed directory remains available.
  */
 static JFileChooser* fci;// = NULL;
 void common();
 Logger* log;
 File* selectFile();
 void invoke(File* file);
 QString _stdErr;
 static bool firstTime;
};
Q_DECLARE_METATYPE(RunJythonScript)
#endif // RUNJYTHONSCRIPT_H
