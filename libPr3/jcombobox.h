#ifndef JCOMBOBOX_H
#define JCOMBOBOX_H

#include <QComboBox>
#include "comboboxmodel.h"

class PropertyChangeEvent;
template <class E, class F>
class JComboBox : public QComboBox
{
    Q_OBJECT
public:
    //explicit JComboBox(QWidget *parent = 0);
//    /*public*/ JComboBox(ComboBoxModel<F>* aModel, QWidget *parent = 0);
    /*public*/ JComboBox(QList<E>* items, QWidget *parent = 0);
    /*public*/ JComboBox(QVector<E>* items, QWidget *parent = 0);
//    /*public*/ void setModel(ComboBoxModel<E>* aModel);
//    /*public*/ ComboBoxModel<E>* getModel();

signals:
    void propertyChange(PropertyChangeEvent*);

public slots:
private:
    /*private*/ void init();
protected:
    /**
     * This protected field is implementation specific. Do not access directly
     * or override. Use the accessor methods instead.
     *
     * @see #getModel
     * @see #setModel
     */
//    /*protected*/ ComboBoxModel<E>*    dataModel;
    /**
     * This protected field is implementation specific. Do not access directly
     * or override.
     */
    /*protected*/ QObject* selectedItemReminder;// = NULL;

};

#endif // JCOMBOBOX_H
