#include "commonconductoryardmasterpanel.h"
#include "location.h"
#include "train.h"
#include "enginemanager.h"
#include "trainmanager.h"
#include "carmanager.h"
#include "traincommon.h"
#include <QLabel>
#include <QScrollArea>
#include "rollingstock.h"
#include <QBoxLayout>
#include <QGroupBox>
#include "control.h"
#include "jbutton.h"
#include <jtextarea.h>
#include "gridbaglayout.h"
#include "setup.h"
#include "engine.h"
#include "routelocation.h"
#include <QCheckBox>
#include "car.h"
#include "route.h"
#include "track.h"
#include "carsetframe.h"
#include "htmltextedit.h"
#include "joptionpane.h"
#include "carstableframe.h"
#include "instancemanager.h"
#include "borderfactory.h"
#include "enginesetframe.h"

namespace Operations
{
/**
 * Common elements for the Conductor and Yardmaster Frames.
 *
 * @author Dan Boudreau Copyright (C) 2013
 * @version $Revision: 18630 $
 */
///*public*/ class CommonConductorYardmasterPanel extends OperationsPanel implements PropertyChangeListener {

 /**
  *
  */
 //private static /*final*/ long serialVersionUID = 4524775039808820663L;
 /*protected*/ /*static*/ /*final*/ QString CommonConductorYardmasterPanel::Tab = "     "; // used to space out headers
 /*protected*/ /*static*/ /*final*/ QString CommonConductorYardmasterPanel::Space = " "; // used to pad out panels



