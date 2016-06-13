#ifndef SPURTABLEMODEL_H
#define SPURTABLEMODEL_H
#include "tracktablemodel.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT SpurTableModel : public TrackTableModel
 {
  Q_OBJECT
 public:
  SpurTableModel(QObject* parent = 0);
  /*public*/ void initTable(JTable* table, Location* location);
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
 private:
  Logger* log;

 protected:
  /*protected*/ void editTrack(int row);

 };
}
#endif // SPURTABLEMODEL_H
