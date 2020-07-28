#include "stagingtablemodel.h"
#include "control.h"
#include "track.h"

namespace Operations
{
/**
 * Table Model for edit of staging tracks used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 29493 $
 */
//public class StagingTableModel extends TrackTableModel {

 /**
  *
  */
 //private static final long serialVersionUID = 406205617566439045L;

 /*public*/ StagingTableModel::StagingTableModel(QObject* parent) : TrackTableModel(parent) {
     //super();
  log = new Logger("StagingTableModel");
  setObjectName("StagingTableModel");
 }

 /*public*/ void StagingTableModel::initTable(JTable* table, Location* location) {
     TrackTableModel::initTable(table, location, Track::STAGING);
 }

 /*public*/ QVariant StagingTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
   switch (section)
   {
         case NAME_COLUMN:
             return tr("Staging Name");
   }
  }
  return TrackTableModel::headerData(section, orientation, role);
 }

 /*protected*/ void StagingTableModel::editTrack(int row) {
     log->debug("Edit staging");
#if 0
     if (tef != null) {
         tef.dispose();
     }
     // use invokeLater so new window appears on top
     SwingUtilities.invokeLater(new Runnable() {
         public void run() {
             tef = new StagingEditFrame();
             Track staging = tracksList.get(row);
             tef.initComponents(_location, staging);
             tef.setTitle(Bundle.getMessage("EditStaging"));
         }
     });
#endif
 }

 // this table listens for changes to a location and it's staging tracks
 /*public*/ void StagingTableModel::propertyChange(PropertyChangeEvent* e)
 {
  if (Control::SHOW_PROPERTY)
  {
   log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
  }
  TrackTableModel::propertyChange(e);
  if (e->getSource()->metaObject()->className()==("Track"))
  {
   Track* track = ((Track*) e->getSource());
   if (track->getTrackType()==(Track::STAGING))
   {
    int row = tracksList.indexOf(track);
    if (Control::SHOW_PROPERTY)
    {
        log->debug(tr("Update staging table row: %1 track: %2").arg(row).arg(track->getName()));
    }
    if (row >= 0)
    {
        fireTableRowsUpdated(row, row);
    }
   }
  }
 }
}
