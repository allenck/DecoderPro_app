#include "defaultcomboboxmodel.h"

//DefaultComboBoxModel::DefaultComboBoxModel(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * The default model for combo boxes.
 *
 * @param <E> the type of the elements of this model
 *
 * @author Arnaud Weber
 * @author Tom Santos
 */

// /*public*/ class DefaultComboBoxModel<E> extends AbstractListModel<E> implements MutableComboBoxModel<E>, Serializable {

/**
 * Constructs an empty DefaultComboBoxModel object.
 */
//template <class E>
///*public*/ DefaultComboBoxModel<E>::DefaultComboBoxModel(QObject *parent) : AbstractListModel(parent)
//{
//    objects = new QVector<E>();
//}

/**
 * Constructs a DefaultComboBoxModel object initialized with
 * an array of objects.
 *
 * @param items  an array of Object objects
 */
template <class E>
/*public*/ DefaultComboBoxModel<E>::DefaultComboBoxModel(/*final*/ QList<E> items, QObject *parent)
    : AbstractListModel(parent)
{
    objects = new QVector<E>();
    objects.reserve(items.size());

    int i,c;
    for ( i=0,c=items.length;i<c;i++ )
        objects.append(items.at(i));

    if ( getSize() > 0 ) {
        selectedObject = objects.at( 0 );
    }
}

/**
 * Constructs a DefaultComboBoxModel object initialized with
 * a vector.
 *
 * @param v  a Vector object ...
 */
template <class E>
/*public*/ DefaultComboBoxModel<E>::DefaultComboBoxModel(QVector<E> v, QObject *parent)
    : AbstractListModel(parent)
{
 objects = v;

 if ( getSize() > 0 ) {
        selectedObject = v.at( 0 );
    }
}

// implements javax.swing.ComboBoxModel
/**
 * Set the value of the selected item. The selected item may be NULL.
 * <p>
 * @param anObject The combo box value or NULL for no selection.
 */
template <class E>
/*public*/ void DefaultComboBoxModel<E>::setSelectedItem(QObject* anObject) {
    if ((selectedObject != NULL && selectedObject!=( anObject )) ||
        selectedObject == NULL && anObject != NULL) {
        selectedObject = anObject;
        fireContentsChanged(this, -1, -1);
    }
}

// implements javax.swing.ComboBoxModel
template <class E>
/*public*/ QObject* DefaultComboBoxModel<E>::getSelectedItem() {
    return selectedObject;
}

// implements javax.swing.ListModel
template <class E>
/*public*/ int DefaultComboBoxModel<E>::getSize() {
    return objects.size();
}

// implements javax.swing.ListModel
//template <class E>
///*public*/ QObject* DefaultComboBoxModel<E>::getElementAt(int index) {
//    if ( index >= 0 && index < objects.size() )
//        return objects.at(index);
//    else
//        return NULL;
//}

/**
 * Returns the index-position of the specified object in the list.
 *
 * @param anObject
 * @return an int representing the index position, where 0 is
 *         the first position
 */
template <class E>
/*public*/ int DefaultComboBoxModel<E>::getIndexOf(QObject* anObject) {
    return objects.indexOf(anObject);
}

// implements javax.swing.MutableComboBoxModel
template <class E>
/*public*/ void DefaultComboBoxModel<E>::addElement(E anObject) {
    objects.addElement(anObject);
    fireIntervalAdded(this,objects.size()-1, objects.size()-1);
    if ( objects.size() == 1 && selectedObject == NULL && anObject != NULL ) {
        setSelectedItem( anObject );
    }
}

// implements javax.swing.MutableComboBoxModel
template <class E>
/*public*/ void DefaultComboBoxModel<E>::insertElementAt(E anObject,int index) {
    objects.insertElementAt(anObject,index);
    fireIntervalAdded(this, index, index);
}

// implements javax.swing.MutableComboBoxModel
template <class E>
/*public*/ void DefaultComboBoxModel<E>::removeElementAt(int index) {
    if ( getElementAt( index ) == selectedObject ) {
        if ( index == 0 ) {
            setSelectedItem( getSize() == 1 ? NULL : getElementAt( index + 1 ) );
        }
        else {
            setSelectedItem( getElementAt( index - 1 ) );
        }
    }

    objects.removeElementAt(index);

    fireIntervalRemoved(this, index, index);
}

// implements javax.swing.MutableComboBoxModel
template <class E>
/*public*/ void DefaultComboBoxModel<E>::removeElement(QObject* anObject) {
    int index = objects.indexOf(anObject);
    if ( index != -1 ) {
        removeElementAt(index);
    }
}

/**
 * Empties the list.
 */
template <class E>
/*public*/ void DefaultComboBoxModel<E>::removeAllElements() {
    if ( objects.size() > 0 ) {
        int firstIndex = 0;
        int lastIndex = objects.size() - 1;
        objects.removeAllElements();
        selectedObject = NULL;
        fireIntervalRemoved(this, firstIndex, lastIndex);
    } else {
        selectedObject = NULL;
    }
}
