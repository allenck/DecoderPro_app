#include "true.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Always evaluates to True.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class True extends AbstractDigitalExpression {

    /*public*/  True::True(QString sys, QString user, QObject* parent) : AbstractDigitalExpression(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException */{
        //super(sys, user);
    }

    //@Override
    /*public*/  Base* True::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        DigitalExpressionBean* copy = new True(sysName, userName);
        copy->NamedBean::setComment(NamedBean::getComment());
        return manager->registerExpression(copy);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category True::getCategory() {
        return Category::OTHER;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool True::evaluate() {
        return true;
    }

    //@Override
    /*public*/  FemaleSocket* True::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int True::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString True::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Always true");
    }

    //@Override
    /*public*/  QString True::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "Always true");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void True::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void True::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void True::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void True::disposeMe() {
    }
