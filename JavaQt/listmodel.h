#ifndef LISTMODEL_H
#define LISTMODEL_H
#include <QObject>
#include <QAbstractItemModel>

class ListDataListener;
//template <class E>
class ListModel/*<E>*/ : public QAbstractListModel
{
public:
    /**
       * Returns the length of the list.
       * @return the length of the list
       */
      virtual int getSize() const {return 0;}

      /**
       * Returns the value at the specified index.
       * @param index the requested index
       * @return the value at <code>index</code>
       */
//    template <class E>
      virtual QVariant getElementAt(int /*index*/) {return QVariant();}
      virtual QVariant get(int /*index*/) {return QVariant();}
      virtual void set(int /*index*/, QVariant /*value*/) {}

      /**
       * Adds a listener to the list that's notified each time a change
       * to the data model occurs.
       * @param l the <code>ListDataListener</code> to be added
       */
      virtual void addListDataListener(ListDataListener* l) = 0;

      /**
       * Removes a listener from the list that's notified each time a
       * change to the data model occurs.
       * @param l the <code>ListDataListener</code> to be removed
       */
      virtual void removeListDataListener(ListDataListener* l)= 0;
};
#endif // LISTMODEL_H
