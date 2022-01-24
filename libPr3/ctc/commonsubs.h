#ifndef COMMONSUBS_H
#define COMMONSUBS_H

#include <QObject>
#include "projectscommonsubs.h"
#include "jtextfield.h"
#include "jbutton.h"
#include <QButtonGroup>
#include <QList>
#include <QListIterator>
#include "jlabel.h"
#include "jtextfield.h"
#include "jcombobox.h"

class CTCSerialData;
class NBHSignal;
class NBHTurnout;
class NBHSensor;
class CodeButtonHandlerData;
class DefaultTableModel;
class JFrame;
class Logger;
class JFormattedTextField;
class CommonSubs : public QObject
{
  Q_OBJECT
 public:
  explicit CommonSubs(QObject *parent = nullptr);
  /*public*/ static void setMillisecondsEdit(JFormattedTextField* formattedTextField);
  /*public*/ static int getIntFromJTextFieldNoThrow(JTextField* textField);
  /*public*/ static bool allowClose(JFrame *parentComponent, bool dataChanged);
  /*public*/ static void addHelpMenu(JFrame* frame, QString ref, bool direct);
  /*public*/ static QString getCSVStringFromDefaultTableModel(DefaultTableModel* defaultTableModel);
  /*public*/ static QList<QString> getStringArrayFromDefaultTableModel(DefaultTableModel* defaultTableModel);
  /*public*/ static int compactDefaultTableModel(DefaultTableModel* defaultTableModel);
  /*public*/ static QList<QString> getArrayListOfSelectableSwitchDirectionIndicators(QList<CodeButtonHandlerData*> codeButtonHandlerDataList);
  /*public*/ static QList<int> getArrayListOfSelectableOSSectionUniqueIDs(QList<CodeButtonHandlerData*> codeButtonHandlerDataList);
  /*public*/ static void populateJComboBoxWithColumnDescriptionsAndSelectViaUniqueID(JComboBox/*<String>*/* jComboBox, CTCSerialData* ctcSerialData, int uniqueID);
  /*public*/ static void populateJComboBoxWithColumnDescriptions(JComboBox/*<String>*/* jComboBox, CTCSerialData* ctcSerialData);
  /*public*/ static bool populateJComboBoxWithColumnDescriptionsExceptOurs(JComboBox/*<String>*/* jComboBox, CTCSerialData* ctcSerialData, int ourUniqueID, QList<int>* uniqueIDS);
  /*public*/ static void populateJComboBoxWithBeans(JComboBox/*<String>*/* jComboBox, QString beanType, QString currentSelection, bool firstRowBlank);
  /*public*/ static void setSelectedIndexOfJComboBoxViaUniqueID(JComboBox/*<String>*/* jComboBox, CTCSerialData* ctcSerialData, int uniqueID);
  /*public*/ static void numberButtonGroup(QButtonGroup* buttonGroup);
  /*public*/ static void setButtonSelected(QButtonGroup *buttonGroup, int selected);
  /*public*/ static bool missingFieldsErrorDialogDisplayed(JFrame* parentComponent, QList<QString> errors, bool isCancel);
  /*public*/ static void checkJTextFieldNotEmpty(JTextField* field, JLabel* promptName, QList<QString> errors);
  /*public*/ static bool isJTextFieldNotEmpty(JTextField* field);
  /*public*/ static void checkJComboBoxNotEmpty(JComboBox/*<String>*/* combo, JLabel* promptName, QList<QString> errors);
  /*public*/ static bool isJComboBoxNotEmpty(JComboBox/*<String>*/* combo);
  /*public*/ static NBHSensor* getNBHSensor(QString newName, bool isInternal);
  /*public*/ static NBHTurnout* getNBHTurnout(QString newName, bool feedbackDifferent);
  /*public*/ static NBHSignal* getNBHSignal(QString newName);
  /*public*/ static void addSensorToSensorList(QList<NBHSensor*>* list, QString sensorName);

 signals:

 public slots:

 private:
  static Logger* log;
};

#endif // COMMONSUBS_H
