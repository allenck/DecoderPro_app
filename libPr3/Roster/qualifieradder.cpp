#include "qualifieradder.h"
#include <QtXml>
#include "variabletablemodel.h"
#include "qualifier.h"
#include "qualifiercombiner.h"

QualifierAdder::QualifierAdder(QObject *parent) :
    QObject(parent)
{
 log = new Logger("QualifierAdder");
}
/**
 * Abstract base for adding qualifiers to objects
 *
 * @see             jmri.jmrit.symbolicprog.Qualifier
 * @see             jmri.jmrit.symbolicprog.ArithmeticQualifier
 * @see             jmri.jmrit.symbolicprog.tabbedframe.PaneProgFrame
 *
 * @author			Bob Jacobsen   Copyright (C) 2014
 * @version			$Revision: 28148 $
 *
 */
// /*public*/ abstract class QualifierAdder {

/**
 * Invoked to create the qualifier object
 * and connect as needed. If extra state
 * is needed, provide it via the subclass constructor.
 *
 * @param var      The variable that qualifies this, e.g. the one that's watched
 * @param relation The relation term from the qualifier definition, e.g. greater than
 * @param value    The value for the comparison
 */
// e.g. return new PaneQualifier(pane, var, Integer.parseInt(value), relation, tabPane, index);
//abstract protected Qualifier createQualifier(VariableValue var, String relation, String value);
//// e.g. arrange for this to be sent a property change event on change of the qualified object
//abstract protected void addListener(java.beans.PropertyChangeListener qc);

/*public*/ void QualifierAdder::processModifierElements(QDomElement e, VariableTableModel* model)
{

 QList<Qualifier*>* lq = new QList<Qualifier*>();

 QDomNodeList le = e.elementsByTagName("qualifier"); // we assign to this to allow us to suppress unchecked error
 processList(le, lq, model);

 // search for enclosing element so we can find all relevant qualifiers
#if 1 // TODO
 QDomNode p = e;
    while ( !(p = p.parentNode()).isNull() && p.isElement()) {
        QDomElement el = p.toElement();
        if (el.tagName() == ("pane")) break;  // stop when we get to an enclosing pane element
        //@SuppressWarnings("unchecked")
        QDomNodeList le2 = el.elementsByTagName("qualifier");  // we assign to this to allow us to suppress unchecked error
        processList(le2, lq, model);
    }
#endif
 // Add the AND logic - listen for change and ensure result correct
 if (lq->size()>1)
 {
  QualifierCombiner* qc = new QualifierCombiner(lq);
  addListener((PropertyChangeListener*)qc);
 }
}

void QualifierAdder::processList(QDomNodeList le, QList<Qualifier*>* lq, VariableTableModel* model)
{
 //   for (Element q : le)
 for(int i = 0; i < le.size(); i++)
 {
  QDomElement q = le.at(i).toElement();
  processElement(q, lq, model);
 }
}

void QualifierAdder::processElement(QDomElement q, QList<Qualifier*>* lq, VariableTableModel* model)
{
 QString variableRef = q.firstChildElement("variableref").text();
 QString relation = q.firstChildElement("relation").text();
 QString value = q.firstChildElement("value").text();

 // find the variable
 VariableValue* var = model->findVar(variableRef);

 if (var != NULL || relation==("exists"))
 {
  // found, attach the qualifier object through creating it
//  log->debug("Attached {} variable for {} {} qualifier", variableRef, relation, value);
 }
 else
 {
//  log->debug("Didn't find {} variable for {} {} qualifier", variableRef, relation, value);
 }

 // create qualifier
 Qualifier* qual = createQualifier(var, relation, value);
 qual->update();
 lq->append(qual);
}
