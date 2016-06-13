#ifndef BEANEDITITEM_H
#define BEANEDITITEM_H

#include <QObject>
#include "libtables_global.h"

class LIBTABLESSHARED_EXPORT BeanEditItem : public QObject
{
 Q_OBJECT
public:
 explicit BeanEditItem(QObject *parent = 0);
 /*public*/ BeanEditItem(QWidget* component, QString description, QString help);
 /*public*/ QString getDescription() ;
 /*public*/ QString getHelp();
 /*public*/ QWidget* getComponent();

signals:

public slots:
private:
 QString help;
 QString description;
 QWidget* component;

};

#endif // BEANEDITITEM_H
