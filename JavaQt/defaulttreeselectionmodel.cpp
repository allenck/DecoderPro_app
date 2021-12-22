#include "defaulttreeselectionmodel.h"
#include <QHash>
#include <propertychangesupport.h>
#include "bitset.h"
#include <rowmapper.h>
#include "eventlistenerlist.h"

//DefaultTreeSelectionModel::DefaultTreeSelectionModel()
//{

//}
/**
 * Default implementation of TreeSelectionModel.  Listeners are notified
 * whenever
 * the paths in the selection change, not the rows. In order
 * to be able to track row changes you may wish to become a listener
 * for expansion events on the tree and test for changes from there.
 * <p>resetRowSelection is called from any of the methods that update
 * the selected paths. If you subclass any of these methods to
 * filter what is allowed to be selected, be sure and message
 * <code>resetRowSelection</code> if you do not message super.
 *
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @see javax.swing.JTree
 *
 * @author Scott Violet
 */
//@SuppressWarnings("serial")
///*public*/ class DefaultTreeSelectionModel implements Cloneable, Serializable, TreeSelectionModel
//{
/*public*/ /*static*/ /*final*/ QString          DefaultTreeSelectionModel::SELECTION_MODE_PROPERTY = "selectionMode";


/**
 * Creates a new instance of DefaultTreeSelectionModel that is
 * empty, with a selection mode of DISCONTIGUOUS_TREE_SELECTION.
 */
/*public*/ DefaultTreeSelectionModel::DefaultTreeSelectionModel() {
//    listSelectionModel = new DefaultListSelectionModel();
    selectionMode = DISCONTIGUOUS_TREE_SELECTION;
    leadIndex = leadRow = -1;
    uniquePaths = new QHash<TreePath*, bool>();
    lastPaths = new QHash<TreePath*, bool>();
    tempPaths = QVector<TreePath*>(); //[1];
    tempPaths.append(nullptr);
    rowMapper = nullptr;
    selection = QVector<TreePath*>();
}
#if 0
/**
 * Sets the RowMapper instance. This instance is used to determine
 * the row for a particular TreePath.
 */
/*public*/ void setRowMapper(RowMapper newMapper) {
    rowMapper = newMapper;
    resetRowSelection();
}

/**
 * Returns the RowMapper instance that is able to map a TreePath to a
 * row.
 */
/*public*/ RowMapper getRowMapper() {
    return rowMapper;
}
#endif
/**
 * Sets the selection model, which must be one of SINGLE_TREE_SELECTION,
 * CONTIGUOUS_TREE_SELECTION or DISCONTIGUOUS_TREE_SELECTION. If mode
 * is not one of the defined value,
 * <code>DISCONTIGUOUS_TREE_SELECTION</code> is assumed.
 * <p>This may change the selection if the current selection is not valid
 * for the new mode. For example, if three TreePaths are
 * selected when the mode is changed to <code>SINGLE_TREE_SELECTION</code>,
 * only one TreePath will remain selected. It is up to the particular
 * implementation to decide what TreePath remains selected.
 * <p>
 * Setting the mode to something other than the defined types will
 * result in the mode becoming <code>DISCONTIGUOUS_TREE_SELECTION</code>.
 */
/*public*/ void DefaultTreeSelectionModel::setSelectionMode(int mode) {
    int            oldMode = selectionMode;

    selectionMode = mode;
    if(selectionMode != TreeSelectionModel::SINGLE_TREE_SELECTION &&
       selectionMode != TreeSelectionModel::CONTIGUOUS_TREE_SELECTION &&
       selectionMode != TreeSelectionModel::DISCONTIGUOUS_TREE_SELECTION)
        selectionMode = TreeSelectionModel::DISCONTIGUOUS_TREE_SELECTION;
    if(oldMode != selectionMode && changeSupport != nullptr)
        changeSupport->firePropertyChange(SELECTION_MODE_PROPERTY,
                                         (oldMode),
                                         (selectionMode));
}

/**
 * Returns the selection mode, one of <code>SINGLE_TREE_SELECTION</code>,
 * <code>DISCONTIGUOUS_TREE_SELECTION</code> or
 * <code>CONTIGUOUS_TREE_SELECTION</code>.
 */
/*public*/ int DefaultTreeSelectionModel::getSelectionMode() {
    return selectionMode;
}

/**
  * Sets the selection to path. If this represents a change, then
  * the TreeSelectionListeners are notified. If <code>path</code> is
  * NULL, this has the same effect as invoking <code>clearSelection</code>.
  *
  * @param path new path to select
  */
/*public*/ void DefaultTreeSelectionModel::setSelectionPath(TreePath* path) {
    if(path == nullptr)
        setSelectionPaths(QVector<TreePath*>());
    else {
        QVector<TreePath*>          newPaths = QVector<TreePath*>();

        newPaths.append( path);
        newPaths.append(nullptr);
        setSelectionPaths(newPaths);
    }
}

