#ifndef COMBORADIOBUTTONS_H
#define COMBORADIOBUTTONS_H

#include <QWidget>
#include <QButtonGroup>
#include <QComboBox>
#include "propertychangeevent.h"
#include "actionevent.h"
#include <QRadioButton>
#include "enumvariablevalue.h"
#include <QVBoxLayout>
#include <QSignalMapper>

class EnumVariableValue;
class ActionListener;
class PropertyChangeListener;
class VariableValue;
class LIBPR3SHARED_EXPORT ComboRadioButtons : public QWidget
{
    Q_OBJECT
public:
 //explicit ComboRadioButtons(QWidget *parent = 0);
 ComboRadioButtons(QComboBox* box, EnumVariableValue* var, QWidget *parent = 0);
 virtual void addToPanel(QRadioButton* b, int i);
 void thisActionPerformed(JActionEvent* /*e*/);
 /*public*/ void setToolTipText(QString t);
 /*public*/ void dispose();
 QColor getBackground(QRadioButton* box);
 void setBackground(QRadioButton* b, QColor c);

signals:
 void valueChanged(VariableValue*);

public slots:
 /*public*/ void actionPerformed(int i);
 void on_valueChanged(EnumVariableValue*);
 void originalActionPerformed(JActionEvent* e = 0) ;
 void originalPropertyChanged(PropertyChangeEvent* e = 0);
 void propertyChange(PropertyChangeEvent* e);

private:
 QButtonGroup* g;// = new QButtonGroup();
 void init();
 QVector<QRadioButton*>* b1;
 /*transient*/ QVector<ActionListener*>* l1;
 /*transient*/ ActionListener* l2;
 /*transient*/ PropertyChangeListener* p1;

 /*transient*/ VariableValue* _var;// = null;
 /*transient*/ QComboBox* _box;// = null;
 /*transient*/ QComboBox* _value;// = null;
 QVector<QRadioButton*>* v;// = new Vector<JRadioButton>();
 Logger* log;
 QVBoxLayout* vLayout;
 QSignalMapper* mapper;
protected:
 /*protected*/ void setColor();
 friend class ComboOnRadioButton;
 friend class ComboOffRadioButton;
};

#endif // COMBORADIOBUTTONS_H
