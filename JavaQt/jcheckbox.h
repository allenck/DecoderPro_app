#ifndef JCHECKBOX_H
#define JCHECKBOX_H
#include <QCheckBox>
#include "focusevent.h"
#include "focuslistener.h"
#include "changelistener.h"
#include "vptr.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT JCheckBox : public QCheckBox
{
 Q_OBJECT
public:
 JCheckBox(QWidget *parent = nullptr);
 JCheckBox(QString text, QWidget* parent = nullptr);

 /*public*/ void addChangeListener(ChangeListener* l);
 /*public*/ void removeChangeListener(ChangeListener* l);
 /*public*/ void addFocusListener(FocusListener* l);
 /*public*/ void removeFocusListener(FocusListener *l);
 virtual /*public*/ void setSelected(bool b) {setChecked(b);}
 virtual /*public*/ bool isSelected() {return isChecked();}
public slots:

signals:
 /*public*/ void focusGained(FocusEvent* fe);
 /*public*/ void focusLost(FocusEvent* fe);
 /*public*/ void stateChanged(ChangeEvent*);

private:
 /*private*/ void focusInEvent(QFocusEvent* e);
 /*private*/ void focusOutEvent(QFocusEvent* e);



};

#endif // JCHECKBOX_H
