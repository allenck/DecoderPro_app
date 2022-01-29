#ifndef NAMEDBEANADDRESSING_H
#define NAMEDBEANADDRESSING_H
#include <QtCore>

/**
 * How should a named bean be addressed by an action or expression?
 *
 * @author Daniel Bergqvist Copyright 2020
 */
/*public*/ /*enum*/class NamedBeanAddressing {
  Q_OBJECT
    public:
  enum TYPE {Direct, Reference, LocalVariable, Formula};
  TYPE _type;
    /**
     * Direct addressing, by entering the name of the named bean
     */
//    Direct(Bundle.getMessage("NamedBeanAddressing_Direct")),

    /**
     * Addresssing by reference, by entering a reference that points to the named bean.
     */
//    Reference(Bundle.getMessage("NamedBeanAddressing_Reference")),

    /**
     * Addresssing by local variable, by entering a local variable that points to the named bean.
     */
//    LocalVariable(Bundle.getMessage("NamedBeanAddressing_LocalVariable")),

    /**
     * Addresssing by formula, by entering a formula that points to the named bean.
     */
//    Formula(Bundle.getMessage("NamedBeanAddressing_Formula"));

    /*private*/ /*final*/ QString _text;

    /*private*/ NamedBeanAddressing(QString text) {
        this->_text = text;
     if(text == "Direct") _type = Direct;
     if(text == "Reference") _type = Reference;
     if(text == "LocalVariable") _type = LocalVariable;
     if(text == "Formula") _type = Formula;
    }
public:
    NamedBeanAddressing(NamedBeanAddressing::TYPE t)
    {
     switch (t) {
     case Direct:
      _text = tr("Direct");
      break;
     case Reference:
      _text = tr("Reference");
      break;
     case LocalVariable:
      _text = tr("Local variable");
      break;
     case Formula:
      _text = tr("Formula");
     default:
      _text = "?";
      break;
     }
    }
    /*public*/ TYPE type() {return _type;}
    //@Override
    /*public*/ QString toString() {
        return _text;
    }
    /*public*/ static QString toString(TYPE t)
    {
     switch (t) {
     case Direct:
      return  tr("Direct");
      break;
     case Reference:
      return  tr("Reference");
      break;
     case LocalVariable:
      return  tr("Local variable");
      break;
     case Formula:
      return  tr("Formula");
     default:
      return  "?";
      break;
     }
    }
};
#endif // NAMEDBEANADDRESSING_H
