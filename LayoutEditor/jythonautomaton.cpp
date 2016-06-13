#include "jythonautomaton.h"
#include "instancemanager.h"
#include "PythonQt.h"

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

//    try {
//        // PySystemState.initialize();
//        Class<?> cs = Class.forName("org.python.core.PySystemState");
//        java.lang.reflect.Method initialize
//                = cs.getMethod("initialize", (Class[]) NULL);
//        initialize.invoke(NULL, (Object[]) NULL);

        // interp = new PythonInterpreter();
//        interp = Class.forName("org.python.util.PythonInterpreter").newInstance();
 interp = PythonQt::self()->getMainModule();

        // load some general objects
        // interp.set("dcc", InstanceManager.commandStationInstance());
        // interp.set("self", this);
//        java.lang.reflect.Method set
//                = interp.getClass().getMethod("set", new Class[]{String.class, Object.class});
//        set.invoke(interp, new Object[]{"dcc", InstanceManager.commandStationInstance()});
 interp.addObject("dcc", InstanceManager::commandStationInstance());
//        set.invoke(interp, new Object[]{"self", this});
 interp.addObject("self", this);


 interp.evalFile(filename);

 connect(PythonQt::self(), SIGNAL(pythonStdErr(const QString&)), this, SLOT(On_stdErr(const QString&)));
#if 0
        // set up the method to exec python functions
        exec = interp.getClass().getMethod("exec", new Class[]{String.class});

        // have jython read the file
        exec.invoke(interp, new Object[]{"execfile(\"" + filename + "\")"});

        // execute the init routine in the jython class
        exec.invoke(interp, new Object[]{"init()"});
#endif
//    } catch (Exception e) {
//        log.error("Exception creating jython system objects: " + e);
//        e.printStackTrace();
//    }
}

void JythonAutomaton::On_stdErr(QString s)
{
 log->error(s);
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
//    try {
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
#endif
        return false;
//    } catch (Exception e) {
//        log.error("Exception invoking jython command: " + e);
//        e.printStackTrace();
//        return false;
//    }
}

//java.lang.reflect.Method exec;
