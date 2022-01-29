#include "stringfunctions.h"
#include "wrongnumberofparametersexception.h"

/**
 * Implementation of string functions.
 *
 * @author Daniel Bergqvist 2020
 */
//@ServiceProvider(service = FunctionFactory.class)
///*/*public*/ */  class StringFunctions implements FunctionFactory {

    //@Override
/**
 * Implementation of string functions.
 *
 * @author Daniel Bergqvist 2020
 */
//@ServiceProvider(service = FunctionFactory.class)
///*public*/  class StringFunctions implements FunctionFactory {

    //@Override
    /*public*/  QString StringFunctions::getModule() {
        return "String";
    }

    //@Override
    /*public*/  QSet<Function*> StringFunctions::getFunctions() {
        QSet<Function*> functionClasses = QSet<Function*>();
        functionClasses.insert(new FormatFunction());
        return functionClasses;
    }

    //@Override
    /*public*/  QSet<Constant*> StringFunctions::getConstants() {
        return QSet<Constant*>();
    }

    //@Override
    /*public*/  QString StringFunctions::getConstantDescription() {
        // This module doesn't define any constants
        return "";
    }



//    /*public*/  static class FormatFunction implements Function {

        //@Override
        /*public*/  QString FormatFunction::getModule() {
            return (new StringFunctions())->getModule();
        }

        //@Override
        /*public*/  QString FormatFunction::getConstantDescriptions() {
            return (new StringFunctions())->getConstantDescription();
        }

        //@Override
        /*public*/  QString FormatFunction::getName() {
            return "format";
        }

        //@Override
        /*public*/  QVariant FormatFunction::calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
                /*throws CalculateException, JmriException*/ {
            if (parameterList.isEmpty()) {
                throw new WrongNumberOfParametersException(tr("WrongNumberOfParameters1").arg(getName()/*, 1)*/));
            }

            QString formatStr = /*TypeConversionUtil.convertToString*/(
                    parameterList.at(0)->calculate(symbolTable), false)?"true":"false";

            QVariantList list = QVariantList();
            for (int i=1; i < parameterList.size(); i++) {
                list.append(parameterList.at(i)->calculate(symbolTable));
            }

            //return QString(formatStr).arg(list);
            return list;
        }

        //@Override
        /*public*/  QString FormatFunction::getDescription() {
            return tr("<html>\n<h1>format()</h1>\n<h2>format(formatString, parameters...)</h2> \nReads the <i>formatString</i> and the following <i>parameters...</i> and sends\nit to the Java method <i>String.format()</i>.\n<p>\n<i>parameters...</i> is zero or more parameters of any type, but the format\nspecifier in the <i>formatString</i> must match its corresponding parameter.\n<p>\nFor the syntax of the <i>formatString</i>, see the Java documentation:<br>\nhttps://docs.oracle.com/javase/8/docs/api/java/util/Formatter.html#syntax \n</html>");
        }


