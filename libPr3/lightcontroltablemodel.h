#ifndef LIGHTCONTROLTABLEMODEL_H
#define LIGHTCONTROLTABLEMODEL_H

#include <abstracttablemodel.h>
#include "lightcontrolpane.h"
#include "lightcontrol.h"

class LightControlPane;
class LightControlTableModel : public AbstractTableModel
{
  Q_OBJECT
 public:
  enum COLS
  {
   TYPE_COLUMN = 0,
   DESCRIPTION_COLUMN = 1,
   EDIT_COLUMN = 2,
   REMOVE_COLUMN = 3
  };
  LightControlTableModel(LightControlPane* pane);
  /*public*/ static QString getControlTypeText(int type);
  /*public*/ QList<LightControl*> getControlList();
  /*public*/ void setTableToLight(Light* light);
  /*public*/ void addControl(LightControl* lc);
  /*public*/ void removeControl(LightControl* lc);
  /*public*/ QString getColumnClass(int c) const override;
  /*public*/ int columnCount(const QModelIndex&) const override;
  /*public*/ int rowCount(const QModelIndex&) const override;
  /*public*/ Qt::ItemFlags flags(const QModelIndex& index)const override;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  /*public*/ QVariant data(const QModelIndex& index, int role) const override;
  /*public*/ bool setData(const QModelIndex& index, const QVariant& value, int role) override;
 private:
  /*private*/ /*final*/ LightControlPane* lcp;
  /*private*/ /*final*/ QList<LightControl*> controlList;

 protected:
  /*protected*/ static /*final*/ QString sensorControl;// = Bundle.getMessage("LightSensorControl");
  /*protected*/ static /*final*/ QString fastClockControl;// = Bundle.getMessage("LightFastClockControl");
  /*protected*/ static /*final*/ QString turnoutStatusControl;// = Bundle.getMessage("LightTurnoutStatusControl");
  /*protected*/ static /*final*/ QString timedOnControl;// = Bundle.getMessage("LightTimedOnControl");
  /*protected*/ static /*final*/ QString twoSensorControl;// = Bundle.getMessage("LightTwoSensorControl");
  /*protected*/ static /*final*/ QString noControl;// = Bundle.getMessage("LightNoControl");
  /*protected*/ static /*final*/ QVector<QString> controlTypes;// = QVector<QString>{
  /*protected*/ static /*final*/ QList<QString> getControlTypeTips();
  /*protected*/ void configureJTable(JTable* table);

  friend class AddEditSingleLightControlFrame;
  friend class LightControlPane;
};

#endif // LIGHTCONTROLTABLEMODEL_H
