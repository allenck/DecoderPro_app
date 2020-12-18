#include "importcodebuttonhandlerdata.h"
#include <qfile.h>
#include <QTextStream>
#include "ctcfiles.h"
/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
// /*public*/ class ImportCodeButtonHandlerData implements Serializable {
    /*private*/ /*final*/ /*static*/ int ImportCodeButtonHandlerData::FILE_VERSION = 6;
    /*public*/ /*static*/ /*final*/ int ImportCodeButtonHandlerData::SWITCH_NOT_SLAVED = -1;

    /*private*/ /*final*/ /*static*/ QMap<int, ImportCodeButtonHandlerData::LOCK_IMPLEMENTATION> ImportCodeButtonHandlerData::LOCK_IMPLEMENTATION::map = QMap<int, ImportCodeButtonHandlerData::LOCK_IMPLEMENTATION>();
    /*public*/  QString ImportCodeButtonHandlerData::LOCK_IMPLEMENTATION::toString()
    {
     if(_mRadioGroupValue == ImportCodeButtonHandlerData::LOCK_IMPLEMENTATION::GREGS) return "GREGS";
     return "OTHER";
    }
    /*private*/ /*final*/ /*static*/ QMap<int, ImportCodeButtonHandlerData::TURNOUT_TYPE> ImportCodeButtonHandlerData::TURNOUT_TYPE::map = QMap<int, ImportCodeButtonHandlerData::TURNOUT_TYPE>();
    /*public*/ QString ImportCodeButtonHandlerData::TURNOUT_TYPE::toString()
    {
     if(_mRadioGroupValue == ImportCodeButtonHandlerData::TURNOUT_TYPE::TURNOUT)
      return "TURNOUT";
     if(_mRadioGroupValue== ImportCodeButtonHandlerData::TURNOUT_TYPE::CROSSOVER)
      return "CROSSOVER";
     return "DOUBLE_CROSSOVER";
    }
    /*public*/ static ImportCodeButtonHandlerData::TURNOUT_TYPE valueOf(QString t)
    {
     if(t =="TURNOUT" ) return ImportCodeButtonHandlerData::TURNOUT_TYPE(ImportCodeButtonHandlerData::TURNOUT_TYPE(ImportCodeButtonHandlerData::TURNOUT_TYPE::TURNOUT));
     else if(t =="CROSSOVER" ) return ImportCodeButtonHandlerData::TURNOUT_TYPE(ImportCodeButtonHandlerData::TURNOUT_TYPE::CROSSOVER);
     return ImportCodeButtonHandlerData::TURNOUT_TYPE(ImportCodeButtonHandlerData::TURNOUT_TYPE::DOUBLE_CROSSOVER);
    }


    /*public*/ ImportCodeButtonHandlerData::ImportCodeButtonHandlerData(QObject *parent) : QObject(parent){
        _mOSSectionSwitchSlavedToUniqueID = SWITCH_NOT_SLAVED;
        _mSWDI_GUITurnoutType = ImportCodeButtonHandlerData::TURNOUT_TYPE::TURNOUT;
        _mTUL_LockImplementation = LOCK_IMPLEMENTATION::GREGS;
    }
    /*private*/ /*static*/ /*final*/ long ImportCodeButtonHandlerData::serialVersionUID = 1L;


    /*public*/ void ImportCodeButtonHandlerData::upgradeSelf() {
        for (int oldVersion = _mFileVersion; oldVersion < FILE_VERSION; oldVersion++) {
            switch(oldVersion) {
                case 0:     // 0->1: Get rid of ALL Traffic locking stuff.  Incompatible with prior version.
                case 1:     // 1->2: Get rid of ALL Traffic locking stuff.  Incompatible with prior version.
                case 2:     // 2->3: Get rid of ALL Traffic locking stuff.  Incompatible with prior version.
                case 3:     // 3->4: Get rid of ALL Traffic locking stuff.  Incompatible with prior version.
                    _mTRL_Enabled = false;
                    _mTRL_LeftTrafficLockingRulesSSVList = "";
                    _mTRL_RightTrafficLockingRulesSSVList = "";
                    break;
                default:    // 4->5, 5->6: Do NOTHING!
                    break;
            }
        }
        _mFileVersion = FILE_VERSION;       // Now at this version
    }

