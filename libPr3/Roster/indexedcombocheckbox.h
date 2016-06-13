#ifndef INDEXEDCOMBOCHECKBOX_H
#define INDEXEDCOMBOCHECKBOX_H

#include <QCheckBox>
#include <QComboBox>
#include "indexedenumvariablevalue.h"
#include "actionevent.h"
#include "actionlistener.h"

class IndexedEnumVariableValue;
class LIBPR3SHARED_EXPORT IndexedComboCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    //explicit IndexedComboCheckBox(QWidget *parent = 0);
    IndexedComboCheckBox(QComboBox* box, IndexedEnumVariableValue* var, QWidget *parent = 0);
//    void thisActionPerformed(ActionEvent* e);
//    void originalActionPerformed(ActionEvent* e) ;
    void originalPropertyChanged(PropertyChangeEvent* e);
    /*public*/ void dispose();
    QColor getBackground();
    void setBackground(QColor c);


signals:
    void propertyChange(PropertyChangeEvent*);

public slots:
    void thisActionPerformed(ActionEvent* e = 0);
    void originalActionPerformed(ActionEvent* e = 0) ;

private:
    /*transient*/ ActionListener* l1;
    /*transient*/ ActionListener* l2;
    /*transient*/ PropertyChangeListener* p1;

    IndexedEnumVariableValue* _var;// = null;
    QComboBox* _box;// = null;


};

#endif // INDEXEDCOMBOCHECKBOX_H
