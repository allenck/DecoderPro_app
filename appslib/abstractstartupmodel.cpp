#include "abstractstartupmodel.h"

/**
 * Abstract startup action model.
 *
 * @author Randall Wood (c) 2016
 */
///*public*/ abstract class AbstractStartupModel implements StartupModel {


/*protected*/ AbstractStartupModel::AbstractStartupModel(QObject* parent)  : StartupModel(parent)
{
 exceptions =  QList<Exception*>();
 this->name = "";
}

//@Override
/*public*/ QString AbstractStartupModel::getName() {
    return this->name;
}

//@Override
/*public*/ void AbstractStartupModel::setName(QString name) {
    this->name = name;
}

//@Override
//@NonNULL
/*public*/ QString AbstractStartupModel::toString() {
    QString string = this->getName();
    if (string == NULL) {
        return StartupModel::toString();
    }
    return string;
}

/**
 * {@inheritDoc}
 *
 * The default behavior is to return true if {@link #getName()} returns a
 * non-NULL, non-empty String.
 *
 * @return true if valid; false otherwise
 */
//@Override
/*public*/ bool AbstractStartupModel::isValid() {
    QString s = this->getName();
    return s != NULL && !s.isEmpty();
}

//@Override
/*public*/ QList<Exception*> AbstractStartupModel::getExceptions() {
    return  QList<Exception*>(this->exceptions);
}

//@Override
/*public*/ void AbstractStartupModel::addException(/*@NonNULL*/ Exception* exception) {
    this->exceptions.append(exception);
}
