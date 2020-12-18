#ifndef JOPTIONPANE_H
#define JOPTIONPANE_H
#include <QWidget>
#include <QVariant>
#include <QIcon>
#include <QList>
#include "jdialog.h"
#include "propertychangesupport.h"
#include "exceptions.h"
#include <QValidator>

class Component;
class JTextField;
class PropertyChangeEvent;
class OptionPaneUI;
class JOptionPane : public QWidget
{
 Q_OBJECT
public:

 /*public*/ static /*final*/ QVariant      UNINITIALIZED_VALUE;// = "uninitializedValue";
 //
 // Option types
 //

 /**
  * Type meaning Look and Feel should not supply any options -- only
  * use the options from the <code>JOptionPane</code>.
  */
 enum OPTIONTYPES
 {
  DEFAULT_OPTION = -1,
 /** Type used for <code>showConfirmDialog</code>. */
  YES_NO_OPTION = 0,
 /** Type used for <code>showConfirmDialog</code>. */
  YES_NO_CANCEL_OPTION = 1,
 /** Type used for <code>showConfirmDialog</code>. */
  OK_CANCEL_OPTION = 2
 };
 Q_ENUM(OPTIONTYPES)
 //
 // Return values.
 //
 enum RETURNVALUES
 {
 /** Return value from class method if YES is chosen. */
  YES_OPTION = 0,
 /** Return value from class method if NO is chosen. */
  NO_OPTION = 1,
 /** Return value from class method if CANCEL is chosen. */
  CANCEL_OPTION = 2,
 /** Return value form class method if OK is chosen. */
  OK_OPTION = 0,
 /** Return value from class method if user closes window without selecting
  * anything, more than likely this should be treated as either a
  * <code>CANCEL_OPTION</code> or <code>NO_OPTION</code>. */
  CLOSED_OPTION = -1
 };
 Q_ENUM(RETURNVALUES)
 //
 // Message types. Used by the UI to determine what icon to display,
 // and possibly what behavior to give based on the type.
 //
 enum MESSAGETYPES
 {
 /** Used for error messages. */
 ERROR_MESSAGE = 0,
 /** Used for information messages. */
 INFORMATION_MESSAGE = 1,
 /** Used for warning messages. */
 WARNING_MESSAGE = 2,
 /** Used for questions. */
 QUESTION_MESSAGE = 3,
 /** No icon is used. */
  PLAIN_MESSAGE = -1
 };
 Q_ENUM(MESSAGETYPES)
  /** Bound property name for <code>icon</code>. */
  /*public*/ static /*final*/ QString      ICON_PROPERTY;// = "icon";
  /** Bound property name for <code>message</code>. */
  /*public*/ static /*final*/ QString      MESSAGE_PROPERTY;// = "message";
  /** Bound property name for <code>value</code>. */
  /*public*/ static /*final*/ QString      VALUE_PROPERTY;// = "value";
  /** Bound property name for <code>option</code>. */
  /*public*/ static /*final*/ QString      OPTIONS_PROPERTY;// = "options";
  /** Bound property name for <code>initialValue</code>. */
  /*public*/ static /*final*/ QString      INITIAL_VALUE_PROPERTY;// = "initialValue";
  /** Bound property name for <code>type</code>. */
  /*public*/ static /*final*/ QString      MESSAGE_TYPE_PROPERTY;// = "messageType";
  /** Bound property name for <code>optionType</code>. */
  /*public*/ static /*final*/ QString      OPTION_TYPE_PROPERTY;// = "optionType";
  /** Bound property name for <code>selectionValues</code>. */
  /*public*/ static /*final*/ QString      SELECTION_VALUES_PROPERTY;// = "selectionValues";
  /** Bound property name for <code>initialSelectionValue</code>. */
  /*public*/ static /*final*/ QString      INITIAL_SELECTION_VALUE_PROPERTY;// = "initialSelectionValue";
  /** Bound property name for <code>inputValue</code>. */
  /*public*/ static /*final*/ QString      INPUT_VALUE_PROPERTY;// = "inputValue";
  /** Bound property name for <code>wantsInput</code>. */
  /*public*/ static /*final*/ QString      WANTS_INPUT_PROPERTY;// = "wantsInput";
 explicit JOptionPane(QWidget *parent = 0);
 /*public*/ JOptionPane(QVariant message, QWidget *parent = 0);
 /*public*/ JOptionPane(QVariant message, int messageType, QWidget *parent = 0);
 /*public*/ JOptionPane(QVariant message, int messageType, int optionType, QWidget* parent = 0);
 /*public*/ JOptionPane(QVariant message, int messageType, int optionType,                                                                                                                        QIcon icon, QWidget* parent = 0);
 /*public*/ JOptionPane(QVariant message, int messageType, int optionType,
                    QIcon icon, QList<QVariant> options, QWidget* parent= 0);
 /*public*/ JOptionPane(QVariant message, int messageType, int optionType,  QIcon icon, QList<QVariant> options, QVariant initialValue, QWidget* parent = 0);