/**
 * Sets the selection. Whether the supplied paths are taken as the
 * new selection depends upon the selection mode. If the supplied
 * array is {@code NULL}, or empty, the selection is cleared. If
 * the selection mode is {@code SINGLE_TREE_SELECTION}, only the
 * first path in {@code pPaths} is used. If the selection
 * mode is {@code CONTIGUOUS_TREE_SELECTION} and the supplied paths
 * are not contiguous, then only the first path in {@code pPaths} is
 * used. If the selection mode is
 * {@code DISCONTIGUOUS_TREE_SELECTION}, then all paths are used.
 * <p>
 * All {@code NULL} paths in {@code pPaths} are ignored.
 * <p>
 * If this represents a change, all registered {@code
 * TreeSelectionListener}s are notified.
 * <p>
 * The lead path is set to the last unique path.
 * <p>
 * The paths returned from {@code getSelectionPaths} are in the same
 * order as those supplied to this method.
 *
 * @param pPaths the new selection
 */
/*public*/ void DefaultTreeSelectionModel::setSelectionPaths(QVector<TreePath*> pPaths) {
    int            newCount, newCounter, oldCount, oldCounter;
    Q_UNUSED(newCounter);
    Q_UNUSED(oldCounter);
    QVector<TreePath*>     paths = pPaths;

    if(paths.isEmpty())
        newCount = 0;
    else
        newCount = paths.length();
    if(selection.isEmpty())
        oldCount = 0;
    else
        oldCount = selection.length();
    if((newCount + oldCount) != 0) {
        if(selectionMode == TreeSelectionModel::SINGLE_TREE_SELECTION) {
            /* If single selection and more than one path, only allow
               first. */
            if(newCount > 1) {
                paths = QVector<TreePath*>();
                paths.append(pPaths.at(0));
                newCount = 1;
            }
        }
        else if(selectionMode ==
                TreeSelectionModel::CONTIGUOUS_TREE_SELECTION) {
            /* If contiguous selection and paths aren't contiguous,
               only select the first path item. */
            if(newCount > 0 && !arePathsContiguous(paths)) {
                paths =  QVector<TreePath*>();
                paths.append(pPaths.at(0));
                newCount = 1;
            }
        }

        TreePath*         beginLeadPath = leadPath;
        Q_UNUSED(beginLeadPath);
#if 0
        Vector<PathPlaceHolder> cPaths = new Vector<PathPlaceHolder>(newCount + oldCount);
        List<TreePath> newSelectionAsList =
                new ArrayList<TreePath>(newCount);

        lastPaths.clear();
        leadPath = NULL;
        /* Find the paths that are new. */
        for(newCounter = 0; newCounter < newCount; newCounter++) {
            TreePath path = paths[newCounter];
            if (path != NULL && lastPaths.get(path) == NULL) {
                lastPaths.put(path, Boolean.TRUE);
                if (uniquePaths.get(path) == NULL) {
                    cPaths.addElement(new PathPlaceHolder(path, true));
                }
                leadPath = path;
                newSelectionAsList.add(path);
            }
        }

        TreePath[] newSelection = newSelectionAsList.toArray(
                new TreePath[newSelectionAsList.size()]);

        /* Get the paths that were selected but no longer selected. */
        for(oldCounter = 0; oldCounter < oldCount; oldCounter++)
            if(selection[oldCounter] != NULL &&
                lastPaths.get(selection[oldCounter]) == NULL)
                cPaths.addElement(new PathPlaceHolder
                                  (selection[oldCounter], false));

        selection = newSelection;

        Hashtable<TreePath, Boolean>  tempHT = uniquePaths;

        uniquePaths = lastPaths;
        lastPaths = tempHT;
        lastPaths.clear();

        // No reason to do this now, but will still call it.
        insureUniqueness();

        updateLeadIndex();

        resetRowSelection();
        /* Notify of the change. */
        if(cPaths.size() > 0)
            notifyPathChange(cPaths, beginLeadPath);
#else
        selection = pPaths;
#endif
    }
}
#if 0
/**
  * Adds path to the current selection. If path is not currently
  * in the selection the TreeSelectionListeners are notified. This has
  * no effect if <code>path</code> is NULL.
  *
  * @param path the new path to add to the current selection
  */
/*public*/ void addSelectionPath(TreePath path) {
    if(path != NULL) {
        TreePath[]            toAdd = new TreePath[1];

        toAdd[0] = path;
        addSelectionPaths(toAdd);
    }
}

/**
  * Adds paths to the current selection. If any of the paths in
  * paths are not currently in the selection the TreeSelectionListeners
  * are notified. This has
  * no effect if <code>paths</code> is NULL.
  * <p>The lead path is set to the last element in <code>paths</code>.
  * <p>If the selection mode is <code>CONTIGUOUS_TREE_SELECTION</code>,
  * and adding the new paths would make the selection discontiguous.
  * Then two things can result: if the TreePaths in <code>paths</code>
  * are contiguous, then the selection becomes these TreePaths,
  * otherwise the TreePaths aren't contiguous and the selection becomes
  * the first TreePath in <code>paths</code>.
  *
  * @param paths the new path to add to the current selection
  */
