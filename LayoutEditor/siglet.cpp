#include "siglet.h"

//Siglet::Siglet(QObject *parent) :
//    AbstractAutomaton(parent)
//{
//}
/**
 * A Siglet is a "an embedded signal automation", like an "applet"
 * an embedded application.
 * <P>
 * Subclasses must load the inputs and outputs arrays
 * during the defineIO method. When any of these change,
 * the Siglet must then recompute and apply the output signal settings.
 * <P>
 * You can't assume that Siglets run in their own thread; they
 * should not use wait() in any of it's various forms.
 * <P>
 * Do not assume that Siglets will always inherit from AbstractAutomaton;
 * that may be an implementation artifact.
 * <P>
 * Do not have any overlap between the items in the input and output
 * lists; this will cause a recursive invocation when the output changes.
 *
 * @author	Bob Jacobsen    Copyright (C) 2003
 * @version     $Revision: 17977 $
 */
// /*public*/ class Siglet extends AbstractAutomaton {

/*public*/
Siglet::Siglet(QObject *parent) : AbstractAutomaton(parent)
{ //super();
}

/*public*/
Siglet::Siglet(QString name, QObject* parent) : AbstractAutomaton(name, parent)
{ //super(name);
}


/**
 * User-provided routine to define the input and output
 * objects to be handled.
 */
/*public*/ void Siglet::defineIO() {}

/**
 * User-provided routine to compute new output state
 * and apply it.
 */
/*public*/ void Siglet::setOutput() {}

/**
 * Implements AbstractAutomaton method to initialise
 * connections to the layout.
 */
/*protected*/ void Siglet::init() {
    defineIO();
}

/**
 * Implements AbstractAutomaton method to wait for
 * state changes and respond.
 */
/*protected*/ bool Siglet::handle() {
    // update the result
    setOutput();
    // wait for changes
    waitChange(inputs);
    // and repeat
    return true;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // OK until Java 1.6 allows cheap array copy
///*public*/ void setInputs(NamedBean[] in) {
//    inputs = in;
//}
