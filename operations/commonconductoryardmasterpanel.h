#ifndef COMMONCONDUCTORYARDMASTERPANEL_H
#define COMMONCONDUCTORYARDMASTERPANEL_H
#include "operationspanel.h"
#include "appslib_global.h"
#include "propertychangelistener.h"
#include "jpanel.h"

class QVBoxLayout;
class QGroupBox;
//class JTextPane;
class QScrollArea;
class PropertyChangeEvent;
class QLabel;
namespace Operations
{
 class EngineSetFrame;
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
 class APPSLIBSHARED_EXPORT CommonConductorYardmasterPanel : public OperationsPanel, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  CommonConductorYardmasterPanel(QWidget* parent = 0);
  /*public*/ void initComponents();
  QObject* self() override {return (QObject*)this; }

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;
  /*public*/ void buttonActionPerformed(QWidget* ae) override;
  /*public*/ void carSetButtonActionPerfomed(QWidget* ae);
  /*public*/ void engineSetButtonActionPerfomed(QWidget* ae);

 private:
  Logger* log;
  CarSetFrame* csf = nullptr;
  QVBoxLayout* thisLayout;
  /*private*/ void addCarToTrain();
  EngineSetFrame* esf = nullptr;

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

  JPanel* locoPaneFrame;
  /*protected*/ QScrollArea* locoPane;
  JPanel* pickupPaneFrame;
  /*protected*/ QScrollArea* pickupPane;
  JPanel* setoutPaneFrame;
  /*protected*/ QScrollArea* setoutPane;
  JPanel* movePaneFrame;
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
  JPanel* textLocationCommentGB;
  /*protected*/ HtmlTextEdit* textLocationCommentPane;//= new JTextPane();
  JPanel* textTrainCommentGB;
  /*protected*/ HtmlTextEdit* textTrainCommentPane;//= new JTextPane();
  JPanel* textTrainRouteCommentGB;
  /*protected*/ HtmlTextEdit* textTrainRouteCommentPane;//= new JTextPane();
  JPanel* textTrainRouteLocationCommentGB;
  /*protected*/ HtmlTextEdit* textTrainRouteLocationCommentPane;//= new JTextPane();

  // panels
  /*protected*/ JPanel* pRailRoadName;// = new JPanel();
  /*protected*/ JPanel* pTrainDescription;//= new JPanel();
  /*protected*/ JPanel* pLocationName = new JPanel();
  /*protected*/ QWidget* pLocos;//= new JPanel();
  /*protected*/ QWidget* pPickupLocos;//= new JPanel();
  /*protected*/ QWidget* pSetoutLocos;//= new JPanel();
  /*protected*/ QWidget* pPickups;//= new JPanel();
  /*protected*/ QWidget* pSetouts;//= new JPanel();
  /*protected*/ QWidget* pWorkPanes;//= new JPanel(); // place car pick ups and set outs side by side using two columns
  /*protected*/ QWidget* pMoves;//= new JPanel();
  /*protected*/ JPanel* pStatus= new JPanel();
  /*protected*/ JPanel* pButtons= new JPanel();

  // check boxes
  /*protected*/ QHash<QString, QCheckBox*> checkBoxes;//= new Hashtable<>();
  /*protected*/ QList<RollingStock*> rollingStock;//= new ArrayList<>();
  // flags
  /*protected*/ bool isSetMode;//= false; // when true, cars that aren't selected (checkbox) can be "set"
  /*protected*/ void initialize();
  /*protected*/ void setModifyButtonText();
  /*protected*/ void removeCarFromList(Car* car);
  /*protected*/ void removePropertyChangeListerners();
  /*protected*/ void updateLocoPanes(RouteLocation* rl);
  /*protected*/ QString getStatus(RouteLocation* rl, bool isManifest);
  /*protected*/ void updateComplete();
  /*protected*/ void check();
  /*protected*/ void selectCheckboxes(bool enable);
  /*protected*/ void checkBoxActionPerformed(QWidget* ae);
  /*protected*/ void blockCars(RouteLocation* rl, bool isManifest);
  /*protected*/ void setLabelFont(QLabel* label);
  /*Protected*/ JPanel* addSet(RollingStock *car);
  /*protected*/ /*abstract*/ virtual void update();
  /*protected*/ void clearAndUpdate();

 friend class YardmasterPanel;
 friend class TrainConductorPanel;
 friend class YardmasterByTrackPanel;
 };
}
#endif // COMMONCONDUCTORYARDMASTERPANEL_H