/*public*/ void addSelectionPaths(TreePath[] paths) {
    int       newPathLength = ((paths == NULL) ? 0 : paths.length);

    if(newPathLength > 0) {
        if(selectionMode == TreeSelectionModel.SINGLE_TREE_SELECTION) {
            setSelectionPaths(paths);
        }
        else if(selectionMode == TreeSelectionModel.
                CONTIGUOUS_TREE_SELECTION && !canPathsBeAdded(paths)) {
            if(arePathsContiguous(paths)) {
                setSelectionPaths(paths);
            }
            else {
                TreePath[]          newPaths = new TreePath[1];

                newPaths[0] = paths[0];
                setSelectionPaths(newPaths);
            }
        }
        else {
            int               counter, validCount;
            int               oldCount;
            TreePath          beginLeadPath = leadPath;
            Vector<PathPlaceHolder>  cPaths = NULL;

            if(selection == NULL)
                oldCount = 0;
            else
                oldCount = selection.length;
            /* Determine the paths that aren't currently in the
               selection. */
            lastPaths.clear();
            for(counter = 0, validCount = 0; counter < newPathLength;
                counter++) {
                if(paths[counter] != NULL) {
                    if (uniquePaths.get(paths[counter]) == NULL) {
                        validCount++;
                        if(cPaths == NULL)
                            cPaths = new Vector<PathPlaceHolder>();
                        cPaths.addElement(new PathPlaceHolder
                                          (paths[counter], true));
                        uniquePaths.put(paths[counter], Boolean.TRUE);
                        lastPaths.put(paths[counter], Boolean.TRUE);
                    }
                    leadPath = paths[counter];
                }
            }

            if(leadPath == NULL) {
                leadPath = beginLeadPath;
            }

            if(validCount > 0) {
                TreePath         newSelection[] = new TreePath[oldCount +
                                                              validCount];

                /* And build the new selection. */
                if(oldCount > 0)
                    System.arraycopy(selection, 0, newSelection, 0,
                                     oldCount);
                if(validCount != paths.length) {
                    /* Some of the paths in paths are already in
                       the selection. */
                    Enumeration<TreePath> newPaths = lastPaths.keys();

                    counter = oldCount;
                    while (newPaths.hasMoreElements()) {
                        newSelection[counter++] = newPaths.nextElement();
                    }
                }
                else {
                    System.arraycopy(paths, 0, newSelection, oldCount,
                                     validCount);
                }

                selection = newSelection;

                insureUniqueness();

                updateLeadIndex();

                resetRowSelection();

                notifyPathChange(cPaths, beginLeadPath);
            }
            else
                leadPath = beginLeadPath;
            lastPaths.clear();
        }
    }
}

/**
  * Removes path from the selection. If path is in the selection
  * The TreeSelectionListeners are notified. This has no effect if
  * <code>path</code> is NULL.
  *
  * @param path the path to remove from the selection
  */
/*public*/ void removeSelectionPath(TreePath path) {
    if(path != NULL) {
        TreePath[]             rPath = new TreePath[1];

        rPath[0] = path;
        removeSelectionPaths(rPath);
    }
}

/**
  * Removes paths from the selection.  If any of the paths in paths
  * are in the selection the TreeSelectionListeners are notified.
  * This has no effect if <code>paths</code> is NULL.
  *
  * @param paths the paths to remove from the selection
  */
/*public*/ void removeSelectionPaths(TreePath[] paths) {
    if (paths != NULL && selection != NULL && paths.length > 0) {
        if(!canPathsBeRemoved(paths)) {
            /* Could probably do something more interesting here! */
            clearSelection();
        }
        else {
            Vector<PathPlaceHolder> pathsToRemove = NULL;

            /* Find the paths that can be removed. */
            for (int removeCounter = paths.length - 1; removeCounter >= 0;
                 removeCounter--) {
                if(paths[removeCounter] != NULL) {
                    if (uniquePaths.get(paths[removeCounter]) != NULL) {
                        if(pathsToRemove == NULL)
                            pathsToRemove = new Vector<PathPlaceHolder>(paths.length);
                        uniquePaths.remove(paths[removeCounter]);
                        pathsToRemove.addElement(new PathPlaceHolder
                                     (paths[removeCounter], false));
                    }
                }
            }
            if(pathsToRemove != NULL) {
                int         removeCount = pathsToRemove.size();
                TreePath    beginLeadPath = leadPath;

                if(removeCount == selection.length) {
                    selection = NULL;
                }
                else {
                    Enumeration<TreePath> pEnum = uniquePaths.keys();
                    int                  validCount = 0;

                    selection = new TreePath[selection.length -
                                            removeCount];
                    while (pEnum.hasMoreElements()) {
                        selection[validCount++] = pEnum.nextElement();
                    }
                }
                if (leadPath != NULL &&
                    uniquePaths.get(leadPath) == NULL) {
                    if (selection != NULL) {
                        leadPath = selection[selection.length - 1];
                    }
                    else {
                        leadPath = NULL;
                    }
                }
                else if (selection != NULL) {
                    leadPath = selection[selection.length - 1];
                }
                else {
                    leadPath = NULL;
                }
                updateLeadIndex();

                resetRowSelection();

                notifyPathChange(pathsToRemove, beginLeadPath);
            }
        }
    }
}
#endif
/**
  * Returns the first path in the selection. This is useful if there
  * if only one item currently selected.
  */
