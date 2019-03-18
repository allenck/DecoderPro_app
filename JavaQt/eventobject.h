#ifndef EVENTOBJECT_H
#define EVENTOBJECT_H

#include <QObject>
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT EventObject : public QObject
{
    Q_OBJECT
public:
    //explicit EventObject(QObject *parent = 0);
 EventObject(QObject* source, QObject *parent = 0);
    /**
     * Constructs a prototypical Event.
     *
     * @param    source    The object on which the Event initially occurred.
     * @exception  IllegalArgumentException  if source is null.
     */
//    /*public*/ EventObject(QObject* source);
    /**
     * The object on which the Event initially occurred.
     *
     * @return   The object on which the Event initially occurred.
     */
 /*public*/ QObject* getSource();
    /**
     * Returns a String representation of this EventObject.
     *
     * @return  A a String representation of this EventObject.
     */
 /*public*/ QString toString();

signals:
    
public slots:
private:
//    /*private*/ static /*final*/ const long long serialVersionUID;// = 5516075349620653480L;
//QObject *parent;
protected:
    /**
     * The object on which the Event initially occurred.
     */
    /*protected transient*/ QObject*  source;

};

#endif // EVENTOBJECT_H
