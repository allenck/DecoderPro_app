#include "yardtablemodel.h"
#include "logger.h"
#include "propertychangeevent.h"
#include "track.h"
#include "control.h"
#include "yardeditframe.h"

namespace Operations
{
/**
 * Table Model for edit of yards used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 29493 $
 */
///*public*/ class YardTableModel extends TrackTableModel {

 /**
  *
  */
 //private static final long serialVersionUID = -7919234279596604386L;

 /*public*/ YardTableModel::YardTableModel(QObject* parent) : TrackTableModel(parent) {
     //super();
  log - new Logger("YardTableModel");
  setObjectName("YardTableModel");
 }

 /*public*/ void YardTableModel::YardTableModel::initTable(JTable* table, Location* location) {
     TrackTableModel::initTable(table, location, Track::YARD);
 }

 /*public*/ QVariant YardTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
     switch (section) {
         case NAME_COLUMN:
             return tr("YardName");
     }
  }
  return TrackTableModel::headerData(section, orientation, role);
 }

 /*protected*/ void YardTableModel::editTrack(int row) {

     log->debug("Edit yard");
     if (tef != NULL) {
         tef->dispose();
     }

     // use invokeLater so new window appears on top
//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
             tef = new YardEditFrame();
             Track* yard = tracksList.at(row);
             tef->initComponents(_location, yard);
             tef->setTitle(tr("EditYard"));
//         }
//     });

 }

 // this table listens for changes to a location and it's yards
 /*public*/ void YardTableModel::propertyChange(PropertyChangeEvent* e) {
     if (Control::showProperty) {
         log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                 ->getNewValue().toString()));
     }
     TrackTableModel::propertyChange(e);
     if (e->getSource()->metaObject()->className()==("Track")) {
         Track* track = ((Track*) e->getSource());
         if (track->getTrackType()==(Track::YARD)) {
             int row = tracksList.indexOf(track);
             if (Control::showProperty) {
                 log->debug(tr("Update yard table row: %1 track: (%2)").arg(row).arg(track->getName()));
             }
             if (row >= 0) {
                 fireTableRowsUpdated(row, row);
             }
         }
     }
 }
}
