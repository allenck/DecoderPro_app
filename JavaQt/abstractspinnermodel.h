#ifndef ABSTRACTSPINNERMODEL_H
#define ABSTRACTSPINNERMODEL_H
#include "spinnermodel.h"
#include <QHash>

class ChangeEvent;
class AbstractSpinnerModel : public SpinnerModel
{
    Q_OBJECT
public:
    explicit AbstractSpinnerModel(QObject *parent = 0);
    /*public*/ void addChangeListener(ChangeListener* l);
    /*public*/ void removeChangeListener(ChangeListener* l);
    /*public*/ QList<ChangeListener*> getChangeListeners();

signals:

public slots:
private:
    /**
     * Only one ChangeEvent is needed per model instance since the
     * event's only (read-only) state is the source property.  The source
     * of events generated here is always "this".
     */
    /*private*/ /*transient*/ ChangeEvent* changeEvent;// = NULL;
protected:
    /**
     * The list of ChangeListeners for this model.  Subclasses may
     * store their own listeners here.
     */
//    /*protected*/ EventListenerList listenerList = new EventListenerList();
    QHash<QString, ChangeListener*>* listenerList;
    /*protected*/ void fireStateChanged();

};

#endif // ABSTRACTSPINNERMODEL_H
