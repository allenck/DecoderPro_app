#include "trainmanifestoptionframe.h"
#include "jfilechooser.h"
#include "file.h"
#include <QBoxLayout>
#include "jtextfield.h"
#include "train.h"
#include <QLabel>
#include "jbutton.h"
#include "gridbaglayout.h"
#include <QCheckBox>
#include "traineditframe.h"
#include <QScrollArea>
#include "control.h"
#include "setup.h"
#include "xmlfile.h"
#include "jfilechooser.h"
#include "operationsxml.h"
#include "file.h"
#include "logger.h"
#include "fileutil.h"
#include "borderfactory.h"

namespace Operations
{
 /**
  * Frame for user edit of the train manifest options
  *
  * @author Dan Boudreau Copyright (C) 2010, 2013
  * @version $Revision: 28746 $
  */
 ///*public*/ class TrainManifestOptionFrame extends OperationsFrame {

  /**
   *
   */
 // private static final long serialVersionUID = 4221631294388076034L;

  /*public*/ TrainManifestOptionFrame::TrainManifestOptionFrame(QWidget* parent)
     : OperationsFrame(tr("Options"), parent)
  {
 log = new Logger("TrainManifestOptionFrame");
      //(tr("TitleOptions"));
      _train = NULL;

      // labels
      textPad = new QLabel("   ");
      logoURL = new QLabel("");

      // major buttons
      saveButton = new JButton(tr("Save"));
      addLogoButton = new JButton(tr("Add Logo"));
      removeLogoButton = new JButton(tr("Remove Logo"));

      // radio buttons
      // check boxes
      ShowTimesCheckBox = new QCheckBox(tr("ShowTimes"));

      // text fields
      railroadNameTextField = new JTextField(35);
      logoTextField = new JTextField(35);

      /**
       * We always use the same file chooser in this class, so that the user's
       * last-accessed directory remains available.
       */
      fc = XmlFile::userFileChooser(tr("Images"));

  }

  /*public*/ void TrainManifestOptionFrame::initComponents(TrainEditFrame* parent) {

      // the following code sets the frame's initial state
      //parent->setChildFrame(this);
      _train = parent->_train;

      // add tool tips
      addLogoButton->setToolTip(tr("Add a logo to this train's manifest"));
      removeLogoButton->setToolTip(tr("Remove logo from this train's manifest"));

      // Option panel
      //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

      JPanel* pOptionNameFrame = new JPanel();
      pOptionNameFrame->setLayout(new QVBoxLayout);
      JPanel* pOptionName = new JPanel();
      pOptionName->setLayout(new GridBagLayout());
      QScrollArea* pOptionNamePane = new QScrollArea(/*pOptionName*/);
      pOptionNamePane->setWidgetResizable(true);
      pOptionNameFrame->layout()->addWidget(pOptionNamePane);
      pOptionNameFrame->setBorder(BorderFactory::createTitledBorder(tr("Optional Railroad Name for this Train")));
      addItem(pOptionName, railroadNameTextField, 0, 0);

      // manifest logo
      JPanel* pOptionLogoFrame = new JPanel;
      pOptionLogoFrame->setLayout(new QVBoxLayout);
      JPanel* pOptionLogo = new JPanel();
      pOptionLogo->setLayout(new GridBagLayout());
      QScrollArea* pOptionLogoPane = new QScrollArea(/*pOptionLogo*/);
      pOptionLogoPane->setWidgetResizable(true);
      pOptionLogoFrame->layout()->addWidget(pOptionLogoPane);
      pOptionLogoFrame->setBorder(BorderFactory::createTitledBorder(tr("Optional Logo for this Train ")));
      addItem(pOptionLogo, textPad, 2, 18);
      addItem(pOptionLogo, addLogoButton, 2, 20);
      addItemLeft(pOptionLogo, removeLogoButton, 0, 21);
      addItemWidth(pOptionLogo, logoURL, 6, 1, 21);
      updateLogoButtons();

      // Checkboxes
      JPanel* pCheckboxesFrame = new JPanel;
      pCheckboxesFrame->setLayout(new QVBoxLayout);
      JPanel* pCheckboxes = new JPanel();
      pCheckboxes->setLayout(new GridBagLayout());
      QScrollArea* pCheckboxesPane = new QScrollArea(/*pCheckboxes*/);
      pCheckboxesPane->setWidgetResizable(true);
      pCheckboxesFrame->layout()->addWidget(pCheckboxesPane);
      pCheckboxesFrame
              ->setBorder(BorderFactory::createTitledBorder(tr("Manifest")));
      addItem(pCheckboxes, ShowTimesCheckBox, 0, 0);

      // row 11
      JPanel* pControl = new JPanel();
      pControl->setLayout(new GridBagLayout());
      addItem(pControl, saveButton, 3, 9);

      pOptionNamePane->setWidget(pOptionName);
      thisLayout->addWidget(pOptionNameFrame);
      pOptionLogoPane->setWidget(pOptionLogo);
      thisLayout->addWidget(pOptionLogoFrame);
      pCheckboxesPane->setWidget(pCheckboxes);
      thisLayout->addWidget(pCheckboxesPane);
      thisLayout->addWidget(pControl);

      // setup buttons
      addButtonAction(addLogoButton);
      addButtonAction(removeLogoButton);
      addButtonAction(saveButton);

      // load fields
      if (_train != NULL) {
          railroadNameTextField->setText(_train->getRailroadName());
          ShowTimesCheckBox->setChecked(_train->isShowArrivalAndDepartureTimesEnabled());
      }

      // build menu
      addHelpMenu("package.jmri.jmrit.operations.Operations_TrainManifestOptions", true);// NOI18N

      adjustSize();
      setMinimumSize(QSize(Control::panelWidth400, Control::panelHeight250));
      setVisible(true);
  }

