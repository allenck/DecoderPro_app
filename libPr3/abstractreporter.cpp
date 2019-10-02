#include "abstractreporter.h"
#include <QApplication>

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

//@Override
/*public*/ QString AbstractReporter::getBeanType() {
    return tr("Reporter");
}

ReporterVariant AbstractReporter::getCurrentReport()
{
 ReporterVariant  rv = ReporterVariant(_currentReport);
 //return _currentReport;
 return rv;
}

ReporterVariant AbstractReporter::getLastReport()
{
 ReporterVariant  rv = ReporterVariant(_lastReport);
 //return _lastReport;
 return rv;
}

/**
 * Provide a general method for updating the report.
 */
void AbstractReporter::setReport(QVariant r)
{

 if (r == _currentReport)
 {
     return;
 }
 QVariant old = _currentReport;
 QVariant oldLast = _lastReport;
 _currentReport = r;
 if (!r.isNull())
 {
  _lastReport = r;
  // notify
  firePropertyChange("lastReport", oldLast, _lastReport);
 }
 // notify
 firePropertyChange("currentReport", old, _currentReport);
}

