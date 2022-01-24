#ifndef TRAINCONDUCTORPANEL_H
#define TRAINCONDUCTORPANEL_H

#include "commonconductoryardmasterpanel.h"

namespace Operations
{
 class TrainConductorPanel : public CommonConductorYardmasterPanel
 {
  Q_OBJECT
 public:
  /*public*/ TrainConductorPanel(QWidget* parent = 0);
  /*public*/ TrainConductorPanel(Train* train, QWidget* parent = 0);
  /*public*/ void dispose();

 public slots:
  /*public*/ virtual void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  // labels
  QLabel* textTrainName;// = new JLabel();
  QLabel* textTrainDepartureTime;// = new JLabel();
  QLabel* textNextLocationName;// = new JLabel();

  // panels
  JPanel* pTrainDepartureTime = new JPanel();
  void common(Train* train);
  /*private*/ void clearAndUpdate();
  /*private*/ void update();
  Logger* log;
 protected:
  /*protected*/ static /*final*/ bool IS_MANIFEST;// = true;

 };
}
#endif // TRAINCONDUCTORPANEL_H