/*  When I change a variable name but want to keep the contents, I need to
    pre-process the file BEFORE I turn it over to serialization.  That is done
    here:
    NOTE:
    This is ALWAYS done BEFORE the normal "upgradeSelf"!  And if it matches a version to change,
    it ALWAYS increments the file version by one!  Therefore "upgradeSelf" will see one greater!
    So if you want to do BOTH, then you need to increase file version by 2, and insure that the
    first increment is processed by this:
*/
    /*private*/ /*final*/ /*static*/ QString ImportCodeButtonHandlerData::FILE_VERSION_STRING = "<string>_mFileVersion</string>"; // NOI18N
    /*private*/ /*final*/ /*static*/ QString ImportCodeButtonHandlerData::LESS_THAN_SIGN = "<";                                   // NOI18N
    /*private*/ /*static*/ /*final*/ QString ImportCodeButtonHandlerData::TEMPORARY_EXTENSION = ".xmlTMP";                        // NOI18N

//  Regarding "@SuppressFBWarnings": My attitude is that if the input file is screwed up, do nothing!:
    //@SuppressFBWarnings(value = "NP_IMMEDIATE_DEREFERENCE_OF_READLINE", justification = "I'm already catching 'NullPointerException', it's ok!")
    /*static*/ /*public*/ void ImportCodeButtonHandlerData::preprocessingUpgradeSelf(QString filename) {
//  First, get the existing _mFileVersion from the file to see if we need to work on it:
        int fileVersion = -1;       // Indicate none found.
        try {
         //(BufferedReader bufferedReader = new BufferedReader(new FileReader(filename)))
         QFile* f = new QFile(filename);
         if(!f->open(QIODevice::ReadOnly | QIODevice::Text))
          throw IOException(tr(" %1 open err: %2").arg(filename).arg(f->errorString()));
         QTextStream* bufferedReader = new QTextStream(f);
            QString aLine;
            while (!(aLine = bufferedReader->readLine()).contains(FILE_VERSION_STRING)) {}   // Skip to the line IF it exists.
            bufferedReader->readLine();  // Ignore <void method="set">
            bufferedReader->readLine();  // Ignore <object idref="CodeButtonHandlerData18"/>
            aLine = bufferedReader->readLine().trimmed();  // Get something like <int>4</int>
            if (aLine.startsWith(INT_START_STRING)) {
                aLine = aLine.mid(5);     // Get rid of it.
                fileVersion = aLine.mid(0, aLine.indexOf(LESS_THAN_SIGN)).toInt();
            }
            f->close();
        } catch (IOException /*| NumberFormatException | NullPointerException*/ e) {}
        if (fileVersion < 0) return;    // Safety: Nothing found, ignore it (though we should have found and parsed it!)
        switch (fileVersion) {
            case 4:
                upgradeVersion4FileTo5(filename);
                break;
            case 5:
                upgradeVersion5FileTo6(filename);
                break;
            default:
                break;
        }
    }

    //@SuppressFBWarnings(value = "RV_RETURN_VALUE_IGNORED_BAD_PRACTICE", justification = "Any problems, I don't care, it's too late by this point")
    /*static*/ /*private*/ void ImportCodeButtonHandlerData::upgradeVersion4FileTo5(QString filename) {
        QString temporaryFilename = CTCFiles::changeExtensionTo(filename, TEMPORARY_EXTENSION);
        (new QFile(temporaryFilename))->remove();   // Just delete it for safety before we start:
        bool hadAChange = false;
#if 0
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(filename));
             BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(temporaryFilename))) {
            QString aLine = null;
            while ((aLine = bufferedReader.readLine()) != null) { // Not EOF:
                if ((aLine = checkFileVersion(bufferedReader, bufferedWriter, aLine, "4", "5")) == null) { hadAChange = true; continue; } // Was processed.
                if ((aLine = checkForRefactor(bufferedWriter, aLine, "_mSWDI_ActualTurnout",                      "_mSWDI_ExternalTurnout")) == null) { hadAChange = true; continue; }  // NOI18N Was processed.
                if ((aLine = checkForRefactor(bufferedWriter, aLine, "_mTUL_ActualTurnout",                       "_mTUL_ExternalTurnout")) == null) { hadAChange = true; continue; }  // NOI18N Was processed.
                if ((aLine = checkForRefactor(bufferedWriter, aLine, "_mTUL_ActualTurnoutFeedbackDifferent",      "_mTUL_ExternalTurnoutFeedbackDifferent")) == null) { hadAChange = true; continue; }  // NOI18N Was processed.
                if ((aLine = checkForRefactor(bufferedWriter, aLine, "_mTUL_AdditionalTurnout1",                  "_mTUL_AdditionalExternalTurnout1")) == null) { hadAChange = true; continue; }  // NOI18N Was processed.
                if ((aLine = checkForRefactor(bufferedWriter, aLine, "_mTUL_AdditionalTurnout1FeedbackDifferent", "_mTUL_AdditionalExternalTurnout1FeedbackDifferent")) == null) { hadAChange = true; continue; }  // NOI18N Was processed.
                if ((aLine = checkForRefactor(bufferedWriter, aLine, "_mTUL_AdditionalTurnout2",                  "_mTUL_AdditionalExternalTurnout2")) == null) { hadAChange = true; continue; }  // NOI18N Was processed.
                if ((aLine = checkForRefactor(bufferedWriter, aLine, "_mTUL_AdditionalTurnout2FeedbackDifferent", "_mTUL_AdditionalExternalTurnout2FeedbackDifferent")) == null) { hadAChange = true; continue; }  // NOI18N Was processed.
                if ((aLine = checkForRefactor(bufferedWriter, aLine, "_mTUL_AdditionalTurnout3",                  "_mTUL_AdditionalExternalTurnout3")) == null) { hadAChange = true; continue; }  // NOI18N Was processed.
                if ((aLine = checkForRefactor(bufferedWriter, aLine, "_mTUL_AdditionalTurnout3FeedbackDifferent", "_mTUL_AdditionalExternalTurnout3FeedbackDifferent")) == null) { hadAChange = true; continue; }  // NOI18N Was processed.
                writeLine(bufferedWriter, aLine);
            }
//  Regarding commented out code (due to SpotBugs):
//  I'm a safety "nut".  I will do such things in case other code is someday inserted
//  between the above "check for != null" and here.  But to satisfy SpotBugs:
            if (/*aLine == null && */hadAChange) { // Do the two step:
                bufferedReader.close();
                bufferedWriter.close();
                File oldFile = new File(filename);
                oldFile.delete();                   // Delete existing old file.
                (new File(temporaryFilename)).renameTo(oldFile);    // Rename temporary filename to proper /*final*/ file.
            }
        } catch (IOException e) {}  // Any other error(s) just cleans up:
        (new File(temporaryFilename)).delete();        // If we get here, just clean up.
