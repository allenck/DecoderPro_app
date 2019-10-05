#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include "exceptions.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(QObject *parent = 0);
    /**
     * OFF is a special level that can be used to turn off logging.
     * This level is initialized to <CODE>Integer.MAX_VALUE</CODE>.
     */
    /*public*/ static /*final*/ Level* OFF;// = new Level("OFF",Integer.MAX_VALUE, defaultBundle);
    /*public*/ static /*final*/ Level* FATAL;
    /*public*/ static /*final*/ Level* _ERROR;


    /**
     * SEVERE is a message level indicating a serious failure.
     * <p>
     * In general SEVERE messages should describe events that are
     * of considerable importance and which will prevent normal
     * program execution.   They should be reasonably intelligible
     * to end users and to system administrators.
     * This level is initialized to <CODE>1000</CODE>.
     */
    /*public*/ static /*final*/ Level* SEVERE;// = new Level("SEVERE",1000, defaultBundle);

    /**
     * WARNING is a message level indicating a potential problem.
     * <p>
     * In general WARNING messages should describe events that will
     * be of interest to end users or system managers, or which
     * indicate potential problems.
     * This level is initialized to <CODE>900</CODE>.
     */
    /*public*/ static /*final*/ Level* WARNING;// = new Level("WARNING", 900, defaultBundle);

    /**
     * INFO is a message level for informational messages.
     * <p>
     * Typically INFO messages will be written to the console
     * or its equivalent.  So the INFO level should only be
     * used for reasonably significant messages that will
     * make sense to end users and system administrators.
     * This level is initialized to <CODE>800</CODE>.
     */
    /*public*/ static /*final*/ Level* INFO;// = new Level("INFO", 800, defaultBundle);

    /**
     * CONFIG is a message level for static configuration messages.
     * <p>
     * CONFIG messages are intended to provide a variety of static
     * configuration information, to assist in debugging problems
     * that may be associated with particular configurations.
     * For example, CONFIG message might include the CPU type,
     * the graphics depth, the GUI look-and-feel, etc.
     * This level is initialized to <CODE>700</CODE>.
     */
    /*public*/ static /*final*/ Level* CONFIG;// = new Level("CONFIG", 700, defaultBundle);

    /**
     * FINE is a message level providing tracing information.
     * <p>
     * All of FINE, FINER, and FINEST are intended for relatively
     * detailed tracing.  The exact meaning of the three levels will
     * vary between subsystems, but in general, FINEST should be used
     * for the most voluminous detailed output, FINER for somewhat
     * less detailed output, and FINE for the  lowest volume (and
     * most important) messages.
     * <p>
     * In general the FINE level should be used for information
     * that will be broadly interesting to developers who do not have
     * a specialized interest in the specific subsystem.
     * <p>
     * FINE messages might include things like minor (recoverable)
     * failures.  Issues indicating potential performance problems
     * are also worth logging as FINE.
     * This level is initialized to <CODE>500</CODE>.
     */
    /*public*/ static /*final*/ Level* FINE;// = new Level("FINE", 500, defaultBundle);

    /**
     * FINER indicates a fairly detailed tracing message.
     * By default logging calls for entering, returning, or throwing
     * an exception are traced at this level.
     * This level is initialized to <CODE>400</CODE>.
     */
    /*public*/ static /*final*/ Level* FINER;// = new Level("FINER", 400, defaultBundle);

    /**
     * FINEST indicates a highly detailed tracing message.
     * This level is initialized to <CODE>300</CODE>.
     */
    /*public*/ static /*final*/ Level* FINEST;// = new Level("FINEST", 300, defaultBundle);

    /**
     * ALL indicates that all messages should be logged.
     * This level is initialized to <CODE>Integer.MIN_VALUE</CODE>.
     */
    /*public*/ static /*final*/ Level* ALL;// = new Level("ALL", Integer.MIN_VALUE, defaultBundle);
    /*public*/ QString getResourceBundleName();
    /*public*/ QString getName();
    /*public*/ QString getLocalizedName();
    /*public*/ /*final*/ QString toString();
    /*public*/ /*final*/ int intValue();

    // Serialization magic to prevent "doppelgangers".
    // This is a performance optimization.
//    /*private*/ Object readResolve() ;
    /*public*/ static /*synchronized*/ Level* parse(QString name) throw (IllegalArgumentException) ;
    /*public*/ bool equals(QObject* ox);
    /*public*/ int hashCode();

signals:

public slots:
private:
    /*private*/ static QList<Level*> known;// = new QList<>();
    /*private*/ static QString defaultBundle;// = "sun.util.logging.resources.logging";

    /**
     * @serial  The non-localized name of the level.
     */
    /*private*/ /*final*/ QString name;

    /**
     * @serial  The integer value of the level.
     */
    /*private*/ /*final*/ int value;

    /**
     * @serial The resource bundle name to be used in localizing the level name.
     */
    /*private*/ /*final*/ QString resourceBundleName;
    /*private*/ static /*final*/ long serialVersionUID;// = -8176160795706313070L;
protected:
//    /*protected*/ Level(QString name, int value);
    /*protected*/ Level(QString name, int value, QString resourceBundleName = "");

};

#endif // LEVEL_H
