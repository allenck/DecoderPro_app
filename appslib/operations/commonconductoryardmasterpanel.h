#ifndef COMMONCONDUCTORYARDMASTERPANEL_H
#define COMMONCONDUCTORYARDMASTERPANEL_H
#include "operationspanel.h"
#include "appslib_global.h"

class QVBoxLayout;
class QGroupBox;
//class JTextPane;
class QScrollArea;
class PropertyChangeEvent;
class QLabel;
namespace Operations
{
 class RouteLocation;
 class CarSetFrame;
 class RollingStock;
 class Location;
 class Train;
 class TrainManager;
 class EngineManager;
 class CarManager;
 class TrainCommon;
 class Car;
 class APPSLIBSHARED_EXPORT CommonConductorYardmasterPanel : public OperationsPanel
 {
  Q_OBJECT
 public:
  CommonConductorYardmasterPanel(QWidget* parent = 0);
  /*public*/ void initComponents();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void setCarButtonActionPerfomed(QWidget* ae);

 private:
  Logger* log;
  CarSetFrame* csf;// = NULL;
  QVBoxLayout* thisLayout;
  /*private*/ void addCarToTrain();

 protected:
  /*protected*/ static /*final*/ QString Tab;//= "     "; // used to space out headers
  /*protected*/ static /*final*/ QString Space;//= " "; // used to pad out panels
  /*protected*/ Location* _location;//= null;
  /*protected*/ Train* _train;//= null;

  /*protected*/ TrainManager* trainManager;//= TrainManager.instance();
  /*protected*/ EngineManager* engManager;//= EngineManager.instance();
  /*protected*/ CarManager* carManager;//= CarManager.instance();
  /*protected*/ TrainCommon* trainCommon;//= new TrainCommon();
  /*protected*/ void setCheckBoxFont(QCheckBox* checkBox);

  QGroupBox* locoPaneFrame;
  /*protected*/ QScrollArea* locoPane;
  QGroupBox* pickupPaneFrame;
  /*protected*/ QScrollArea* pickupPane;
  QGroupBox* setoutPaneFrame;
  /*protected*/ QScrollArea* setoutPane;
  QGroupBox* movePaneFrame;
  /*protected*/ QScrollArea* movePane;

  // labels
  /*protected*/ QLabel* textRailRoadName;//= new JLabel();
  /*protected*/ QLabel* textTrainDescription;//= new JLabel();
  /*protected*/ QLabel* textLocationName;//= new JLabel();
  /*protected*/ QLabel* textStatus;//= new JLabel();

  // major buttons
  /*protected*/ QPushButton* selectButton;//= new JButton(Bundle.getMessage("Select"));
  /*protected*/ QPushButton* clearButton;//= new JButton(Bundle.getMessage("Clear"));
  /*protected*/ QPushButton* modifyButton;// = new JButton(Bundle.getMessage("Modify")); // see setModifyButtonText()

  /*protected*/ QPushButton* moveButton;//= new JButton(Bundle.getMessage("Move"));

  // text panes
  QGroupBox* textLocationCommentGB;
  /*protected*/ HtmlTextEdit* textLocationCommentPane;//= new JTextPane();
  QGroupBox* textTrainCommentGB;
  /*protected*/ HtmlTextEdit* textTrainCommentPane;//= new JTextPane();
  QGroupBox* textTrainRouteCommentGB;
  /*protected*/ HtmlTextEdit* textTrainRouteCommentPane;//= new JTextPane();
  QGroupBox* textTrainRouteLocationCommentGB;
  /*protected*/ HtmlTextEdit* textTrainRouteLocationCommentPane;//= new JTextPane();

  // panels
  /*protected*/ QGroupBox* pRailRoadName;//= new JPanel();
  /*protected*/ QGroupBox* pTrainDescription;//= new JPanel();
  /*protected*/ QGroupBox* pLocationName;//= new JPanel();
  /*protected*/ QWidget* pLocos;//= new JPanel();
  /*protected*/ QWidget* pPickupLocos;//= new JPanel();
  /*protected*/ QWidget* pSetoutLocos;//= new JPanel();
  /*protected*/ QWidget* pPickups;//= new JPanel();
  /*protected*/ QWidget* pSetouts;//= new JPanel();
  /*protected*/ QWidget* pWorkPanes;//= new JPanel(); // place car pick ups and set outs side by side using two columns
  /*protected*/ QWidget* pMoves;//= new JPanel();
  /*protected*/ QGroupBox* pStatus;//= new JPanel();
  /*protected*/ QGroupBox* pButtons;//= new JPanel();

  // check boxes
  /*protected*/ QHash<QString, QCheckBox*> checkBoxes;//= new Hashtable<>();
  /*protected*/ QList<RollingStock*> rollingStock;//= new ArrayList<>();
  // flags
  /*protected*/ bool isSetMode;//= false; // when true, cars that aren't selected (checkbox) can be "set"
  /*protected*/ void initialize();
  /*protected*/ void setModifyButtonText();
  /*protected*/ void removePropertyChangeListerners();
  /*protected*/ void updateLocoPanes(RouteLocation* rl);
  /*protected*/ QString getStatus(RouteLocation* rl, bool isManifest);
  /*protected*/ void updateComplete();
  /*protected*/ void check();
  /*protected*/ void selectCheckboxes(bool enable);
  /*protected*/ void checkBoxActionPerformed(QWidget* ae);
  /*protected*/ void blockCars(RouteLocation* rl, bool isManifest);
  /*protected*/ void setLabelFont(QLabel* label);
  /*Protected*/ QWidget* addSet(Car* car);

 friend class YardmasterPanel;
 friend class TrainConductorPanel;
 friend class YardmasterByTrackPanel;
 };
}
#endif // COMMONCONDUCTORYARDMASTERPANEL_H
