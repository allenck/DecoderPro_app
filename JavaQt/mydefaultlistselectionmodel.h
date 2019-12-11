#ifndef MYDEFAULTLISTSELECTIONMODEL_H
#define MYDEFAULTLISTSELECTIONMODEL_H
#include <QItemSelectionModel>
#include <QAbstractItemView>

class MyDefaultListSelectionModel : public QItemSelectionModel
{
public:
 MyDefaultListSelectionModel(QObject* parent = 0);
 enum SELECTIONS
 {
 /**
  * A value for the selectionMode property: select one list index
  * at a time.
  *
  * @see #setSelectionMode
  */
  SINGLE_SELECTION = QAbstractItemView::SingleSelection,

 /**
  * A value for the selectionMode property: select one contiguous
  * range of indices at a time.
  *
  * @see #setSelectionMode
  */
  SINGLE_INTERVAL_SELECTION = QAbstractItemView::MultiSelection,

 /**
  * A value for the selectionMode property: select one or more
  * contiguous ranges of indices at a time.
  *
  * @see #setSelectionMode
  */
  MULTIPLE_INTERVAL_SELECTION = QAbstractItemView::ContiguousSelection,

  /**
   * When the user selects an item in the usual way, the selection is cleared
   * and the new item selected. However, if the user presses the Ctrl key
   * when clicking on an item, the clicked item gets toggled
   * and all other items are left untouched. If the user presses the Shift key
   * while clicking on an item, all items between the current item and the
   * clicked item are selected or unselected, depending on the state of the
   * clicked item. Multiple items can be selected by dragging the mouse over them.
   */
  EXTENDED_SELECTION = QAbstractItemView::ExtendedSelection
 };
 Q_ENUM(SELECTIONS)
};

#endif // MYDEFAULTLISTSELECTIONMODEL_H
