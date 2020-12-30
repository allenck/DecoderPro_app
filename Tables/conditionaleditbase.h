#ifndef CONDITONALEDITBASE_H
#define CONDITONALEDITBASE_H
#include "loggerfactory.h"
#include <QObject>
#include "logix.h"
#include "logixmanager.h"
#include "conditionalmanager.h"
#include "jmribeancombobox.h"
#include "jtable.h"
#include "jframe.h"
#include "pickframe.h"
#include "jtextfield.h"
#include "listselectionlistener.h"
#include "actionevent.h"
#include "actionlistener.h"

class Light;
class LogixEventListener;
class PickSingleListener;
class ConditionalEditBase : public QObject
{
 Q_OBJECT
public:
 explicit ConditionalEditBase(QObject *parent = nullptr);
 ConditionalEditBase(QString sName, QObject *parent = nullptr);
 /**
  * Input selection names
  *
  * @since 4.7.3
  */
 /*public*/ enum SelectionMode {
     /**
      * Use the traditional text field, with the tabbed Pick List available
      * for drag-n-drop
      */
     USEMULTI,
     /**
      * Use the traditional text field, but with a single Pick List that
      * responds with a click
      */
     USESINGLE,
     /**
      * Use combo boxes to select names instead of a text field.
      */
     USECOMBO
 };
 /*public*/ void addLogixEventListener(LogixEventListener* listener);
 /*public*/ void removeLogixEventListener(LogixEventListener* listener);
 /*public*/ static QString formatTime(int hour, int minute);
 /**
  * This contains a list of commands to be processed by the listener
  * recipient
  */
 /*public*/ QMap<QString, QString>* logixData;// = new HashMap<>();
 /*public*/ static QString translateAntecedent(QString antecedent, bool isLocal);
signals:
 void logixEventOccurred();

public slots:

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(ConditionalEditBase.class);
 void common();
 // ------------ variable definitions ------------
 ConditionalManager* _conditionalManager;// = null;
 LogixManager* _logixManager;// = null;
 Logix* _curLogix;// = null;

 int _numConditionals;// = 0;
 bool _inEditMode;// = false;

 bool _showReminder;// = false;
 bool _suppressReminder;// = false;
 bool _suppressIndirectRef;// = false;

 JmriBeanComboBox* _comboNameBox;// = null;
 SelectionMode _selectionMode;
 void loadSelectionMode();
 JTable* _pickTable;// = NULL;               // Current pick table
 QTabWidget* _pickTabPane;// = NULL;        // The tabbed panel for the pick table
 PickFrame* _pickTables;

 JFrame* _pickSingleFrame;// = NULL;
 PickSingleListener* _pickListener = NULL;
 /**
  * Maintain a list of listeners -- normally only one.
  */
 QList<LogixEventListener*>* listenerList;// = new QList<LogixEventListener*>();
 void fireLogixEvent();
 bool checkConditionalReferences(QString logixName);
 void updateWhereUsed(QStringList oldTargetNames, QStringList newTargetNames, QString refName);
 void openPickListTable();
 void hidePickListTable();
 void createSinglePanelPickList(int itemType, PickSingleListener* listener, bool actionType);
 void closeSinglePanelPickList();
 void setPickListTab(int curType, bool actionType);
 void findPickListTabPane(QObjectList compList, int level);
 JmriBeanComboBox* createNameBox(int itemType);
 QString validateSensorReference(QString name);
 QString validateTurnoutReference(QString name);
 QString validateSignalHeadReference(QString name);
 QString validateSignalMastReference(QString name);
 QString validateWarrantReference(QString name);
 QString validateOBlockReference(QString name);
 QString validateConditionalReference(QString name);
 QString validateLogixReference(QString name);
 QString validateRouteReference(QString name);
 QString validateAudioReference(QString name);
 QString validateEntryExitReference(QString name);
 QString validateLightReference(QString name);
 QString validateMemoryReference(QString name);
 void messageInvalidSignalHeadAppearance(QString name, QString appearance);
 void messageInvalidActionItemName(QString name, QString itemType);
 void messageDuplicateConditionalUserName(QString svName);
 int parseTime(QString s);
 bool confirmIndirectMemory(QString memName);
 void loadReferenceNames(QList<ConditionalVariable*> varList, QSet<QString> treeSet);
 bool validateTimeReference(int actionType, QString ref);
 Light* getLight(QString name);
 bool validateIntensityReference(int actionType, QString intReference);
 void displayBadNumberReference(int actionType);
 bool validateIntensity(int time);
 void showSaveReminder();
 bool checkConditionalUserName(QString uName, Logix* logix);
 QString makeAntecedent(QList<ConditionalVariable*> variableList);
 QString appendToAntecedent(Conditional::AntecedentOperator logicType, int varListSize, QString antecedent);
 bool validateAntecedent(Conditional::AntecedentOperator logicType, QString antecedentText, QList<ConditionalVariable*> variableList, Conditional* curConditional);
protected:
 /*protected*/ QString getClassName();

friend class LTALogixEventListener;
friend class LTALogixEventListener1;
friend class ConditionalListEdit;
friend class PickSingleListener;
friend class LVariableTableModel;
friend class ConditionalTableModel;
friend class EditLogixFrameWindowListener;
friend class ConditionalTreeEdit;
};

/*public*/ class LogixEventListener : public QObject,public EventListener {
 Q_OBJECT
 Q_INTERFACES(EventListener)
 ConditionalEditBase* ceb;
public:
LogixEventListener(ConditionalEditBase* ceb);
QObject* self() {return (QObject*)this;}
public slots:
    virtual void logixEventOccurred();
};

class PickSingleListener : public ListSelectionListener {
 Q_OBJECT
 JTextField* saveTextField;
 int saveItemType;          // Current table type
 ConditionalEditBase* base;
public:
 QObject* self() {return (QObject*)this;}
    /**
     * @param textField The target field object when an entry is selected
     * @param itemType  The current selected table type number
     */
    /*public*/ PickSingleListener(JTextField* textField, int itemType, ConditionalEditBase* base) ;
    /*public*/ void valueChanged(ListSelectionEvent* e) ;
    /*public*/ int getItemType();
private:
 void closeSinglePanelPickList();

};
/**
 * Listen for name combo box selection events.
 * <p>
 * When a combo box row is selected, the user/system name is copied to the
 * Action or Variable name field.
 *
 * @since 4.7.3
 */
/*static*/ class NameBoxListener : public ActionListener {
 JTextField* saveTextField;
 QObject* src;
Q_OBJECT
public:
    /**
     * @param textField The target field object when an entry is selected
     */
    /*public*/ NameBoxListener(JTextField* textField, QObject* src) {
        saveTextField = textField;
        this->src = src;
    }
public slots:

    //@Override
    /*public*/ void actionPerformed(JActionEvent* /*e*/ = 0) {
        // Get the combo box and display name
        //QObject* src = e.getSource();
        //if (!(src instanceof JmriBeanComboBox))
        if(qobject_cast<JmriBeanComboBox*>(src) != NULL)
        {
            return;
        }
        JmriBeanComboBox* srcBox = (JmriBeanComboBox*) src;
        QString newName = srcBox->currentText();

//        if (log.isDebugEnabled()) {
//            log.debug("NameBoxListener: new name = '{}'", newName);  // NOI18N
//        }
        saveTextField->setText(newName);
    }
 friend class ConditionalListEdit;
};

#endif // CONDITONALEDITBASE_H
