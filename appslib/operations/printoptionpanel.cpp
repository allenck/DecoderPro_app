#include "printoptionpanel.h"
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QBoxLayout>
#include "gridbaglayout.h"
#include "jtextfield.h"
#include <QLabel>
#include "setup.h"
#include <QScrollArea>
#include <QGroupBox>
#include "flowlayout.h"
#include "jtextarea.h"
#include "logger.h"
#include "file.h"
#include "printoptionframe.h"
#include "jfilechooser.h"
#include "xmlfile.h"
#include <QFontComboBox>
#include "fileutil.h"
#include "trainmanager.h"
#include "operationssetupxml.h"
#include "htmltextedit.h"
#include "flowlayout.h"


namespace Operations
{
/**
 * Frame for user edit of manifest and switch list print options
 *
 * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2012, 2013
 * @version $Revision: 29132 $
 */
///*public*/ class PrintOptionPanel extends OperationsPreferencesPanel {

 /**
  *
  */
 //private static final long serialVersionUID = 2753161901627545371L;
 //private static final Logger log = LoggerFactory.getLogger(PrintOptionPanel.class);



 /*public*/ PrintOptionPanel::PrintOptionPanel(QWidget* parent )
     : OperationsPreferencesPanel(parent)
 {
 log = new Logger("PrintOptionPanel");
  // labels
  logoURL = new QLabel("");
  /**
   * We always use the same file chooser in this class, so that the user's
   * last-accessed directory remains available.
   */
  fc = XmlFile::userFileChooser(tr("Images"));

  // major buttons
  saveButton = new QPushButton(tr("Save"));
  addLogoButton = new QPushButton(tr("AddLogo"));
  removeLogoButton = new QPushButton(tr("RemoveLogo"));

  addEngPickupComboboxButton = new QPushButton("+");
  deleteEngPickupComboboxButton = new QPushButton("-");
  addEngDropComboboxButton = new QPushButton("+");
  deleteEngDropComboboxButton = new QPushButton("-");
  addCarPickupComboboxButton = new QPushButton("+");
  deleteCarPickupComboboxButton = new QPushButton("-");
  addCarDropComboboxButton = new QPushButton("+");
  deleteCarDropComboboxButton = new QPushButton("-");
  addLocalComboboxButton = new QPushButton("+");
  deleteLocalComboboxButton = new QPushButton("-");
  addSwitchListPickupComboboxButton = new QPushButton("+");
  deleteSwitchListPickupComboboxButton = new QPushButton("-");
  addSwitchListDropComboboxButton = new QPushButton("+");
  deleteSwitchListDropComboboxButton = new QPushButton("-");
  addSwitchListLocalComboboxButton = new QPushButton("+");
  deleteSwitchListLocalComboboxButton = new QPushButton("-");

  // check boxes
  tabFormatCheckBox = new QCheckBox(tr("TabFormat"));
  formatSwitchListCheckBox = new QCheckBox(tr("SameAsManifest"));
  editManifestCheckBox = new QCheckBox(tr("UseTextEditor"));
  printLocCommentsCheckBox = new QCheckBox(tr("PrintLocationComments"));
  printRouteCommentsCheckBox = new QCheckBox(tr("PrintRouteComments"));
  printLoadsEmptiesCheckBox = new QCheckBox(tr("PrintLoadsEmpties"));
  printTimetableNameCheckBox = new QCheckBox(tr("PrintTimetableName"));
  use12hrFormatCheckBox = new QCheckBox(tr("12hrFormat"));
  printValidCheckBox = new QCheckBox(tr("PrintValid"));
  sortByTrackCheckBox = new QCheckBox(tr("SortByTrack"));
  printHeadersCheckBox = new QCheckBox(tr("PrintHeaders"));
  truncateCheckBox = new QCheckBox(tr("Truncate"));
  departureTimeCheckBox = new QCheckBox(tr("DepartureTime"));
  trackSummaryCheckBox = new QCheckBox(tr("TrackSummary"));
  routeLocationCheckBox = new QCheckBox(tr("RouteLocation"));

  // text field
  pickupEngPrefix = new JTextField(10);
  dropEngPrefix = new JTextField(10);
  pickupCarPrefix = new JTextField(10);
  dropCarPrefix = new JTextField(10);
  localPrefix = new JTextField(10);
  switchListPickupCarPrefix = new JTextField(10);
  switchListDropCarPrefix = new JTextField(10);
  switchListLocalPrefix = new JTextField(10);
  hazardousTextField = new JTextField(20);

  // text area
  commentTextArea = new HtmlTextEdit(2, 90);

  commentScroller = new QScrollArea(commentTextArea); //
 //         JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

  // combo boxes
  fontComboBox = new QFontComboBox();
  manifestFormatComboBox = Setup::getManifestFormatComboBox();
  manifestOrientationComboBox = Setup::getOrientationComboBox();
  fontSizeComboBox = new QComboBox();
  pickupComboBox = Setup::getPrintColorComboBox(); // colors
  dropComboBox = Setup::getPrintColorComboBox();
  localComboBox = Setup::getPrintColorComboBox();
  switchListOrientationComboBox = Setup::getOrientationComboBox();

  // message formats
  enginePickupMessageList = QList<QComboBox*>();
  engineDropMessageList = QList<QComboBox*>();
  carPickupMessageList = QList<QComboBox*>();
  carDropMessageList = QList<QComboBox*>();
  localMessageList = QList<QComboBox*>();
  switchListCarPickupMessageList = QList<QComboBox*>();
  switchListCarDropMessageList = QList<QComboBox*>();
  switchListLocalMessageList = QList<QComboBox*>();

  // manifest panels
  QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

  pManifest = new QWidget();
  pEngPickup = new QGroupBox();
  pEngPickup->setLayout(new QHBoxLayout);
  pEngPickup->setStyleSheet(gbStyleSheet);
  pEngPickup->setTitle(tr("Pick Up Locomotive Message Format"));
  pEngDrop = new QGroupBox();
  pEngDrop->setLayout(new QHBoxLayout);
  pEngDrop->setStyleSheet(gbStyleSheet);
  pEngDrop->setTitle(tr("Set Out Locomotive Message Format"));
  pPickup = new QGroupBox();
  pPickup->setLayout(new QHBoxLayout);
  pPickup->setStyleSheet(gbStyleSheet);
  pPickup->setTitle("Pick Up Car Message Format");
  pDrop = new QGroupBox();
  pDrop->setLayout(new QHBoxLayout);
  pDrop->setStyleSheet(gbStyleSheet);
  pDrop->setTitle("Set Out Car Message Format");
  pLocal = new QGroupBox();
  pLocal->setLayout(new QHBoxLayout);
  pLocal->setStyleSheet(gbStyleSheet);
  pLocal->setTitle("Local Move Message Format");

  // switch list panels
  pSwitchListOrientation = new QGroupBox();
  pSwPickup = new QGroupBox();
  pSwPickup->setLayout(new QHBoxLayout);
  pSwPickup->setStyleSheet(gbStyleSheet);
  pSwPickup->setTitle("Switch List Pick Up Car Message Format");
  pSwDrop = new QGroupBox();
  pSwDrop->setLayout(new QHBoxLayout);
  pSwDrop->setStyleSheet(gbStyleSheet);
  pSwDrop->setTitle("Switch List Set Out Car Message Format");
  pSwLocal = new QGroupBox();
  pSwLocal->setLayout(new QHBoxLayout);
  pSwLocal->setStyleSheet(gbStyleSheet);
  pSwLocal->setTitle("Switch List Local Move Message Format");

     // the following code sets the frame's initial state
     // add tool tips
     saveButton->setToolTip(tr("SaveToolTip"));
     addLogoButton->setToolTip(tr("AddLogoToolTip"));
     removeLogoButton->setToolTip(tr("RemoveLogoToolTip"));
     tabFormatCheckBox->setToolTip(tr("TabComment"));
     printLocCommentsCheckBox->setToolTip(tr("AddLocationComments"));
     printRouteCommentsCheckBox->setToolTip(tr("AddRouteComments"));
     printLoadsEmptiesCheckBox->setToolTip(tr("LoadsEmptiesComment"));
     printTimetableNameCheckBox->setToolTip(tr("ShowTimetableTip"));
     use12hrFormatCheckBox->setToolTip(tr("Use12hrFormatTip"));
     printValidCheckBox->setToolTip(tr("PrintValidTip"));
     sortByTrackCheckBox->setToolTip(tr("SortByTrackTip"));
     printHeadersCheckBox->setToolTip(tr("PrintHeadersTip"));
     truncateCheckBox->setToolTip(tr("TruncateTip"));
     departureTimeCheckBox->setToolTip(tr("DepartureTimeTip"));
     routeLocationCheckBox->setToolTip(tr("RouteLocationTip"));
     editManifestCheckBox->setToolTip(tr("UseTextEditorTip"));

     addEngPickupComboboxButton->setToolTip(tr("AddMessageComboboxTip"));
     deleteEngPickupComboboxButton->setToolTip(tr("DeleteMessageComboboxTip"));
     addEngDropComboboxButton->setToolTip(tr("AddMessageComboboxTip"));
     deleteEngDropComboboxButton->setToolTip(tr("DeleteMessageComboboxTip"));

     addCarPickupComboboxButton->setToolTip(tr("AddMessageComboboxTip"));
     deleteCarPickupComboboxButton->setToolTip(tr("DeleteMessageComboboxTip"));
     addCarDropComboboxButton->setToolTip(tr("AddMessageComboboxTip"));
     deleteCarDropComboboxButton->setToolTip(tr("DeleteMessageComboboxTip"));
     addLocalComboboxButton->setToolTip(tr("AddMessageComboboxTip"));
     deleteLocalComboboxButton->setToolTip(tr("DeleteMessageComboboxTip"));

     addSwitchListPickupComboboxButton->setToolTip(tr("AddMessageComboboxTip"));
     deleteSwitchListPickupComboboxButton->setToolTip(tr("DeleteMessageComboboxTip"));
     addSwitchListDropComboboxButton->setToolTip(tr("AddMessageComboboxTip"));
     deleteSwitchListDropComboboxButton->setToolTip(tr("DeleteMessageComboboxTip"));
     addSwitchListLocalComboboxButton->setToolTip(tr("AddMessageComboboxTip"));
     deleteSwitchListLocalComboboxButton
             ->setToolTip(tr("DeleteMessageComboboxTip"));

     // Manifest panel
     setLayout(new QVBoxLayout);//(this, BoxLayout.Y_AXIS));
     pManifest->setLayout(new QVBoxLayout); //(pManifest, BoxLayout.Y_AXIS));
     QScrollArea* pManifestPane = new QScrollArea(/*pManifest*/);
     //pManifestPane->setBorder(BorderFactory.createTitledBorder(""));
     pManifestPane->setWidgetResizable(true);
     pManifestPane->setFrameStyle(QFrame::Box | QFrame::Raised);

     // row 1 font type and size
     QWidget* p1 = new QWidget();
     p1->setLayout(new QVBoxLayout);//(p1, BoxLayout.X_AXIS));


     QGroupBox* pFont = new QGroupBox();
     pFont->setLayout(new FlowLayout());
     //pFont->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutFont")));
     pFont->setStyleSheet(gbStyleSheet);
     pFont->setTitle(tr("Layout Font"));
     pFont->layout()->addWidget(fontComboBox);

     QGroupBox* pFontSize = new QGroupBox();
     pFontSize->setLayout(new FlowLayout());
     //pFontSize->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutFontSize")));
     pFontSize->setStyleSheet(gbStyleSheet);
     pFontSize->setTitle(tr("Layout Font Size"));
     pFontSize->layout()->addWidget(fontSizeComboBox);

     QGroupBox* pFormat = new QGroupBox();
     pFormat->setLayout(new FlowLayout);
     //pFormat->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutFormat")));
     pFormat->setStyleSheet(gbStyleSheet);
     pFormat->setTitle(tr("Layout Format"));
     pFormat->layout()->addWidget(tabFormatCheckBox);
     pFormat->layout()->addWidget(manifestFormatComboBox);

     manifestFormatComboBox->setCurrentIndex(manifestFormatComboBox->findText(Setup::getManifestFormat()));

     QGroupBox* pOrientation = new QGroupBox();
     pOrientation->setLayout(new FlowLayout);
     //pOrientation->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutOrientation")));
     pOrientation->setStyleSheet(gbStyleSheet);
     pOrientation->setTitle(tr("Layout Orientation"));
     pOrientation->layout()->addWidget(manifestOrientationComboBox);

     QGroupBox* pPickupColor = new QGroupBox();
     pPickupColor->setLayout(new FlowLayout);
     //pPickupColor->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutPickupColor")));
     pPickupColor->setStyleSheet(gbStyleSheet);
     pPickupColor->setTitle(tr("Pick Up Text Color"));
     pPickupColor->layout()->addWidget(pickupComboBox);

     QGroupBox* pDropColor = new QGroupBox();
     pDropColor->setLayout(new FlowLayout);
//     pDropColor
//             ->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutDropColor")));
     pDropColor->setStyleSheet(gbStyleSheet);
     pDropColor->setTitle(tr("Set Out Text Color"));
     pDropColor->layout()->addWidget(dropComboBox);

     QGroupBox* pLocalColor = new QGroupBox();
     pLocalColor->setLayout(new FlowLayout);
//     pLocalColor->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutLocalColor")));
     pLocalColor->setStyleSheet(gbStyleSheet);
     pLocalColor->setTitle(tr("Local Move Text Color"));
     pLocalColor->layout()->addWidget(localComboBox);

     p1->layout()->addWidget(pFont);
     p1->layout()->addWidget(pFontSize);
     p1->layout()->addWidget(pFormat);
     p1->layout()->addWidget(pOrientation);
     p1->layout()->addWidget(pPickupColor);
     p1->layout()->addWidget(pDropColor);
     p1->layout()->addWidget(pLocalColor);

     // load all of the message combo boxes
     loadFormatComboBox();

     // Optional Switch List Panel
     QWidget* pSl = new QWidget();
     pSl->setLayout(new QHBoxLayout);//(pSl, BoxLayout.X_AXIS));

     QGroupBox* pSwitchFormat = new QGroupBox();
     pSwitchFormat->setLayout(new FlowLayout);
     //pSwitchFormat->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutSwitchListFormat")));
     pSwitchFormat->setStyleSheet(gbStyleSheet);
     pSwitchFormat->setTitle(tr("Switch List Format"));
     pSwitchFormat->layout()->addWidget(formatSwitchListCheckBox);

     pSwitchListOrientation->setLayout(new GridBagLayout());
     //pSwitchListOrientation->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutSwitchListOrientation")));
     pSwitchListOrientation->setStyleSheet(gbStyleSheet);
     pSwitchListOrientation->setTitle(tr("Switch List Page Orientation"));
     pSwitchListOrientation->setMaximumSize(QSize(8000, 100));
     addItem(pSwitchListOrientation, switchListOrientationComboBox, 0, 0);
     addItem(pSwitchListOrientation, new QLabel(" "), 1, 0); // pad
     addItem(pSwitchListOrientation, new QLabel(" "), 2, 0); // pad
     addItem(pSwitchListOrientation, new QLabel(" "), 3, 0); // pad

     QGroupBox* pSwitchOptions = new QGroupBox();
     pSwitchOptions->setLayout(new FlowLayout);
     //pSwitchOptions->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutSwitchListOptions")));
     pSwitchOptions->setStyleSheet(gbStyleSheet);
     pSwitchOptions->setTitle(tr("Switch List Options"));
     pSwitchOptions->layout()->addWidget(trackSummaryCheckBox);
     pSwitchOptions->layout()->addWidget(routeLocationCheckBox);

     pSl->layout()->addWidget(pSwitchFormat);
     pSl->layout()->addWidget(pSwitchListOrientation);
     pSl->layout()->addWidget(pSwitchOptions);

     // Manifest comments
     QGroupBox* pManifestOptions = new QGroupBox();
     pManifestOptions->setLayout(new FlowLayout);
//     pManifestOptions->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutManifestOptions")));
     pManifestOptions->setStyleSheet(gbStyleSheet);
     pManifestOptions->setTitle(tr("Manifest & Switch List Options"));
     pManifestOptions->layout()->addWidget(printValidCheckBox);
     pManifestOptions->layout()->addWidget(printLocCommentsCheckBox);
     pManifestOptions->layout()->addWidget(printRouteCommentsCheckBox);
     pManifestOptions->layout()->addWidget(printLoadsEmptiesCheckBox);
     pManifestOptions->layout()->addWidget(use12hrFormatCheckBox);
     pManifestOptions->layout()->addWidget(departureTimeCheckBox);
     pManifestOptions->layout()->addWidget(printTimetableNameCheckBox);
     pManifestOptions->layout()->addWidget(truncateCheckBox);
     pManifestOptions->layout()->addWidget(sortByTrackCheckBox);
     pManifestOptions->layout()->addWidget(printHeadersCheckBox);

     QWidget* p2 = new QWidget();
     p2->setLayout(new QHBoxLayout);//(p2, BoxLayout.X_AXIS));

     // Use text editor for manifest
     QGroupBox* pEdit = new QGroupBox();
     pEdit->setLayout(new FlowLayout);
//     pEdit->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutManifestPreview")));
     pEdit->setStyleSheet(gbStyleSheet);
     pEdit->setTitle(tr("Manifest & Switch List Preview"));
     pEdit->layout()->addWidget(editManifestCheckBox);

     // manifest logo
     QGroupBox* pLogo = new QGroupBox();
     pLogo->setLayout(new FlowLayout);
     //pLogo->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutLogo")));
     pLogo->setStyleSheet(gbStyleSheet);
     pLogo->setTitle(tr("Logo"));
     pLogo->layout()->addWidget(removeLogoButton);
     pLogo->layout()->addWidget(addLogoButton);
     pLogo->layout()->addWidget(logoURL);

     p2->layout()->addWidget(pEdit);
     p2->layout()->addWidget(pLogo);

     // comments
     QWidget* pComments = new QWidget();
     pComments->setLayout(new QHBoxLayout);//(pComments, BoxLayout.X_AXIS));

     // missing cars comment
     QGroupBox* pComment = new QGroupBox();
     pComment->setLayout(new GridBagLayout());
//     pComment->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutCommentOptions")));
     pComment->setStyleSheet(gbStyleSheet);
     pComment->setTitle(tr("Misplaced Cars Comment"));
     addItem(pComment, commentScroller, 0, 0);

     // Hazardous comment
     QGroupBox* pHazardous = new QGroupBox();
     pHazardous->setLayout(new FlowLayout);
//     pHazardous
//             ->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutHazardous")));
     pHazardous->setStyleSheet(gbStyleSheet);
     pHazardous->setTitle(tr("Hazardous Comment"));
     pHazardous->layout()->addWidget(hazardousTextField);

     pComments->layout()->addWidget(pComment);
     pComments->layout()->addWidget(pHazardous);

     pManifest->layout()->addWidget(p1);
     pManifest->layout()->addWidget(pEngPickup);
     pManifest->layout()->addWidget(pEngDrop);
     pManifest->layout()->addWidget(pPickup);
     pManifest->layout()->addWidget(pDrop);
     pManifest->layout()->addWidget(pLocal);
     pManifest->layout()->addWidget(pSl);
     pManifest->layout()->addWidget(pSwPickup);
     pManifest->layout()->addWidget(pSwDrop);
     pManifest->layout()->addWidget(pSwLocal);
     pManifest->layout()->addWidget(pManifestOptions);
     pManifest->layout()->addWidget(p2);
     pManifest->layout()->addWidget(pComments);

     // row 11
     QGroupBox* pControl = new QGroupBox();
     //pControl->setBorder(BorderFactory.createTitledBorder(""));
     pControl->setStyleSheet(gbStyleSheet);
     pControl->setLayout(new GridBagLayout());
     addItem(pControl, saveButton, 0, 0);

     pManifestPane->setWidget(pManifest);
     layout()->addWidget(pManifestPane);
     layout()->addWidget(pControl);

     manifestOrientationComboBox->setCurrentIndex(manifestOrientationComboBox->findText(Setup::getManifestOrientation()));
     switchListOrientationComboBox->setCurrentIndex(switchListOrientationComboBox->findText(Setup::getSwitchListOrientation()));

     tabFormatCheckBox->setChecked(Setup::isTabEnabled());
     formatSwitchListCheckBox->setChecked(Setup::isSwitchListFormatSameAsManifest());
     printLocCommentsCheckBox->setChecked(Setup::isPrintLocationCommentsEnabled());
     printRouteCommentsCheckBox->setChecked(Setup::isPrintRouteCommentsEnabled());
     printLoadsEmptiesCheckBox->setChecked(Setup::isPrintLoadsAndEmptiesEnabled());
     printTimetableNameCheckBox->setChecked(Setup::isPrintTimetableNameEnabled());
     use12hrFormatCheckBox->setChecked(Setup::is12hrFormatEnabled());
     printValidCheckBox->setChecked(Setup::isPrintValidEnabled());
     sortByTrackCheckBox->setChecked(Setup::isSortByTrackEnabled());
     printHeadersCheckBox->setChecked(Setup::isPrintHeadersEnabled());
     truncateCheckBox->setChecked(Setup::isTruncateManifestEnabled());
     departureTimeCheckBox->setChecked(Setup::isUseDepartureTimeEnabled());
     trackSummaryCheckBox->setChecked(Setup::isTrackSummaryEnabled());
     routeLocationCheckBox->setChecked(Setup::isSwitchListRouteLocationCommentEnabled());
     editManifestCheckBox->setChecked(Setup::isManifestEditorEnabled());

     hazardousTextField->setText(Setup::getHazardousMsg());

     setSwitchListVisible(!formatSwitchListCheckBox->isChecked());

     updateLogoButtons();
     dropComboBox->setCurrentIndex(dropComboBox->findText(Setup::getDropTextColor()));
     pickupComboBox->setCurrentIndex(pickupComboBox->findText(Setup::getPickupTextColor()));
     localComboBox->setCurrentIndex(localComboBox->findText(Setup::getLocalTextColor()));

     commentTextArea->setText(Setup::getMiaComment());

     // load font sizes 7 through 18
     for (int i = 7; i < 19; i++) {
         fontSizeComboBox->addItem(QString::number(i),i);
     }
     fontSizeComboBox->setCurrentIndex(fontSizeComboBox->findData(Setup::getManifestFontSize()));
     loadFontComboBox();

     // setup buttons
     addButtonAction(addLogoButton);
     addButtonAction(removeLogoButton);
     addButtonAction(saveButton);

     addButtonAction(addEngPickupComboboxButton);
     addButtonAction(deleteEngPickupComboboxButton);
     addButtonAction(addEngDropComboboxButton);
     addButtonAction(deleteEngDropComboboxButton);

     addButtonAction(addCarPickupComboboxButton);
     addButtonAction(deleteCarPickupComboboxButton);
     addButtonAction(addCarDropComboboxButton);
     addButtonAction(deleteCarDropComboboxButton);
     addButtonAction(addLocalComboboxButton);
     addButtonAction(deleteLocalComboboxButton);

     addButtonAction(addSwitchListPickupComboboxButton);
     addButtonAction(deleteSwitchListPickupComboboxButton);
     addButtonAction(addSwitchListDropComboboxButton);
     addButtonAction(deleteSwitchListDropComboboxButton);
     addButtonAction(addSwitchListLocalComboboxButton);
     addButtonAction(deleteSwitchListLocalComboboxButton);

     addCheckBoxAction(tabFormatCheckBox);
//		addCheckBoxAction(twoColumnFormatCheckBox);
     addCheckBoxAction(formatSwitchListCheckBox);

     addComboBoxAction(manifestFormatComboBox);

     initMinimumSize();
 }

