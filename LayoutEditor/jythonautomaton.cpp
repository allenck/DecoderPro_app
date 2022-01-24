#include "jythonautomaton.h"
#include "instancemanager.h"
#include "PythonQt.h"
#include "pythonwrappers.h"
#include <QApplication>

//JythonAutomaton::JythonAutomaton(QObject *parent) :
//  AbstractAutomaton(parent)
//{
//}
/**
 * This sample Automaton invokes a Jython interpreter to handle a script.
 * <P>
 * Access is via Java reflection so that both users and developers can work
 * without the jython.jar file in the classpath. To make it easier to read the
 * code, the "non-reflection" statements are in the comments
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 * @version $Revision: 28746 $
 */
// /*public*/ class JythonAutomaton extends AbstractAutomaton {



/*public*/ JythonAutomaton::JythonAutomaton(QString file, QObject *parent) :
  AbstractAutomaton(parent)
{
    filename = file;
    log = new Logger("JythonAutomaton");
    //PythonWrappers::defineClasses();
}


/**
 * Initialize this object.
 * <UL>
 * <LI>Create the Python interpreter.
 * <LI>Load the generally-available objects
 * <LI>Read the file
 * <LI>Run the python init routine
 * </UL>
 * Initialization of the Python in the actual script file is deferred until
 * the {@link #handle} method.
 */
/*protected*/ void JythonAutomaton::init() {

    try {
//        // PySystemState.initialize();
//        Class<?> cs = Class.forName("org.python.core.PySystemState");
//        java.lang.reflect.Method initialize
//                = cs.getMethod("initialize", (Class[]) NULL);
//        initialize.invoke(NULL, (Object[]) NULL);

        // interp = new PythonInterpreter();
//        interp = Class.forName("org.python.util.PythonInterpreter").newInstance();
 interp = PythonQt::self()->getMainModule();
 connect(PythonQt::self(), SIGNAL(pythonStdErr(const QString&)), this, SLOT(On_stdErr(const QString&)));

        // load some general objects
        // interp.set("dcc", InstanceManager.commandStationInstance());
        // interp.set("self", this);
//        java.lang.reflect.Method set
//                = interp.getClass().getMethod("set", new Class[]{String.class, Object.class});
//        set.invoke(interp, new Object[]{"dcc", InstanceManager.commandStationInstance()});
 interp.addObject("dcc", InstanceManager::getDefault("CommandStation"));
//        set.invoke(interp, new Object[]{"self", this});
 if(bHasError)
     throw new Exception("error setting CommandStation");
 interp.addObject("self", this);


 interp.evalFile(filename);
 if(bHasError)
     throw new Exception(tr("error evaluating file %s").arg(filename));

#if 0
        // set up the method to exec python functions
        exec = interp.getClass().getMethod("exec", new Class[]{String.class});

        // have jython read the file
        exec.invoke(interp, new Object[]{"execfile(\"" + filename + "\")"});

        // execute the init routine in the jython class
        exec.invoke(interp, new Object[]{"init()"});
#endif
    } catch (Exception* e) {
        log->error("Exception creating jython system objects: " + e->getMessage());
        //e.printStackTrace();
    }
}

void JythonAutomaton::On_stdErr(QString s)
{
 //log->error(s);
 bHasError = true;
 _stdErr += s;
 int idx;
 while ((idx = _stdErr.indexOf('\n'))!=-1)
 {
  log->error( _stdErr.left(idx) );
   _stdErr = _stdErr.mid(idx+1);
 }
}

/**
 * Invoke the Jython automat function
 *
 * @return True to continue operation if successful
 */
/*protected*/ bool JythonAutomaton::handle() {
    if (interp == NULL) {
        log->error("No interpreter, so cannot handle automat");
        return false; // to terminate operation
    }
    try {
        // execute the handle routine in the jython and check return value
#if 0
        exec.invoke(interp, new Object[]{"retval = handle()"});
        java.lang.reflect.Method get
                = interp.getClass().getMethod("get", new Class[]{String.class});
        Object retval = get.invoke(interp, new Object[]{"retval"});
        System.out.println("retval = " + retval);
        if (retval.toString().equals("1")) {
            return true;
        }
#else
//        if(!r.isValid())
//            log->warn(tr("error finding handle()"));
        QVariant retval = interp.getVariable("retval");
        if(!retval.isValid())
        {
            QVariant r = interp.evalScript("retval = handle()");
            bool br = r.toBool();
        }
        if(bHasError)
            throw new Exception(tr("an error has occurred in the script"));
//        log->debug(tr("r = %1").arg(r.toString()));
//        QVariant retval = interp.call("retval");
        if (retval.toBool()) {
            return true;
        }

#endif
        qApp->processEvents();
        return true;
    } catch (Exception* e) {
        log->error("Exception invoking jython command: " + e->getMessage());
//        e.printStackTrace();
        return false;
    }
}

//java.lang.reflect.Method exec;
