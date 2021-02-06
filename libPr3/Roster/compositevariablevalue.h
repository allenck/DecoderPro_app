#ifndef COMPOSITEVARIABLEVALUE_H
#define COMPOSITEVARIABLEVALUE_H
#include "enumvariablevalue.h"
#include <QComboBox>
#include "actionevent.h"
#include <QSet>

class JActionEvent;
/**
 * Define objects to save and manipulate a particular setting
 */
/*static*/ class LIBPR3SHARED_EXPORT Setting {
 public:
    QString varName;
    VariableValue* variable;
    int value;

    Setting(QString varName, VariableValue* variable, QString value)
    {
        log = new Logger("Setting");
        this->varName = varName;
        this->variable = variable;
        this->value = value.toInt();
        if (log->isDebugEnabled()) log->debug("    cTor Setting "+varName+" = "+value);

    }
    void setValue() {
        if (log->isDebugEnabled()) log->debug("    Setting.setValue of "+varName+" to "+value);
        variable->setIntValue(value);
    }
    bool match() {
        if (log->isDebugEnabled()) log->debug("         Match checks "+QString::number(variable->getIntValue())+" == "+QString::number(value));
        return (variable->getIntValue() == value);
    }
private:
 Logger* log;
};

/**
 * Defines a list of Setting objects.
 * <P> Serves as a home for various service methods
 */
/*static*/ class LIBPR3SHARED_EXPORT SettingList : QVector<Setting*>
{
public:
    /*public*/ SettingList() {
        //super();
        log = new Logger("SettingList");
        log->setDebugEnabled(true);
        if (log->isDebugEnabled()) log->debug("New setting list");
    }

    void addSetting(QString varName, VariableValue* variable, QString value) {
        Setting* s = new Setting(varName, variable, value);
        append(s);
    }
    void setValues() {
        if (log->isDebugEnabled()) log->debug(" setValues in length "+QString::number(size()));
        for (int i = 0; i<this->size(); i++) {
            Setting* s = this->at(i);
            s->setValue();
        }
    }
    bool match() {
        for (int i = 0; i<size(); i++) {
            if (!this->at(i)->match()) {
                if (log->isDebugEnabled()) log->debug("      No match in setting list of length "+QString::number(size())+" at position "+QString::number(i));
                return false;
            }
        }
        if (log->isDebugEnabled()) log->debug("      Match in setting list of length "+size());
        return true;
    }
private:
 Logger* log;
};

class CvValue;
class LIBPR3SHARED_EXPORT CompositeVariableValue : public EnumVariableValue
{
    Q_OBJECT
public:
    //explicit CompositeVariableValue(QObject *parent = 0);
    /*public*/ CompositeVariableValue(QString name, QString comment, QString cvName,
                             bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                             QString cvNum, QString mask, int minVal, int maxVal,
                             QMap<QString,CvValue*>* v, JLabel *status, QString stdname, QObject *parent = 0);
    /*public*/ CompositeVariableValue(QObject *parent = 0);
    /*public*/ QVector<CvValue*> usesCVs();
    /*public*/ void addChoice(QString name) ;
    /*public*/ void addSetting(QString choice, QString varName, VariableValue* variable, QString value);
    /*public*/ void lastItem();
    /*public*/ void setToolTipText(QString t);
    /*public*/ QVariant rangeVal();
    /*public*/ void setState(int state);
    /*public*/ int getIntValue();
    /*public*/ QWidget* getCommonRep();
    /*public*/ void setValue(int value);
    /*public*/ void setCvState(int state);
    /*public*/ bool isChanged();
    /*public*/ void setToRead(bool state);
    /*public*/ bool isToRead();
    /*public*/ void setToWrite(bool state) ;
    /*public*/ bool isToWrite() ;
    /*public*/ void readChanges() ;
    /*public*/ void writeChanges() ;
    /*public*/ void readAll() ;
    /*public*/ void writeAll();
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    void findValue();
    // clean up connections when done
    /*public*/ void dispose();

public slots:
    /*public*/ void actionPerformed(JActionEvent* e = 0);
private:
    QHash<QString,SettingList*>* choiceHash;// = new QHash<QString,SettingList>();
    QSet<VariableValue*>*   variables;// = new QSet<VariableValue>(20);  // VariableValue; 20 is an arbitrary guess
    bool amReading;// = false;
    bool readingChanges;// = false;
    bool amWriting;// = false;
    bool writingChanges;// = false;

protected:
    /*protected*/ void selectValue(int value);
    /*protected*/ void continueRead();
    /*protected*/ void continueWrite();

};

#endif // COMPOSITEVARIABLEVALUE_H
