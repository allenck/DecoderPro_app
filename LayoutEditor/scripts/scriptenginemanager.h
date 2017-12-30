#ifndef SCRIPTENGINEMANAGER_H
#define SCRIPTENGINEMANAGER_H

#include <QObject>
#include <QSet>
#include <QMap>

class ScriptEngine;
class Bindings;
class ScriptEngineFactory;
class ClassLoader;
class ScriptEngineManager : public QObject
{
 Q_OBJECT
public:
 explicit ScriptEngineManager(QObject *parent = 0);
/*public*/ ScriptEngineManager(ClassLoader* loader, QObject *parent = 0);
 /*public*/ ScriptEngine* getEngineByName(QString shortName);
 /*public*/ void setBindings(Bindings* bindings);
 /*public*/ Bindings* getBindings();
 /*public*/ QList<ScriptEngineFactory*> getEngineFactories();

signals:

public slots:
private:
 /*private*/ static /*final*/ bool DEBUG;// = false;
 /** Set of script engine factories discovered. */
 /*private*/ QSet<ScriptEngineFactory*> engineSpis;

 /** Map of engine name to script engine factory. */
 /*private*/ QMap<QString, ScriptEngineFactory*> nameAssociations;

 /** Map of script file extension to script engine factory. */
 /*private*/ QMap<QString, ScriptEngineFactory*> extensionAssociations;

 /** Map of script script MIME type to script engine factory. */
 /*private*/ QMap<QString, ScriptEngineFactory*> mimeTypeAssociations;

 /** Global bindings associated with script engines created by this manager. */
 /*private*/ Bindings* globalScope;
 /*private*/ void init(/*final*/ ClassLoader* loader);
 /*private*/ void initEngines(/*final*/ ClassLoader* loader);

};

#endif // SCRIPTENGINEMANAGER_H
