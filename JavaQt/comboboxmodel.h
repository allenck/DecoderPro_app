#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H
#include "listmodel.h"
#include <QObject>

//template <class E>
class ComboBoxModel //: public ListModel
{
    /**
       * Set the selected item. The implementation of this  method should notify
       * all registered <code>ListDataListener</code>s that the contents
       * have changed.
       *
       * @param anItem the list object to select or <code>null</code>
       *        to clear the selection
       */
  virtual void setSelectedItem(QString anItem) {}

      /**
       * Returns the selected item
       * @return The selected item or <code>null</code> if there is no selection
       */
  virtual QString getSelectedItem() = 0;
  virtual QObject* self() = 0;
};
Q_DECLARE_INTERFACE(ComboBoxModel, "ComboBoxModel")
#endif // COMBOBOXMODEL_H
