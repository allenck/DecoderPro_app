#include "mathfunctions.h"
#include "constant.h"
#include "qmath.h"
#include "typeconversionutil.h"
#include "wrongnumberofparametersexception.h"
#include "calculateexception.h"
#include <QRandomGenerator>
/**
 * Implementation of mathematical functions.
 *
 * @author Daniel Bergqvist 2019
 */
//@ServiceProvider(service = FunctionFactory.class)
// /*public*/  class MathFunctions implements FunctionFactory {

    //@Override
    /*public*/  QString MathFunctions::getModule() {
        return "Math";
    }

    //@Override
    /*public*/  QSet<Function*> MathFunctions::getFunctions() {
        QSet<Function*> functionClasses = QSet<Function*>();
        functionClasses.insert(new RandomFunction());
        functionClasses.insert(new SinFunction());
        return functionClasses;
    }

    //@Override
    /*public*/  QSet<Constant*> MathFunctions::getConstants() {
        QSet<Constant*> constantClasses = QSet<Constant*>();
        constantClasses.insert(new Constant(getModule(), "MathPI", M_PI));
        constantClasses.insert(new Constant(getModule(), "MathE", M_E));
        return constantClasses;
    }

    //@Override
    /*public*/  QString MathFunctions::getConstantDescription() {
        return tr("<html>                          <h1>Constants</h1>                                                          <table>                                                                     <tr><td>MathPI</td><td>The value of PI, 3.14159...</td></tr>              <tr><td>MathE</td><td>The value of e, 2.71828...</td></tr>                </table>                                                                    </html>");
    }



    // /*public*/  static class RandomFunction implements Function {

        //@Override
        /*public*/  QString RandomFunction::getModule() {
            return (new MathFunctions())->getModule();
        }

        //@Override
        /*public*/  QString RandomFunction::getConstantDescriptions() {
            return (new MathFunctions())->getConstantDescription();
        }

        //@Override
        /*public*/  QString RandomFunction::getName() {
            return "random";
        }

        //@Override
        /*public*/  QVariant RandomFunction::calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
                /*throws CalculateException, JmriException*/ {

            double min;
            double max;
            switch (parameterList.size()) {
                case 0:
                    return QRandomGenerator::global()->generateDouble();
                case 1:
                    max = TypeConversionUtil::convertToDouble(
                            parameterList.at(0)->calculate(symbolTable), false);
                    return qrand() * max;
                case 2:
                    min = TypeConversionUtil::convertToDouble(
                            parameterList.at(0)->calculate(symbolTable), false);
                    max = TypeConversionUtil::convertToDouble(
                            parameterList.at(1)->calculate(symbolTable), false);
                    return min + qrand() * (max-min);
                default:
                    throw new WrongNumberOfParametersException(tr("Function \"%1\" has wrong number of parameters").arg(getName()));
            }
        }

        //@Override
        /*public*/  QString RandomFunction::getDescription() {
            return tr("<html>                                                    <h1>random()</h1>                                                                           <h2>random()</h2>                                                                           Returns a random value 0.0 &lt;= x &lt; 1.0                                                 <h2>random(max)</h2>                                                                        Returns a random value 0.0 &lt;= x &lt; <i>max</i>                                          <h2>random(min, max)</h2>                                                                   Returns a random value <i>min</i> &lt;= x &lt; <i>max</i>      ");
        }

    //}

    ///*public*/  static class SinFunction implements Function {

        //@Override
        /*public*/  QString SinFunction::getModule() {
            return (new MathFunctions())->getModule();
        }

        //@Override
        /*public*/  QString SinFunction::getConstantDescriptions() {
            return (new MathFunctions())->getConstantDescription();
        }

        //@Override
        /*public*/  QString SinFunction::getName() {
            return "sin";
        }

        //@Override
        /*public*/  QVariant SinFunction::calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
                /*throws JmriException*/ {

            if (parameterList.size() == 1) {
                double param = TypeConversionUtil::convertToDouble(
                        parameterList.at(0)->calculate(symbolTable), false);
                return qSin(param);
            } else if (parameterList.size() >= 2) {
                double param0 = TypeConversionUtil::convertToDouble(
                        parameterList.at(0)->calculate(symbolTable), false);
                QVariant param1 = parameterList.at(1)->calculate(symbolTable);
                double result;
                //if (param1 instanceof String)
                if(param1.type() == QMetaType::QString)
                {
                    if(param1.toString() == "rad")
                            result = qSin(param0);
                    else if(param1.toString() == "deg")
                            result = qSin(qDegreesToRadians(param0));
                    else
                            throw new CalculateException(tr("Parameter \"%1\" with value \"%2\" for function \"%3\" is invalid").arg(2).arg(param1.toString(), getName()));
                }
#if 1
            else if (param1.canConvert<int>()) {
                    double p1 = TypeConversionUtil::convertToDouble(param1, false);
                    double angle = param0 / p1 * 2.0 * M_PI;
                    result = qSin(angle);
                } else {
                    throw new CalculateException(tr("Parameter \"%1\" with value \"%2\" for function \"%3\" is invalid").arg(2).arg(param1.toString(), getName()));
                }
#endif
                switch (parameterList.size()) {
                    case 2:
                        return result;
                    case 4:
                {
                        double min = TypeConversionUtil::convertToDouble(
                                parameterList.at(2)->calculate(symbolTable), false);
                        double max = TypeConversionUtil::convertToDouble(
                                parameterList.at(3)->calculate(symbolTable), false);
                        return (result+1.0)/2.0 * (max-min) + min;
                }
                    default:
                        throw new WrongNumberOfParametersException(tr("Function \"%1\" has wrong number of parameters").arg(getName()));
                }
            }
            throw new WrongNumberOfParametersException(tr("Function \"%1\" has wrong number of parameters").arg(getName()));
        }

        //@Override
        /*public*/  QString SinFunction::getDescription() {
            return tr("<html>                                                    <h1>sin()</h1>                                                                              <h2>sin(angle)</h2>                                                                         Returns the sine value of <i>angle</i>, where <i>angle</i> is measured in radians.          <hr>                                                                                        <h2>sin(angle, unit)</h2>                                                                   Returns the sine value of <i>angle</i>, there <i>angle</i> is measured in <i>unit</i>.      <p>                                                                                         The <i>unit</i> may be given by a string or by the number of units per full                 rotation of the circle. The supported strings are \"rad\" for radians and \"deg\"               for degrees.                                                                                <p>                                                                                         An example when it's desired to use an integer value as unit is if you want to              control the light in the room by the fast clock. If you let the minute of the               day be the angle and let 1440 be the unit, then you can use sin() to control the            brightness of the lights in the room. To let it be complete dark at midnight and            full brightness at noon, you can use this formula:                                          <p>                                                                                         <b>sin( fastClock() - 360, 1440 ) / 2 + 0.5</b>                                             <p>                                                                                         This formula uses the function <i>fastClock()</i> to get the number of minutes              since midnight and adds 360 minutes (6 hours or a quarter of a 24h day) to get              the bottom of the sine curve to be at midnight.                                             <hr>                                                                                        <h2>sin(angle, unit, min, max)</h2>                                                         Returns the sine value of <i>angle</i>, there <i>angle</i> is measured in <i>unit</i>       between <i>min</i> and <i>max</i>.                                                          <p>                                                                                         Lets say you want to control the light in the room by the fast clock and you want           the brightness be between 20 and 100. You can then use the following formula:               <p>                                                                                         <b>sin( fastClock() - 360, 1440, 20, 100 )</b>                                              </html>");
        }

//    };
