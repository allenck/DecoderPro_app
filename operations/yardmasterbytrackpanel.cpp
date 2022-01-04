#include "yardmasterbytrackpanel.h"
#include "loggerfactory.h"
#include <QBoxLayout>
#include <QGroupBox>
#include "htmltextedit.h"
#include "location.h"
#include "jcombobox.h"
#include <QPushButton>
#include "borderfactory.h"
#include <QScrollArea>
#include <QLabel>
#include "setup.h"
#include "vptr.h"
#include "track.h"
#include "trainmanager.h"
#include "trainswitchlisttext.h"
#include "engine.h"
#include "enginemanager.h"
#include "train.h"
#include "traincommon.h"
#include "car.h"
#include "carmanager.h"
#include "routelocation.h"
#include "locationmanager.h"
#include "routemanager.h"
#include "route.h"
#include "carroads.h"
#include "carcolors.h"
#include "cartypes.h"
#include "carloads.h"
#include "instancemanager.h"
#include <QCheckBox>
#include "control.h"
#include "jpanel.h"
#include "borderfactory.h"

using namespace Operations;
/**
 * Yardmaster frame by track-> Shows work at one location listed by track->
 *
 * @author Dan Boudreau Copyright (C) 2015
 *
 */
// /*public*/ class YardmasterByTrackPanel extends CommonConductorYardmasterPanel {

/*protected*/ /*static*/ /*final*/ bool YardmasterByTrackPanel::IS_MANIFEST = false;


/*public*/ YardmasterByTrackPanel::YardmasterByTrackPanel(QWidget* parent)  {
    //this(NULL);
common();
}

void YardmasterByTrackPanel::common()
{
 _track = NULL;

// text panes
 textSwitchListCommentPane = new HtmlTextEdit();
 textTrackCommentPane = new HtmlTextEdit();
 textTrackCommentWorkPane = new HtmlTextEdit();

 // combo boxes
 trackComboBox = new JComboBox(); // <Track>

 // buttons
 nextButton = new QPushButton(tr("Next"));

 // panel
 pTrack = new QWidget();
 pTrackLayout = new QVBoxLayout(pTrack);
}

/*public*/ YardmasterByTrackPanel::YardmasterByTrackPanel(Location* location, QWidget* parent) : CommonConductorYardmasterPanel(parent){
    //super();
 common();
    initComponents();

    // this window doesn't use the set button
    modifyButton->setVisible(false);

    _location = location;

    JPanel* textSwitchListCommentFrame = new JPanel();
    textSwitchListCommentFrame->setBorder(BorderFactory::createTitledBorder(tr("Comment")));
    textSwitchListCommentFrame->setLayout(new QVBoxLayout());
    //textSwitchListCommentPane->setBorder(BorderFactory::createTitledBorder(tr("Comment")));
//    textSwitchListCommentPane->setBackground(NULL);
    textSwitchListCommentPane->setEditable(false);
    textSwitchListCommentPane->setMaximumSize(QSize(2000, 200));

    JPanel* textTrackCommentFrame = new JPanel();
    textTrackCommentFrame->setLayout(new QVBoxLayout());
    textTrackCommentFrame->setBorder(BorderFactory::createTitledBorder(tr("Comment")));
//    textTrackCommentPane->setBackground(NULL);
    textTrackCommentPane->setEditable(false);
    textTrackCommentPane->setMaximumSize(QSize(2000, 200));

    JPanel* textTrackCommentWorkFrame = new JPanel();
    textTrackCommentWorkFrame->setLayout(new QVBoxLayout());
    textTrackCommentWorkFrame->setBorder(BorderFactory::createTitledBorder(tr("Comments")));
//    textTrackCommentWorkPane->setBackground(NULL);
    textTrackCommentWorkPane->setEditable(false);
    textTrackCommentWorkPane->setMaximumSize(QSize(2000, 200));

    JPanel* pTrackSelect = new JPanel();
    QVBoxLayout* pTrackSelectLayout = new QVBoxLayout(pTrackSelect);
    pTrackSelect->setBorder(BorderFactory::createTitledBorder(tr("Track")));
    pTrackSelectLayout->addWidget(trackComboBox);
    // add next button for web server
    pTrackSelectLayout->addWidget(nextButton);

    // work at this location by track
    pTrack->setLayout(new QVBoxLayout());//(pTrack, BoxLayout.Y_AXIS));
    pTrackPane = new QScrollArea();//JScrollPane(pTrack);
    pTrackPane->setWidget(pTrack);

    pLocationName->setMaximumSize(QSize(2000, 200));
    pTrackSelect->setMaximumSize(QSize(2000, 200));
    pButtons->setMaximumSize(QSize(2000, 200));

    thisLayout->addWidget(pLocationName);
    thisLayout->addWidget(textLocationCommentPane);
    textSwitchListCommentFrame->layout()->addWidget(textSwitchListCommentPane);
    thisLayout->addWidget(textSwitchListCommentFrame);
    thisLayout->addWidget(pTrackSelect);
    textTrackCommentFrame->layout()->addWidget(textTrackCommentPane);
    thisLayout->addWidget(textTrackCommentFrame);
    textTrackCommentWorkFrame->layout()->addWidget(textTrackCommentWorkPane);
    thisLayout->addWidget(textTrackCommentWorkFrame);
    thisLayout->addWidget(pTrackPane);
    thisLayout->addWidget(pButtons);

    if (_location != NULL) {
        textLocationName->setText(_location->getName());
        textLocationCommentPane->setText(_location->getComment());
        textLocationCommentPane->setVisible(_location->getComment() != (Location::NONE)
                && Setup::isPrintLocationCommentsEnabled());
        textSwitchListCommentPane->setText(_location->getSwitchListComment());
        textSwitchListCommentPane->setVisible(_location->getSwitchListComment() != (Location::NONE));
        updateTrackComboBox();
        _location->PropertyChangeSupport::addPropertyChangeListener(this);
    }

    update();

    addComboBoxAction(trackComboBox);
    addButtonAction(nextButton);

    setVisible(true);

}

