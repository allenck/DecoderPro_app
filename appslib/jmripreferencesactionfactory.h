#ifndef JMRIPREFERENCESACTIONFACTORY_H
#define JMRIPREFERENCESACTIONFACTORY_H

#include <QObject>
#include "instancemanagerautodefault.h"
#include "jmriabstractaction.h"

class JmriPreferencesActionFactory : public QObject,  public InstanceManagerAutoDefault
{
    Q_OBJECT
    Q_INTERFACES(InstanceManagerAutoDefault)
public:
    Q_INVOKABLE explicit JmriPreferencesActionFactory(QObject *parent = nullptr);
    ~JmriPreferencesActionFactory() {}
    JmriPreferencesActionFactory(const JmriPreferencesActionFactory&) : QObject() {}
    /*public*/ JmriAbstractAction* getDefaultAction();
    /*public*/ JmriAbstractAction* getNamedAction(QString name);
    /*public*/ JmriAbstractAction* getCategorizedAction(QString name, QString category);
    /*public*/ JmriAbstractAction* getCategorizedAction(QString name, QString category,QString subCategory);

signals:

};
Q_DECLARE_METATYPE(JmriPreferencesActionFactory)

class JPAFJmriAbstractAction : public JmriAbstractAction
{
    Q_OBJECT
public:
    JPAFJmriAbstractAction(QString text, QObject* parent) : JmriAbstractAction(text, parent) {}
    //@Override
    /*public*/ JmriPanel* makePanel() override{
        return nullptr;
    }
};

#endif // JMRIPREFERENCESACTIONFACTORY_H