/*public*/ TreePath* DefaultTreeSelectionModel::getSelectionPath() {
    if (!selection.isEmpty() && selection.length() > 0) {
        return selection.at(0);
    }
    return nullptr;
}

/**
  * Returns the selection.
  *
  * @return the selection
  */
/*public*/ QVector<TreePath*> DefaultTreeSelectionModel::getSelectionPaths() {
    if(!selection.isEmpty()) {
        int                 pathSize = selection.length();
        Q_UNUSED(pathSize);
        QVector<TreePath*>   result =  QVector<TreePath*>();

        //System.arraycopy(selection, 0, result, 0, pathSize);
        foreach (TreePath* p, selection)
        {
         result.append(p);
        }
        return result;
    }
    return QVector<TreePath*>();
}

/**
 * Returns the number of paths that are selected.
 */
/*public*/ int DefaultTreeSelectionModel::getSelectionCount() {
    return (selection.isEmpty()) ? 0 : selection.length();
}

/**
  * Returns true if the path, <code>path</code>,
  * is in the current selection.
  */
/*public*/ bool DefaultTreeSelectionModel::isPathSelected(TreePath* path) {
    return (path != nullptr) ? (uniquePaths->value(path) != 0) : false;
}

/**
  * Returns true if the selection is currently empty.
  */
/*public*/ bool DefaultTreeSelectionModel::isSelectionEmpty() {
    return (selection.isEmpty() || selection.length() == 0);
}

/**
  * Empties the current selection.  If this represents a change in the
  * current selection, the selection listeners are notified.
  */
/*public*/ void DefaultTreeSelectionModel::clearSelection() {
    if (!selection.isEmpty() && selection.length() > 0) {
        int                    selSize = selection.length();
        QVector<bool>      newness = QVector<bool>(selSize);

        for(int counter = 0; counter < selSize; counter++)
            newness.replace(counter, false);

        TreeSelectionEvent*     event = new TreeSelectionEvent
            (this, selection, newness, leadPath, nullptr);

        leadPath = nullptr;
        leadIndex = leadRow = -1;
        uniquePaths->clear();
        selection = QVector<TreePath*>();
        resetRowSelection();
        fireValueChanged(event);
    }
}

/**
  * Adds x to the list of listeners that are notified each time the
  * set of selected TreePaths changes.
  *
  * @param x the new listener to be added
  */
/*public*/ void DefaultTreeSelectionModel::addTreeSelectionListener(TreeSelectionListener* x) {
    listenerList->add("TreeSelectionListener", x);
}

/**
  * Removes x from the list of listeners that are notified each time
  * the set of selected TreePaths changes.
  *
  * @param x the listener to remove
  */
/*public*/ void DefaultTreeSelectionModel::removeTreeSelectionListener(TreeSelectionListener* /*x*/) {
//    listenerList->remove("TreeSelectionListener", x);
}

/**
 * Returns an array of all the tree selection listeners
 * registered on this model.
 *
 * @return all of this model's <code>TreeSelectionListener</code>s
 *         or an empty
 *         array if no tree selection listeners are currently registered
 *
 * @see #addTreeSelectionListener
 * @see #removeTreeSelectionListener
 *
 * @since 1.4
 */
/*public*/ QVector<TreeSelectionListener*> DefaultTreeSelectionModel::getTreeSelectionListeners() {
    //return listenerList->getListeners(QString("TreeSelectionListener"));
 QVector<TreeSelectionListener*> rslt = QVector<TreeSelectionListener*>();
 QVector<EventListener*> olist = listenerList->getListenerList();
 foreach (EventListener* el, olist) {
  if(qobject_cast<TreeSelectionListener*>(el->self()) != nullptr)
    rslt.append((TreeSelectionListener*)el);
 }
 return rslt;
}

/**
 * Notifies all listeners that are registered for
 * tree selection events on this object.
 * @see #addTreeSelectionListener
 * @see EventListenerList
 */
/*protected*/ void DefaultTreeSelectionModel::fireValueChanged(TreeSelectionEvent* e) {
    // Guaranteed to return a non-NULL array
    QVector<EventListener*> listeners = listenerList->getListenerList();
    // TreeSelectionEvent e = NULL;
    // Process the listeners last to first, notifying
    // those that are interested in this event
    for (int i = listeners.length()-2; i>=0; i-=2) {
        //if (listeners.at(i)=="TreeSelectionListener")
     if(qobject_cast<TreeSelectionListener*>(listeners.at(i)->self()) != nullptr)
        {
            // Lazily create the event:
            // if (e == NULL)
            // e = new ListSelectionEvent(this, firstIndex, lastIndex);
            ((TreeSelectionListener*)listeners.at(i+1))->valueChanged(e);
        }
    }
}

