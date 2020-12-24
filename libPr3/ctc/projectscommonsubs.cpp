#include "projectscommonsubs.h"
#include "loggerfactory.h"
#include <QPushButton>
#include "nbhsignal.h"
#include "namedbeanhandle.h"
#include "ctcmanager.h"
#include "instancemanager.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */

///*public*/ class ProjectsCommonSubs {
    /*static*/ /*final*/ /*public*/ char ProjectsCommonSubs::SSV_SEPARATOR = ';';

    /*static*/ /*public*/ QList<QString> ProjectsCommonSubs::getArrayListFromCSV(QString csvString) { return helper1(csvString, /*CSVFormat.DEFAULT.getDelimiter()*/'/');}
    /*static*/ /*public*/ QList<QString> ProjectsCommonSubs::getArrayListFromSSV(QString ssvString) { return helper1(ssvString, SSV_SEPARATOR); }
    /*static*/ /*private*/ QList<QString> ProjectsCommonSubs::helper1(QString ssvString, char separator) {
        QList<QString> list = QList<QString>();
#if 0
        try (CSVParser parser = new CSVParser(new StringReader(ssvString), CSVFormat.DEFAULT.withQuote(null).withDelimiter(separator).withRecordSeparator(null))) {
            parser.getRecords().forEach(record -> record.forEach(item -> list.add(item)));
        } catch (IOException ex) {
            log.error("Unable to parse {}", ssvString, ex);
        }
#endif
        return list;
    }

    /*static*/ /*public*/ QList<QString> ProjectsCommonSubs::getArrayListOfSignalNames(QList<NBHSignal*>* array) {
        QList<QString> stringList = QList<QString>();
        //array.forEach(row ->
        foreach(NBHSignal* row, *array)
        {
            NamedBeanHandle<NamedBean*>* handle = (NamedBeanHandle<NamedBean*>*) row->getBeanHandle();
            stringList.append(handle->getName());
        }//);
        return stringList;
    }

    /*static*/ /*public*/ QList<NBHSignal*>* ProjectsCommonSubs::getArrayListOfSignals(QList<QString> signalNames) {
        CtcManager* cm = (CtcManager*)InstanceManager::getDefault("CtcManager");
        QList<NBHSignal*>* newList = new QList<NBHSignal*>();
        //signalNames.forEach(name ->
        foreach(QString name, signalNames)
        {
            NBHSignal* newSignal = cm->getNBHSignal(name);
            if (newSignal == nullptr) {
                newSignal = new NBHSignal(name);
            }
            if (newSignal->valid()) {
                newList->append(newSignal);
            }
        }//);
        return newList;
    }

//  Returns an ArrayList guaranteed to have exactly "returnArrayListSize" entries,
//  and if the passed "csvString" has too few entries, then those missing end values are set to "":
    /*static*/ /*public*/ QList<QString> ProjectsCommonSubs::getFixedArrayListSizeFromCSV(QString csvString, int returnArrayListSize) {
        QList<QString> returnArray = ProjectsCommonSubs::getArrayListFromCSV(csvString);
        while (returnArray.size() < returnArrayListSize) returnArray.append("");
        return returnArray;
    }

    /*static*/ /*public*/ int ProjectsCommonSubs::getIntFromStringNoThrow(QString aString, int defaultValueIfProblem) {
        int returnValue = defaultValueIfProblem;    // Default if error
        bool ok;
         returnValue =(aString).toInt(&ok);
    if(!ok) {}
        return returnValue;
    }

    /*public*/ /*static*/ bool ProjectsCommonSubs::isNullOrEmptyString(QString aString) {
        return aString.isNull() || aString.trimmed().length() == 0;
    }

//  If you used "CommonSubs.numberButtonGroup" above to setup the button group, then
//  you can call this routine to get the switch value as an int value,
//  since exception "NumberFormatException" should NEVER be thrown!
//  If it does throw because you screwed something up, it will return -1.
    /*public*/ /*static*/ int ProjectsCommonSubs::getButtonSelectedInt(QButtonGroup* buttonGroup) {
      bool ok;
      return (getButtonSelectedString(buttonGroup).toInt(&ok));
     if(!ok) { return -1; }
    }

    /*public*/ /*static*/ QString ProjectsCommonSubs::getButtonSelectedString(QButtonGroup* buttonGroup) {
        //return buttonGroup.getSelection().getActionCommand();
     return buttonGroup->checkedButton()->text();
    }

    /*private*/ /*static*/ /*final*/ Logger* ProjectsCommonSubs::log = LoggerFactory::getLogger("ProjectsCommonSubs");
