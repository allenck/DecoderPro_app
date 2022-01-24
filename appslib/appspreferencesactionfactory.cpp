#include "appspreferencesactionfactory.h"
#include "tabbedpreferencesaction.h"

AppsPreferencesActionFactory::AppsPreferencesActionFactory(QObject *parent)
{

}
// /*public*/ class AppsPreferencesActionFactory extends JmriPreferencesActionFactory {

    //@Override
    /*public*/ JmriAbstractAction* AppsPreferencesActionFactory::getDefaultAction(QObject* parent) {
        return new TabbedPreferencesAction(parent);
    }

    //@Override
    /*public*/ JmriAbstractAction* AppsPreferencesActionFactory::getNamedAction(QString name, QObject *parent) {
        return new TabbedPreferencesAction(name, parent);
    }

    //@Override
    /*public*/ JmriAbstractAction* AppsPreferencesActionFactory::getCategorizedAction(QString name, QString category, QObject* parent) {
        return new TabbedPreferencesAction(name, category, parent);
    }

    //@Override
    /*public*/ JmriAbstractAction* AppsPreferencesActionFactory::getCategorizedAction(QString name, QString category, QString subCategory,QObject* parent) {
        return new TabbedPreferencesAction(name, category, subCategory, parent);
    }
