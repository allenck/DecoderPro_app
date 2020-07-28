#include "control.h"

//Control::Control(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * {@link Line Lines} often have a set of controls, such as gain and pan, that affect
 * the audio signal passing through the line.  Java Sound's <code>Line</code> objects
 * let you obtain a particular control object by passing its class as the
 * argument to a {@link Line#getControl(Control.Type) getControl} method.
 * <p>
 * Because the various types of controls have different purposes and features,
 * all of their functionality is accessed from the subclasses that define
 * each kind of control.
 *
 * @author Kara Kytle
 *
 * @see Line#getControls
 * @see Line#isControlSupported
 * @since 1.3
 */
// /*public*/ abstract class Control {

/*public*/ /*static*/ /*final*/ bool Control::showProperty = false;
/*public*/ /*static*/ /*final*/ bool Control::showInstance = false;

/*public*/ /*static*/ /*final*/ bool Control::SHOW_PROPERTY = false;



// CONSTRUCTORS

/**
 * Constructs a Control with the specified type.
 * @param type the kind of control desired
 */
/*protected*/ Control::Control(Type* type, QObject* parent)
 : QObject(parent)
{
 this->type = type;
}


// METHODS

/**
 * Obtains the control's type.
 * @return the control's type.
 */
/*public*/ Control::Type* Control::getType() {
    return type;
}


// ABSTRACT METHODS

/**
 * Obtains a String describing the control type and its current state.
 * @return a String representation of the Control.
 */
/*public*/ QString Control::toString() {
    return QString(getType()->toString() + " Control");
}


/**
 * An instance of the <code>Type</code> class represents the type of
 * the control.  Static instances are provided for the
 * common types.
 */
///*public*/ static class Type {

//    // CONTROL TYPE DEFINES

//    // INSTANCE VARIABLES

//    /**
//     * Type name.
//     */
//    private String name;


    // CONSTRUCTOR

    /**
     * Constructs a new control type with the name specified.
     * The name should be a descriptive string appropriate for
     * labelling the control in an application, such as "Gain" or "Balance."
     * @param name  the name of the new control type.
     */
/*protected*/ Control::Type::Type(QString name, QObject* parent) : QObject(parent)
{
        this->name = name;
    }


    // METHODS

    /**
     * Finalizes the equals method
     */
    /*public*/ /*final*/ bool Control::Type::equals(QObject* obj) {
        //return super.equals(obj);
 return (this == obj);
    }

    /**
     * Finalizes the hashCode method
     */
//    /*public*/ final int hashCode() {
//        return super.hashCode();
//    }

    /**
     * Provides the <code>String</code> representation of the control type.  This <code>String</code> is
     * the same name that was passed to the constructor.
     *
     * @return the control type name
     */
    /*public*/ /*final*/ QString Control::Type::toString() {
        return name;
    }
//}; // class Type

//}; // class Control
