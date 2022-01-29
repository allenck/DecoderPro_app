#include "constant.h"
#include <QString>
#include <QVariant>
/**
 * Definition of a constant used in expressions.
 *
 * @author Daniel Bergqvist 2021
 */
///*public*/  final class Constant {



    /*public*/  Constant::Constant(QString m, QString name, QVariant value) {
        this->_module = m;
        this->_name = name;
        this->_value = value;
    }

    /**
     * Get the module of the constant, for example "Math" or "Conversion".
     * @return the module name
     */
    /*public*/  QString Constant::getModule() {
        return _module;
    }

    /**
     * Get name of the function, for example "MathPI" or "MathE"
     * @return the name
     */
    /*public*/  QString Constant::getName() {
        return _name;
    }

    /**
     * Return the value of the constant.
     * @return the result
     */
    /*public*/  QVariant Constant::getValue() {
        return _value;
    }
