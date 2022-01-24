#ifndef JFRAMEOPERATOR_H
#define JFRAMEOPERATOR_H

#include "jdialog.h"
#include <QObject>
#include <QRadioButton>
#include <QLabel>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include "jmrijframe.h"
#include "jtogglebutton.h"
#include <QCheckBox>
#include "jslider.h"
#include "jspinner.h"
#include "jtextfield.h"
#include "functionbutton.h"
#include "jcombobox.h"
#include "jcheckbox.h"
#include "jtabbedpane.h"
#include "jtable.h"

class JDialogOperator;
class NameComponentChooser;
class JmriJFrame;
class JFrameOperator : public QObject
{
 Q_OBJECT
public:
 explicit JFrameOperator(QObject *parent = nullptr);
 JFrameOperator(QWidget *widget, QObject *parent = nullptr);
 JFrameOperator(QString chooser);
 JmriJFrame* getFrame();
 void requestClose() { }
 void waitClosed();
 static JmriJFrame* waitJFrame(QString, bool, bool);
signals:

public slots:

private:
 JmriJFrame* _frame = nullptr;
};

class JRadioButtonOperator : public QObject
{
 Q_OBJECT
 QRadioButton* button = nullptr;
 QString text;
 QObject* parent;
public:
  JRadioButtonOperator(QObject*parent, QString text);
  void push() {if(button) button->click();}
  void doClick() {if(button) button->click();}
private:
  QWidget* parentWidget();
};

class JButtonOperator : public QObject
{
 Q_OBJECT
 QPushButton* button = nullptr;
 QString text;
 QObject* parent = nullptr;
 QList<QPushButton*> list;
public:
  JButtonOperator(QObject*parent, QString text);
  JButtonOperator(JDialogOperator*, NameComponentChooser*);
  void push();
  void pushNoBlock();
  void doClick();
  bool isEnabled();
private:
  QWidget* parentWidget();
  virtual bool checkComponent(QWidget* comp);
  virtual QString getDescription();
  /*private*/ void findButton();

};

class JCheckBoxOperator : public QObject
{
 Q_OBJECT
 QCheckBox* checkBox = nullptr;
 QString text;
 QObject* parent;

public:
  JCheckBoxOperator(QObject*parent, QString text);
  void push() {if(checkBox) checkBox->click();}
  void doClick() {if(checkBox) checkBox->click();}

  bool isEnabled();
private:
  QWidget* parentWidget();
};

class JToggleButtonOperator : public QObject
{
 Q_OBJECT
 JToggleButton* button = nullptr;
 QString text;
 QObject* parent;

public:
  JToggleButtonOperator(QObject* parent, QString text);
  JToggleButtonOperator(QObject* parent);
  JToggleButtonOperator(FunctionButton* fb);
  void push() {if(button) button->click();}
  void doClick() {if(button) button->click();}
  void clickForPopup() {}
  bool isEnabled();
private:
  QWidget* parentWidget();
};


class JLabelOperator : public QObject
{
 Q_OBJECT
 QLabel* label;
 QObject* parent;
 QString text;
public:
 JLabelOperator(QObject*parent, QString text);
 QWidget* getLabelFor();
private:
 QWidget* parentWidget();

};

class JMenuBarOperator : public QObject
{
 Q_OBJECT
 QObject* parent;
 QMenuBar* menuBar;
public:
 JMenuBarOperator(QObject* parent);

private:
 JmriJFrame* getFrame();
 friend class JMenuOperator;
};

class JMenuOperator : public QObject
{
 Q_OBJECT
 QMenu* menu = nullptr;
 QAction* action = nullptr;
public:
 JMenuOperator(QMenu* parent, QString text);
 JMenuOperator(JMenuBarOperator* jmbo, QString text);
 void push();
 QMenu* getMenu();
};

class JPopupMenuOperator : public QObject
{
 Q_OBJECT
 QMenu* menu;
public:
 JPopupMenuOperator();
 JPopupMenuOperator(QMenu* parent, QString text);
 void push();
 void pushMenuNoBlock(QString text);
};

class JMenuItemOperator : public QObject
{
 Q_OBJECT
 QAction* action = nullptr;
public:
 JMenuItemOperator(QMenu* parent, QString text);
 JMenuItemOperator(JFrameOperator* jmbo, QString text);
 void push();
};

class JDialogOperator : public QObject
{
 Q_OBJECT
 QObject* parent = nullptr;
 QString text;
 int number = -1;
 JFrameOperator* frameOperator = nullptr;
 JDialog* dialog = nullptr;
public:
 JDialogOperator( QString text);
 JDialogOperator(JFrameOperator *frame, int number);
 JDialog* getDialog() { return dialog;}
 JDialogOperator(JFrameOperator *frame, QString text);
};

class JSliderOperator : public QObject
{
 Q_OBJECT
 QObject* parent;
 QString text;
 JSlider* slider;
public:
 JSliderOperator(QObject* parent);
 JSliderOperator(QObject* parent, QString text);
 int getValue();
 void setValue(int i);
 void scrollToValue(int i);
 void scrollToMaximum();
 void scrollToMinimum();
private:
 QWidget* parentWidget();

};

class JSpinnerOperator : public QObject
{
 Q_OBJECT
 QObject* parent;
 QString text;
 JSpinner* spinner;
public:
 JSpinnerOperator(QObject* parent);
 JSpinnerOperator(QObject* parent, QString text);
 int getValue();
 void setValue(int i);
 void scrollToValue(int i);
 void scrollToMaximum();
 void scrollToMinimum();
};

class JTextFieldOperator : public QObject
{
 QObject* parent;
 QString name;
 JTextField* textField;
public:
 JTextFieldOperator(QObject* parent, QString name);
 JTextFieldOperator(QObject *);
 void typeText(QString);
 void setText(QString);
 void clickMouse();
};

class JInternalFrameOperator : public QObject
{
 Q_OBJECT
 QObject* parent= nullptr;
 QString name;
 QWidget* _result;
public:
 JInternalFrameOperator(QObject* parent, QString name );
 QWidget* result() {return _result;}
 void clickForPopup();
};

class JComboBoxOperator : public QObject
{
  Q_OBJECT
  QObject* parent= nullptr;
  JComboBox* comboBox = nullptr;
 public:
  JComboBoxOperator(QObject* parent, int index );
  void setSelectedItem(QString s);
  void setSelectedIndex(int);
};

class JTabbedPaneOperator :public QObject
{
  Q_OBJECT
  QObject* parent= nullptr;
  JTabbedPane* jTabbedPane = nullptr;
 public:
  JTabbedPaneOperator(QObject* parent);
  QWidget* selectPage(QString);
};

class JTableOperator :public QObject
{
  Q_OBJECT
  QObject* parent= nullptr;
  JTable* jTable = nullptr;
 public:
  JTableOperator(QObject *parent);
  void clickOnCell(int r, int col);
};

#endif // JFRAMEOPERATOR_H
