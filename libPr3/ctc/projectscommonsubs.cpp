#include "projectscommonsubs.h"
#include "loggerfactory.h"
#include <QPushButton>

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
#if 0
    static /*public*/ ArrayList<String> getArrayListOfSignalNames(ArrayList<NBHSignal> array) {
        ArrayList<String> stringList = new ArrayList<>();
        array.forEach(row -> {
            NamedBeanHandle handle = (NamedBeanHandle) row.getBeanHandle();
            stringList.add(handle.getName());
        });
        return stringList;
    }

    static /*public*/ ArrayList<NBHSignal> getArrayListOfSignals(ArrayList<String> signalNames) {
        CtcManager cm = InstanceManager.getDefault(CtcManager.class);
        ArrayList<NBHSignal> newList = new ArrayList<>();
        signalNames.forEach(name -> {
            NBHSignal newSignal = cm.getNBHSignal(name);
            if (newSignal == null) {
                newSignal = new NBHSignal(name);
            }
            if (newSignal.valid()) {
                newList.add(newSignal);
            }
        });
        return newList;
    }

//  Returns an ArrayList guaranteed to have exactly "returnArrayListSize" entries,
//  and if the passed "csvString" has too few entries, then those missing end values are set to "":
    static /*public*/ ArrayList<String> getFixedArrayListSizeFromCSV(String csvString, int returnArrayListSize) {
        ArrayList<String> returnArray = getArrayListFromCSV(csvString);
        while (returnArray.size() < returnArrayListSize) returnArray.add("");
        return returnArray;
    }
#endif
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
