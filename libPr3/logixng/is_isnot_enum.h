#ifndef IS_ISNOT_ENUM_H
#define IS_ISNOT_ENUM_H
#include <QObject>
/**
 * An enum with the values "is" and "is not"
 *
 * @author Daniel Bergqvist 2019
 */
/*public*/ /*enum*/ class Is_IsNot_Enum : QObject {

 Q_OBJECT
//    Is(tr("Is")),
//    IsNot(tr("Is not"));
  enum VAL {Is, IsNot};

    /*private*/ /*final*/ QString _text;

    /*private*/ Is_IsNot_Enum(QString text) {
        this->_text = text;
    }

    //@Override
    /*public*/ QString toString() {
        return _text;
    }

};
#endif // IS_ISNOT_ENUM_H