 /*public*/ CommonConductorYardmasterPanel::CommonConductorYardmasterPanel(QWidget* parent)
  : OperationsPanel(parent)
 {
  //super();
  log = new Logger("CommonConductorYardmasterPanel");
  _location = NULL;
  _train = NULL;

  trainManager = ((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"));
  engManager = ((EngineManager*)InstanceManager::getDefault("Operations::EngineManager"));
  carManager = ((CarManager*)InstanceManager::getDefault("Operations::CarManager"));
  trainCommon = new TrainCommon();

  // labels
  textRailRoadName = new QLabel();
   textTrainDescription = new QLabel();
   textLocationName = new QLabel();
   textStatus = new QLabel();

   // major buttons
   selectButton = new QPushButton(tr("Select"));
   clearButton = new QPushButton(tr("Clear"));
   modifyButton = new QPushButton(tr("Modify")); // see setModifyButtonText()

   moveButton = new QPushButton(tr("Move"));

   // text panes
   textLocationCommentPane = new HtmlTextEdit();
   textTrainCommentPane = new HtmlTextEdit();
   textTrainRouteCommentPane = new HtmlTextEdit();
   textTrainRouteLocationCommentPane = new HtmlTextEdit();

   // panels
   pRailRoadName = new JPanel();
   pTrainDescription = new JPanel();
   pLocos = new QWidget();
   pPickupLocos = new QWidget();
   pSetoutLocos = new QWidget();
   pPickups = new QWidget();
   pSetouts = new QWidget();
   pWorkPanes = new QWidget(); // place car pick ups and set outs side by side using two columns
   pMoves = new QWidget();

   // check boxes
   checkBoxes =  QHash<QString, QCheckBox*>();
   rollingStock =  QList<RollingStock*>();

   // flags
   isSetMode = false; // when true, cars that aren't selected (checkbox) can be "set"
   csf = NULL;

 }

 /*public*/ void CommonConductorYardmasterPanel::initComponents()
 {
  //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
  thisLayout = new QVBoxLayout(this);

  locoPaneFrame = new JPanel;
  locoPaneFrame->setLayout(new QVBoxLayout);
  locoPane = new QScrollArea(); //JScrollPane(pLocos);
  locoPane->setWidgetResizable(true);
  locoPaneFrame->layout()->addWidget(locoPane);
  pLocos = new QWidget;
  //pLocos->setLayout(new QVBoxLayout); // is set later!
  locoPaneFrame->layout()->addWidget(locoPane);
  locoPaneFrame->setBorder(BorderFactory::createTitledBorder(tr("Engines")));

//        pickupPane = new JScrollPane(pPickups);
//        pickupPane->setBorder(BorderFactory.createTitledBorder(tr("Pickup")));
  pickupPaneFrame = new JPanel;
  pickupPaneFrame->setLayout(new QVBoxLayout);
  pickupPane = new QScrollArea(); //JScrollPane(pLocos);
  pickupPaneFrame->layout()->addWidget(pickupPane);
  pPickups = new QWidget;
  pPickups->setLayout(new QVBoxLayout);
  pickupPane->setWidgetResizable(true);
  pickupPaneFrame->setBorder(BorderFactory::createTitledBorder(tr("Pickup")));
//        setoutPane = new JScrollPane(pSetouts);
//        setoutPane->setBorder(BorderFactory.createTitledBorder(tr("Setut")));
  setoutPaneFrame = new JPanel;
  setoutPaneFrame->setLayout(new QVBoxLayout);
  setoutPane = new QScrollArea(); //JScrollPane(pLocos);
  setoutPane->setWidgetResizable(true);
  setoutPaneFrame->layout()->addWidget(setoutPane);
  pSetouts = new QWidget;
  pSetouts->setLayout(new QVBoxLayout);
  setoutPaneFrame->setBorder(BorderFactory::createTitledBorder(tr("Set out")));

//        movePane = new JScrollPane(pMoves);
//        movePane->setBorder(BorderFactory.createTitledBorder(tr("LocalMoves")));
  movePaneFrame = new JPanel();
  movePaneFrame->setLayout(new QVBoxLayout);
  movePane = new QScrollArea;
  movePane->setWidgetResizable(true);
  pMoves = new QWidget;
  pMoves->setLayout(new QVBoxLayout);
  movePaneFrame->setBorder(BorderFactory::createTitledBorder(tr("Local moves")));

  // Set up the panels
  pPickupLocos->setLayout(new QVBoxLayout);//(pPickupLocos, BoxLayout.Y_AXIS));
  pSetoutLocos->setLayout(new QVBoxLayout);//(pSetoutLocos, BoxLayout.Y_AXIS));
  pPickups->setLayout(new QVBoxLayout);//(pPickups, BoxLayout.Y_AXIS));
  pSetouts->setLayout(new QVBoxLayout);//(pSetouts, BoxLayout.Y_AXIS));
  pMoves->setLayout(new QVBoxLayout);//(pMoves, BoxLayout.Y_AXIS));

  // railroad name
  pRailRoadName->setBorder(BorderFactory::createTitledBorder(tr("Railroad Name")));
  pRailRoadName->setLayout(new QHBoxLayout);
  pRailRoadName->layout()->addWidget(textRailRoadName);

  // location name
  pLocationName->setBorder(BorderFactory::createTitledBorder(tr("Location")));
  pLocationName->setLayout(new QHBoxLayout);
  pLocationName->layout()->addWidget(textLocationName);

  // location comment
  textLocationCommentGB = new JPanel;
  textLocationCommentGB->setBorder(BorderFactory::createTitledBorder(tr("Location Comment")));
  textLocationCommentGB->setLayout(new QVBoxLayout);
  textLocationCommentGB->layout()->addWidget(textLocationCommentPane);
  //textLocationCommentPane->setBackground(NULL);
  textLocationCommentPane->setEditable(false);
  textLocationCommentPane->setMaximumSize(QSize(2000, 200));

  // train description
  pTrainDescription->setBorder(BorderFactory::createTitledBorder(tr("Description")));
  pTrainDescription->setLayout(new QHBoxLayout);
  pTrainDescription->layout()->addWidget(textTrainDescription);

  // train comment
  textTrainCommentGB = new JPanel;
  textTrainCommentGB->setBorder(BorderFactory::createTitledBorder(tr("Train Comment")));
  //textTrainCommentPane->setBackground(NULL);
  textTrainCommentGB->setLayout(new QVBoxLayout);
  textTrainCommentGB->layout()->addWidget(textTrainCommentPane);
  textTrainCommentPane->setEditable(false);
  textTrainCommentPane->setMaximumSize(QSize(2000, 200));

  // train route comment
  textTrainRouteCommentGB = new JPanel;
  textTrainRouteCommentGB->setBorder(BorderFactory::createTitledBorder(tr("Route Comment")));
  textTrainRouteCommentGB->setLayout(new QVBoxLayout);
  //textTrainRouteCommentPane->setBackground(NULL);
  textTrainRouteCommentGB->layout()->addWidget(textTrainRouteCommentPane);
  textTrainRouteCommentPane->setEditable(false);
  textTrainRouteCommentPane->setMaximumSize(QSize(2000, 200));

  // train route location comment
  textTrainRouteLocationCommentGB = new JPanel;
  textTrainRouteLocationCommentGB->setBorder(BorderFactory::createTitledBorder(tr("Location")));
  textTrainRouteLocationCommentGB->setLayout(new QVBoxLayout);
  //textTrainRouteLocationCommentPane->setBackground(NULL);
  textTrainRouteLocationCommentGB->layout()->addWidget(textTrainRouteLocationCommentPane);
  textTrainRouteLocationCommentPane->setEditable(false);
  textTrainRouteLocationCommentPane->setMaximumSize(QSize(2000, 200));

  // row 12
  if ((sizeHint().width() > Control::panelWidth1025 && Setup::isTabEnabled())
          || (sizeHint().width() > Control::panelWidth1025 - 200 && !Setup::isTabEnabled())) {
      pLocos->setLayout(new QHBoxLayout); //(pLocos, BoxLayout.X_AXIS));
      pWorkPanes->setLayout(new QHBoxLayout);//(pWorkPanes, BoxLayout.X_AXIS));
  } else {
      pLocos->setLayout(new QVBoxLayout);//(pLocos, BoxLayout.Y_AXIS));
      pWorkPanes->setLayout(new QVBoxLayout);//(pWorkPanes, BoxLayout.Y_AXIS));
  }

  pLocos->layout()->addWidget(pPickupLocos);
  pLocos->layout()->addWidget(pSetoutLocos);
  pickupPane->setWidget(pPickups);
  pWorkPanes->layout()->addWidget(pickupPaneFrame);
  setoutPane->setWidget(pSetouts);
  pWorkPanes->layout()->addWidget(setoutPaneFrame);

  // row 13
  pStatus->setLayout(new GridBagLayout());
  pStatus->setBorder(BorderFactory::createTitledBorder(""));
  addItem(pStatus, textStatus, 0, 0);

  // row 14
  pButtons->setLayout(new GridBagLayout());
  pButtons->setBorder(BorderFactory::createTitledBorder(tr("Work")));
  addItem(pButtons, selectButton, 0, 0);
  addItem(pButtons, clearButton, 1, 0);
  addItem(pButtons, modifyButton, 2, 0);

  // setup buttons
  addButtonAction(selectButton);
  addButtonAction(clearButton);
  addButtonAction(modifyButton);

  setMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500));
 }

