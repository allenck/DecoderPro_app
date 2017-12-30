#ifndef AUXILIARYPROPERTIES_H
#define AUXILIARYPROPERTIES_H

#include <QObject>

class /*interface*/ AuxiliaryProperties : public QObject
{
 Q_OBJECT
public:
 explicit AuxiliaryProperties(QObject *parent = 0) : QObject(parent) {}

 virtual QString get(QString /*key*/, bool /*shared*/) {return "";}

 virtual QList<QString> listKeys(bool /*shared*/) { return QList<QString>();}

 virtual void put(QString /*key*/, QString /*value*/, bool /*shared*/) {}
};

#endif // AUXILIARYPROPERTIES_H
