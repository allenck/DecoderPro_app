#include "false.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Always evaluates to False.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
// /*public*/  class False extends AbstractDigitalExpression {

    /*public*/  False::False(QString sys, QString user, QObject* parent) : AbstractDigitalExpression(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
        setObjectName("False");
    }

    //@Override
    /*public*/  Base* False::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        DigitalExpressionBean* copy = new False(sysName, userName);
        copy->Base::setComment(Base::getComment());
        return manager->registerExpression(copy);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category False::getCategory() {
        return Category::OTHER;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool False::evaluate() {
        return false;
    }

    //@Override
    /*public*/  FemaleSocket* False::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int False::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString False::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "False");
    }

    //@Override
    /*public*/  QString False::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "False");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void False::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void False::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void False::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void False::disposeMe() {
    }
