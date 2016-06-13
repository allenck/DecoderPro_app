#ifndef QUALIFIERADDER_H
#define QUALIFIERADDER_H

#include <QObject>
#include "logger.h"

class QDomNodeList;
class QDomElement;
class VariableTableModel;
class PropertyChangeListener;
class VariableValue;
class Qualifier;
class QualifierAdder : public QObject
{
    Q_OBJECT
public:
    explicit QualifierAdder(QObject *parent = 0);
    /*public*/ void processModifierElements(QDomElement e, VariableTableModel* model);

signals:

public slots:
private:
    void processList(QDomNodeList le, QList<Qualifier*>* lq, VariableTableModel* model);
    void processElement(QDomElement q, QList<Qualifier*>* lq, VariableTableModel* model);
    Logger* log;
protected:
    /*abstract*/ /*protected*/ virtual Qualifier* createQualifier(VariableValue* /*var*/, QString /*relation*/, QString /*value*/) {return NULL;}
    // e.g. arrange for this to be sent a property change event on change of the qualified object
    /*abstract*/ /*protected*/ virtual void addListener(PropertyChangeListener* /*qc*/) {}

};

#endif // QUALIFIERADDER_H
