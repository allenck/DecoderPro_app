#ifndef PRINTOPTIONPANEL_H
#define PRINTOPTIONPANEL_H

#include "operationspreferencespanel.h"

class QScrollArea;
class QFontComboBox;
class QGroupBox;
class File;
class JFileChooser;
class JTextField;
class QLabel;
namespace Operations
{
 class PrintOptionPanel : public OperationsPreferencesPanel
 {
  Q_OBJECT
 public:
  PrintOptionPanel(QWidget* parent = 0);
  /*public*/ QString getTabbedPreferencesTitle() override;
  /*public*/ QString getPreferencesTooltip() override;
  /*public*/ void savePreferences() override;
  /*public*/ bool isDirty() override;
  /*public*/ QString className() override {return "jmri.jmrit.operations.PrintOptionPanel";}
 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae) override;
  /*public*/ void checkBoxActionPerformed(QWidget* ae) override;
  /*public*/ void comboBoxActionPerformed(QWidget* ae) override;

 private:
   Logger* log;
  // labels
  QLabel* logoURL;//= new JLabel("");

  // major buttons
  QPushButton* saveButton;//= new JButton(Bundle.getMessage("Save"));
  QPushButton* addLogoButton;//= new JButton(Bundle.getMessage("AddLogo"));
  QPushButton* removeLogoButton;//= new JButton(Bundle.getMessage("RemoveLogo"));

  QPushButton* addEngPickupComboboxButton;//= new JButton("+");
  QPushButton* deleteEngPickupComboboxButton;//= new JButton("-");
  QPushButton* addEngDropComboboxButton;//= new JButton("+");
  QPushButton* deleteEngDropComboboxButton;//= new JButton("-");
  QPushButton* addCarPickupComboboxButton;//= new JButton("+");
  QPushButton* deleteCarPickupComboboxButton;//= new JButton("-");
  QPushButton* addCarDropComboboxButton;//= new JButton("+");
  QPushButton* deleteCarDropComboboxButton;//= new JButton("-");
  QPushButton* addLocalComboboxButton;//= new JButton("+");
  QPushButton* deleteLocalComboboxButton;//= new JButton("-");
  QPushButton* addSwitchListPickupComboboxButton;//= new JButton("+");
  QPushButton* deleteSwitchListPickupComboboxButton;//= new JButton("-");
  QPushButton* addSwitchListDropComboboxButton;//= new JButton("+");
  QPushButton* deleteSwitchListDropComboboxButton;//= new JButton("-");
  QPushButton* addSwitchListLocalComboboxButton;//= new JButton("+");
  QPushButton* deleteSwitchListLocalComboboxButton;//= new JButton("-");

  // check boxes
  QCheckBox* tabFormatCheckBox;//= new JCheckBox(Bundle.getMessage("TabFormat"));
  QCheckBox* formatSwitchListCheckBox;//= new JCheckBox(Bundle.getMessage("SameAsManifest"));
  QCheckBox* editManifestCheckBox;//= new JCheckBox(Bundle.getMessage("UseTextEditor"));
  QCheckBox* printLocCommentsCheckBox;//= new JCheckBox(Bundle.getMessage("PrintLocationComments"));
  QCheckBox* printRouteCommentsCheckBox;//= new JCheckBox(Bundle.getMessage("PrintRouteComments"));
  QCheckBox* printLoadsEmptiesCheckBox;//= new JCheckBox(Bundle.getMessage("PrintLoadsEmpties"));
  QCheckBox* printTimetableNameCheckBox;//= new JCheckBox(Bundle.getMessage("PrintTimetableName"));
  QCheckBox* use12hrFormatCheckBox;//= new JCheckBox(Bundle.getMessage("12hrFormat"));
  QCheckBox* printValidCheckBox;//= new JCheckBox(Bundle.getMessage("PrintValid"));
  QCheckBox* sortByTrackCheckBox;//= new JCheckBox(Bundle.getMessage("SortByTrack"));
  QCheckBox* printHeadersCheckBox;//= new JCheckBox(Bundle.getMessage("PrintHeaders"));
  QCheckBox* truncateCheckBox;//= new JCheckBox(Bundle.getMessage("Truncate"));
  QCheckBox* departureTimeCheckBox;//= new JCheckBox(Bundle.getMessage("DepartureTime"));
  QCheckBox* trackSummaryCheckBox;//= new JCheckBox(Bundle.getMessage("TrackSummary"));
  QCheckBox* routeLocationCheckBox;//= new JCheckBox(Bundle.getMessage("RouteLocation"));

