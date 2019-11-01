#include "interchangetablemodel.h"
#include "control.h"
#include "track.h"
#include "interchangeeditframe.h"

namespace Operations
{
/**
 * Table Model for edit of interchanges used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 29493 $
 */
//public class InterchangeTableModel extends TrackTableModel {

    /**
     *
     */
    //private static final long serialVersionUID = -3985319043804319680L;

    /*public*/ InterchangeTableModel::InterchangeTableModel(QObject* parent) : TrackTableModel(parent) {
        //super();
     log = new Logger("InterchangeTableModel");
     setObjectName("InterchangeTableModel");
    }

    /*public*/ void InterchangeTableModel::initTable(JTable* table, Location* location) {
        TrackTableModel::initTable(table, location, Track::INTERCHANGE);
    }

    /*public*/ QVariant InterchangeTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
     if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
     {
        switch (section)
        {
            case NAME_COLUMN:
                return tr("Interchange Name");
        }
     }
     return TrackTableModel::headerData(section, orientation, role);
    }

    /*protected*/ void InterchangeTableModel::editTrack(int row) {

        log->debug("Edit interchange");
        if (tef != NULL) {
            tef->dispose();
        }
        // use invokeLater so new window appears on top
//        SwingUtilities.invokeLater(new Runnable() {
//            public void run() {
                tef = new InterchangeEditFrame();
                Track* interchange = tracksList.at(row);
                tef->initComponents(_location, interchange);
                tef->setTitle(tr("Edit Interchange"));
//            }
//        });

    }

    // this table listens for changes to a location and it's interchanges
    /*public*/ void InterchangeTableModel::propertyChange(PropertyChangeEvent* e) {
        if (Control::showProperty) {
            log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                    ->getNewValue().toString()));
        }
        TrackTableModel::propertyChange(e);
        if (e->getSource()->metaObject()->className()==("Track")) {
            Track* track = ((Track*) e->getSource());
            if (track->getTrackType()==(Track::INTERCHANGE)) {
                int row = tracksList.indexOf(track);
                if (Control::showProperty) {
                    log->debug(tr("Update interchange table row: %1 track: %2").arg(row).arg(track->getName()));
                }
                if (row >= 0) {
                    fireTableRowsUpdated(row, row);
                }
            }
        }
    }
}
