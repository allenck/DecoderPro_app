#ifndef JSPINNER_H
#define JSPINNER_H
#include <QSpinBox>
#include "jcomponent.h"
#include "spinnermodel.h"

class ChangeEvent;
class JSpinner : public QSpinBox, public JComponent
{
 Q_OBJECT
 Q_INTERFACES(JComponent)
public:
 JSpinner(SpinnerModel* model, QWidget* parent = nullptr);
 JSpinner(QWidget* parent = nullptr);
 SpinnerModel* getModel();
 void setModel(SpinnerModel* model);
 bool isOpaque();
 QColor getBackground();
 void setBackground(QColor);
 void setOpaque(bool);
 QFont getFont();
 /*public*/ void setFont(QFont);
 /*public*/ int getValue() {return value();}

 /*public*/ QObject* jself() {return (QObject*)this;}
 /*public*/ void addChangeListener(ChangeListener*);
 /*public*/ void removeChangeListener(ChangeListener*);
// /*public*/ void setVisible(bool b);
 /*public*/ void setBorder(Border* border) override {this->_border = border;}
 /*public*/ Border* getBorder() {return _border;}

public slots:
 void onValueChanged(int);

signals:
 void stateChanged(ChangeEvent*);

private:
 SpinnerModel* model = nullptr;
 bool _opaque = false;
 QVector<ChangeListener*> listeners;
 Border* _border = nullptr;

};

#endif // JSPINNER_H