/**
 * Returns an array of all the objects currently registered
 * as <code><em>Foo</em>Listener</code>s
 * upon this model.
 * <code><em>Foo</em>Listener</code>s are registered using the
 * <code>add<em>Foo</em>Listener</code> method.
 *
 * <p>
 *
 * You can specify the <code>listenerType</code> argument
 * with a class literal,
 * such as
 * <code><em>Foo</em>Listener.class</code>.
 * For example, you can query a
 * <code>DefaultTreeSelectionModel</code> <code>m</code>
 * for its tree selection listeners with the following code:
 *
 * <pre>TreeSelectionListener[] tsls = (TreeSelectionListener[])(m.getListeners(TreeSelectionListener.class));</pre>
 *
 * If no such listeners exist, this method returns an empty array.
 *
 * @param listenerType the type of listeners requested; this parameter
 *          should specify an interface that descends from
 *          <code>java.util.EventListener</code>
 * @return an array of all objects registered as
 *          <code><em>Foo</em>Listener</code>s on this component,
 *          or an empty array if no such
 *          listeners have been added
 * @exception ClassCastException if <code>listenerType</code>
 *          doesn't specify a class or interface that implements
 *          <code>java.util.EventListener</code>
 *
 * @see #getTreeSelectionListeners
 * @see #getPropertyChangeListeners
 *
 * @since 1.3
 */
//template<class T>
///*public*/ /*<T extends EventListener>*/ QVector<T*> DefaultTreeSelectionModel::getListeners(QString listenerType) {
//    return listenerList->getListeners(listenerType);
//}

/**
 * Returns the selection in terms of rows. There is not
 * necessarily a one-to-one mapping between the {@code TreePath}s
 * returned from {@code getSelectionPaths} and this method. In
 * particular, if a {@code TreePath} is not viewable (the {@code
 * RowMapper} returns {@code -1} for the row corresponding to the
 * {@code TreePath}), then the corresponding row is not included
 * in the returned array. For example, if the selection consists
 * of two paths, {@code A} and {@code B}, with {@code A} at row
 * {@code 10}, and {@code B} not currently viewable, then this method
 * returns an array with the single entry {@code 10}.
 *
 * @return the selection in terms of rows
 */
/*public*/ QVector<int> DefaultTreeSelectionModel::getSelectionRows() {
    // This is currently rather expensive.  Needs
    // to be better support from ListSelectionModel to speed this up.
    if (rowMapper != nullptr && !selection.isEmpty() && selection.length() > 0) {
        QVector<int>      rows = rowMapper->getRowsForPaths(selection);

        if (!rows.isEmpty()) {
            int       invisCount = 0;

            for (int counter = rows.length() - 1; counter >= 0; counter--) {
                if (rows[counter] == -1) {
                    invisCount++;
                }
            }
            if (invisCount > 0) {
                if (invisCount == rows.length()) {
                    rows = QVector<int>();
                }
                else {
                    QVector<int>    tempRows = QVector<int>(rows.length() - invisCount);

                    for (int counter = rows.length() - 1, visCounter = 0;
                         counter >= 0; counter--) {
                        if (rows.at(counter) != -1) {
                            tempRows.replace(visCounter++, rows.at(counter));
                        }
                    }
                    rows = tempRows;
                }
            }
        }
        return rows;
    }
    return QVector<int>();
}

/**
 * Returns the smallest value obtained from the RowMapper for the
 * current set of selected TreePaths. If nothing is selected,
 * or there is no RowMapper, this will return -1.
  */
/*public*/ int DefaultTreeSelectionModel::getMinSelectionRow() {
    return listSelectionModel->getMinSelectionIndex();
}

/**
 * Returns the largest value obtained from the RowMapper for the
 * current set of selected TreePaths. If nothing is selected,
 * or there is no RowMapper, this will return -1.
  */
/*public*/ int DefaultTreeSelectionModel::getMaxSelectionRow() {
    return listSelectionModel->getMaxSelectionIndex();
}

/**
  * Returns true if the row identified by <code>row</code> is selected.
  */
/*public*/ bool DefaultTreeSelectionModel::isRowSelected(int row) {
    return listSelectionModel->isSelectedIndex(row);
}

/**
 * Updates this object's mapping from TreePath to rows. This should
 * be invoked when the mapping from TreePaths to integers has changed
 * (for example, a node has been expanded).
 * <p>You do not normally have to call this, JTree and its associated
 * Listeners will invoke this for you. If you are implementing your own
 * View class, then you will have to invoke this.
 * <p>This will invoke <code>insureRowContinuity</code> to make sure
 * the currently selected TreePaths are still valid based on the
 * selection mode.
 */
