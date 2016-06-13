#include "jythonsiglet.h"
#include "instancemanager.h"
#include "turnout.h"
#include "sensor.h"
#include "signalhead.h"

//JythonSiglet::JythonSiglet(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * This sample Automaton invokes a Jython interpreter to handle a script that
 * defines a Siglet implementation.
 * <P>
 * The python file should define two functions:
 * <UL>
 * <LI>defineIO()
 * <LI>setOutput()
 * </UL>
 * <P>
 * Access is via Java reflection so that both users and developers can work
 * without the jython.jar file in the classpath. To make it easier to read the
 * code, the "non-reflection" statements are in the comments.
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 * @version $Revision: 28746 $
 */
// /*public*/ class JythonSiglet extends Siglet {


/*public*/ JythonSiglet::JythonSiglet(QString file, QObject *parent) :
Siglet(parent) {
    filename = file;
    log = new Logger("JythonSiglet");
}


/**
 * Initialize this object.
 * <UL>
 * <LI>Create the Python interpreter.
 * <LI>Load the generally-available objects
 * <LI>Read the file
 * <LI>Run the python defineIO routine
 * </UL>
 * Initialization of the Python in the actual script file is deferred until
 * the {@link #handle} method.
 */
/*public*/ void JythonSiglet::defineIO()
{

//    try {
        // PySystemState.initialize();
//        Class<?> cs = Class.forName("org.python.core.PySystemState");
//        java.lang.reflect.Method initialize
//                = cs.getMethod("initialize", (Class[]) null);
//        initialize.invoke(null, (Object[]) null);

//        // interp = new PythonInterpreter();
//        interp = Class.forName("org.python.util.PythonInterpreter").newInstance();
 interp = PythonQt::self()->getMainModule();


        // load some general objects
        // interp.set("dcc", InstanceManager::commandStationInstance());Qt
        // interp.set("self", this);

#if 0
        java.lang.reflect.Method set
                = interp.getClass().getMethod("set", new Class[]{String.class, Object.class});
        set.invoke(interp, new Object[]{"self", this});

        set.invoke(interp, new Object[]{"inputs", inputs});
        set.invoke(interp, new Object[]{"outputs", outputs});

        set.invoke(interp, new Object[]{"turnouts", InstanceManager::turnoutManagerInstance()});
        set.invoke(interp, new Object[]{"sensors", InstanceManager::sensorManagerInstance()});
        set.invoke(interp, new Object[]{"signals", InstanceManager::signalHeadManagerInstance()});
        set.invoke(interp, new Object[]{"dcc", InstanceManager::commandStationInstance()});

        set.invoke(interp, new Object[]{"CLOSED", Integer.valueOf(Turnout::CLOSED)});
        set.invoke(interp, new Object[]{"THROWN", Integer.valueOf(Turnout::THROWN)});
        set.invoke(interp, new Object[]{"ACTIVE", Integer.valueOf(Sensor::ACTIVE)});
        set.invoke(interp, new Object[]{"INACTIVE", Integer.valueOf(Sensor::INACTIVE)});
        set.invoke(interp, new Object[]{"GREEN", Integer.valueOf(SignalHead::GREEN)});
        set.invoke(interp, new Object[]{"YELLOW", Integer.valueOf(SignalHead::YELLOW)});
        set.invoke(interp, new Object[]{"RED", Integer.valueOf(SignalHead::RED)});

        // set up the method to exec python functions
        exec = interp.getClass().getMethod("exec", new Class[]{String.class});

        // have jython read the file
        exec.invoke(interp, new Object[]{"execfile(\"" + filename + "\")"});

        // execute the init routine in the jython class
        exec.invoke(interp, new Object[]{"defineIO()"});

        System.out.println("inputs[0]: " + inputs[0]);
#endif
//    } catch (IllegalAccessException e) {
//        log.error("IllegalAccessException creating jython system objects", e);
//    } catch (NoSuchMethodException e) {
//        log.error("NoSuchMethodException creating jython system objects", e);
//    } catch (ClassNotFoundException e) {
//        log.error("ClassNotFoundException creating jython system objects", e);
//    } catch (InstantiationException e) {
//        log.error("InstantiationException creating jython system objects", e);
//    } catch (java.lang.reflect.InvocationTargetException e) {
//        log.error("InvocationTargetException creating jython system objects", e);
//    }
}

/**
 * Invoke the Jython setOutput function
 */
/*public*/ void JythonSiglet::setOutput() {
    if (interp == NULL) {
        log->error("No interpreter, so cannot handle automat");
        return;
    }
#if 0
    try {
        // execute the handle routine in the jython
        exec.invoke(interp, new Object[]{"setOutput()"});
    } catch (Exception e) {
        log->error("Exception invoking jython command: " + e);
        //e.printStackTrace();
    }
#endif
}

//java.lang.reflect.Method exec;
