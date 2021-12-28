#ifndef LIGHTTABLEDATAMODEL_H
#define LIGHTTABLEDATAMODEL_H

#include "beantabledatamodel.h"
#include "light.h"
#include "jbutton.h"
#include "bufferedimage.h"
#include "jlabel.h"

class LightTableDataModel : public BeanTableDataModel
{
 public:
  enum COLUMNS
  {
    ENABLECOL = BeanTableDataModel::NUMCOLUMN,
    INTENSITYCOL = ENABLECOL + 1,
    EDITCOL = INTENSITYCOL + 1,
    CONTROLCOL = EDITCOL + 1
};
  LightTableDataModel();
  /*public*/ LightTableDataModel(Manager/*<Light>*/* mgr);
  /*private*/ void initTable();
  /*public*/ AbstractManager/*<Light>*/* getManager() override;
  /*public*/ int columnCount(const QModelIndex& parent) const override;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  /*public*/ QString getColumnClass(int col) const override;
  /*public*/ int getPreferredWidth(int col) override;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
  /*public*/ QString getValue(QString name) override;
  /*public*/ QVariant data(const QModelIndex &index, int role) const override;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  /*public*/ NamedBean* getBySystemName(/*@Nonnull*/ QString name) const override;
  /*public*/ void configureTable(JTable *table) override;
  /*public*/ JButton* configureButton()override;
  /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString name) override;
  /*public*/ void clickOn(NamedBean* t)override;

 private:
  static Logger* log;
  /*private*/ AbstractManager* lightManager;
  /*private*/ void editButton(Light* bean);

 protected:
  // for icon state col
  /*protected*/ bool _graphicState = false; // updated from prefs
  /*protected*/ /*final*/ void setManager(/*@Nonnull*/ AbstractManager/*<Light>*/* manager) override;
  /*protected*/ void doDelete(NamedBean* bean)override;
  /*protected*/ QString getMasterClassName() override;
  /*protected*/ void configValueColumn(JTable* table) override;
  /*protected*/ QString rootPath = "resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
  /*protected*/ char beanTypeChar = 'L'; // for Light
  /*protected*/ QString onIconPath = rootPath + beanTypeChar + "-on-s.png";
  /*protected*/ QString offIconPath = rootPath + beanTypeChar + "-off-s.png";
  BufferedImage* onImage;
  BufferedImage* offImage;
  /*protected*/ QPixmap onIcon;
  /*protected*/ QPixmap offIcon;
  /*protected*/ int iconHeight = -1;
  /*protected*/ void loadIcons();

 protected slots:
  /*protected*/ bool matchPropertyName(PropertyChangeEvent* e) override;

  friend class LightTableAction;
};

#endif // LIGHTTABLEDATAMODEL_H