/*public*/ void DefaultTreeSelectionModel::resetRowSelection() {
    listSelectionModel->clearSelection();
    if(!selection.isEmpty() && rowMapper != nullptr) {
        int               aRow;
        int               validCount = 0;
        QVector<int>             rows = rowMapper->getRowsForPaths(selection);

        for(int counter = 0, maxCounter = selection.length();
            counter < maxCounter; counter++) {
            aRow = rows[counter];
            if(aRow != -1) {
                listSelectionModel->addSelectionInterval(aRow, aRow);
            }
        }
        if(leadIndex != -1 && !rows.isEmpty()) {
            leadRow = rows[leadIndex];
        }
        else if (leadPath != nullptr) {
            // Lead selection path doesn't have to be in the selection.
            tempPaths.replace(0, leadPath);
            rows = rowMapper->getRowsForPaths(tempPaths);
            leadRow = (!rows .isEmpty()) ? rows.at(0) : -1;
        }
        else {
            leadRow = -1;
        }
        insureRowContinuity();

    }
    else
        leadRow = -1;
}

/**
 * Returns the lead selection index. That is the last index that was
 * added.
 */
/*public*/ int DefaultTreeSelectionModel::getLeadSelectionRow() {
    return leadRow;
}

/**
 * Returns the last path that was added. This may differ from the
 * leadSelectionPath property maintained by the JTree.
 */
/*public*/ TreePath* DefaultTreeSelectionModel::getLeadSelectionPath() {
    return leadPath;
}

/**
 * Adds a PropertyChangeListener to the listener list.
 * The listener is registered for all properties.
 * <p>
 * A PropertyChangeEvent will get fired when the selection mode
 * changes.
 *
 * @param listener  the PropertyChangeListener to be added
 */
/*public*/ /*synchronized*/ void DefaultTreeSelectionModel::addPropertyChangeListener(
                            PropertyChangeListener* listener) {
    if (changeSupport == nullptr) {
        changeSupport = new PropertyChangeSupport(this);
    }
    changeSupport->PropertyChangeSupport::addPropertyChangeListener(listener);
}

/**
 * Removes a PropertyChangeListener from the listener list.
 * This removes a PropertyChangeListener that was registered
 * for all properties.
 *
 * @param listener  the PropertyChangeListener to be removed
 */

/*public*/ /*synchronized*/ void DefaultTreeSelectionModel::removePropertyChangeListener(
                            PropertyChangeListener* listener) {
    if (changeSupport == nullptr) {
        return;
    }
    changeSupport->removePropertyChangeListener(listener);
}

/**
 * Returns an array of all the property change listeners
 * registered on this <code>DefaultTreeSelectionModel</code>.
 *
 * @return all of this model's <code>PropertyChangeListener</code>s
 *         or an empty
 *         array if no property change listeners are currently registered
 *
 * @see #addPropertyChangeListener
 * @see #removePropertyChangeListener
 *
 * @since 1.4
 */
/*public*/ QVector<PropertyChangeListener*> DefaultTreeSelectionModel::getPropertyChangeListeners() {
    if (changeSupport == nullptr) {
        return QVector<PropertyChangeListener*>();
    }
    return changeSupport->getPropertyChangeListeners();
}

/**
 * Makes sure the currently selected <code>TreePath</code>s are valid
 * for the current selection mode.
 * If the selection mode is <code>CONTIGUOUS_TREE_SELECTION</code>
 * and a <code>RowMapper</code> exists, this will make sure all
 * the rows are contiguous, that is, when sorted all the rows are
 * in order with no gaps.
 * If the selection isn't contiguous, the selection is
 * reset to contain the first set, when sorted, of contiguous rows.
 * <p>
 * If the selection mode is <code>SINGLE_TREE_SELECTION</code> and
 * more than one TreePath is selected, the selection is reset to
 * contain the first path currently selected.
 */
/*protected*/ void DefaultTreeSelectionModel::insureRowContinuity() {
    if(selectionMode == TreeSelectionModel::CONTIGUOUS_TREE_SELECTION &&
       !selection.isEmpty() && !rowMapper != NULL) {
        DefaultListSelectionModel* lModel = listSelectionModel;
        int                       min = lModel->getMinSelectionIndex();

        if(min != -1) {
            for(int counter = min,
                    maxCounter = lModel->getMaxSelectionIndex();
                    counter <= maxCounter; counter++) {
                if(!lModel->isSelectedIndex(counter)) {
                    if(counter == min) {
                        clearSelection();
                    }
                    else {
                        QVector<TreePath*> newSel =  QVector<TreePath*>(counter - min);
                        QVector<int> selectionIndex = rowMapper->getRowsForPaths(selection);
                        // find the actual selection pathes corresponded to the
                        // rows of the new selection
                        for (int i = 0; i < selectionIndex.length(); i++) {
                            if (selectionIndex[i]<counter) {
                                newSel.replace(selectionIndex[i]-min, selection[i]);
                            }
                        }
                        setSelectionPaths(newSel);
                        break;
                    }
                }
            }
        }
    }
    else if(selectionMode == TreeSelectionModel::SINGLE_TREE_SELECTION &&
            !selection.isEmpty() && selection.length() > 1) {
        setSelectionPath(selection.at(0));
    }
}

/**
 * Returns true if the paths are contiguous,
 * or this object has no RowMapper.
 */