// Select, Clear, and Next Buttons
//@Override
/*public*/ void YardmasterByTrackPanel::buttonActionPerformed(QWidget* source) {
    if (source == nextButton) {
        nextButtonAction();
    }
    CommonConductorYardmasterPanel::buttonActionPerformed(source);
}

/*private*/ void YardmasterByTrackPanel::nextButtonAction() {
    log->debug("next button activated");
    if (trackComboBox->count() > 1) {
        int index = trackComboBox->currentIndex();
        // index = -1 if first item (NULL) in trainComboBox
        if (index == -1) {
            index = 1;
        } else {
            index++;
        }
        if (index >= trackComboBox->count()) {
            index = 0;
        }
        trackComboBox->setCurrentIndex(index);
    }
}

//@Override
/*protected*/ void YardmasterByTrackPanel::comboBoxActionPerformed(QWidget* source) {
    // made the combo box not visible during updates, so ignore if not visible
    if (source == trackComboBox && trackComboBox->isVisible()) {
        _track = NULL;
        if (trackComboBox->currentData() != QVariant()) {
            _track = VPtr<Track>::asPtr(trackComboBox->currentData());
        }
        update();
    }
}

//@Override
/*protected*/ void YardmasterByTrackPanel::update() {
    // use invokeLater to prevent deadlock
//    SwingUtilities.invokeLater(new Runnable() {
//        //@Override
//        /*public*/ void run() {
//            runUpdate();
//        }
//    });
// YardmasterByTrackPanelUpdate* worker = new YardmasterByTrackPanelUpdate(this);
// QThread* thread = new QThread();
// worker->moveToThread(thread);
// connect(thread, SIGNAL(started()), worker, SLOT(process()));
// connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
// connect(worker, SIGNAL(finished()), thread, SLOT(deleteLater()));
// thread->start();
 runUpdate();
}

