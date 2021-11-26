#include "operationssettingspanel.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "setup.h"
#include <QBoxLayout>
#include "jpanel.h"
#include "borderfactory.h"
#include <QScrollArea>
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include <QButtonGroup>
#include "joptionpane.h"
#include "backupdialog.h"
#include "locoicon.h"
#include "routemanagerxml.h"
#include "autobackup.h"
#include "exceptions.h"
#include "cartypes.h"
#include "enginetypes.h"
#include "webserverpreferences.h"
#include "operationssetupxml.h"
#include "operationssettingsframe.h"
#include "routelocation.h"
#include "routemanager.h"
#include "route.h"
#include "restoredialog.h"

/**
 * Frame for user edit of operation parameters
 *
 * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2012
 */
// /*public*/ class OperationsSettingsPanel extends OperationsPreferencesPanel implements PropertyChangeListener {
namespace Operations
{

    /*private*/ /*final*/ /*static*/ Logger* OperationsSettingsPanel::log = LoggerFactory::getLogger("OperationsSettingsPanel");


    /*public*/ OperationsSettingsPanel::OperationsSettingsPanel(QWidget* parent) : OperationsPreferencesPanel(parent){
        //super();

        // the following code sets the frame's initial state
        // create manager to load operation settings
        InstanceManager::getDefault("OperationsSetupXml");

        // load fields
        maxLengthTextField->setText(QString::number(Setup::getMaxTrainLength()));
        maxEngineSizeTextField->setText(QString::number(Setup::getMaxNumberEngines()));
        hptTextField->setText(QString::number(Setup::getHorsePowerPerTon()));
        switchTimeTextField->setText(QString::number(Setup::getSwitchTime()));
        travelTimeTextField->setText(QString::number(Setup::getTravelTime()));
        panelTextField->setText(Setup::getPanelName());
        yearTextField->setText(Setup::getYearModeled());
        commentTextArea->setText(Setup::getComment());

        // load checkboxes
        mainMenuCheckBox->setChecked(Setup::isMainMenuEnabled());
        closeOnSaveCheckBox->setChecked(Setup::isCloseWindowOnSaveEnabled());
        autoSaveCheckBox->setChecked(Setup::isAutoSaveEnabled());
        autoBackupCheckBox->setChecked(Setup::isAutoBackupEnabled());
        iconCheckBox->setChecked(Setup::isTrainIconCordEnabled());
        appendCheckBox->setChecked(Setup::isTrainIconAppendEnabled());

        // add tool tips
        backupButton->setToolTip(tr("Creates Operations backup files"));
        restoreButton->setToolTip(tr("Restores Operations files using backup files"));
        saveButton->setToolTip(tr("Writes this window's settings to file"));
        panelTextField->setToolTip(tr("Enter the panel's name"));
        yearTextField->setToolTip(tr("Optionally enter four digits representing the year that your are modeling"));
        autoSaveCheckBox->setToolTip(tr("When selected, Operations files are automatically saved after a change is made"));
        autoBackupCheckBox->setToolTip(tr("When selected, a backup copy of your Operations files is created at startup"));
        maxLengthTextField->setToolTip(tr("Enter the maximum scale length of your trains"));
        maxEngineSizeTextField->setToolTip(tr("Enter the maximum number of locos that can be assigned to a train"));
        hptTextField->setToolTip(tr("Enter the horsepower per ton required when calculating the number of locos needed per train"));
        switchTimeTextField->setToolTip(tr("Enter in minutes the average time it takes to pull or spot a car"));
        travelTimeTextField->setToolTip(tr("Enter in minutes the average time it takes to travel between locations"));
        railroadNameTextField->setToolTip(tr("To change the railroad name, go to Edit -> Preferences -> Railroad Name"));
        commentTextArea->setToolTip(tr("Comment for backup and restoring files. Also shown on train build reports"));

        // Layout the panel by rows
        setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));
        JPanel* panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
        QScrollArea* panelPane = new QScrollArea(/*panel*/);
        panel->setBorder(BorderFactory::createTitledBorder(""));
        panelPane->setWidget(panel);
        panelPane->setWidgetResizable(true);

        // row 1a
        JPanel* p1 = new JPanel();
        p1->setLayout(new QHBoxLayout());//p1, BoxLayout.X_AXIS));

        JPanel* pRailroadName = new JPanel();
        pRailroadName->setLayout(new GridBagLayout());
        pRailroadName->setBorder(BorderFactory::createTitledBorder(tr("Railroad Name")));
        addItem(pRailroadName, railroadNameTextField, 0, 0);
        p1->layout()->addWidget(pRailroadName);

        // row 1b
        JPanel* pTrainDir = new JPanel();
        pTrainDir->setLayout(new GridBagLayout());
        pTrainDir->setBorder(BorderFactory::createTitledBorder(tr("Trains Travel")));
        addItemLeft(pTrainDir, northCheckBox, 1, 2);
        addItemLeft(pTrainDir, eastCheckBox, 2, 2);
        p1->layout()->addWidget(pTrainDir);

        setDirectionCheckBox(Setup::getTrainDirection());

        // row 3a
        JPanel* p3 = new JPanel();
        p3->setLayout(new QHBoxLayout());//p3, BoxLayout.X_AXIS));

        JPanel* pTrainLength = new JPanel(new GridBagLayout());
        pTrainLength->setBorder(BorderFactory::createTitledBorder(tr("Maximum Train Length")));
        addItem(pTrainLength, maxLengthTextField, 0, 0);
        p3->layout()->addWidget(pTrainLength);

        // row 3b
        JPanel* pMaxEngine = new JPanel(new GridBagLayout());
        pMaxEngine->setBorder(BorderFactory::createTitledBorder(tr("Max Locos per Train")));
        addItem(pMaxEngine, maxEngineSizeTextField, 0, 0);
        p3->layout()->addWidget(pMaxEngine);

        // row 3c
        JPanel* pHPT = new JPanel(new GridBagLayout());
        pHPT->setBorder(BorderFactory::createTitledBorder(tr("HPT")));
        addItem(pHPT, hptTextField, 0, 0);
        p3->layout()->addWidget(pHPT);

        JPanel* pSwitchTime = new JPanel(new GridBagLayout());
        pSwitchTime->setBorder(BorderFactory::createTitledBorder(tr("MoveTime")));
        addItem(pSwitchTime, switchTimeTextField, 0, 0);
        p3->layout()->addWidget(pSwitchTime);

        // row 3d
        JPanel* pTravelTime = new JPanel(new GridBagLayout());
        pTravelTime->setBorder(BorderFactory::createTitledBorder(tr("Travel Time (minutes)")));
        addItem(pTravelTime, travelTimeTextField, 0, 0);
        p3->layout()->addWidget(pTravelTime);

        // row 2
        JPanel* pScale = new JPanel(new FlowLayout());
        pScale->setBorder(BorderFactory::createTitledBorder(tr("Scale")));

        QButtonGroup* scaleGroup = new QButtonGroup();
        scaleGroup->addButton(scaleZ);
        scaleGroup->addButton(scaleN);
        scaleGroup->addButton(scaleTT);
        scaleGroup->addButton(scaleHOn3);
        scaleGroup->addButton(scaleOO);
        scaleGroup->addButton(scaleHO);
        scaleGroup->addButton(scaleSn3);
        scaleGroup->addButton(scaleS);
        scaleGroup->addButton(scaleOn3);
        scaleGroup->addButton(scaleO);
        scaleGroup->addButton(scaleG);

        pScale->layout()->addWidget(scaleZ);
        pScale->layout()->addWidget(scaleN);
        pScale->layout()->addWidget(scaleTT);
        pScale->layout()->addWidget(scaleHOn3);
        pScale->layout()->addWidget(scaleOO);
        pScale->layout()->addWidget(scaleHO);
        pScale->layout()->addWidget(scaleSn3);
        pScale->layout()->addWidget(scaleS);
        pScale->layout()->addWidget(scaleOn3);
        pScale->layout()->addWidget(scaleO);
        pScale->layout()->addWidget(scaleG);
        setScale();

        // row 4a
        JPanel* p9 = new JPanel();
        p9->setLayout(new QHBoxLayout());//p9, BoxLayout.X_AXIS));

        JPanel* pCarTypeButtons = new JPanel(new FlowLayout());
        pCarTypeButtons->setBorder(BorderFactory::createTitledBorder(tr("Car Types")));
        QButtonGroup* carTypeGroup = new QButtonGroup();
        carTypeGroup->addButton(typeDesc);
        carTypeGroup->addButton(typeAAR);
        pCarTypeButtons->layout()->addWidget(typeDesc);
        pCarTypeButtons->layout()->addWidget(typeAAR);
        p9->layout()->addWidget(pCarTypeButtons);
        setCarTypes();

        // row 4b
        JPanel* pLengthUnit = new JPanel(new FlowLayout());
        pLengthUnit->setBorder(BorderFactory::createTitledBorder(tr("Unit of Length")));
        QButtonGroup* lengthUnitGroup = new QButtonGroup();
        lengthUnitGroup->addButton(feetUnit);
        lengthUnitGroup->addButton(meterUnit);
        pLengthUnit->layout()->addWidget(feetUnit);
        pLengthUnit->layout()->addWidget(meterUnit);
        p9->layout()->addWidget(pLengthUnit);
        setLengthUnit();

        // row 4c
        JPanel* pYearModeled = new JPanel(new FlowLayout());
        pYearModeled->setBorder(BorderFactory::createTitledBorder(tr("Optional Year Modeled")));
        pYearModeled->layout()->addWidget(yearTextField);

        p9->layout()->addWidget(pYearModeled);

        // Option panel
        JPanel* options = new JPanel();
        options->setLayout(new GridBagLayout());
        options->setBorder(BorderFactory::createTitledBorder(tr("Options")));
        addItem(options, mainMenuCheckBox, 0, 0);
        addItem(options, closeOnSaveCheckBox, 1, 0);
        addItem(options, autoSaveCheckBox, 2, 0);
        addItem(options, autoBackupCheckBox, 3, 0);

        // p9.add(options);
        // 1st scroll panel
        panel->layout()->addWidget(p1);
        panel->layout()->addWidget(pScale);
        panel->layout()->addWidget(p3);
        panel->layout()->addWidget(p9);

        // Icon panel
        JPanel* pIcon = new JPanel();
        pIcon->setLayout(new QVBoxLayout());//pIcon, BoxLayout.Y_AXIS));
        QScrollArea* pIconPane = new QScrollArea(/*pIcon*/);
        pIcon->setBorder(BorderFactory::createTitledBorder(tr("Panel Options")));
        pIconPane->setWidget(pIcon);
        pIconPane->setWidgetResizable(true);

        // row 1 Icon panel
        JPanel* p1Icon = new JPanel();
        p1Icon->setLayout(new QHBoxLayout());//p1Icon, BoxLayout.X_AXIS));

        JPanel* pPanelName = new JPanel();
        pPanelName->setLayout(new GridBagLayout());
        pPanelName->setBorder(BorderFactory::createTitledBorder(tr("Create Train Icons on Panel (use panel name) ")));
        addItem(pPanelName, panelTextField, 0, 0);
        p1Icon->layout()->addWidget(pPanelName);

        JPanel* pIconControl = new JPanel();
        pIconControl->setLayout(new GridBagLayout());
        pIconControl->setBorder(BorderFactory::createTitledBorder(tr("Train Icon Options")));
        addItem(pIconControl, appendCheckBox, 0, 0);
        addItem(pIconControl, iconCheckBox, 1, 0);
        p1Icon->layout()->addWidget(pIconControl);

        pIcon->layout()->addWidget(p1Icon);

        JPanel* pIconColors = new JPanel();
        pIconColors->setLayout(new GridBagLayout());
        pIconColors->setBorder(BorderFactory::createTitledBorder(tr("Icon Colors")));

        textIconNorth->setLabelFor(northComboBox);
        addItem(pIconColors, textIconNorth, 0, 4);
        addItemLeft(pIconColors, northComboBox, 1, 4);
        textIconSouth->setLabelFor(southComboBox);
        addItem(pIconColors, textIconSouth, 0, 5);
        addItemLeft(pIconColors, southComboBox, 1, 5);
        textIconEast->setLabelFor(eastComboBox);
        addItem(pIconColors, textIconEast, 0, 8);
        addItemLeft(pIconColors, eastComboBox, 1, 8);
        textIconWest->setLabelFor(westComboBox);
        addItem(pIconColors, textIconWest, 0, 9);
        addItemLeft(pIconColors, westComboBox, 1, 9);
        textIconLocal->setLabelFor(localComboBox);
        addItem(pIconColors, textIconLocal, 0, 10);
        addItemLeft(pIconColors, localComboBox, 1, 10);
        textIconTerminate->setLabelFor(terminateComboBox);
        addItem(pIconColors, textIconTerminate, 0, 11);
        addItemLeft(pIconColors, terminateComboBox, 1, 11);

        pIcon->layout()->addWidget(pIconColors);

        loadIconComboBox(northComboBox);
        loadIconComboBox(southComboBox);
        loadIconComboBox(eastComboBox);
        loadIconComboBox(westComboBox);
        loadIconComboBox(localComboBox);
        loadIconComboBox(terminateComboBox);

        northComboBox->setSelectedItem(Setup::getTrainIconColorNorth());
        southComboBox->setSelectedItem(Setup::getTrainIconColorSouth());
        eastComboBox->setSelectedItem(Setup::getTrainIconColorEast());
        westComboBox->setSelectedItem(Setup::getTrainIconColorWest());
        localComboBox->setSelectedItem(Setup::getTrainIconColorLocal());
        terminateComboBox->setSelectedItem(Setup::getTrainIconColorTerminate());

        // comment
        JPanel* pC = new JPanel();
        pC->setLayout(new GridBagLayout());
        pC->setBorder(BorderFactory::createTitledBorder(tr("Comment")));
