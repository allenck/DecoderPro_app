#ifndef JMRISCRIPTENGINEMANAGER_H
#define JMRISCRIPTENGINEMANAGER_H

#include <QObject>
#include <QMap>

class Logger;
class File;
class PythonInterpreter;
class ScriptEngineManager;
class ScriptEngine;
class ScriptEngineFactory;
class ScriptContext;
class JmriScriptEngineManager : public QObject
{
 Q_OBJECT
public:
 explicit JmriScriptEngineManager(QObject *parent = 0);
 /*public*/ static /*final*/ QString PYTHON;// = "jython";
 /*public*/ static JmriScriptEngineManager* getDefault();
 /*public*/ void runScript(File* file);
 /*public*/ QObject* eval(File* file); //throws ScriptException, FileNotFoundException, IOException
 /*public*/ ScriptEngineManager* getManager();
 /*public*/ ScriptEngine* getEngineByExtension(QString extension);
 /*public*/ ScriptEngine* getEngine(QString engineName);
 /*public*/ void initializePython();

signals:

public slots:
 
private:
 Logger* log;
 /*private*/ /*final*/ ScriptEngineManager* manager;// = new ScriptEngineManager();
 /*private*/ /*final*/ QMap<QString, QString> names;// = new HashMap<>();
 /*private*/ /*final*/ QMap<QString, ScriptEngineFactory*> factories;// = new HashMap<>();
 /*private*/ /*final*/ QMap<QString, ScriptEngine*> engines;// = new HashMap<>();
 /*private*/ /*final*/ ScriptContext* context;
 /*private*/ PythonInterpreter* jython;// = NULL;
 bool firstTime;
};

#endif // JMRISCRIPTENGINEMANAGER_H
