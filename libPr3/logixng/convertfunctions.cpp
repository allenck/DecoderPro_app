#include "convertfunctions.h"
#include "wrongnumberofparametersexception.h"
#include "typeconversionutil.h"
/**
 * Implementation of conversion functions.
 *
 * @author Daniel Bergqvist 2020
 */
//@ServiceProvider(service = FunctionFactory.class)
// /*public*/  class ConvertFunctions implements FunctionFactory {

    //@Override
    /*public*/  QString ConvertFunctions::getModule() {
        return "Convert";
    }

    //@Override
    /*public*/  QSet<Function*> ConvertFunctions::getFunctions() {
        QSet<Function*> functionClasses = QSet<Function*>();
        functionClasses.insert(new IntFunction());
        functionClasses.insert(new FloatFunction());
        functionClasses.insert(new StrFunction());
        return functionClasses;
    }

    //@Override
    /*public*/  QSet<Constant*> ConvertFunctions::getConstants() {
        return QSet<Constant*>();
    }

    //@Override
    /*public*/  QString ConvertFunctions::getConstantDescription() {
        // This module doesn't define any constants
        return "";
    }



//    /*public*/  static class IntFunction implements Function {

        //@Override
        /*public*/  QString IntFunction::getModule() {
            return (new ConvertFunctions())->getModule();
        }

        //@Override
        /*public*/  QString IntFunction::getConstantDescriptions() {
            return (new ConvertFunctions())->getConstantDescription();
        }

        //@Override
        /*public*/  QString IntFunction::getName() {
            return "int";
        }

        //@Override
        /*public*/  QVariant IntFunction::calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
                /*throws JmriException*/ {

            if (parameterList.size() != 1) {
                throw new WrongNumberOfParametersException(tr("Function \"%1\" has wrong number of parameters. \"%2\" parameters expected").arg(getName()).arg(1));
            }
            return (int) TypeConversionUtil::convertToLong(
                    parameterList.at(0)->calculate(symbolTable));
        }

        //@Override
        /*public*/  QString IntFunction::getDescription() {
            return tr("<html>                                                    <h1>int()</h1>                                                                              <h2>int(value)</h2>                                                                         Converts <i>value</i> to an  and returns it.                                         </html>");
        }



//    /*public*/  static class FloatFunction implements Function {

        //@Override
        /*public*/  QString FloatFunction::getModule() {
            return (new ConvertFunctions())->getModule();
        }

        //@Override
        /*public*/  QString FloatFunction::getConstantDescriptions() {
            return (new ConvertFunctions())->getConstantDescription();
        }

        //@Override
        /*public*/  QString FloatFunction::getName() {
            return "float";
        }

        //@Override
        /*public*/  QVariant FloatFunction::calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
                /*throws JmriException */{

            switch (parameterList.size()) {
                case 1:
                    return TypeConversionUtil::convertToDouble(parameterList.at(0)->calculate(symbolTable), false);
                case 2:
                {
                    bool do_i18n = TypeConversionUtil::convertToBoolean(
                            parameterList.at(0)->calculate(symbolTable), false);
                    return TypeConversionUtil::convertToDouble(
                            parameterList.at(0)->calculate(symbolTable), do_i18n);
                }
                default:
                    throw new WrongNumberOfParametersException(tr("Function \"%1\" has wrong number of parameters. \"%2\" parameters expected").arg(getName()).arg(1));
            }
        }

        //@Override
        /*public*/  QString FloatFunction::getDescription() {
            return tr("<html>                                                    <h1>float()</h1>                                                                            <h2>float(value)</h2>                                                                       Converts <i>value</i> to a floating point number and returns it.                            <h2>float(value, do_i18n)</h2>                                                              Converts <i>value</i> to a floating point number and returns it. <i>do_i18n</i>             is a boolean value (true or false) that tells if internationalization should be             done.                                                                                       </html>");
        }


//    /*public*/  static class StrFunction implements Function {

        //@Override
        /*public*/  QString StrFunction::getModule() {
            return (new ConvertFunctions())->getModule();
        }

        //@Override
        /*public*/  QString StrFunction::getConstantDescriptions() {
            return (new ConvertFunctions())->getConstantDescription();
        }

        //@Override
        /*public*/  QString StrFunction::getName() {
            return "str";
        }

        //@Override
        /*public*/  QVariant StrFunction::calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
                /*throws JmriException*/ {

            switch (parameterList.size()) {
                case 1:
                    return TypeConversionUtil::convertToString(parameterList.at(0)->calculate(symbolTable), false);
                case 2:
                {
                    bool do_i18n = TypeConversionUtil::convertToBoolean(
                            parameterList.at(0)->calculate(symbolTable), false);
                    return TypeConversionUtil::convertToString(
                            parameterList.at(0)->calculate(symbolTable), do_i18n);
                }
                default:
                    throw new WrongNumberOfParametersException(tr("Function \"%1\" has wrong number of parameters. \"%2\" parameters expected").arg(getName()).arg(1));
            }
        }

        //@Override
        /*public*/  QString StrFunction::getDescription() {
            return tr("<html>                                                    <h1>str()</h1>                                                                              <h2>str(value)</h2>                                                                         Converts <i>value</i> to a string and returns it.                                           <h2>str(value, do_i18n)</h2>                                                                Converts <i>value</i> to a string and returns it. <i>do_i18n</i> is a boolean value         (true or false) that tells if internationalization should be done.                          </html>");
        }

    //}
