#include "abstractreporter.h"

AbstractReporter::AbstractReporter(QObject *parent) :
    Reporter(parent)
{
 _lastReport = QVariant();
 _currentReport = QVariant();
state = 0;
}
/**
 * Abstract base for the Reporter interface.
 * <P>
 * Implements the parameter binding support.
 * <P>
 * Note that we consider it an error for there to be more than one object
 * that corresponds to a particular physical Reporter on the layout.
 *
 * Description:		Abstract class providing the basic logic of the Reporter interface
 * @author			Bob Jacobsen Copyright (C) 2001
 * @author                      Matthew Harris  Copyright (C) 2011
 * @version			$Revision: 17977 $
 */
//public abstract class AbstractReporter extends AbstractNamedBean implements Reporter, java.io.Serializable {

AbstractReporter::AbstractReporter(QString systemName, QObject* parent)
    : Reporter(systemName.toUpper(), parent)
{
 //super(systemName.toUpper());
    _lastReport = QVariant();
    _currentReport = QVariant();
 state = 0;

}

AbstractReporter::AbstractReporter(QString systemName, QString userName, QObject* parent)
    : Reporter(systemName.toUpper(), userName, parent)
{
 //super(systemName.toUpper(), userName);
 _lastReport = QVariant();
 _currentReport = QVariant();
 state = 0;
}

QVariant AbstractReporter::getCurrentReport()
{
 return _currentReport;
}

QVariant AbstractReporter::getLastReport() {return _lastReport;}

/**
 * Provide a general method for updating the report.
 */
void AbstractReporter::setReport(QVariant r)
{
 QVariant old = _currentReport;
 QVariant oldLast = _lastReport;
 _currentReport = r;
 if (r != QVariant())
 {
  _lastReport = old;
  // notify
  firePropertyChange("lastReport", oldLast, _lastReport);
  emit propertyChange(this, "lastReport", oldLast, _lastReport);
 }
 // notify
 firePropertyChange("currentReport", old, _currentReport);
 emit propertyChange(this, "currentReport", old, _currentReport);
}