/*private*/ void YardmasterByTrackPanel::runUpdate() {
    log->debug("run update");
    removePropertyChangeListerners();
    trainCommon->clearUtilityCarTypes(); // reset the utility car counts
    checkBoxes.clear();
    //pTrack->removeAll();
    QLayout* _layout = pTrackLayout;
    QLayoutItem* item;
    if(_layout!= NULL)
    {
     while ( ( item = _layout->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
    }
    else
     pTrack->setLayout(pTrackLayout = new QVBoxLayout);
    bool pickup = false;
    bool setout = false;
    if (_track != NULL) {
//        pTrackPane->setBorder(BorderFactory::createTitledBorder(_track->getName()));
        textTrackCommentPane->setText(_track->getComment());
        textTrackCommentPane->setVisible(_track->getComment() != (Track::NONE));
        textTrackCommentWorkPane->setText("");
        for (Train* train : trainManager->getTrainsArrivingThisLocationList(_track->getLocation())) {
            QWidget* pTrain = new QWidget();
            QVBoxLayout* pTrainLayout;
            pTrain->setLayout(pTrainLayout = new QVBoxLayout());//(pTrain, BoxLayout.Y_AXIS));
//            pTrain->setBorder(BorderFactory::createTitledBorder(TrainSwitchListText
//                    ::getStringScheduledWork().arg(train->getName()).arg(train->getDescription())));
            // List locos first
            QList<Engine*>* engList = engManager->getByTrainBlockingList(train);
            if (Setup::isPrintHeadersEnabled()) {
                for (Engine* engine : *engList) {
                    if (engine->getTrack() == _track) {
                        QLabel* header = new QLabel(Tab + trainCommon->getPickupEngineHeader());
                        setLabelFont(header);
                        pTrainLayout->addWidget(header);
                        break;
                    }
                }
            }
            for (Engine* engine : *engList) {
                if (engine->getTrack() == _track) {
                 engine->PropertyChangeSupport::addPropertyChangeListener(this);
                    rollingStock.append(engine);
                    QCheckBox* checkBox = new QCheckBox(trainCommon->pickupEngine(engine));
                    setCheckBoxFont(checkBox);
                    pTrainLayout->addWidget(checkBox);
                    checkBoxes.insert(engine->getId(), checkBox);
                    pTrackLayout->addWidget(pTrain);
                }
            }
            // now do locomotive set outs
            if (Setup::isPrintHeadersEnabled()) {
                for (Engine* engine : *engList) {
                    if (engine->getDestinationTrack() == _track) {
                        QLabel* header = new QLabel(Tab + trainCommon->getDropEngineHeader());
                        setLabelFont(header);
                        pTrainLayout->addWidget(header);
                        break;
                    }
                }
            }
            for (Engine* engine : *engList) {
                if (engine->getDestinationTrack() == _track) {
                 engine->PropertyChangeSupport::addPropertyChangeListener(this);
                    rollingStock.append(engine);
                    QCheckBox* checkBox = new QCheckBox(trainCommon->dropEngine(engine));
                    setCheckBoxFont(checkBox);
                    pTrainLayout->addWidget(checkBox);
                    checkBoxes.insert(engine->getId(), checkBox);
                    pTrackLayout->addWidget(pTrain);
                }
            }
            // now cars
            QList<Car*>* carList = carManager->getByTrainDestinationList(train);
            if (Setup::isPrintHeadersEnabled()) {
                for (Car* car : *carList) {
                    if (car->getTrack() == _track && car->getRouteDestination() != car->getRouteLocation()) {
                        QLabel* header = new QLabel(Tab +
                                trainCommon->getPickupCarHeader(!IS_MANIFEST, !TrainCommon::IS_TWO_COLUMN_TRACK));
                        setLabelFont(header);
                        pTrainLayout->addWidget(header);
                        break;
                    }
                }
            }
            // sort car pick ups by their destination
            QList<RouteLocation*>* routeList = train->getRoute()->getLocationsBySequenceList();
            for (RouteLocation* rl : *routeList) {
                for (Car* car : *carList) {
                    if (car->getTrack() == _track &&
                            car->getRouteDestination() != car->getRouteLocation() &&
                            car->getRouteDestination() == rl) {
                     car->PropertyChangeSupport::addPropertyChangeListener(this);
                        rollingStock.append(car);
                        QString text;
                        if (car->isUtility()) {
                            text = trainCommon->pickupUtilityCars(carList, car, !IS_MANIFEST, !TrainCommon::IS_TWO_COLUMN_TRACK);
                            if (text == NULL) {
                                continue; // this car type has already been processed
                            }
                        } else {
                            text = trainCommon->pickupCar(car, !IS_MANIFEST, !TrainCommon::IS_TWO_COLUMN_TRACK);
                        }
                        pickup = true;
                        QCheckBox* checkBox = new QCheckBox(text);
                        setCheckBoxFont(checkBox);
                        pTrainLayout->addWidget(checkBox);
                        checkBoxes.insert(car->getId(), checkBox);
                        pTrackLayout->addWidget(pTrain);
                    }
                }
            }
            // now do car set outs
            if (Setup::isPrintHeadersEnabled()) {
                for (Car* car : *carList) {
                    if (car->getDestinationTrack() == _track &&
                            car->getRouteDestination() != car->getRouteLocation()) {
                       QLabel* header = new QLabel(Tab +
                                trainCommon->getDropCarHeader(!IS_MANIFEST, !TrainCommon::IS_TWO_COLUMN_TRACK));
                        setLabelFont(header);
                        pTrainLayout->addWidget(header);
                        break;
                    }
                }
            }
            for (Car* car : *carList) {
                if (car->getDestinationTrack() == _track &&
                        car->getRouteLocation() != car->getRouteDestination()) {
                 car->PropertyChangeSupport::addPropertyChangeListener(this);
                    rollingStock.append(car);
                    QString text;
                    if (car->isUtility()) {
                        text = trainCommon->setoutUtilityCars(carList, car, !TrainCommon::LOCAL, !IS_MANIFEST);
                        if (text == NULL) {
                            continue; // this car type has already been processed
                        }
                    } else {
                        text = trainCommon->dropCar(car, !IS_MANIFEST, !TrainCommon::IS_TWO_COLUMN_TRACK);
                    }
                    setout = true;
                    QCheckBox* checkBox = new QCheckBox(text);
                    setCheckBoxFont(checkBox);
                    pTrainLayout->addWidget(checkBox);
                    checkBoxes.insert(car->getId(), checkBox);
                    pTrackLayout->addWidget(pTrain);
                }
            }
            // now do local car moves
            if (Setup::isPrintHeadersEnabled()) {
                for (Car* car : *carList) {
                    if ((car->getTrack() == _track || car->getDestinationTrack() == _track) &&
                            car->getRouteDestination() == car->getRouteLocation()) {
                        QLabel* header = new QLabel(Tab + trainCommon->getLocalMoveHeader(!IS_MANIFEST));
                        setLabelFont(header);
                        pTrainLayout->addWidget(header);
                        break;
                    }
                }
            }
            for (Car* car : *carList) {
                if ((car->getTrack() == _track || car->getDestinationTrack() == _track) &&
                        car->getRouteLocation() != NULL && car->getRouteLocation() == car->getRouteDestination()) {
                 car->PropertyChangeSupport::addPropertyChangeListener(this);
                    rollingStock.append(car);
                    QString text;
                    if (car->isUtility()) {
                        text = trainCommon->setoutUtilityCars(carList, car, TrainCommon::LOCAL, !IS_MANIFEST);
                        if (text == NULL) {
                            continue; // this car type has already been processed
                        }
                    } else {
                        text = trainCommon->localMoveCar(car, !IS_MANIFEST);
                    }
                    setout = true;
                    QCheckBox* checkBox = new QCheckBox(text);
                    setCheckBoxFont(checkBox);
                    pTrainLayout->addWidget(checkBox);
                    checkBoxes.insert(car->getId(), checkBox);
                    pTrackLayout->addWidget(pTrain);
                }
            }
            pTrackPane->update();
            pTrain->setMaximumSize(QSize(2000, pTrain->height()));
//            pTrain->revalidate();
        }
        // now do car holds
        // we only need the cars on this track
        QList<RollingStock*>* rsList = carManager->getByTrainList();
        QList<Car*> carList = QList<Car*>();
        for (RollingStock* rs : *rsList) {
            if (rs->getTrack() != _track || rs->getRouteLocation() != NULL)
                continue;
            carList.append((Car*)rs);
        }
        QWidget* pHoldCars = new QWidget();
        QVBoxLayout* pHoldCarsLayout;
        pHoldCars->setLayout(pHoldCarsLayout= new QVBoxLayout());//(pHoldCars, BoxLayout.Y_AXIS));
//        pHoldCars->setBorder(BorderFactory::createTitledBorder(tr("Hold Cars")));
        for (Car* car : carList) {
            QString text;
            if (car->isUtility()) {
                QString s = trainCommon->pickupUtilityCars(&carList, car, !IS_MANIFEST, !TrainCommon::IS_TWO_COLUMN_TRACK);
                if (s == NULL)
                    continue;
                text = TrainSwitchListText::getStringHoldCar().split(QRegExp("\\{"))[0] + s.trimmed();
            } else {
                text = TrainSwitchListText::getStringHoldCar().arg(
                        TrainCommon::padAndTruncateString(car->getRoadName(),((CarRoads*) InstanceManager::getDefault("Operations::CarRoads"))->getMaxNameLength())).arg(
                                TrainCommon::padAndTruncateString(TrainCommon::splitString(car->getNumber()), Control::max_len_string_print_road_number)).arg(
                                TrainCommon::padAndTruncateString(car->getTypeName().split("-")[0], ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getMaxNameLength()),
                                TrainCommon::padAndTruncateString(car->getLength() + TrainCommon::LENGTHABV, Control::max_len_string_length_name)).arg(
                                TrainCommon::padAndTruncateString(car->getLoadName(),((CarLoads*) InstanceManager::getDefault("Operations::CarLoads"))->getMaxNameLength()).arg(
                                TrainCommon::padAndTruncateString(_track->getName(),((LocationManager*) InstanceManager::getDefault("Operations::LocationManager"))->getMaxTrackNameLength()).arg(
                                TrainCommon::padAndTruncateString(car->getColor(),((CarColors*) InstanceManager::getDefault("Operations::CarColors"))->getMaxNameLength()))));

            }
            QCheckBox* checkBox = new QCheckBox(text);
            setCheckBoxFont(checkBox);
            pHoldCarsLayout->addWidget(checkBox);
            checkBoxes.insert(car->getId(), checkBox);
            pTrackLayout->addWidget(pHoldCars);
        }
        pTrackPane->update();
        pHoldCars->setMaximumSize(QSize(2000, pHoldCars->height()));
        //pHoldCars.revalidate();
        if (pickup && !setout) {
            textTrackCommentWorkPane->setText(_track->getCommentPickup());
        } else if (!pickup && setout) {
            textTrackCommentWorkPane->setText(_track->getCommentSetout());
        } else if (pickup && setout) {
            textTrackCommentWorkPane->setText(_track->getCommentBoth());
        }
        textTrackCommentWorkPane->setVisible(textTrackCommentWorkPane->toPlainText() != (""));
    } else {
//        pTrackPane->setBorder(BorderFactory::createTitledBorder(""));
        textTrackCommentPane->setVisible(false);
        textTrackCommentWorkPane->setVisible(false);
    }
}

/*private*/ void YardmasterByTrackPanel::updateTrackComboBox() {
    QString selectedItem = trackComboBox->currentText();
    trackComboBox->setVisible(false); // used as a flag to ignore updates
    if (_location != NULL) {
        _location->updateComboBox(trackComboBox);
    }
    if (selectedItem != QVariant()) {
        trackComboBox->setCurrentText(selectedItem);
    }
    trackComboBox->setVisible(true);
}

//@Override
/*public*/ void YardmasterByTrackPanel::dispose() {
    if (_location != NULL)
     _location->removePropertyChangeListener(this);
    CommonConductorYardmasterPanel::removePropertyChangeListerners();
}

//@Override
/*public*/ void YardmasterByTrackPanel::propertyChange(PropertyChangeEvent* e) {
    //        if (Control.showProperty) {
    log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e->getNewValue().toString()));
    //        }
    if (e->getPropertyName() == (RollingStock::ROUTE_LOCATION_CHANGED_PROPERTY)) {
        update();
    }
    if (e->getPropertyName() == (Location::TRACK_LISTLENGTH_CHANGED_PROPERTY)) {
        updateTrackComboBox();
    }
}

/*private*/ /*final*/ /*static*/ Logger* YardmasterByTrackPanel::log = LoggerFactory::getLogger("YardmasterByTrackPanel");
