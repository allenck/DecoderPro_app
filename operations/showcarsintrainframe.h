#ifndef SHOWCARSINTRAINFRAME_H
#define SHOWCARSINTRAINFRAME_H


#include "operationsframe.h"
class QLabel;
namespace Operations
{
 class Train;
 class RouteLocation;
 class CarManager;
 class TrainCommon;
 class ShowCarsInTrainFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  ShowCarsInTrainFrame(QWidget* parent = 0);
  /*public*/ void initComponents(Train* train);
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
 private:
  Train* _train;// = null;
  CarManager* carManager;// = CarManager.instance();
  TrainCommon* trainCommon;// = new TrainCommon();

  QScrollArea* carPane;

  // labels
  QLabel* textTrainName;// = new JLabel();
  QLabel* textLocationName;// = new JLabel();
  QLabel* textNextLocationName;// = new JLabel();
  HtmlTextEdit* textStatus;// = new JTextPane();
  QLabel* textPickUp;// = new JLabel(Bundle.getMessage("Pickup"));
  QLabel* textInTrain;// = new JLabel(Bundle.getMessage("InTrain"));
  QLabel* textSetOut;// = new JLabel(Bundle.getMessage("SetOut"));

  // major buttons
  // radio buttons
  // text field
  // combo boxes
  // panels
  QWidget* pCars;// = new QWidget();
  /*private*/ void update();
  Logger* log;
  /*private*/ QString getStatus(RouteLocation* rl);
  /*private*/ void packFrame();

  friend class SCITFWorker;
 };
#if 1
 class SCITFWorker : public QObject
 {
  Q_OBJECT
  ShowCarsInTrainFrame* scitf;
 public:

  SCITFWorker(ShowCarsInTrainFrame* scitf);
 public slots:
  void process();
 signals:
  void finished();
 };
#endif
}
#endif // SHOWCARSINTRAINFRAME_H
