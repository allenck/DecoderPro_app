#include "spurtablemodel.h"
#include "control.h"
#include "logger.h"
#include "track.h"
#include "spureditframe.h"

namespace Operations {
/**
 * Table Model for edit of spurs used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2008
 * @versi/on $Revision: 29493 $
 */
//*public*/ class SpurTableModel extends TrackTableModel {

 /**
  *
  */
 //private static final long serialVersionUID = -8498399811366483939L;

 /*public*/ SpurTableModel::SpurTableModel(QObject* parent) : TrackTableModel(parent) {
     //super();
  log = new Logger("SpurTableModel");
  setObjectName("SpruTableModel");
 }

 /*public*/ void SpurTableModel::initTable(JTable* table, Location* location)
 {
  TrackTableModel::initTable(table, location, Track::SPUR);
 }

 /*public*/ QVariant SpurTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
   switch (section)
   {
    case NAME_COLUMN:
     return tr("Spur Name");
   }
  }
  return TrackTableModel::headerData(section, orientation, role);
 }

 /*protected*/ void SpurTableModel::editTrack(int row)
 {
  log->debug("Edit spur");

  if (tef != NULL) {
      tef->dispose();
  }

  // use invokeLater so new window appears on top
//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
  tef = new SpurEditFrame();
  Track* spur = tracksList.at(row);
  tef->initComponents(_location, spur);
  tef->setTitle(tr("Edit Spur"));
//         }
//     });
 }

 // this table listens for changes to a location and it's spurs
 /*public*/ void SpurTableModel::propertyChange(PropertyChangeEvent* e)
 {
  if (Control::showProperty)
  {
   log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                 ->getNewValue().toString()));
  }
  TrackTableModel::propertyChange(e);
  if (e->getSource()->metaObject()->className()==("Track"))
  {
   Track* track = ((Track*) e->getSource());
   if (track->getTrackType()==(Track::SPUR))
   {
    int row = tracksList.indexOf(track);
    if (Control::showProperty)
    {
     log->debug(tr("Update spur table row: %1 track: %2").arg(row).arg(track->getName()));
    }
    if (row >= 0) {
     fireTableRowsUpdated(row, row);
    }
   }
  }
 }

}
