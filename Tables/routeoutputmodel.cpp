#include "routeoutputmodel.h"
#include "instancemanager.h"
#include "turnoutmanager.h"
#include "routeaddframe.h"

/**
 * Base table model for selecting outputs.
 *
 * Split from {@link jmri.jmrit.beantable.RouteTableAction}
 *
 * @author Dave Duchamp Copyright (C) 2004
 * @author Bob Jacobsen Copyright (C) 2007
 * @author Simon Reader Copyright (C) 2008
 * @author Pete Cressman Copyright (C) 2009
 * @author Egbert Broerse Copyright (C) 2016
 * @author Paul Bender Copyright (C) 2020
 */
//abstract class RouteOutputModel extends AbstractTableModel implements PropertyChangeListener {

    //@Override
    /*public*/ QString RouteOutputModel::getColumnClass(int c) const {
        if (c == INCLUDE_COLUMN) {
            return "Boolean";
        } else {
            return "String";
        }
    }

    //@Override
    /*public*/ void RouteOutputModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName() == ("length")) {
            // a new NamedBean is available in the manager
            fireTableDataChanged();
        }
    }

    void RouteOutputModel::dispose() {
        InstanceManager::turnoutManagerInstance()->removePropertyChangeListener((PropertyChangeListener*)this);
    }

    //@Override
    /*public*/ QString RouteOutputModel::getColumnName(int c) const{
        return RouteAddFrame::COLUMN_NAMES[c];
    }

    //@Override
    /*public*/ int RouteOutputModel:: columnCount(const QModelIndex &parent) const {
        return 4;
    }

    //@Override
    /*public*/ Qt::ItemFlags RouteOutputModel::flags(const QModelIndex &index) const{
        //return ((c == INCLUDE_COLUMN) || (c == STATE_COLUMN));
     if(index.column() == INCLUDE_COLUMN )
      return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
     if( index.column() == STATE_COLUMN)
      return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }

