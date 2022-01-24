#ifndef ACTIONEVENT_H
#define ACTIONEVENT_H

#include <QObject>
#include <QString>
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT JActionEvent : public QObject
{
    //Q_OBJECT
public:
    explicit JActionEvent(QObject *parent = 0);
    /*public*/ JActionEvent(QObject* source, int id, QString command, QObject *parent = 0);
    /*public*/ JActionEvent(QObject* source, int id, QString command, int modifiers, QObject *parent = 0) ;
    /*public*/ JActionEvent(QObject* source, int id, QString command, long when,
                       int modifiers, QObject *parent = 0);
    ~JActionEvent() {}
    JActionEvent(const JActionEvent&) : QObject() {}
    /*public*/ QString getActionCommand() ;
    /*public*/ long getWhen() ;
    /*public*/ int getModifiers();
    /*public*/ QString paramString();
    /*public*/ QObject* getSource();

signals:

public slots:

    /**
     * The shift modifier. An indicator that the shift key was held
     * down during the event.
     */
    /*public*/ static /*final*/ const int SHIFT_MASK          = Qt::ShiftModifier /*Event.SHIFT_MASK*/;

    /**
     * The control modifier. An indicator that the control key was held
     * down during the event.
     */
    /*public*/ static /*final*/ const int CTRL_MASK           = Qt::ControlModifier/*Event.CTRL_MASK*/;

    /**
     * The meta modifier. An indicator that the meta key was held
     * down during the event.
     */
    /*public*/ static /*final*/ const int META_MASK           = Qt::MetaModifier /*Event.META_MASK*/;

    /**
     * The alt modifier. An indicator that the alt key was held
     * down during the event.
     */
    /*public*/ static /*final*/ const int ALT_MASK            = Qt::AltModifier/*Event.ALT_MASK*/;


    /**
     * The first number in the range of ids used for action events.
     */
    /*public*/ static /*final*/ const int ACTION_FIRST                = 1001;

    /**
     * The last number in the range of ids used for action events.
     */
    /*public*/ static /*final*/ const int ACTION_LAST                 = 1001;

    /**
     * This event id indicates that a meaningful action occured.
     */
    /*public*/ static /*final*/ const int ACTION_PERFORMED    = ACTION_FIRST; //Event.ACTION_EVENT

private:
    /**
     * The nonlocalized string that gives more details
     * of what actually caused the event.
     * This information is very specific to the component
     * that fired it.

     * @serial
     * @see #getActionCommand
     */
    QString actionCommand;

    /**
     * Timestamp of when this event occurred. Because an ActionEvent is a high-
     * level, semantic event, the timestamp is typically the same as an
     * underlying InputEvent.
     *
     * @serial
     * @see #getWhen
     */
    long when;

    /**
     * This represents the key modifier that was selected,
     * and is used to determine the state of the selected key.
     * If no modifier has been selected it will default to
     * zero.
     *
     * @serial
     * @see #getModifiers
     */
    int modifiers;
    int id;
    /*
     * JDK 1.1 serialVersionUID
     */
    /*private*/ static /*final*/ const long serialVersionUID = -7671078796273832149L;
    QObject* source;

};
//Q_DECLARE_METATYPE(ActionEvent*)
#endif // ACTIONEVENT_H