#endif
    }

    /**
     * This routine was written because CSVPrinter at some point began putting "\r\n" at the
     * end of lines returned by "toString()" based upon the version of the Java Library that
     * was present.  This corrupted my data internally, and a user out in the field got caught
     * by this change in the Java library.  The result was lines like:
     * Hurricane X-over Track 1 West,LEFTTRAFFIC,Flashing Red,,Hurricane Track 1,IS5:SWNI,IS3:SWNI,IS1:SWNI,,,;;;;Hurricane X-over Track 1 West,LEFTTRAFFIC,Flashing Red,,Hurricane Track 2,IS5:SWNI,IS3:SWNI,IS1:SWRI,,,;;;;Hurricane X-over Track 1 East,RIGHTTRAFFIC,Flashing Red,,East Hurricane Track 1,IS1:SWNI,IS3:SWNI,IS5:SWNI,,,;;;;Hurricane X-over Track 1 East,RIGHTTRAFFIC,Flashing Red,,East Hurricane Track 2,IS1:SWNI,IS3:SWNI,IS5:SWRI,IS7:SWNI,,
     * You'll notice here (and other places in the line) that there are multiple ;;;; in a row                ^^^^ ...-> also
     * caused by this.  What I will do here is fix any multiple ;;;; to a single ;:
     * @param filename The .xml file to convert from version 5 format to version 6 format.
     */
    //@SuppressFBWarnings(value = "RV_RETURN_VALUE_IGNORED_BAD_PRACTICE", justification = "Any problems, I don't care, it's too late by this point")
    /*static*/ /*private*/ void ImportCodeButtonHandlerData::upgradeVersion5FileTo6(QString filename) {
        QString temporaryFilename = CTCFiles::changeExtensionTo(filename, TEMPORARY_EXTENSION);
#if 0
        (new File(temporaryFilename)).delete();   // Just delete it for safety before we start:
        bool hadAChange = false;
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(filename)); BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(temporaryFilename))) {
            String aLine = null;
            while ((aLine = bufferedReader.readLine()) != null) { // Not EOF:
                if ((aLine = checkFileVersion(bufferedReader, bufferedWriter, aLine, "5", "6")) == null) { hadAChange = true; continue; } // Was processed.
                if ((aLine = checkForMultipleSemiColons(bufferedWriter, aLine)) == null) { hadAChange = true; continue; }  // NOI18N Was processed.
                writeLine(bufferedWriter, aLine);
            }
//  Regarding commented out code (due to SpotBugs):
//  I'm a safety "nut".  I will do such things in case other code is someday inserted
//  between the above "check for != null" and here.  But to satisfy SpotBugs:
            if (/*aLine == null && */hadAChange) { // Do the two step:
                bufferedReader.close();
                bufferedWriter.close();
                File oldFile = new File(filename);
                oldFile.delete();                   // Delete existing old file.
                (new File(temporaryFilename)).renameTo(oldFile);    // Rename temporary filename to proper /*final*/ file.
            }
        } catch (IOException e) {}  // Any other error(s) just cleans up:
        (new File(temporaryFilename)).delete();        // If we get here, just clean up.