  /*private*/ void TrainManifestOptionFrame::updateLogoButtons() {
      if (_train != NULL) {
          bool flag = _train->getManifestLogoURL()==("");
          addLogoButton->setVisible(flag);
          removeLogoButton->setVisible(!flag);
          logoURL->setText(_train->getManifestLogoURL());
          pack();
      }
  }


  /*private*/ File* TrainManifestOptionFrame::selectFile() {
      if (fc == NULL) {
          log->error("Could not find user directory");
      } else {
          fc->setDialogTitle(tr("FindDesiredImage"));
          // when reusing the chooser, make sure new files are included
          //fc.rescanCurrentDirectory();
          int retVal = fc->showOpenDialog(NULL);
          // handle selection or cancel
          if (retVal == JFileChooser::APPROVE_OPTION) {
              File* file = fc->getSelectedFile();
              return file;
          }
      }
      return NULL;
  }

  // Save button
  /*public*/ void TrainManifestOptionFrame::buttonActionPerformed(QWidget* ae)
  {
 JButton* source = (JButton*)ae;
      if (source == addLogoButton) {
          log->debug("add logo button pressed");
          File* f = selectFile();
          if (f != NULL && _train != NULL) {
              _train->setManifestLogoURL(FileUtil::getPortableFilename(f));

          updateLogoButtons();
      }
      if (source == removeLogoButton) {
          log->debug("remove logo button pressed");
          if (_train != NULL) {
              _train->setManifestLogoURL("");
          }
          updateLogoButtons();
      }
      if (source == saveButton) {
          if (_train != NULL) {
              _train->setRailroadName(railroadNameTextField->text());
              _train->setShowArrivalAndDepartureTimes(ShowTimesCheckBox->isChecked());
              _train->setModified(true);
          }
          OperationsXml::save();
          if (Setup::isCloseWindowOnSaveEnabled()) {
              dispose();
          }
      }
  }

 }
/*public*/ QString TrainManifestOptionFrame::getClassName()
{
 return "jmri.jmrit.operations.trains.tools.TrainManifestOptionFrame";
}

}
