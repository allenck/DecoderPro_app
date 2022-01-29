#include "clockfunctions.h"
#include <QDateTime>
#include "calculateexception.h"
#include "wrongnumberofparametersexception.h"

/**
 * Implementation of clock functions.
 *
 * @author Daniel Bergqvist 2020
 */
//@ServiceProvider(service = FunctionFactory.class)
///*public*/  class ClockFunctions implements FunctionFactory {

    //@Override
    /*public*/  QString ClockFunctions::getModule() {
        return "Clock";
    }

    //@Override
    /*public*/  QSet<Function*> ClockFunctions::getFunctions() {
        QSet<Function*> functionClasses = QSet<Function*>();
        functionClasses.insert(new SystemClockFunction());
        functionClasses.insert(new FastClockFunction());
        return functionClasses;
    }

    //@Override
    /*public*/  QSet<Constant*> ClockFunctions::getConstants() {
        return QSet<Constant*>();
    }

    //@Override
    /*public*/  QString ClockFunctions::getConstantDescription() {
        // This module doesn't define any constants
        return "";
    }



    ///*public*/  static class SystemClockFunction implements Function {

        //@Override
        /*public*/  QString SystemClockFunction::getModule() {
            return (new ClockFunctions())->getModule();
        }

        //@Override
        /*public*/  QString SystemClockFunction::getConstantDescriptions() {
            return (new ClockFunctions())->getConstantDescription();
        }

        //@Override
        /*public*/  QString SystemClockFunction::getName() {
            return "systemClock";
        }

        //@Override
        //@SuppressWarnings("deprecation")        // Date.getMinutes, Date.getHours
        /*public*/  QVariant SystemClockFunction::calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
                /*throws CalculateException, JmriException*/
        {
            QDateTime currentTime = QDateTime::currentDateTime();//Date.from(Instant.now());
            QVariant param;
            if (parameterList.isEmpty())
            {  // Num minutes since midnight
                return (currentTime.time().hour() * 60) + currentTime.time().minute();
            } else if (parameterList.size() == 1)
            {
                param = parameterList.at(0)->calculate(symbolTable);
                if (param.canConvert<QString>()) {
                    if(param == "hour")
                        return currentTime.time().hour();
                    else if(param == "min")
                        return currentTime.time().minute();
                    else if(param == "sec")
                        return currentTime.time().second();
                    else if(param == "minOfDay")
                        return (currentTime.time().hour() * 60) + currentTime.time().minute();
                    else if(param ==  "secOfDay")
                        return ((currentTime.time().hour() * 60) + currentTime.time().minute()) * 60 + currentTime.time().second();
                    else
                        throw new CalculateException(tr("Parameter \"%1\" with value \"%2\"  for function \"%3\" is invalid").arg(1).arg( param.toString(), getName()));
                } else {
                    throw new CalculateException(tr("Parameter \"%1\" with value \"%2\"  for function \"%3\" is invalid").arg(1).arg( param.toString(), getName()));
                }
            }
            throw new WrongNumberOfParametersException(tr("Function \"%1\" has wrong number of parameters").arg(getName()));
        }

        //@Override
        /*public*/  QString SystemClockFunction::getDescription() {
            return tr("<html>\n<h1>systemClock()</h1>\n<h2>systemClock()</h2>\nReturns the number of minutes since midnight\n<h2>systemClock(\"hour\")</h2>\nReturns the hour\n<h2>systemClock(\"min\")</h2>\nReturns the minute \n <h2>systemClock(\"sec\")</h2>\nReturns the second \n<h2>systemClock(\"minOfDay\")</h2>\nReturns the number of minutes since midnight\n<h2>systemClock(\"secOfDay\")</h2>\nReturns the number of seconds since midnight\n</html>");
        }


//    /*public*/  static class FastClockFunction implements Function {


        //@Override
        /*public*/  QString FastClockFunction::getModule() {
            return (new ClockFunctions())->getModule();
        }

        //@Override
        /*public*/  QString FastClockFunction::getConstantDescriptions() {
            return (new ClockFunctions())->getConstantDescription();
        }

        //@Override
        /*public*/  QString FastClockFunction::getName() {
            return "fastClock";
        }

        //@Override
        //@SuppressWarnings("deprecation")        // Date.getMinutes, Date.getHours
        /*public*/  QVariant FastClockFunction::calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
                /*throws JmriException*/ {

            QDateTime currentTime = _fastClock->getTime();
            QVariant param;
            if (parameterList.isEmpty()) {  // Num minutes since midnight
                return (currentTime.time().hour() * 60) + currentTime.time().minute();
            } else if (parameterList.size() == 1) {
                QVariant param = parameterList.at(0)->calculate(symbolTable);
                if (param.canConvert<QString>()) {
                    if(param == "hour")
                        return currentTime.time().hour();
                    else if(param == "min")
                        return currentTime.time().minute();
                    else if(param == "minOfDay")
                        return (currentTime.time().hour() * 60) + currentTime.time().minute();
                    else
                        throw new CalculateException(tr("Parameter \"%1\" with value \"%2\"  for function \"%3\" is invalid").arg(1).arg(param.toString(), getName()));
                } else {
                    throw new CalculateException(tr("Parameter \"%1\" with value \"%2\"  for function \"%3\" is invalid").arg(1).arg(param.toString(), getName()));
                }
            }
            throw new WrongNumberOfParametersException(tr("Function \"%1\" has wrong number of parameters").arg(getName()));
        }

        //@Override
        /*/*public*/  QString FastClockFunction::getDescription() {
            return tr("<html>\n<h1>fastClock()</h1>\n<h2>fastClock()</h2> \nReturns the number of minutes since midnight\n<h2>fastClock(\"hour\")</h2>\nReturns the hour\n<h2>fastClock(\"min\")</h2> \nReturns the minute\n<h2>fastClock(\"minOfDay\")</h2>\nReturns the number of minutes since midnight\n</html>");
        }