/*protected*/ bool DefaultTreeSelectionModel::arePathsContiguous(QVector<TreePath*> paths) {
    if(rowMapper == nullptr || paths.length() < 2)
        return true;

    else {
        BitSet*                             bitSet =  new BitSet(32);
        int                                anIndex, counter, min;
        int                                pathCount = paths.length();
        int                                validCount = 0;
        QVector<TreePath*>                  tempPath = QVector<TreePath*>();

        tempPath.append(paths.at(0));
        min = rowMapper->getRowsForPaths(tempPath).at(0);
        for(counter = 0; counter < pathCount; counter++) {
            if(!paths.at(counter) != NULL) {
                tempPath.replace(0, paths[counter]);
                QVector<int> rows = rowMapper->getRowsForPaths(tempPath);
                if (rows.isEmpty()) {
                    return false;
                }
                anIndex = rows.at(0);
                if(anIndex == -1 || anIndex < (min - pathCount) ||
                   anIndex > (min + pathCount))
                    return false;
                if(anIndex < min)
                    min = anIndex;
                if(!bitSet->get(anIndex)) {
                    bitSet->set(anIndex);
                    validCount++;
                }
            }
        }
        int          maxCounter = validCount + min;

        for(counter = min; counter < maxCounter; counter++)
            if(!bitSet->get(counter))
                return false;
    }
    return true;
}

/**
 * Used to test if a particular set of <code>TreePath</code>s can
 * be added. This will return true if <code>paths</code> is NULL (or
 * empty), or this object has no RowMapper, or nothing is currently selected,
 * or the selection mode is <code>DISCONTIGUOUS_TREE_SELECTION</code>, or
 * adding the paths to the current selection still results in a
 * contiguous set of <code>TreePath</code>s.
 */
/*protected*/ bool DefaultTreeSelectionModel::canPathsBeAdded(QVector<TreePath*> paths) {
    if(paths.isEmpty() || paths.length() == 0 || rowMapper == nullptr ||
       selection == QVector<TreePath*>() || selectionMode ==
       TreeSelectionModel::DISCONTIGUOUS_TREE_SELECTION)
        return true;
    else {
        BitSet*                       bitSet = new BitSet();
        DefaultListSelectionModel*    lModel = listSelectionModel;
        int                          anIndex;
        int                          counter;
        int                          min = lModel->getMinSelectionIndex();
        int                          max = lModel->getMaxSelectionIndex();
        QVector<TreePath*>                   tempPath = QVector<TreePath*>(1);

        if(min != -1) {
            for(counter = min; counter <= max; counter++) {
                if(lModel->isSelectedIndex(counter))
                    bitSet->set(counter);
            }
        }
        else {
            tempPath.replace(0, paths.at(0));
            min = max = rowMapper->getRowsForPaths(tempPath).at(0);
        }
        for(counter = paths.length() - 1; counter >= 0; counter--) {
            if(paths[counter] != nullptr) {
                tempPath.replace(0, paths.at(counter));
                QVector<int>   rows = rowMapper->getRowsForPaths(tempPath);
                if (rows.isEmpty()) {
                    return false;
                }
                anIndex = rows.at(0);
                min = qMin(anIndex, min);
                max = qMax(anIndex, max);
                if(anIndex == -1)
                    return false;
                bitSet->set(anIndex);
            }
        }
        for(counter = min; counter <= max; counter++)
            if(!bitSet->get(counter))
                return false;
    }
    return true;
}

/**
 * Returns true if the paths can be removed without breaking the
 * continuity of the model.
 * This is rather expensive.
 */
/*protected*/ bool DefaultTreeSelectionModel::canPathsBeRemoved(QVector<TreePath*> paths) {
    if(rowMapper == nullptr || selection.isEmpty() ||
       selectionMode == TreeSelectionModel::DISCONTIGUOUS_TREE_SELECTION)
        return true;
    else {
        BitSet*               bitSet =  new BitSet();
        int                  counter;
        int                  pathCount = paths.length();
//        int                  anIndex;
        int                  min = -1;
        int                  validCount = 0;
        QVector<TreePath*>           tempPath =  QVector<TreePath*>(1);
        QVector<int>                rows;

        /* Determine the rows for the removed entries. */
        lastPaths->clear();
        for (counter = 0; counter < pathCount; counter++) {
            if (paths[counter] != nullptr) {
                lastPaths->insert(paths[counter], true);
            }
        }
        for(counter = selection.length() - 1; counter >= 0; counter--) {
            if(lastPaths->value(selection[counter]) == 0) {
                tempPath.replace(0, selection.at(counter));
                rows = rowMapper->getRowsForPaths(tempPath);
                if(!rows.isEmpty() && rows.at(0) != -1 && !bitSet->get(rows.at(0))) {
                    validCount++;
                    if(min == -1)
                        min = rows.at(0);
                    else
                        min = qMin(min, rows.at(0));
                    bitSet->set(rows.at(0));
                }
            }
        }
        lastPaths->clear();
        /* Make sure they are contiguous. */
        if(validCount > 1) {
            for(counter = min + validCount - 1; counter >= min;
                counter--)
                if(!bitSet->get(counter))
                    return false;
        }
    }
    return true;
}
#if 0
/**
 * Notifies listeners of a change in path. changePaths should contain
 * instances of PathPlaceHolder.
 *
 * @deprecated As of JDK version 1.7
 */
