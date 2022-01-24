#ifndef PHYSICALLOCATIONPANEL_H
#define PHYSICALLOCATIONPANEL_H

#include "jpanel.h"
#include "titledborder.h"
#include "jspinner.h"
#include "gridbagconstraints.h"

class PhysicalLocation;
class PhysicalLocationPanel : public JPanel
{
  Q_OBJECT
 public:
  PhysicalLocationPanel(QWidget* parent = nullptr);
  /*public*/  PhysicalLocationPanel(QString title, QWidget *parent=nullptr);
  /*public*/  void setTitle(QString t);
  /*public*/  QString getTitle();
  /*public*/  void setValue(PhysicalLocation* p);
  /*public*/  void setValue(QString s);
  /*public*/  PhysicalLocation* getValue();

 private:
  static Logger* log;
  TitledBorder* tb;
  JSpinner* xs, *ys, *zs;
  SpinnerNumberModel* spinnerModel;
  static /*final*/constexpr float min_spin = -1000.0f;
  static /*final*/constexpr float max_spin = 1000.0f;
  static /*final*/constexpr float spin_value = 0.0f;
  static /*final*/constexpr float spin_inc = 0.1f;
  /*private*/ GridBagConstraints setConstraints(int x, int y, bool fill);
  /*protected*/ void initComponents(QString title);

};

#endif // PHYSICALLOCATIONPANEL_H