  // text field
  JTextField* pickupEngPrefix;//= new JTextField(10);
  JTextField* dropEngPrefix;//= new JTextField(10);
  JTextField* pickupCarPrefix;//= new JTextField(10);
  JTextField* dropCarPrefix;//= new JTextField(10);
  JTextField* localPrefix;//= new JTextField(10);
  JTextField* switchListPickupCarPrefix;//= new JTextField(10);
  JTextField* switchListDropCarPrefix;//= new JTextField(10);
  JTextField* switchListLocalPrefix;//= new JTextField(10);
  JTextField* hazardousTextField;//= new JTextField(20);

  // text area
  HtmlTextEdit* commentTextArea;//= new JTextArea(2, 90);

  QScrollArea* commentScroller;//= new JScrollPane(commentTextArea,
//          JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

  // combo boxes
  QFontComboBox* fontComboBox;//= new JComboBox<>();
  JComboBox* manifestFormatComboBox;//= Setup.getManifestFormatComboBox();
  JComboBox* manifestOrientationComboBox;//= Setup.getOrientationComboBox();
  JComboBox* fontSizeComboBox;//= new JComboBox<>();
  JComboBox* pickupComboBox;//= Setup.getPrintColorComboBox(); // colors
  JComboBox* dropComboBox;//= Setup.getPrintColorComboBox();
  JComboBox* localComboBox;//= Setup.getPrintColorComboBox();
  JComboBox* switchListOrientationComboBox;//= Setup.getOrientationComboBox();

  // message formats
  QList<JComboBox*> enginePickupMessageList;//= new ArrayList<>();
  QList<JComboBox*> engineDropMessageList;//= new ArrayList<>();
  QList<JComboBox*> carPickupMessageList;//= new ArrayList<>();
  QList<JComboBox*> carDropMessageList;//= new ArrayList<>();
  QList<JComboBox*> localMessageList;//= new ArrayList<>();
  QList<JComboBox*> switchListCarPickupMessageList;//= new ArrayList<>();
  QList<JComboBox*> switchListCarDropMessageList;//= new ArrayList<>();
  QList<JComboBox*> switchListLocalMessageList;//= new ArrayList<>();

  // manifest panels
  QWidget* pManifest;//= new JPanel();
  JPanel* pEngPickup;//= new JPanel();
  JPanel* pEngDrop;//= new JPanel();
  JPanel* pPickup;//= new JPanel();
  JPanel* pDrop;//= new JPanel();
  JPanel* pLocal;//= new JPanel();

  // switch list panels
  JPanel* pSwitchListOrientation;//= new JPanel();
  JPanel* pSwPickup;//= new JPanel();
  JPanel* pSwDrop;//= new JPanel();
  JPanel* pSwLocal;//= new JPanel();
  /*private*/ void loadFontComboBox();
  /*private*/ void setSwitchListVisible(bool b);
  /**
   * We always use the same file chooser in this class, so that the user's
   * last-accessed directory remains available.
   */
  JFileChooser* fc;// = XmlFile::userFileChooser(tr("Images"));
  /*private*/ File* selectFile();
  /*private*/ void updateLogoButtons();
  /*private*/ void loadFormatComboBox();
  /*private*/ void addComboBox(QWidget* panel, QList<JComboBox*> list, JComboBox* box);
  /*private*/ void removeComboBox(QWidget* panel, QList<JComboBox*>list);

 };
}
#endif // PRINTOPTIONPANEL_H
