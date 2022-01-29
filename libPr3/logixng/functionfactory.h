#ifndef FUNCTIONFACTORY_H
#define FUNCTIONFACTORY_H
#include "function.h"
#include "constant.h"
/**
 * Factory class for Function classes.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/  /*interface*/class FunctionFactory : public QObject{
 Q_OBJECT
 public:
  FunctionFactory(QObject* parent = nullptr) : QObject(parent) {}
    /**
     * Get the module of the functions in this factory, for example "Math" or
     * "Conversion".
     * @return the module name
     */
    /*public*/ virtual QString getModule()=0;

    /**
     * Get a set of classes that implements the Function interface.
     *
     * @return a set of functions
     */
    /*public*/virtual  QSet<Function*> getFunctions()=0;

    /**
     * Get a set of classes that implements the Constant interface.
     *
     * @return a set of constants
     */
    /*public*/ virtual QSet<Constant*> getConstants()=0;

    /**
     * Get the description of the constants in Markdown format
     * @return the description of the constants
     */
    /*public*/virtual  QString getConstantDescription()=0;


};
//Q_DECLARE_INTERFACE(FunctionFactory, "FunctionFactory")
#endif // FUNCTIONFACTORY_H
