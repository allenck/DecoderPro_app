#ifndef BEANTABLESTARTUPACTIONFACTORY_H
#define BEANTABLESTARTUPACTIONFACTORY_H

#include <abstractstartupactionfactory.h>

class BeanTableStartupActionFactory : public AbstractStartupActionFactory
{
    Q_OBJECT
public:
    explicit BeanTableStartupActionFactory(QObject *parent = nullptr);
    /*public*/ QString getTitle(QString clazz, QLocale locale) /*throws IllegalArgumentException*/ override;

};

#endif // BEANTABLESTARTUPACTIONFACTORY_H
