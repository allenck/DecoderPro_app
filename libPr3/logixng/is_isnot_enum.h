#ifndef IS_ISNOT_ENUM_H
#define IS_ISNOT_ENUM_H
#include <QObject>
#include "exceptions.h"

/**
 * An enum with the values "is" and "is not"
 *
 * @author Daniel Bergqvist 2019
 */
/*public*/ /*enum*/ class Is_IsNot_Enum : QObject {

 Q_OBJECT
 public:
//    Is(tr("Is")),
//    IsNot(tr("Is not"));
  enum VAL {Is, IsNot};
 /*public*/static  QList<VAL> values() {return QList<VAL> {Is, IsNot};};
    /*private*/ /*final*/ QString _text;

    /*private*/ Is_IsNot_Enum(QString text) {
        this->_text = text;
    }

    //@Override
    /*public*/static  QString toString(VAL v) {
        if(v== Is) return tr("Is");
        return tr("IsNot");
    }

    static VAL valueOf(QString s)
    {
     if(s==tr("Is")) return Is;
     if(s== tr("IsNot")) return IsNot;
     throw new IllegalArgumentException("illegal value");
    }
};
#endif // IS_ISNOT_ENUM_H