 // Add Remove Logo and Save buttons
 //@Override
 /*public*/ void PrintOptionPanel::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == addLogoButton) {
         log->debug("add logo button pressed");
         File* f = selectFile();
         if (f != NULL) {
             Setup::setManifestLogoURL(FileUtil::getPortableFilename(f));
         }
         updateLogoButtons();
     }
     if (source == removeLogoButton) {
         log->debug("remove logo button pressed");
         Setup::setManifestLogoURL("");
         updateLogoButtons();
     }
     // add or delete message comboBox
     if (source == addEngPickupComboboxButton) {
         addComboBox(pEngPickup, enginePickupMessageList, Setup::getEngineMessageComboBox());
     }
     if (source == deleteEngPickupComboboxButton) {
         removeComboBox(pEngPickup, enginePickupMessageList);
     }
     if (source == addEngDropComboboxButton) {
         addComboBox(pEngDrop, engineDropMessageList, Setup::getEngineMessageComboBox());
     }
     if (source == deleteEngDropComboboxButton) {
         removeComboBox(pEngDrop, engineDropMessageList);
     }

     if (source == addCarPickupComboboxButton) {
         addComboBox(pPickup, carPickupMessageList, Setup::getCarMessageComboBox());
     }
     if (source == deleteCarPickupComboboxButton) {
         removeComboBox(pPickup, carPickupMessageList);
     }
     if (source == addCarDropComboboxButton) {
         addComboBox(pDrop, carDropMessageList, Setup::getCarMessageComboBox());
     }
     if (source == deleteCarDropComboboxButton) {
         removeComboBox(pDrop, carDropMessageList);
     }

     if (source == addLocalComboboxButton) {
         addComboBox(pLocal, localMessageList, Setup::getCarMessageComboBox());
     }
     if (source == deleteLocalComboboxButton) {
         removeComboBox(pLocal, localMessageList);
     }

     if (source == addSwitchListPickupComboboxButton) {
         addComboBox(pSwPickup, switchListCarPickupMessageList, Setup::getCarMessageComboBox());
     }
     if (source == deleteSwitchListPickupComboboxButton) {
         removeComboBox(pSwPickup, switchListCarPickupMessageList);
     }
     if (source == addSwitchListDropComboboxButton) {
         addComboBox(pSwDrop, switchListCarDropMessageList, Setup::getCarMessageComboBox());
     }
     if (source == deleteSwitchListDropComboboxButton) {
         removeComboBox(pSwDrop, switchListCarDropMessageList);
     }

     if (source == addSwitchListLocalComboboxButton) {
         addComboBox(pSwLocal, switchListLocalMessageList, Setup::getCarMessageComboBox());
     }
     if (source == deleteSwitchListLocalComboboxButton) {
         removeComboBox(pSwLocal, switchListLocalMessageList);
     }

     if (source == saveButton) {
         this->savePreferences();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }

 //@Override
 /*public*/ void PrintOptionPanel::checkBoxActionPerformed(QWidget* ae) {
 QCheckBox* source = (QCheckBox*)ae;
     if (source == tabFormatCheckBox) {
         loadFontComboBox();
     }
     if (source == formatSwitchListCheckBox) {
         log->debug("Switch list check box activated");
         setSwitchListVisible(!formatSwitchListCheckBox->isChecked());
         resize(QSize());
//         if (this.getTopLevelAncestor() instanceof PrintOptionFrame) {
//             ((PrintOptionFrame) this.getTopLevelAncestor()).pack();
//         }
         if(qobject_cast<PrintOptionFrame*>(this->topLevelWidget()) != NULL)
         {
            ((PrintOptionFrame*) this->topLevelWidget())->adjustSize();
     }
     }
 }

 //@Override
 /*public*/ void PrintOptionPanel::comboBoxActionPerformed(QWidget* ae) {

     if ((QComboBox*)ae == manifestFormatComboBox) {
         loadFontComboBox();
     }
 }

 /*private*/ void PrintOptionPanel::setSwitchListVisible(bool b) {
     pSwitchListOrientation->setVisible(b);
     pSwPickup->setVisible(b);
     pSwDrop->setVisible(b);
     pSwLocal->setVisible(b);
 }


 /*private*/ File* PrintOptionPanel::selectFile() {
     if (fc == NULL) {
         log->error("Could not find user directory");
     } else {
         fc->setDialogTitle(tr("FindDesiredImage"));
         // when reusing the chooser, make sure new files are included
         //fc->rescanCurrentDirectory();
         int retVal = fc->showOpenDialog(NULL);
         // handle selection or cancel
         if (retVal == JFileChooser::APPROVE_OPTION) {
             File* file = fc->getSelectedFile();
             return file;
         }
     }
     return NULL;
 }

 /*private*/ void PrintOptionPanel::updateLogoButtons() {
     bool flag = Setup::getManifestLogoURL()==("");
     addLogoButton->setVisible(flag);
     removeLogoButton->setVisible(!flag);
     logoURL->setText(Setup::getManifestLogoURL());
     if (qobject_cast<PrintOptionFrame*>(this->topLevelWidget())!= NULL) {
         ((PrintOptionFrame*) this->topLevelWidget())->adjustSize();
     }
 }

 /*private*/ void PrintOptionPanel::addComboBox(QWidget* panel, QList<QComboBox*> list, QComboBox* box) {
     list.append(box);
     ((QHBoxLayout*)panel->layout())->insertWidget(list.size(), box);
     panel->update();
     pManifest->update();
 }

 /*private*/ void PrintOptionPanel::removeComboBox(QWidget* panel, QList<QComboBox*>list) {
     for (int i = 0; i < list.size(); i++) {
         QComboBox* cb = list.at(i);
         if (cb->currentText() == Setup::BLANK) {
             list.removeAt(i);
             panel->layout()->removeWidget(cb);
             panel->update();
             pManifest->update();
             return;
         }
     }
 }

 /*private*/ void PrintOptionPanel::loadFormatComboBox() {
     // loco pick up message format
     //pEngPickup.removeAll();
 QLayoutItem* item;
 while ( ( item = pEngPickup->layout()->takeAt( 0 ) ) != NULL )
 {
     delete item->widget();
     delete item;
 }

     enginePickupMessageList.clear();
//     pEngPickup->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutPickupEngine")));

     pEngPickup->layout()->addWidget(pickupEngPrefix);
     pickupEngPrefix->setText(Setup::getPickupEnginePrefix());
     QStringList format = Setup::getPickupEngineMessageFormat();
     foreach (QString f, format) {
      QComboBox*   cb = Setup::getEngineMessageComboBox();
         cb->setCurrentIndex(cb->findText(f));
         pEngPickup->layout()->addWidget(cb);
         enginePickupMessageList.append(cb);
     }
     pEngPickup->layout()->addWidget(addEngPickupComboboxButton);
     pEngPickup->layout()->addWidget(deleteEngPickupComboboxButton);
     pEngPickup->update();

     // loco set out message format
     //pEngDrop.removeAll();
     while ( ( item = pEngDrop->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     engineDropMessageList.clear();
     //pEngDrop->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutDropEngine")));
     pEngDrop->layout()->addWidget(dropEngPrefix);
     dropEngPrefix->setText(Setup::getDropEnginePrefix());
     format = Setup::getDropEngineMessageFormat();
     foreach (QString f, format) {
     QComboBox*    cb = Setup::getEngineMessageComboBox();
         cb->setCurrentIndex(cb->findText(f));
         pEngDrop->layout()->addWidget(cb);
         engineDropMessageList.append(cb);
     }
     pEngDrop->layout()->addWidget(addEngDropComboboxButton);
     pEngDrop->layout()->addWidget(deleteEngDropComboboxButton);
     pEngDrop->update();

     // car pickup message format
     //pPickup.removeAll();
     while ( ( item = pPickup->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     carPickupMessageList.clear();
     //pPickup->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutPickupCar")));
     pPickup->layout()->addWidget(pickupCarPrefix);
     pickupCarPrefix->setText(Setup::getPickupCarPrefix());
     QStringList pickFormat = Setup::getPickupManifestMessageFormat();
     foreach (QString pf, pickFormat) {
     QComboBox*    cb = Setup::getCarMessageComboBox();
         cb->setCurrentIndex(cb->findText(pf));
         pPickup->layout()->addWidget(cb);
         carPickupMessageList.append(cb);
     }
     pPickup->layout()->addWidget(addCarPickupComboboxButton);
     pPickup->layout()->addWidget(deleteCarPickupComboboxButton);
     pPickup->update();

     // car drop message format
     //pDrop.removeAll();
     while ( ( item = pDrop->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     carDropMessageList.clear();
     //pDrop->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutDropCar")));
     pDrop->layout()->addWidget(dropCarPrefix);
     dropCarPrefix->setText(Setup::getDropCarPrefix());
     QStringList dropFormat = Setup::getDropManifestMessageFormat();
     foreach (QString lf, dropFormat) {
      QComboBox*   cb = Setup::getCarMessageComboBox();
         cb->setCurrentIndex(cb->findText(lf));
         pDrop->layout()->addWidget(cb);
         carDropMessageList.append(cb);
     }
     pDrop->layout()->addWidget(addCarDropComboboxButton);
     pDrop->layout()->addWidget(deleteCarDropComboboxButton);
     pDrop->update();

     // local car move message format
     //pLocal.removeAll();
     while ( ( item = pLocal->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     localMessageList.clear();
     //pLocal->setBorder(BorderFactory.createTitledBorder(tr("BorderLayoutLocal")));
     pLocal->layout()->addWidget(localPrefix);
     localPrefix->setText(Setup::getLocalPrefix());
     QStringList localFormat = Setup::getLocalManifestMessageFormat();
     foreach (QString lf, localFormat) {
      QComboBox*   cb = Setup::getCarMessageComboBox();
         cb->setCurrentIndex(cb->findText(lf));
         pLocal->layout()->addWidget(cb);
         localMessageList.append(cb);
     }
     pLocal->layout()->addWidget(addLocalComboboxButton);
     pLocal->layout()->addWidget(deleteLocalComboboxButton);
     pLocal->update();

     // switch list car pickup message format
     //pSwPickup.removeAll();
     while ( ( item = pSwPickup->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     switchListCarPickupMessageList.clear();
//     pSwPickup->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutSwitchListPickupCar")));
     pSwPickup->layout()->addWidget(switchListPickupCarPrefix);
     switchListPickupCarPrefix->setText(Setup::getSwitchListPickupCarPrefix());
     pickFormat = Setup::getPickupSwitchListMessageFormat();
     foreach (QString pf, pickFormat) {
      QComboBox*   cb = Setup::getCarMessageComboBox();
         cb->setCurrentIndex(cb->findText(pf));
         pSwPickup->layout()->addWidget(cb);
         switchListCarPickupMessageList.append(cb);
     }
     pSwPickup->layout()->addWidget(addSwitchListPickupComboboxButton);
     pSwPickup->layout()->addWidget(deleteSwitchListPickupComboboxButton);

     // switch list car drop message format
     //pSwDrop.removeAll();
     while ( ( item = pSwDrop->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     switchListCarDropMessageList.clear();
//     pSwDrop->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutSwitchListDropCar")));
     pSwDrop->layout()->addWidget(switchListDropCarPrefix);
     switchListDropCarPrefix->setText(Setup::getSwitchListDropCarPrefix());
     dropFormat = Setup::getDropSwitchListMessageFormat();
     foreach (QString df, dropFormat) {
      QComboBox*   cb = Setup::getCarMessageComboBox();
         cb->setCurrentIndex(cb->findText(df));
         pSwDrop->layout()->addWidget(cb);
         switchListCarDropMessageList.append(cb);
     }
     pSwDrop->layout()->addWidget(addSwitchListDropComboboxButton);
     pSwDrop->layout()->addWidget(deleteSwitchListDropComboboxButton);

     // switch list local car move message format
     //pSwLocal.removeAll();
     while ( ( item = pSwLocal->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     switchListLocalMessageList.clear();
//     pSwLocal->setBorder(BorderFactory.createTitledBorder(Bundle
//             .getMessage("BorderLayoutSwitchListLocal")));
     pSwLocal->layout()->addWidget(switchListLocalPrefix);
     switchListLocalPrefix->setText(Setup::getSwitchListLocalPrefix());
     localFormat = Setup::getLocalSwitchListMessageFormat();
     foreach (QString lf, localFormat) {
      QComboBox*   cb = Setup::getCarMessageComboBox();
         cb->setCurrentIndex(cb->findText(lf));
         pSwLocal->layout()->addWidget(cb);
         switchListLocalMessageList.append(cb);
     }
     pSwLocal->layout()->addWidget(addSwitchListLocalComboboxButton);
     pSwLocal->layout()->addWidget(deleteSwitchListLocalComboboxButton);
 }

 /*private*/ void PrintOptionPanel::loadFontComboBox() {
//     fontComboBox->clear();
//     QList<QString> fonts = FontComboUtil.getFonts(FontComboUtil.ALL);
//     if (tabFormatCheckBox->isChecked() || !manifestFormatComboBox->currentText()==(Setup::STANDARD_FORMAT)) {
//         fonts = FontComboUtil.getFonts(FontComboUtil.MONOSPACED);
//     }
 if(tabFormatCheckBox->isChecked() || manifestFormatComboBox->currentText() != (Setup::STANDARD_FORMAT))
 {
  fontComboBox->setFontFilters(QFontComboBox::MonospacedFonts);
 }

//     for (String font : fonts) {
//         fontComboBox.addItem(font);
//     }

     fontComboBox->setCurrentIndex(fontComboBox->findText(Setup::getFontName()));
 }

 //@Override
 /*public*/ QString PrintOptionPanel::getTabbedPreferencesTitle() {
     return tr("Print Options");
 }

 //@Override
 /*public*/ QString PrintOptionPanel::getPreferencesTooltip() {
     return NULL;
 }

 //@Override
 /*public*/ void PrintOptionPanel::savePreferences() {
     // font name
     Setup::setFontName( fontComboBox->currentText());
     // font size
     Setup::setManifestFontSize( fontSizeComboBox->currentData().toInt());
     // page orientation
     Setup::setManifestOrientation( manifestOrientationComboBox->currentText());
     Setup::setSwitchListOrientation( switchListOrientationComboBox->currentText());
     // format
     Setup::setManifestFormat( manifestFormatComboBox->currentText());
     // drop and pick up color option
     Setup::setDropTextColor( dropComboBox->currentText());
     Setup::setPickupTextColor( pickupComboBox->currentText());
     Setup::setLocalTextColor( localComboBox->currentText());
     // save engine pick up message format
     Setup::setPickupEnginePrefix(pickupEngPrefix->text());
     QVector<QString> format = QVector<QString>(enginePickupMessageList.size());
     for (int i = 0; i < enginePickupMessageList.size(); i++) {
         QComboBox* cb = enginePickupMessageList.at(i);
         format.replace(i,  cb->currentText());
     }
     Setup::setPickupEngineMessageFormat(format.toList());
     // save engine drop message format
     Setup::setDropEnginePrefix(dropEngPrefix->text());
     format = QVector<QString>(engineDropMessageList.size());
     for (int i = 0; i < engineDropMessageList.size(); i++) {
         QComboBox* cb = engineDropMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     Setup::setDropEngineMessageFormat(format.toList());
     // save car pick up message format
     Setup::setPickupCarPrefix(pickupCarPrefix->text());
     format = QVector<QString>(carPickupMessageList.size());
     for (int i = 0; i < carPickupMessageList.size(); i++) {
         QComboBox* cb = carPickupMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     Setup::setPickupManifestMessageFormat(format.toList());
     // save car drop message format
     Setup::setDropCarPrefix(dropCarPrefix->text());
     format = QVector<QString>(carDropMessageList.size());
     for (int i = 0; i < carDropMessageList.size(); i++) {
         QComboBox* cb = carDropMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     Setup::setDropManifestMessageFormat(format.toList());
     // save local message format
     Setup::setLocalPrefix(localPrefix->text());
     format = QVector<QString>(localMessageList.size());
     for (int i = 0; i < localMessageList.size(); i++) {
         QComboBox* cb = localMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     Setup::setLocalManifestMessageFormat(format.toList());
     // save switch list car pick up message format
     Setup::setSwitchListPickupCarPrefix(switchListPickupCarPrefix->text());
     format = QVector<QString>(switchListCarPickupMessageList.size());
     for (int i = 0; i < switchListCarPickupMessageList.size(); i++) {
         QComboBox* cb = switchListCarPickupMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     Setup::setPickupSwitchListMessageFormat(format.toList());
     // save switch list car drop message format
     Setup::setSwitchListDropCarPrefix(switchListDropCarPrefix->text());
     format = QVector<QString>(switchListCarDropMessageList.size());
     for (int i = 0; i < switchListCarDropMessageList.size(); i++) {
         QComboBox* cb = switchListCarDropMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     Setup::setDropSwitchListMessageFormat(format.toList());
     // save switch list local message format
     Setup::setSwitchListLocalPrefix(switchListLocalPrefix->text());
     format = QVector<QString>(switchListLocalMessageList.size());
     for (int i = 0; i < switchListLocalMessageList.size(); i++) {
         QComboBox* cb = switchListLocalMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     Setup::setLocalSwitchListMessageFormat(format.toList());
     // hazardous comment
     Setup::setHazardousMsg(hazardousTextField->text());
     // misplaced car comment
     Setup::setMiaComment(commentTextArea->toHtml());
     Setup::setSwitchListFormatSameAsManifest(formatSwitchListCheckBox->isChecked());
     Setup::setPrintLocationCommentsEnabled(printLocCommentsCheckBox->isChecked());
     Setup::setPrintRouteCommentsEnabled(printRouteCommentsCheckBox->isChecked());
     Setup::setPrintLoadsAndEmptiesEnabled(printLoadsEmptiesCheckBox->isChecked());
     Setup::set12hrFormatEnabled(use12hrFormatCheckBox->isChecked());
     Setup::setPrintValidEnabled(printValidCheckBox->isChecked());
     Setup::setSortByTrackEnabled(sortByTrackCheckBox->isChecked());
     Setup::setPrintHeadersEnabled(printHeadersCheckBox->isChecked());
     Setup::setPrintTimetableNameEnabled(printTimetableNameCheckBox->isChecked());
     Setup::setTruncateManifestEnabled(truncateCheckBox->isChecked());
     Setup::setUseDepartureTimeEnabled(departureTimeCheckBox->isChecked());
     Setup::setManifestEditorEnabled(editManifestCheckBox->isChecked());
     Setup::setTrackSummaryEnabled(trackSummaryCheckBox->isChecked());
     Setup::setSwitchListRouteLocationCommentEnabled(routeLocationCheckBox->isChecked());

     // reload combo boxes if tab changed
     bool oldTabEnabled = Setup::isTabEnabled();
     Setup::setTabEnabled(tabFormatCheckBox->isChecked());
     if (oldTabEnabled ^ Setup::isTabEnabled()) {
         loadFormatComboBox();
     }

     // recreate all train manifests
     TrainManager::instance()->setTrainsModified();

     OperationsSetupXml::instance()->writeOperationsFile();
 }

 //@Override
 /*public*/ bool PrintOptionPanel::isDirty() {
     if ( // font name
             Setup::getFontName()!=(fontComboBox->currentText())
             // font size
             || Setup::getManifestFontSize() != fontSizeComboBox->currentText().toInt()
             // page orientation
             || Setup::getManifestOrientation()!=(manifestOrientationComboBox->currentText())
             || Setup::getSwitchListOrientation()!=(switchListOrientationComboBox->currentText())
             // format
             || Setup::getManifestFormat()!=(manifestFormatComboBox->currentText())
             // drop and pick up color option
             || Setup::getDropTextColor()!=(dropComboBox->currentText())
             || Setup::getPickupTextColor()!=(pickupComboBox->currentText())
             || Setup::getLocalTextColor()!=(localComboBox->currentText())
             // hazardous comment
             || Setup::getHazardousMsg()!=(hazardousTextField->text())
             // misplaced car comment
             || Setup::getMiaComment()!=(commentTextArea->toHtml())
             || Setup::isSwitchListFormatSameAsManifest() != formatSwitchListCheckBox->isChecked()
             || Setup::isPrintLocationCommentsEnabled() != printLocCommentsCheckBox->isChecked()
             || Setup::isPrintRouteCommentsEnabled() != printRouteCommentsCheckBox->isChecked()
             || Setup::isPrintLoadsAndEmptiesEnabled() != printLoadsEmptiesCheckBox->isChecked()
             || Setup::is12hrFormatEnabled() != use12hrFormatCheckBox->isChecked()
             || Setup::isPrintValidEnabled() != printValidCheckBox->isChecked()
             || Setup::isSortByTrackEnabled() != sortByTrackCheckBox->isChecked()
             || Setup::isPrintHeadersEnabled() != printHeadersCheckBox->isChecked()
             || Setup::isPrintTimetableNameEnabled() != printTimetableNameCheckBox->isChecked()
             || Setup::isTruncateManifestEnabled() != truncateCheckBox->isChecked()
             || Setup::isUseDepartureTimeEnabled() != departureTimeCheckBox->isChecked()
             || Setup::isManifestEditorEnabled() != editManifestCheckBox->isChecked()
             || Setup::isSwitchListRouteLocationCommentEnabled() != routeLocationCheckBox->isChecked()
             || Setup::isTrackSummaryEnabled() != trackSummaryCheckBox->isChecked()
             || Setup::isTabEnabled() != this->tabFormatCheckBox->isChecked())
     {
         return true;
     }
     // save engine pick up message format
     QVector<QString> format = QVector<QString>(enginePickupMessageList.size());
     for (int i = 0; i < enginePickupMessageList.size(); i++) {
         QComboBox* cb = enginePickupMessageList.at(i);
         format.replace(i,  cb->currentText());
     }
     if (Setup::getPickupEnginePrefix()!=(pickupEngPrefix->text())
             || (Setup::getPickupEngineMessageFormat() != format.toList()))
     {
         return true;
     }
     // save engine drop message format
     format = QVector<QString>(engineDropMessageList.size());
     for (int i = 0; i < engineDropMessageList.size(); i++) {
         QComboBox* cb = engineDropMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     if (Setup::getDropEnginePrefix()!=(dropEngPrefix->text())
             || (Setup::getDropEngineMessageFormat()!= format.toList()))
     {
         return true;
     }
     // save car pick up message format
     format = QVector<QString>(carPickupMessageList.size());
     for (int i = 0; i < carPickupMessageList.size(); i++) {
         QComboBox* cb = carPickupMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     if (Setup::getPickupCarPrefix()!=(this->pickupCarPrefix->text())
             || (Setup::getPickupManifestMessageFormat()!= format.toList())) {
         return true;
     }
     // save car drop message format
     format = QVector<QString>(carDropMessageList.size());
     for (int i = 0; i < carDropMessageList.size(); i++) {
         QComboBox* cb = carDropMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     if (Setup::getDropCarPrefix()!=(this->dropCarPrefix->text())
             || (Setup::getDropManifestMessageFormat() != format.toList())) {
         return true;
     }
     // save local message format
     format = QVector<QString>(localMessageList.size());
     for (int i = 0; i < localMessageList.size(); i++) {
         QComboBox* cb = localMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     if (Setup::getLocalPrefix()!=(this->localPrefix->text())
             || (Setup::getLocalManifestMessageFormat()!= format.toList())) {
         return true;
     }
     // save switch list car pick up message format
     format = QVector<QString>(switchListCarPickupMessageList.size());
     for (int i = 0; i < switchListCarPickupMessageList.size(); i++) {
         QComboBox* cb = switchListCarPickupMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     if (Setup::getSwitchListPickupCarPrefix()!=(this->switchListPickupCarPrefix->text())
             || (Setup::getPickupSwitchListMessageFormat() != format.toList())) {
         return true;
     }
     // save switch list car drop message format
     format = QVector<QString>(switchListCarDropMessageList.size());
     for (int i = 0; i < switchListCarDropMessageList.size(); i++) {
         QComboBox* cb = switchListCarDropMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     if (Setup::getSwitchListDropCarPrefix()!=(this->switchListDropCarPrefix->text())
             || (Setup::getDropSwitchListMessageFormat()!= format.toList())) {
         return true;
     }
     // save switch list local message format
     format = QVector<QString>(switchListLocalMessageList.size());
     for (int i = 0; i < switchListLocalMessageList.size(); i++) {
         QComboBox* cb = switchListLocalMessageList.at(i);
         format.replace(i, cb->currentText());
     }
     return Setup::getSwitchListLocalPrefix()!=(this->switchListLocalPrefix->text())
             || (Setup::getLocalSwitchListMessageFormat() !=  format.toList());
 }
}
