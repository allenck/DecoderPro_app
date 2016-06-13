#ifndef INTERCHANGETABLEMODEL_H
#define INTERCHANGETABLEMODEL_H
#include "tracktablemodel.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT InterchangeTableModel : public TrackTableModel
 {
 public:
  InterchangeTableModel(QObject* parent = 0);
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
#endif // INTERCHANGETABLEMODEL_H