 // Select, Clear, and Set Buttons
 //@Override
 /*public*/ void CommonConductorYardmasterPanel::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == selectButton) {
         selectCheckboxes(true);
     }
     if (source == clearButton) {
         selectCheckboxes(false);
     }
     if (source == modifyButton)
     {
      isSetMode = !isSetMode; // toggle setMode
      update();
      // ask if user wants to add cars to train
      if (isSetMode) {
          addCarToTrain();
      }
     }
     check();
 }

 /*protected*/ void CommonConductorYardmasterPanel::initialize() {
     removePropertyChangeListerners();
     //pPickupLocos->clear();
     QLayoutItem* item;
     while ( ( item = pPickupLocos->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     //pSetoutLocos->clear();
     while ( ( item = pSetoutLocos->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     //pPickups->clear();
     while ( ( item = pPickups->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     //pSetouts->clear();
     while ( ( item = pSetouts->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     //pMoves->clear();
     while ( ( item = pMoves->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }

     // turn everything off and re-enable if needed
     pWorkPanes->setVisible(false);
     //pickupPane->setVisible(false);
     pickupPaneFrame->setVisible(false);
     //setoutPane->setVisible(false);
     setoutPaneFrame->setVisible(false);
     //locoPane->setVisible(false);
     locoPaneFrame->setVisible(false);
     pPickupLocos->setVisible(false);
     pSetoutLocos->setVisible(false);
     //movePane->setVisible(false);
     movePaneFrame->setVisible(false);

     textTrainRouteLocationCommentGB->setVisible(false);

     setModifyButtonText();
 }

 /*protected*/ void CommonConductorYardmasterPanel::updateComplete() {
//     pPickupLocos->repaint();
//     pSetoutLocos->repaint();
//     pPickups->repaint();
//     pSetouts->repaint();
//     pMoves->repaint();

     pPickupLocos->update();
     pSetoutLocos->update();
     pPickups->update();
     pSetouts->update();
     pMoves->update();

     selectButton->setEnabled(checkBoxes.size() > 0);
     clearButton->setEnabled(checkBoxes.size() > 0);
     check();

     log->debug("update complete");
 }

 /*private*/ void CommonConductorYardmasterPanel::addCarToTrain()
 {
  if (JOptionPane::showConfirmDialog(this,
          tr("Do you want to add cars to train (%1)?").arg(_train->getName()),
          tr("Add cars to train?"),
          JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION) {
      new CarsTableFrame(false, textLocationName->text(), NULL);
  }
 }

 // action for set button for a car, opens the set car window
 /*public*/ void CommonConductorYardmasterPanel::carSetButtonActionPerfomed(QWidget* ae) {
     QString name = ((JButton*) ae)->objectName();
     log->debug("Set button for car " + name);
     Car* car = carManager->getById(name);
     if (csf != NULL) {
         csf->dispose();
     }
     csf = new CarSetFrame();
     csf->initComponents();
     csf->loadCar(car);
     // csf->setTitle(tr("TitleCarSet"));
     csf->setVisible(true);
     csf->setExtendedState(JFrame::NORMAL);
 }

 // action for set button for an engine, opens the set engine window
 /*public*/ void CommonConductorYardmasterPanel::engineSetButtonActionPerfomed(QWidget* ae) {
  QString name = ((JButton*) ae)->objectName();
     log->debug(tr("Set button for loco %1").arg(name));
     Engine* eng = (Engine*)engManager->getById(name);
     if (esf != nullptr) {
         esf->dispose();
     }
     esf = new EngineSetFrame();
     esf->initComponents();
     esf->loadEngine(eng);
 }

 // confirm that all work is done
 //@Override
 /*protected*/ void CommonConductorYardmasterPanel::checkBoxActionPerformed(QWidget* ae) {
     check();
 }

 // Determines if all car checkboxes are selected. Disables the Set button if
 // all checkbox are selected.
 /*protected*/ void CommonConductorYardmasterPanel::check() {
     QListIterator<QCheckBox*> en(checkBoxes.values());
     while (en.hasNext()) {
         QCheckBox* checkBox = en.next();
         if (!checkBox->isChecked()) {
             // log->debug("Checkbox (" + checkBox.getText() + ") isn't selected ");
             moveButton->setEnabled(false);
             modifyButton->setEnabled(true);
             return;
         }
     }
     // all selected, work done!
     moveButton->setEnabled(_train != NULL && _train->isBuilt());
     modifyButton->setEnabled(false);
     isSetMode = false;
     setModifyButtonText();
 }

 /*protected*/ void CommonConductorYardmasterPanel::selectCheckboxes(bool enable) {
     QListIterator<QCheckBox*> en = checkBoxes.values();
     while (en.hasNext()) {
         QCheckBox* checkBox = en.next();
         checkBox->setChecked(enable);
     }
     isSetMode = false;
 }

 /*protected*/ void CommonConductorYardmasterPanel::updateLocoPanes(RouteLocation* rl) {
     if (Setup::isPrintHeadersEnabled()) {
         QLabel* header = new QLabel(Tab + trainCommon->getPickupEngineHeader());
         setLabelFont(header);
         pPickupLocos->layout()->addWidget(header);
         QLabel* headerDrop = new QLabel(Tab + trainCommon->getDropEngineHeader());
         setLabelFont(headerDrop);
         pSetoutLocos->layout()->addWidget(headerDrop);
     }
     // check for locos
     QList<Engine*>* engList = engManager->getByTrainBlockingList(_train);
     foreach (Engine* engine, *engList) {
         if (engine->getRouteLocation() == rl && engine->getTrack() != NULL) {
             //locoPane->setVisible(true);
          locoPaneFrame->setVisible(true);
             pPickupLocos->setVisible(true);
             rollingStock.append(engine);
             engine->SwingPropertyChangeSupport::addPropertyChangeListener(this);
             QCheckBox* checkBox = new QCheckBox(trainCommon->pickupEngine(engine));
             setCheckBoxFont(checkBox);
             pPickupLocos->layout()->addWidget(checkBox);
         }
         if (engine->getRouteDestination() == rl) {
             //locoPane->setVisible(true);
             locoPaneFrame->setVisible(true);
             pSetoutLocos->setVisible(true);
             rollingStock.append(engine);
             engine->SwingPropertyChangeSupport::addPropertyChangeListener(this);
             QCheckBox* checkBox = new QCheckBox(trainCommon->dropEngine(engine));
             setCheckBoxFont(checkBox);
             pSetoutLocos->layout()->addWidget(checkBox);
         }
     }
     // pad the panels in case the horizontal scroll bar appears
     pPickupLocos->layout()->addWidget(new QLabel(Space));
     pSetoutLocos->layout()->addWidget(new QLabel(Space));
 }

 /**
  * Block cars by track (optional), then pick up and set out for each
  * location in a train's route. This shows each car with a check box or with
  * a set button. The set button is displayed when the checkbox isn't
  * selected and the display is in "set" mode. If the car is a utility. Show
  * the number of cars that have the same attributes, and not the car's road
  * and number. Each car is displayed only once in one of three panes. The
  * three panes are pick up, set out, or local move. To keep track of each
  * car and which pane to use, they are placed in the list "rollingStock"
  * with the prefix "p", "s" or "m" and the car's unique id.
  *
  * @param rl
  * @param isManifest
  */
 /*protected*/ void CommonConductorYardmasterPanel::blockCars(RouteLocation* rl, bool isManifest)
 {
  if (Setup::isPrintHeadersEnabled())
  {
      QLabel* header = new QLabel(Tab
              + trainCommon->getPickupCarHeader(isManifest, !TrainCommon::IS_TWO_COLUMN_TRACK));
      setLabelFont(header);
      pPickups->layout()->addWidget(header);
      header = new QLabel(Tab + trainCommon->getDropCarHeader(isManifest, !TrainCommon::IS_TWO_COLUMN_TRACK));
      setLabelFont(header);
      pSetouts->layout()->addWidget(header);
      header = new QLabel(Tab + trainCommon->getLocalMoveHeader(isManifest));
      setLabelFont(header);
      pMoves->layout()->addWidget(header);
  }
  QList<Track*> tracks = rl->getLocation()->getTracksByNameList(NULL);
  QList<RouteLocation*>* routeList = _train->getRoute()->getLocationsBySequenceList();
  QList<Car*>* carList = carManager->getByTrainDestinationList(_train);
  foreach (Track* track, tracks)
  {
   foreach (RouteLocation* rld, *routeList)
   {
    foreach (Car* car, *carList)
    {
     // determine if car is a pick up from the right track
     if (car->getTrack() != NULL
             && (!Setup::isSortByTrackEnabled() || car->getTrackName()==(track->getName()))
             && car->getRouteLocation() == rl && car->getRouteDestination() == rld
             && car->getRouteDestination() != rl)
     {
      // yes we have a pick up
      pWorkPanes->setVisible(true);
      pickupPane->setVisible(true);
      if (!rollingStock.contains(car))
      {
          rollingStock.append(car);
          car->SwingPropertyChangeSupport::addPropertyChangeListener(this);
      }
      // did we already process this car?
      if (checkBoxes.contains("p" + car->getId()))
      {
          if (isSetMode && !checkBoxes.value("p" + car->getId())->isChecked()) {
              // change to set button so user can remove car from train
              pPickups->layout()->addWidget(addSet(car));
          } else {
              pPickups->layout()->addWidget(checkBoxes.value("p" + car->getId()));
          }
          // figure out the checkbox text, either single car or utility
      }
      else
      {
       QString text;
       if (car->isUtility())
       {
        text = trainCommon->pickupUtilityCars(carList, car, isManifest, !TrainCommon::IS_TWO_COLUMN_TRACK);
        if (text == NULL)
        {
         continue; // this car type has already been processed
        }
       }
       else
       {
        text = trainCommon->pickupCar(car, isManifest, !TrainCommon::IS_TWO_COLUMN_TRACK);
       }
       QCheckBox* checkBox = new QCheckBox(text);
       setCheckBoxFont(checkBox);
       addCheckBoxAction(checkBox);
       pPickups->layout()->addWidget(checkBox);
       checkBoxes.insert("p" + car->getId(), checkBox);
      }
     }
    }
   }
   // set outs and local moves
   foreach (Car* car, *carList)
   {
    if (car->getRouteDestination() != rl || car->getDestinationTrack() == NULL)
    {
        continue;
    }
    // car in train if track NULL, second check is for yard master window
    if (car->getTrack() == NULL || car->getTrack() != NULL && (car->getRouteLocation() != rl))
    {
        if (Setup::isSortByTrackEnabled() && car->getDestinationTrack()->getName()!=(track->getName()))
        {
            continue;
        }
        // we have set outs
        pWorkPanes->setVisible(true);
        //setoutPane->setVisible(true);
        setoutPaneFrame->setVisible(true);
        if (!rollingStock.contains(car)) {
            rollingStock.append(car);
            car->SwingPropertyChangeSupport::addPropertyChangeListener(this);
        }
        if (checkBoxes.contains("s" + car->getId())) {
            if (isSetMode && !checkBoxes.value("s" + car->getId())->isChecked()) {
                // change to set button so user can remove car from train
                pSetouts->layout()->addWidget(addSet(car));
            } else {
                pSetouts->layout()->addWidget(checkBoxes.value("s" + car->getId()));
            }
        } else {
            QString text;
            if (car->isUtility()) {
//                         text = trainCommon->setoutUtilityCars(carList, car, !TrainCommon::LOCAL, isManifest);
                if (text == NULL) {
                    continue; // this car type has already been processed
                }
            } else {
//                         text = trainCommon->dropCar(car, isManifest, !TrainCommon::IS_TWO_COLUMN_TRACK);
            }
            QCheckBox* checkBox = new QCheckBox(text);
            setCheckBoxFont(checkBox);
            addCheckBoxAction(checkBox);
            pSetouts->layout()->addWidget(checkBox);
            checkBoxes.insert("s" + car->getId(), checkBox);
        }
        // local move?
    }
    else if (car->getTrack() != NULL && car->getRouteLocation() == rl
            && (!Setup::isSortByTrackEnabled() || car->getTrack()->getName()==(track->getName())))
    {
     //movePane->setVisible(true);
     movePaneFrame->setVisible(true);
     if (!rollingStock.contains(car)) {
         rollingStock.append(car);
         //car.addPropertyChangeListener(this);
     }
     if (checkBoxes.contains("m" + car->getId())) {
         if (isSetMode && !checkBoxes.value("m" + car->getId())->isChecked()) {
             // change to set button so user can remove car from train
             pMoves->layout()->addWidget(addSet(car));
         } else {
             pMoves->layout()->addWidget(checkBoxes.value("m" + car->getId()));
         }
     }
     else
     {
      QString text;
      if (car->isUtility())
      {
       text = trainCommon->setoutUtilityCars(carList, car, TrainCommon::LOCAL, isManifest);
       if (text == NULL)
       {
           continue; // this car type has already been processed
       }
      }
      else
      {
       text = trainCommon->localMoveCar(car, isManifest);
      }
      QCheckBox* checkBox = new QCheckBox(text);
      setCheckBoxFont(checkBox);
      addCheckBoxAction(checkBox);
      pMoves->layout()->addWidget(checkBox);
      checkBoxes.insert("m" + car->getId(), checkBox);
     }
    }
   }
   // if not sorting by track, we're done
   if (!Setup::isSortByTrackEnabled()) {
       break;
   }
  }
  // pad the panels in case the horizontal scroll bar appears
  pPickups->layout()->addWidget(new QLabel(Space));
  pSetouts->layout()->addWidget(new QLabel(Space));
  pMoves->layout()->addWidget(new QLabel(Space));
 }

 // replace the car or engine checkbox and text with only the road and number and
 // a Set button
 /*Protected*/ JPanel* CommonConductorYardmasterPanel::addSet(RollingStock* rs) {
     JPanel* pSet = new JPanel();
     pSet->setLayout(new GridBagLayout());
     JButton* setButton = new JButton(tr("Set"));
     setButton->setObjectName(rs->getId());
//     setButton.addActionListener((ActionEvent e) -> {
     connect(setButton, &JButton::clicked, [=]{
      if (qobject_cast<Car*>(rs)) {
          carSetButtonActionPerfomed(setButton);
      } else {
          engineSetButtonActionPerfomed(setButton);
      }
     });
     JLabel* label = new JLabel(TrainCommon::padString(rs->toString(),
             Control::max_len_string_attibute + Control::max_len_string_road_number));
     setLabelFont(label);
     addItem(pSet, label, 0, 0);
     addItemLeft(pSet, setButton, 1, 0);
//     pSet->setAlignmentX(/*LEFT_ALIGNMENT*/Qt::AlignLeft);
     return pSet;
}

 /*protected*/ void CommonConductorYardmasterPanel::setCheckBoxFont(QCheckBox* checkBox) {
     if (Setup::isTabEnabled()) {
         QFont font = QFont(Setup::getFontName(),checkBox->font().pointSize());//new Font(Setup::getFontName(), Font.PLAIN, checkBox.getFont().getSize());
         checkBox->setFont(font);
     }
 }

 /*protected*/ void CommonConductorYardmasterPanel::setLabelFont(QLabel* label) {
     if (Setup::isTabEnabled()) {
         QFont font = QFont(Setup::getFontName(),label->font().pointSize()); //Font(Setup::getFontName(), Font.PLAIN, label.getFont().getSize());
         label->setFont(font);
     }
 }

 /*protected*/ void CommonConductorYardmasterPanel::setModifyButtonText() {
     if (isSetMode) {
         modifyButton->setText(tr("Done"));
     } else {
         modifyButton->setText(tr("Set"));
     }
 }

 // returns one of two possible departure strings for a train
 /*protected*/ QString CommonConductorYardmasterPanel::getStatus(RouteLocation* rl, bool isManifest) {
     if (rl == _train->getRoute()->getTerminatesRouteLocation()) {
//         return MessageFormat.format(TrainManifestText.getStringTrainTerminates(), new Object[]{_train
//             .getTrainTerminatesName()});
      return tr("Train terminates in (%1)").arg(_train->getTrainTerminatesName());
     }
     if (rl != _train->getCurrentLocation() && _train->getExpectedArrivalTime(rl)==(Train::ALREADY_SERVICED)) {
//         return MessageFormat.format(TrainSwitchListText.getStringTrainDone(), new Object[]{_train
//             .getName()});
      return tr("Train (%1) has serviced this location").arg(_train->getName());
     }
     if (Setup::isPrintLoadsAndEmptiesEnabled()) {
         int emptyCars = _train->getNumberEmptyCarsInTrain(rl);
         QString text;
         if (isManifest) {
             text = tr("Train departs %1 %2bound with %3 loads, %4 empties, %5 %6, %7 tons");
             //TrainManifestText.getStringTrainDepartsLoads();
         } else {
             text = tr("Train departs %1 %2bound with %3 loads, %4 empties, %5 %6, %7 tons");
             //TrainSwitchListText.getStringTrainDepartsLoads();
         }
         return QString(text).arg(TrainCommon::splitString(rl->getName())).arg(
             rl->getTrainDirectionString()).arg(_train->getNumberCarsInTrain(rl) - emptyCars).arg(emptyCars).arg(
             _train->getTrainLength(rl)).arg(Setup::getLengthUnit().toLower()).arg(_train->getTrainWeight(rl)).arg(
             _train->getTrainTerminatesName()).arg(_train->getName());
     } else {
         QString text;
         if (isManifest) {
             text = tr("Train departs %1 %2bound with %3 cars, %4 %5, %6 tons"); //TrainManifestText.getStringTrainDepartsCars();
         } else {
             text = tr("Train departs %1 %2bound with %3 cars, %4 %5, %6 tons");//TrainSwitchListText.getStringTrainDepartsCars();
         }
         return QString(text).arg(TrainCommon::splitString(rl->getName())).arg(
             rl->getTrainDirectionString()).arg(_train->getNumberCarsInTrain(rl)).arg(_train->getTrainLength(rl)).arg(
             Setup::getLengthUnit().toLower()).arg(_train->getTrainWeight(rl)).arg(_train->getTrainTerminatesName()).arg(
             _train->getName());
     }
 }

 /*protected*/ void CommonConductorYardmasterPanel::removeCarFromList(Car* car) {
     checkBoxes.remove("p" + car->getId());
     checkBoxes.remove("s" + car->getId());
     checkBoxes.remove("m" + car->getId());
     log->debug(tr("Car (%1) removed from list").arg(car->toString()));
     if (car->isUtility()) {
         clearAndUpdate(); // need to recalculate number of utility cars
     }
 }

 /*protected*/ void CommonConductorYardmasterPanel::clearAndUpdate() {
     trainCommon->clearUtilityCarTypes(); // reset the utility car counts
     checkBoxes.clear();
     isSetMode = false;
     update();
 }

 // to be overridden
 /*protected*/ /*abstract*/ void CommonConductorYardmasterPanel::update() {}

 /*protected*/ void CommonConductorYardmasterPanel::removePropertyChangeListerners() {
//     rollingStock.stream().forEach((rs) -> {
//         rs.removePropertyChangeListener(this);
//     });
  foreach (RollingStock* rs, rollingStock) {
  rs->removePropertyChangeListener(this);
  }
  rollingStock.clear();
 }

 //@Override
 /*public*/ void CommonConductorYardmasterPanel::propertyChange(PropertyChangeEvent* e) {
     // if (Control.showProperty && log->isDebugEnabled())
log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
      ->getNewValue().toString()));
 }

}
