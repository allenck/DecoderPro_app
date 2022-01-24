#include "jynstrumentfactory.h"
#include "loggerfactory.h"
#include "file.h"
#include "scriptengine.h"
#include "jmriscriptenginemanager.h"
#include "filereader.h"
#include "jynstrumentpopupmenu.h"

/**
 * A JynstrumentFactory handles instantiation and connection of
 * {@link Jynstrument} instances.
 *
 * @see Jynstrument
 * @author Lionel Jeanson Copyright 2009
 * @since 2.7.8
 */
///*public*/ class JynstrumentFactory {

    /*private*/ /*static*/ /*final*/ QString JynstrumentFactory::instanceName = "jynstrumentObjectInstance";

/*public*/ /*static*/ Jynstrument* JynstrumentFactory::createInstrument(QString path, QObject* context) {
    QString className = validate(path);
    if (className == NULL) {
        // Try containing directory
        File* f = new File(path);
        path = f->getParent();
        className = validate(path);
        if (className == NULL) {
            log->error("Invalid instrument");
            return NULL;
        }
    }
    QString jyFile = path + File::separator + className + ".py";
    ScriptEngine* engine = JmriScriptEngineManager::getDefault()->getEngine(JmriScriptEngineManager::PYTHON);
    Jynstrument* jyns;
    FileReader* fr;
    try {
         fr = new FileReader(jyFile);
        try {
            engine->eval(fr);
            engine->eval(instanceName + " = " + className + "()");
            jyns = (Jynstrument*) engine->get(instanceName);
            engine->eval("del " + instanceName);
         }
         catch (Exception* ex)
         {}
//        finally {
//            fr.close();
//        }
    } catch (IOException*  ex) {
        log->error("Exception while creating Jynstrument: " + ex->getMessage());
        return NULL;
    }
    catch ( ScriptException* ex) {
       log->error("Exception while creating Jynstrument: " + ex->getMessage());
       return NULL;
    }
    fr->close();

    jyns->setClassName(className);
    jyns->setContext(context);
    if (!jyns->validateContext()) {  // check validity of this Jynstrument for that extended context
        log->error(tr("Invalid context for Jynstrument, host is ") + context->metaObject()->className() + " and " + jyns->getExpectedContextClassName() + " kind of host is expected");
        return NULL;
    }
    jyns->setJythonFile(jyFile);
    jyns->setFolder(path);
    jyns->setPopUpMenu(new JynstrumentPopupMenu(jyns));
    jyns->init();  // GO!
    return jyns;
}

// validate Jynstrument path, return className
/*private*/ /*static*/ QString JynstrumentFactory::validate(QString path) {
    if (path == NULL) {
        return NULL;
    }
    if (path.length() - 4 < 0) {
        log->error("File name too short");
        return NULL;
    }
    File* f = new File(path);

    // Path must be a folder named xyz.jin
    if (!f->isDirectory()) {
        log->debug("Not a directory, trying parent");
        return NULL;
    }
    if (path.mid(path.length() - 4).toLower()  != ".jyn")  {
        log->debug("Not an instrument");
        return NULL;
    }

    // must contain a xyz.py file and construct class name from filename (xyz actually) xyz class in xyz.py file in xyz.jin folder
    QStringList children = f->list();
    QString className = NULL;
    QString assumedClassName = f->getName().mid(0, f->getName().length() - 4);
    for (int i = 0; i < children.length(); i++) {
        if ((children[i]).toLower() == (assumedClassName + ".py")) {
            return assumedClassName; // got exact match for folder name
        } else if (children[i].mid(children[i].length() - 3).toLower() == (".py") ) {
            className = children[i].mid(0, children[i].length() - 3); // else take whatever comes
        }
    }
    return className;
}

/*private*/ /*final*/ /*static*/ Logger* JynstrumentFactory::log = LoggerFactory::getLogger("JynstrumentFactory");
