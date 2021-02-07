#ifndef DEFAULTCOMBOBOXMODEL_H
#define DEFAULTCOMBOBOXMODEL_H

#include <QObject>
#include <QVector>
#include "abstractlistmodel.h"
#include "javaqt_global.h"
#include "comboboxmodel.h"

//template <class E>
class JAVAQTSHARED_EXPORT DefaultComboBoxModel : public AbstractListModel, public ComboBoxModel
{
    //Q_OBJECT
  Q_INTERFACES(ComboBoxModel)
public:
    //explicit DefaultComboBoxModel(QObject *parent = 0);
    /**
     * Constructs an empty DefaultComboBoxModel object.
     */
//    /*public*/ DefaultComboBoxModel<E>(QObject *parent = 0);
    /**
     * Constructs a DefaultComboBoxModel object initialized with
     * an array of objects.
     *
     * @param items  an array of Object objects
     */
    /*public*/ DefaultComboBoxModel(/*final*/ QList<QString> items,QObject *parent = 0);
    /*public*/ DefaultComboBoxModel(QVector<QString> v, QObject *parent = 0);
    /*public*/ void setSelectedItem(QString anObject);
    /*public*/ QString getSelectedItem();
    /*public*/ int getSize();
//    /*public*/ QObject* getElementAt(int index);
    /*public*/ int getIndexOf(QString anObject) ;
    /*public*/ void addElement(QString anObject) {
        objects.append(anObject);
        fireIntervalAdded(this,objects.size()-1, objects.size()-1);
        if ( objects.size() == 1 && selectedObject == NULL && anObject != NULL ) {
//            setSelectedItem( anObject );
        }
    }
    /*public*/ void insertElementAt(QString anObject,int index);
    /*public*/ void removeElementAt(int index);
    /*public*/ void removeElement(QString anObject);
    /**
     * Empties the list.
     */
    /*public*/ void removeAllElements();
  /*public*/ int rowCount(const QModelIndex &parent) const {return 0;}
  /*public*/ QVariant data(const QModelIndex &index, int role) const {return QVariant();}
  QObject* self() {return (QObject*)this;}

signals:

public slots:
private:
    QVector<QString> objects;
    QString selectedObject;


};

#endif // DEFAULTCOMBOBOXMODEL_H