//@Deprecated
/*protected*/ void notifyPathChange(Vector<?> changedPaths,
                                TreePath oldLeadSelection) {
    int                    cPathCount = changedPaths.size();
    boolean[]              newness = new boolean[cPathCount];
    TreePath[]            paths = new TreePath[cPathCount];
    PathPlaceHolder        placeholder;

    for(int counter = 0; counter < cPathCount; counter++) {
        placeholder = (PathPlaceHolder) changedPaths.elementAt(counter);
        newness[counter] = placeholder.isNew;
        paths[counter] = placeholder.path;
    }

    TreeSelectionEvent     event = new TreeSelectionEvent
                      (this, paths, newness, oldLeadSelection, leadPath);

    fireValueChanged(event);
}
#endif
/**
 * Updates the leadIndex instance variable.
 */
/*protected*/ void DefaultTreeSelectionModel::updateLeadIndex() {
    if(leadPath != nullptr) {
        if(selection.isEmpty()) {
            leadPath = nullptr;
            leadIndex = leadRow = -1;
        }
        else {
            leadRow = leadIndex = -1;
            for(int counter = selection.length() - 1; counter >= 0;
                counter--) {
                // Can use == here since we know leadPath came from
                // selection
                if(selection.at(counter) == leadPath) {
                    leadIndex = counter;
                    break;
                }
            }
        }
    }
    else {
        leadIndex = -1;
    }
}

/**
 * This method is obsolete and its implementation is now a noop.  It's
 * still called by setSelectionPaths and addSelectionPaths, but only
 * for backwards compatibility.
 */
/*protected*/ void DefaultTreeSelectionModel::insureUniqueness() {
}


/**
 * Returns a string that displays and identifies this
 * object's properties.
 *
 * @return a String representation of this object
 */
/*public*/ QString DefaultTreeSelectionModel::toString() {
    int                selCount = getSelectionCount();
    QString       retBuffer;// = new StringBuffer();
    QVector<int>              rows;

    if(rowMapper != nullptr)
        rows = rowMapper->getRowsForPaths(selection);
    else
        rows = QVector<int>();
    retBuffer.append(QString(metaObject()->className()) + " " /*+ hashCode() */+ " [ ");
    for(int counter = 0; counter < selCount; counter++) {
        if(!rows.isEmpty())
            retBuffer.append(selection.at(counter)->toString() + "@" +
                             QString::number(rows.at(counter))+ " ");
        else
            retBuffer.append(selection[counter]->toString() + " ");
    }
    retBuffer.append("]");
    return retBuffer/*.toString()*/;
}

/**
 * Returns a clone of this object with the same selection.
 * This method does not duplicate
 * selection listeners and property listeners.
 *
 * @exception CloneNotSupportedException never thrown by instances of
 *                                       this class
 */
/*public*/ QObject* DefaultTreeSelectionModel::clone() throw (CloneNotSupportedException) {
#if 0
    DefaultTreeSelectionModel        clone = (DefaultTreeSelectionModel)
                        TreeSelectionModel::clone();

    clone.changeSupport = NULL;
    if(selection != NULL) {
        int              selLength = selection.length();

        clone.selection = new TreePath[selLength];
        System.arraycopy(selection, 0, clone.selection, 0, selLength);
    }
    clone.listenerList = new EventListenerList();
    clone.listSelectionModel = (DefaultListSelectionModel)
        listSelectionModel.clone();
    clone.uniquePaths = new Hashtable<TreePath, Boolean>();
    clone.lastPaths = new Hashtable<TreePath, Boolean>();
    clone.tempPaths = new TreePath[1];
    return clone;
#else
 return nullptr;
#endif
}
#if 0
// Serialization support.
/*private*/ void writeObject(ObjectOutputStream s) throws IOException {
    Object[]             tValues;

    s.defaultWriteObject();
    // Save the rowMapper, if it implements Serializable
    if(rowMapper != NULL && rowMapper instanceof Serializable) {
        tValues = new Object[2];
        tValues[0] = "rowMapper";
        tValues[1] = rowMapper;
    }
    else
        tValues = new Object[0];
    s.writeObject(tValues);
}


/*private*/ void readObject(ObjectInputStream s)
    throws IOException, ClassNotFoundException {
    Object[]      tValues;

    s.defaultReadObject();

    tValues = (Object[])s.readObject();

    if(tValues.length > 0 && tValues[0].equals("rowMapper"))
        rowMapper = (RowMapper)tValues[1];
}
}
#endif
#if 0
/**
* Holds a path and whether or not it is new.
*/
class PathPlaceHolder {
/*protected*/ boolean             isNew;
/*protected*/ TreePath           path;

PathPlaceHolder(TreePath path, boolean isNew) {
    this.path = path;
    this.isNew = isNew;
}
#endif
