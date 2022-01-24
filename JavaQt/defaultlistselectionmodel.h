#ifndef DEFAULTLISTSELECTIONMODEL_H
#define DEFAULTLISTSELECTIONMODEL_H
#include "listselectionmodel.h"
#include "limits.h"
#include "bitset.h"
#include "exceptions.h"
#include "javaqt_global.h"
#include "abstracttablemodel.h"
#include <QVector>
#include "listselectionlistener.h"

class ListSelectionEvent;
class JAVAQTSHARED_EXPORT DefaultListSelectionModel : public QItemSelectionModel,  public ListSelectionModel
{
 Q_OBJECT
 Q_INTERFACES(ListSelectionModel)
public:
    explicit DefaultListSelectionModel(QObject *parent = 0);
    /*public*/ int getMinSelectionIndex();
    /*public*/ int getMaxSelectionIndex();
    /*public*/ bool getValueIsAdjusting() ;
    /*public*/ int getSelectionMode() ;
    /*public*/ void setSelectionMode(int selectionMode);
    /*public*/ bool isSelectedIndex(int index);
    /*public*/ bool isSelectionEmpty();
    /*public*/ void addListSelectionListener(ListSelectionListener* l);
    /*public*/ void removeListSelectionListener(ListSelectionListener* l);
    /*public*/ QVector<ListSelectionListener*> getListSelectionListeners();
//    /*public*/ <T extends EventListener> T[] getListeners(Class<T> listenerType);
    /*public*/ void setLeadAnchorNotificationEnabled(bool flag);
    /*public*/ bool isLeadAnchorNotificationEnabled();
    /*public*/ void clearSelection() ;
    /*public*/ void setSelectionInterval(int index0, int index1);
    /*public*/ void addSelectionInterval(int index0, int index1);
    /*public*/ void removeSelectionInterval(int index0, int index1);
    /*public*/ void insertIndexInterval(int index, int length, bool before);
    /*public*/ void removeIndexInterval(int index0, int index1);
    /*public*/ void setValueIsAdjusting(bool isAdjusting) ;
    /*public*/ QString toString();
    /*public*/ QObject* clone() /*throw (CloneNotSupportedException)*/;
    /*public*/ int getAnchorSelectionIndex();
    /*public*/ int getLeadSelectionIndex();
    /*public*/ void setAnchorSelectionIndex(int anchorIndex);
    /*public*/ void moveLeadSelectionIndex(int leadIndex);
    /*public*/ void setLeadSelectionIndex(int leadIndex);
//    /*public*/ QItemSelectionModel* getItemSelectionModel();
    ///*public*/ void setItemSelectionModel(QItemSelectionModel* itemSelectionModel);

signals:
    void listSelectionChanged(ListSelectionEvent*);

public slots:
    void onSelectionChanged(QItemSelection selected, QItemSelection deselected);

private:
    /*private*/ static const int MIN = -1;
    /*private*/ static const int MAX = INT_MAX;
    /*private*/ int selectionMode;// = MULTIPLE_INTERVAL_SELECTION;
    /*private*/ int minIndex;// = MAX;
    /*private*/ int maxIndex;// = MIN;
    /*private*/ int anchorIndex;// = -1;
    /*private*/ int leadIndex;// = -1;
    /*private*/ int firstAdjustedIndex;// = MAX;
    /*private*/ int lastAdjustedIndex;// = MIN;
    /*private*/ bool isAdjusting;// = false;

    /*private*/ int firstChangedIndex;// = MAX;
    /*private*/ int lastChangedIndex;// = MIN;

    /*private*/ BitSet* value;// = new BitSet(32);
    /*private*/ void fireValueChanged();
    /*private*/ void markAsDirty(int r);
    /*private*/ void set(int r) ;
    /*private*/ void clear(int r);
    /*private*/ bool contains(int a, int b, int i);
    /*private*/ void removeSelectionIntervalImpl(int index0, int index1,
                                             bool changeLeadAnchor);
    /*private*/ void setState(int index, bool state);
    /*private*/ void updateLeadAnchorIndices(int anchorIndex, int leadIndex);
    /*private*/ void changeSelection(int clearMin, int clearMax,
                                 int setMin, int setMax, bool clearFirst);
    /*private*/ void changeSelection(int clearMin, int clearMax, int setMin, int setMax);
//    QItemSelectionModel* itemSelectionModel = nullptr;
    QVector<ListSelectionListener*> listenerList;
    /*private*/ QItemSelection mapSelections(QItemSelection selections);

protected:
//    /*protected*/ EventListenerList listenerList = new EventListenerList();

    /*protected*/ bool leadAnchorNotificationEnabled;// = true;
    /*protected*/ void fireValueChanged(bool isAdjusting);
    /*protected*/ void fireValueChanged(int firstIndex, int lastIndex);
    /*protected*/ void fireValueChanged(int firstIndex, int lastIndex, bool isAdjusting);

};

#endif // DEFAULTLISTSELECTIONMODEL_H