//        QScrollArea* commentScroller = new QScrollArea();//commentTextArea, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
////                JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
//        commentScroller->setWidget(commentTextArea);
        addItem(pC, commentTextArea, 0, 0);

        pIcon->layout()->addWidget(pC);

        // row 15
        JPanel* pControl = new JPanel();
        pControl->setLayout(new GridBagLayout());
        addItem(pControl, restoreButton, 0, 9);
        addItem(pControl, backupButton, 1, 9);
        addItem(pControl, saveButton, 3, 9);

        layout()->addWidget(panelPane);
        layout()->addWidget(options);
        layout()->addWidget(pIconPane);
        layout()->addWidget(pControl);

        // set up buttons
        addButtonAction(backupButton);
        addButtonAction(restoreButton);
        addButtonAction(saveButton);
        addCheckBoxAction(eastCheckBox);
        addCheckBoxAction(northCheckBox);

        // now provide the railroad name
        railroadNameTextField->setText(Setup::getRailroadName());
    }

    // Save, Delete, Add buttons
    //@Override
    /*public*/ void OperationsSettingsPanel::buttonActionPerformed(QWidget* src) {
        if (src == backupButton) {
            // Backup and Restore dialogs are now modal. so no need to check for an existing
            // instance
            BackupDialog* bd = new BackupDialog();
            bd->pack();
            bd->setLocationRelativeTo(nullptr);
            bd->setVisible(true);
        }
        if (src == restoreButton) {
            RestoreDialog* rd = new RestoreDialog();
            rd->pack();
            rd->setLocationRelativeTo(nullptr);
            rd->setVisible(true);
        }
        if (src == saveButton) {
            save();
        }
    }

    //@SuppressFBWarnings(value = "BC_UNCONFIRMED_CAST_OF_RETURN_VALUE", justification = "checks for instance of OperationsSetupFrame")
    /*private*/ void OperationsSettingsPanel::save() {
        // check input fields
        int maxTrainLength;
        bool bok;
            maxTrainLength = maxLengthTextField->text().toInt(&bok);
        if(!bok) {
            JOptionPane::showMessageDialog(this, tr("MaxLength"), tr("CanNotAcceptNumber"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        }
        // warn about train length being too short
        if (maxTrainLength != Setup::getMaxTrainLength()) {
            if ((maxTrainLength < 500 && Setup::getLengthUnit() == (Setup::FEET) )||
                    (maxTrainLength < 160 && Setup::getLengthUnit() == (Setup::METER))) {
                JOptionPane::showMessageDialog(this,
                        tr("Are you sure that you want to limit your trains to %1 scale %2?").arg(
                                maxTrainLength).arg(Setup::getLengthUnit().toLower()),
                        tr("Warning train length might be too short!"), JOptionPane::WARNING_MESSAGE);
            }
        }

            maxEngineSizeTextField->text();
        if(!bok) {
            JOptionPane::showMessageDialog(this, tr("Max Locos per Train"), tr("Can not accept number"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        }


            hptTextField->text().toInt();
        if(!bok) {
            JOptionPane::showMessageDialog(this, tr("Horsepower per Ton"), tr("Can not accept number"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        }


            switchTimeTextField->text().toInt();
        if(!bok) {
            JOptionPane::showMessageDialog(this, tr("Switch Time (minutes)"), tr("Can not accept number"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        }

        try{
         bool bok;
             travelTimeTextField->text().toInt(&bok);
         if(!bok) {
             JOptionPane::showMessageDialog(this, tr("Travel Time (minutes)"),
                     tr("Can not accept number"), JOptionPane::ERROR_MESSAGE);
             return;
         }


            if (!yearTextField->text().trimmed().isEmpty()) {
                yearTextField->text().trimmed().toInt(&bok);
                if(!bok)
                 throw NumberFormatException();
            }
        } catch (NumberFormatException e) {
            JOptionPane::showMessageDialog(this, tr("Optional Year Modeled"),
                    tr("Can not accept number"), JOptionPane::ERROR_MESSAGE);
            return;
        }

        // if max train length has changed, check routes
        checkRoutes();

        // set car types
        if ((typeDesc->isChecked() && (Setup::getCarTypes() != (Setup::DESCRIPTIVE))) ||
                (typeAAR->isChecked() && (Setup::getCarTypes() != (Setup::AAR)))) {

            // backup files before changing car type descriptions
            AutoBackup* backup = new AutoBackup();
            try {
                backup->autoBackup();
            } catch (IOException ex) {
#if 0
                UnexpectedExceptionContext context = new UnexpectedExceptionContext(ex,
                        "Auto backup before changing Car types"); // NOI18N
                new ExceptionDisplayFrame(context, nullptr)->setVisible(true);
#endif
            }

            if (typeDesc->isChecked()) {
                ((CarTypes*)InstanceManager::getDefault("CarTypes"))->changeDefaultNames(Setup::DESCRIPTIVE);
                Setup::setCarTypes(Setup::DESCRIPTIVE);
            } else {
                ((CarTypes*)InstanceManager::getDefault("CarTypes"))->changeDefaultNames(Setup::AAR);
                Setup::setCarTypes(Setup::AAR);
            }

            // save all the modified files
            OperationsXml::save();
        }
        // main menu enabled?
        Setup::setMainMenuEnabled(mainMenuCheckBox->isChecked());
        Setup::setCloseWindowOnSaveEnabled(closeOnSaveCheckBox->isChecked());
        Setup::setAutoSaveEnabled(autoSaveCheckBox->isChecked());
        Setup::setAutoBackupEnabled(autoBackupCheckBox->isChecked());

        // add panel name to setup
        Setup::setPanelName(panelTextField->text());

        // train Icon X&Y
        Setup::setTrainIconCordEnabled(iconCheckBox->isChecked());
        Setup::setTrainIconAppendEnabled(appendCheckBox->isChecked());

        // save train icon colors
        Setup::setTrainIconColorNorth( northComboBox->getSelectedItem());
        Setup::setTrainIconColorSouth(southComboBox->getSelectedItem());
        Setup::setTrainIconColorEast(eastComboBox->getSelectedItem());
        Setup::setTrainIconColorWest(westComboBox->getSelectedItem());
        Setup::setTrainIconColorLocal(localComboBox->getSelectedItem());
        Setup::setTrainIconColorTerminate(terminateComboBox->getSelectedItem());
        // set train direction
        int direction = 0;
        if (eastCheckBox->isChecked()) {
            direction = Setup::EAST + Setup::WEST;
        }
        if (northCheckBox->isChecked()) {
            direction += Setup::NORTH + Setup::SOUTH;
        }
        Setup::setTrainDirection(direction);
        Setup::setMaxNumberEngines(maxEngineSizeTextField->text().toInt());
        Setup::setHorsePowerPerTon(hptTextField->text().toInt());
        // set switch time
        Setup::setSwitchTime(switchTimeTextField->text().toInt());
        // set travel time
        Setup::setTravelTime(travelTimeTextField->text().toInt());
        // set scale
        Setup::setScale(getSelectedScale());

        if (railroadNameTextField->text()
                 != ((WebServerPreferences*)InstanceManager::getDefault("WebServerPreferences"))->getRailroadName()) {
            Setup::setRailroadName(railroadNameTextField->text());
            int results = JOptionPane::showConfirmDialog(this,
                    tr("Do you want the change your railroad name from \"%1\" to \"%2""?").arg(
                             ((WebServerPreferences*)InstanceManager::getDefault("WebServerPreferences"))->getRailroadName(),
                                    Setup::getRailroadName() ),
                    tr("Change your JMRI railroad name?"), JOptionPane::YES_NO_OPTION);
            if (results == JOptionPane::YES_OPTION) {
                ((WebServerPreferences*)InstanceManager::getDefault("WebServerPreferences"))->setRailroadName(Setup::getRailroadName());
                ((WebServerPreferences*)InstanceManager::getDefault("WebServerPreferences"))->save();
            }
        }
        // Set Unit of Length
        if (feetUnit->isChecked()) {
            Setup::setLengthUnit(Setup::FEET);
        }
        if (meterUnit->isChecked()) {
            Setup::setLengthUnit(Setup::METER);
        }
        Setup::setYearModeled(yearTextField->text().trimmed());
        // set max train length
        Setup::setMaxTrainLength(maxLengthTextField->text().toInt());
        Setup::setComment(commentTextArea->getText());

        ((OperationsSetupXml*)InstanceManager::getDefault("OperationsSetupXml"))->writeOperationsFile();
        if (Setup::isCloseWindowOnSaveEnabled() && qobject_cast<OperationsSettingsFrame*>(this->window())) {
            ((OperationsSettingsFrame*) this->window())->dispose();
        }
    }

    // if max train length has changed, check routes
    /*private*/ void OperationsSettingsPanel::checkRoutes() {
        int maxLength = maxLengthTextField->text().toInt();
        if (maxLength > Setup::getMaxTrainLength()) {
            JOptionPane::showMessageDialog(this, tr("You need to manually edit your train's routes if you want to use the longer length!"),
                    tr("You''ve increased the maximum train length to %1 %2.").arg(
                             maxLength).arg( Setup::getLengthUnit().toLower() ),
                    JOptionPane::INFORMATION_MESSAGE);
        }
        if (maxLength < Setup::getMaxTrainLength()) {
            QString sb;// = new StringBuilder();
            QList<Route*> routes = ((RouteManager*)InstanceManager::getDefault("RouteManager"))->getRoutesByNameList();
            int count = 0;
            for (Route* route : routes) {
                foreach (RouteLocation* rl , *route->getLocationsBySequenceList()) {
                    if (rl->getMaxTrainLength() > maxLength) {
                        QString s = tr("Route (%1) has a location (%2) with a maximum departure train length (%3) that exceeds the new maximum length (%4)").arg(
                                 route->getName(), rl->getName()).arg(rl->getMaxTrainLength(), maxLength );
                        log->info(s);
                        sb.append(s).append(NEW_LINE);
                        count++;
                        break;
                    }
                }
                // maximum of 20 route warnings
                if (count > 20) {
                    sb.append(tr("More")).append(NEW_LINE);
                    break;
                }
            }
            if (sb.length() > 0) {
                JOptionPane::showMessageDialog(this, sb, tr("You need to adjust your routes! (You can also view this warning message using the JMRI System Console) "),
                        JOptionPane::WARNING_MESSAGE);
                if (JOptionPane::showConfirmDialog(this,
                        tr("Change maximum train departure length to %1?").arg(maxLength ),
                        tr("ModifyAllRoutes"), JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION) {
                    //routes.stream().forEach((route) ->
                    foreach(Route* route, routes)
                    {
//                        route->getLocationsBySequenceList().stream().filter((rl) -> (rl.getMaxTrainLength() > maxLength))
//                                .map((rl) ->
                     foreach(RouteLocation* rl, *route->getLocationsBySequenceList())
                     {
                      if(rl->getMaxTrainLength() > maxLength)
                      {
                       log->debug(tr("Setting route (%1) routeLocation (%2) max traim length to %3").arg(
                               route->getName(), rl->getName()).arg(maxLength)); // NOI18N
//                       return rl;
                      }//).forEach((rl) -> {
                      rl->setMaxTrainLength(maxLength);
                     }//);
                    }//);
                    // save the route changes
                    ((RouteManagerXml*)InstanceManager::getDefault("RouteManagerXml"))->writeOperationsFile();
                }
            }
        }
    }

    //@Override
    /*public*/ void OperationsSettingsPanel::checkBoxActionPerformed(QWidget* src) {
        if (src == northCheckBox) {
            if (!northCheckBox->isChecked()) {
                eastCheckBox->setChecked(true);
            }
        }
        if (src == eastCheckBox) {
            if (!eastCheckBox->isChecked()) {
                northCheckBox->setChecked(true);
            }
        }
        int direction = 0;
        if (eastCheckBox->isChecked()) {
            direction += Setup::EAST;
        }
        if (northCheckBox->isChecked()) {
            direction += Setup::NORTH;
        }
        setDirectionCheckBox(direction);
    }

    /*private*/ void OperationsSettingsPanel::setScale() {
        switch (Setup::getScale()) {
            case Setup::Z_SCALE:
                scaleZ->setChecked(true);
                break;
            case Setup::N_SCALE:
                scaleN->setChecked(true);
                break;
            case Setup::TT_SCALE:
                scaleTT->setChecked(true);
                break;
            case Setup::HOn3_SCALE:
                scaleHOn3->setChecked(true);
                break;
            case Setup::OO_SCALE:
                scaleOO->setChecked(true);
                break;
            case Setup::HO_SCALE:
                scaleHO->setChecked(true);
                break;
            case Setup::Sn3_SCALE:
                scaleSn3->setChecked(true);
                break;
            case Setup::S_SCALE:
                scaleS->setChecked(true);
                break;
            case Setup::On3_SCALE:
                scaleOn3->setChecked(true);
                break;
            case Setup::O_SCALE:
                scaleO->setChecked(true);
                break;
            case Setup::G_SCALE:
                scaleG->setChecked(true);
                break;
            default:
                log->error("Unknown scale");
        }
    }

    /*private*/ int OperationsSettingsPanel::getSelectedScale() {
        int scale = 0;
        if (scaleZ->isChecked()) {
            scale = Setup::Z_SCALE;
        }
        if (scaleN->isChecked()) {
            scale = Setup::N_SCALE;
        }
        if (scaleTT->isChecked()) {
            scale = Setup::TT_SCALE;
        }
        if (scaleOO->isChecked()) {
            scale = Setup::OO_SCALE;
        }
        if (scaleHOn3->isChecked()) {
            scale = Setup::HOn3_SCALE;
        }
        if (scaleHO->isChecked()) {
            scale = Setup::HO_SCALE;
        }
        if (scaleSn3->isChecked()) {
            scale = Setup::Sn3_SCALE;
        }
        if (scaleS->isChecked()) {
            scale = Setup::S_SCALE;
        }
        if (scaleOn3->isChecked()) {
            scale = Setup::On3_SCALE;
        }
        if (scaleO->isChecked()) {
            scale = Setup::O_SCALE;
        }
        if (scaleG->isChecked()) {
            scale = Setup::G_SCALE;
        }
        return scale;
    }

    /*private*/ void OperationsSettingsPanel::setCarTypes() {
        typeDesc->setChecked(Setup::getCarTypes() == (Setup::DESCRIPTIVE));
        typeAAR->setChecked(Setup::getCarTypes() == (Setup::AAR));
    }

    /*private*/ void OperationsSettingsPanel::setDirectionCheckBox(int direction) {
        eastCheckBox->setChecked((direction & Setup::EAST) == Setup::EAST);
        textIconEast->setVisible((direction & Setup::EAST) == Setup::EAST);
        eastComboBox->setVisible((direction & Setup::EAST) == Setup::EAST);
        textIconWest->setVisible((direction & Setup::EAST) == Setup::EAST);
        westComboBox->setVisible((direction & Setup::EAST) == Setup::EAST);
        northCheckBox->setChecked((direction & Setup::NORTH) == Setup::NORTH);
        textIconNorth->setVisible((direction & Setup::NORTH) == Setup::NORTH);
        northComboBox->setVisible((direction & Setup::NORTH) == Setup::NORTH);
        textIconSouth->setVisible((direction & Setup::NORTH) == Setup::NORTH);
        southComboBox->setVisible((direction & Setup::NORTH) == Setup::NORTH);
    }

    /*private*/ void OperationsSettingsPanel::setLengthUnit() {
        feetUnit->setChecked(Setup::getLengthUnit() == (Setup::FEET));
        meterUnit->setChecked(Setup::getLengthUnit() == (Setup::METER));
    }

    /*private*/ void OperationsSettingsPanel::loadIconComboBox(JComboBox* comboBox) {
        for (QString color : LocoIcon::getLocoColors()) {
            comboBox->addItem(color);
        }
    }

    //@Override
    /*public*/ void OperationsSettingsPanel::propertyChange(PropertyChangeEvent* e) {
        log->debug(tr("propertyChange (%1), new: (%2)").arg(e->getPropertyName(), e->getNewValue().toString()));
    }

    //@Override
    /*public*/ QString OperationsSettingsPanel::getTabbedPreferencesTitle() {
        return tr("OperationsPro Settings");
    }

    //@Override
    /*public*/ QString OperationsSettingsPanel::getPreferencesTooltip() {
        return QString();
    }

    //@Override
    /*public*/ void OperationsSettingsPanel::savePreferences() {
        this->save();
    }

    //@Override
    /*public*/ bool OperationsSettingsPanel::isDirty() {
        if (// set car types
        (typeDesc->isChecked() && Setup::getCarTypes() != (Setup::DESCRIPTIVE)) ||
                (typeAAR->isChecked() && Setup::getCarTypes() != (Setup::AAR))
                // main menu enabled?
                ||
                Setup::isMainMenuEnabled() != mainMenuCheckBox->isChecked() ||
                Setup::isCloseWindowOnSaveEnabled() != closeOnSaveCheckBox->isChecked() ||
                Setup::isAutoSaveEnabled() != autoSaveCheckBox->isChecked() ||
                Setup::isAutoBackupEnabled() != autoBackupCheckBox->isChecked()
                // add panel name to setup
                ||
                Setup::getPanelName() != (panelTextField->text())
                // train Icon X&Y
                ||
                Setup::isTrainIconCordEnabled() != iconCheckBox->isChecked() ||
                Setup::isTrainIconAppendEnabled() != appendCheckBox->isChecked()
                // train Icon X&Y
                ||
                Setup::isTrainIconCordEnabled() != iconCheckBox->isChecked() ||
                Setup::isTrainIconAppendEnabled() != appendCheckBox->isChecked()
                // save train icon colors
                ||
                Setup::getTrainIconColorNorth() != (northComboBox->getSelectedItem()) ||
                Setup::getTrainIconColorSouth() != (southComboBox->getSelectedItem()) ||
                Setup::getTrainIconColorEast() != (eastComboBox->getSelectedItem()) ||
                Setup::getTrainIconColorWest() != (westComboBox->getSelectedItem()) ||
                Setup::getTrainIconColorLocal() != (localComboBox->getSelectedItem()) ||
                Setup::getTrainIconColorTerminate() != (terminateComboBox->getSelectedItem()) ||
                Setup::getMaxNumberEngines() != maxEngineSizeTextField->text().toInt() ||
                Setup::getHorsePowerPerTon() != hptTextField->text().toInt()
                // switch time
                ||
                Setup::getSwitchTime() != switchTimeTextField->text().toInt()
                // travel time
                ||
                Setup::getTravelTime() != travelTimeTextField->text().toInt() ||
                Setup::getYearModeled() != (yearTextField->text().trimmed()) ||
                Setup::getMaxTrainLength() != maxLengthTextField->text().toInt() ||
                Setup::getComment() != (commentTextArea->getText())) {
            return true;
        }

        // set train direction
        int direction = 0;
        if (eastCheckBox->isChecked()) {
            direction = Setup::EAST + Setup::WEST;
        }
        if (northCheckBox->isChecked()) {
            direction += Setup::NORTH + Setup::SOUTH;
        }
        // get scale
        int scale = getSelectedScale();
        QString lengthUnit = "";
        // Set Unit of Length
        if (feetUnit->isChecked()) {
            lengthUnit = Setup::FEET;
        }
        if (meterUnit->isChecked()) {
            lengthUnit = Setup::METER;
        }
        return (Setup::getTrainDirection() != direction ||
                Setup::getScale() != scale ||
                Setup::getRailroadName() != (this->railroadNameTextField->text()) ||
                Setup::getLengthUnit() != (lengthUnit));
    }
}