#endif
    }


/*
    Returns:    null if we processed it or it was the wrong format, and in either case WROTE the line(s) out indicating that we handled it.
        or
                The original aLine passed and NOTHING written, so that other(s) can check it further.
*/
    /*private*/ /*final*/ /*static*/ QString ImportCodeButtonHandlerData::INT_START_STRING = "<int>"; // NOI18N
    /*private*/ /*final*/ /*static*/ QString ImportCodeButtonHandlerData::INT_END_STRING = "</int>";  // NOI18N
    /*static*/ /*private*/ QString ImportCodeButtonHandlerData::checkFileVersion(QTextStream* bufferedReader, QTextStream* bufferedWriter, QString aLine, QString oldVersion, QString newVersion) throw (IOException) {
        if (aLine.contains(FILE_VERSION_STRING)) {
            writeLine(bufferedWriter, aLine);
            writeLine(bufferedWriter, bufferedReader->readLine());   // Ignore <void method="set">
            writeLine(bufferedWriter, bufferedReader->readLine());   // Ignore <object idref="CodeButtonHandlerData18"/>
            aLine = bufferedReader->readLine();  // Get something like <int>4</int>
            if (!aLine.isEmpty()) {
                int intStart = aLine.indexOf(INT_START_STRING + oldVersion + INT_END_STRING);
                if (intStart >= 0) { // Found, replace:
//                    writeLine(bufferedWriter, aLine.substring(0, intStart) + INT_START_STRING + newVersion + INT_END_STRING);
                 *bufferedWriter << aLine.mid(0, intStart) + INT_START_STRING + newVersion + INT_END_STRING;
                } else {
//                    writeLine(bufferedWriter, aLine);
                 *bufferedWriter <<aLine;
                }
            }
            return QString();
        }
        return aLine;   // Line wasn't for us!
    }

    /*private*/ /*final*/ /*static*/ QString ImportCodeButtonHandlerData::STRING_START_STRING = "<string>";   // NOI18N
    /*private*/ /*final*/ /*static*/ QString ImportCodeButtonHandlerData::STRING_END_STRING = "</string>";    // NOI18N
    /*static*/ /*private*/ QString ImportCodeButtonHandlerData::checkForRefactor(QTextStream* bufferedWriter, QString aLine, QString oldName, QString newName) throw (IOException) {
        int intStart = aLine.indexOf(STRING_START_STRING + oldName + STRING_END_STRING);
        if (intStart >= 0) { // Found, replace:
            //writeLine(bufferedWriter, aLine.substring(0, intStart) + STRING_START_STRING + newName + STRING_END_STRING);
         *bufferedWriter << aLine.mid(0, intStart) + STRING_START_STRING + newName + STRING_END_STRING;
         return QString();
        }
        return aLine;
    }

    /*static*/ /*private*/ QString ImportCodeButtonHandlerData::checkForMultipleSemiColons(QTextStream* bufferedWriter, QString aLine) throw (IOException) {
        int intStart = aLine.indexOf(STRING_START_STRING);
        int intEnd = aLine.indexOf(STRING_END_STRING);
        if (intStart >=0 && intEnd >=0 && intStart < intEnd) { // Insure a line we might look at:
           while (aLine.contains(";;")) {
               aLine= aLine.replace(";;", ";");
           }
        }
        if (intStart >= 0) { // Found, replace:
            writeLine(bufferedWriter, aLine);
            return QString();
        }
        return aLine;
    }


    /*static*/ /*private*/ void ImportCodeButtonHandlerData::writeLine(QTextStream* bufferedWriter, QString aLine) throw (IOException) {
        *bufferedWriter << aLine; *bufferedWriter << "\n"/*newLine()*/;
    }