 /*public*/ static QString showInputDialog(QVariant message);
 /*public*/ static QString showInputDialog(QVariant message, QVariant initialSelectionValue);
 /*public*/ static QString showInputDialog(QWidget* parentComponent,
     QVariant message); //throws HeadlessException
 /*public*/ static QString showInputDialog(QWidget* parentComponent, QVariant message,
                                      QVariant initialSelectionValue);
 /*public*/ static QString showInputDialog(QWidget* parentComponent,
     QVariant message, QString title, int messageType);
 /*public*/ static QVariant showInputDialog(QWidget* parentComponent,
     QVariant message, QString title, int messageType, QIcon icon,
     QList<QVariant> selectionValues, QVariant initialSelectionValue);
     //throws HeadlessException
 /*public*/ static int showOptionDialog(QWidget* parentComponent,
     QVariant message, QString title, int optionType, int messageType,
     QIcon icon = QIcon(), QList<QVariant> options= QList<QVariant>(), QVariant initialValue=QVariant());
     //throws HeadlessException
 /*public*/ static void showMessageDialog(QWidget* parentComponent,
     QVariant message); //throws HeadlessException
 /*public*/ static void showMessageDialog(QWidget* parentComponent,
     QVariant message, QString title, int messageType);
 /*public*/ static void showMessageDialog(QWidget* parentComponent,
     QVariant message, QString title, int messageType, QIcon icon);
 /*public*/ static int showInternalOptionDialog(Component* parentComponent,
                                    QVariant message,
                                    QString title, int optionType,
                                    int messageType, QIcon icon,
                                    QVariantList options, QVariant initialValue);


 /*public*/ void setMessage(QVariant newMessage);
 /*public*/ QVariant getMessage();
 /*public*/ void setIcon(QIcon newIcon);
 /*public*/ QIcon getIcon();
 /*public*/ void setValue(QVariant newValue);
 /*public*/ QVariant getValue();
 /*public*/ void setOptions(QList<QVariant> newOptions);
 /*public*/ QList<QVariant> getOptions();
 /*public*/ void setInitialValue(QVariant newInitialValue);
 /*public*/ QVariant getInitialValue();
 /*public*/ void setMessageType(int newType);
 /*public*/ int getMessageType();
 /*public*/ void setOptionType(int newType);
 /*public*/ int getOptionType();
 /*public*/ void setSelectionValues(QList<QVariant> newValues);
 /*public*/ QList<QVariant> getSelectionValues();
 /*public*/ void setInitialSelectionValue(QVariant newValue);
 /*public*/ QVariant getInitialSelectionValue();
 /*public*/ void setInputValue(QVariant newValue);
 /*public*/ QVariant getInputValue();
 /*public*/ int getMaxCharactersPerLineCount();
 /*public*/ void setWantsInput(bool newValue);
 /*public*/ bool getWantsInput();
 /*public*/ void selectInitialValue();
 /*public*/ static int showConfirmDialog(QWidget* parentComponent,
     QVariant message) throw (HeadlessException);
 /*public*/ static int showConfirmDialog(QWidget* parentComponent,
     QVariant message, QString title, int optionType)
     throw (HeadlessException);
 /*public*/ static int showConfirmDialog(QWidget* parentComponent,
     QVariant message, QString title, int optionType, int messageType)
     throw (HeadlessException);
 /*public*/ static int showConfirmDialog(QWidget* parentComponent,
     QVariant message, QString title, int optionType,
     int messageType, QIcon icon) throw (HeadlessException);
 static QWidget* getWindowForComponent(QWidget* parentComponent) throw (HeadlessException);
 /*public*/ JDialog* createDialog(QWidget* parentComponent, QString title);
 /*public*/ JDialog* createDialog(QString title);
 /*public*/ void setValidator(QValidator* val);

 signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* event);
 void handleTextInput();
 void handleOk();
 void handleCancel();
 void handleYes();
 void handleNo();
 void handleOptionButton(int);

private:
 /*private*/ static /*final*/ QString uiClassID;// = "OptionPaneUI";
 /** Icon used in pane. */
 /*transient*/ /*protected*/ QIcon                  icon;
 /** Message to display. */
 /*transient*/ /*protected*/ QVariant                message;
 /** Options to display to the user. */
 /*transient*/ /*protected*/ QList<QVariant>              options;
 /** Value that should be initially selected in <code>options</code>. */
 /*transient*/ /*protected*/ QVariant                initialValue;
 /** Message type. */
 /*private*/ static int styleFromMessageType(int messageType);
 /*private*/ JDialog* createDialog(QWidget* parentComponent, QString title,
         int style, int optionType =0);
 void common(QVariant message, int messageType = 0, int optionType = DEFAULT_OPTION,
             QIcon icon = QIcon(), QList<QVariant> options = QList<QVariant>(), QVariant initialValue = QVariant());
 /*private*/ void initDialog(/*final*/ JDialog* dialog, int style, QWidget* parentComponent);
 PropertyChangeSupport* changeSupport;
 QWidget* layoutPane(JDialog* dialog);
 JTextField* f;
 QPushButton* btnOk;
 QPushButton* btnCancel;
 JDialog* _dialog;
 QPushButton* btnYes;
 QPushButton* btnNo;

private slots:

protected:
 /*protected*/ int                   messageType;

 /**
  * Option type, one of <code>DEFAULT_OPTION</code>,
  * <code>YES_NO_OPTION</code>,
  * <code>YES_NO_CANCEL_OPTION</code> or
  * <code>OK_CANCEL_OPTION</code>.
  */
 /*protected*/ int                   optionType = 0;
 /** Currently selected value, will be a valid option, or
  * <code>UNINITIALIZED_VALUE</code> or <code>NULL</code>. */
 /*transient*/ /*protected*/ QVariant                value;
 /** Array of values the user can choose from. Look and feel will
  * provide the UI component to choose this from. */
 /*protected*/ /*transient*/ QList<QVariant>              selectionValues;
 /** Value the user has input. */
 /*protected*/ /*transient*/ QVariant                inputValue;
 /** Initial value to select in <code>selectionValues</code>. */
 /*protected*/ /*transient*/ QVariant                initialSelectionValue;
 /** If true, a UI widget will be provided to the user to get input. */
 /*protected*/ bool                         wantsInput;
 /*protected*/ void firePropertyChange(QString propertyName,
                                   QVariant oldValue, QVariant newValue);

};

#endif // JOPTIONPANE_H
