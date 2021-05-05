#ifndef BLOCKTABLEDATAMODEL_H
#define BLOCKTABLEDATAMODEL_H

#include <beantabledatamodel.h>
#include "guilafpreferencesmanager.h"
#include "instancemanager.h"
#include "userpreferencesmanager.h"
#include "blocktableaction.h"

class BlockTableDataModel : public BeanTableDataModel
{
  Q_OBJECT
 public:
  BlockTableDataModel(Manager* mgr);
  enum COLUMNS
  {
   EDITCOL = BeanTableDataModel::NUMCOLUMN,
   DIRECTIONCOL = EDITCOL + 1,
   LENGTHCOL = DIRECTIONCOL + 1,
   CURVECOL = LENGTHCOL + 1,
   STATECOL = CURVECOL + 1,
   SENSORCOL = STATECOL + 1,
   REPORTERCOL = SENSORCOL + 1,
   CURRENTREPCOL = REPORTERCOL + 1,
   PERMISCOL = CURRENTREPCOL + 1,
   SPEEDCOL = PERMISCOL + 1
  };
  /*public*/ QString getValue(QString name) override;
  /*public*/ AbstractManager/*<Block>*/* getManager()override;
  /*public*/ NamedBean* getBySystemName(/*@Nonnull*/ QString name) const override;
  /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString name) override;
  /*public*/ void clickOn(NamedBean* t) override;
  /*public*/ int getColumnCount() const override;
  /*public*/ QVariant getValueAt(int row, int col) const override;
  /*public*/ void setValueAt(QVariant value, int row, int col) override;
  /*public*/ QString getColumnName(int col) const override;
  /*public*/ QString getColumnClass(int col)const override;
  /*public*/ int getPreferredWidth(int col)override;
  /*public*/ void configValueColumn(JTable* table) override;
  /*public*/ bool isCellEditable(int row, int col) const override;
  /*public*/ void configureTable(JTable* table)override;
  /*public*/ JButton* configureButton() override;
  /*public*/ void setMetric(bool boo);
  /*public*/ void setDefaultSpeeds(JFrame* _who);
  /*synchronized*/ /*public*/ void dispose() override;
  /*public*/ QString getCellToolTip(JTable* table, int row, int col) const override;
  /*public*/ int columnCount(const QModelIndex &parent) const override {return getColumnCount();}
 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;

 private:
  static Logger* log;
  /*private*/ /*final*/ bool _graphicState = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isGraphicTableState();

  /*private*/ /*final*/ DecimalFormat twoDigit =  DecimalFormat("0.00");

  /*private*/ QVector<QString>* speedList = new QVector<QString>();
  /*private*/ QVector<QString> sensorList;
  /*private*/ QVector<QString> reporterList;

  QString defaultBlockSpeedText;
  /*private*/ bool metricUi = ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))
      ->getSimplePreferenceState(BlockTableAction::BLOCK_METRIC_PREF);
  /*private*/ QString blockDescribeState(int blockState) const;
  void editButton(Block* b);
  /*private*/ void updateSensorList();
  /*private*/ void updateReporterList();
  /*private*/ void updateSpeedList();
//  QVariant data(const QModelIndex &index, int role) const override;

 protected:
  /*protected*/ QString getMasterClassName() override;
  /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
  /*protected*/ void configStateColumn(JTable* table);

};

#endif // BLOCKTABLEDATAMODEL_H
