#ifndef JSPINNER_H
#define JSPINNER_H
#include <QSpinBox>
#include "jcomponent.h"
#include "spinnermodel.h"
#include "focuslistener.h"

class ChangeEvent;
class JSpinner : public QSpinBox, public JComponent
{
 Q_OBJECT
 Q_INTERFACES(JComponent)
public:
  class NumberEditor
  {
    JSpinner* val;
    QString s;
   public:
    NumberEditor(JSpinner* val, QString s) {this->val = val; this->s = s;}
  };
 JSpinner(SpinnerModel* model, QWidget* parent = nullptr);
 JSpinner(QWidget* parent = nullptr);
 SpinnerModel* getModel();
 void setModel(SpinnerModel* model);
 bool isOpaque()override;
 /*public*/ QColor getForeground()override;
 QColor getBackground()override;
 void setBackground(QColor)override;
 void setOpaque(bool)override;
 QFont getFont()override;
 /*public*/ void setFont(QFont)override;
 /*public*/ int getValue() {return value();}

 /*public*/ QObject* jself() {return (QObject*)this;}
 /*public*/ void addChangeListener(ChangeListener*);
 /*public*/ void removeChangeListener(ChangeListener*);
 /*public*/ void addFocusListener(FocusListener *l);
 /*public*/ void removeFocusListener(FocusListener* l);
// /*public*/ void setVisible(bool b);
 /*public*/ void setBorder(Border* border) override {this->_border = border;}
 /*public*/ Border* getBorder() override{return _border;}
 /*public*/ void setEnabled(bool b) override;
 void setTickInterval(int i);
 void setTickPosition(int i);
 void setEditor(NumberEditor* editor) {this->editor = editor;}
 void commitEdit() {}

public slots:
 void onValueChanged(int);

signals:
 void stateChanged(ChangeEvent*);
 /*public*/ void focusGained(FocusEvent* fe);
 /*public*/ void focusLost(FocusEvent* fe);

private:
 SpinnerModel* model = nullptr;
 bool _opaque = false;
 QVector<ChangeListener*> listeners;
 Border* _border = nullptr;
 /*private*/ void focusInEvent(QFocusEvent* e)override;
 /*private*/ void focusOutEvent(QFocusEvent* e)override;
 NumberEditor* editor = nullptr;
};

#endif // JSPINNER_H
