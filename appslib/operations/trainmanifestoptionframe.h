#ifndef TRAINMANIFESTOPTIONFRAME_H
#define TRAINMANIFESTOPTIONFRAME_H

#include "operationsframe.h"

class File;
class JFileChooser;
class QLabel;
class JTextField;
namespace Operations
{
 class Train;
 class TrainEditFrame;
 class TrainManifestOptionFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrainManifestOptionFrame(QWidget* parent = 0);
  /*public*/ void initComponents(TrainEditFrame* parent);
 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  Train* _train;// = null;

  // labels
  QLabel* textPad;// =new JLabel("   ");
  QLabel* logoURL;// =new JLabel("");

  // major buttons
  QPushButton* saveButton;// =new JButton(Bundle.getMessage("Save"));
  QPushButton* addLogoButton;// =new JButton(Bundle.getMessage("AddLogo"));
  QPushButton* removeLogoButton;// =new JButton(Bundle.getMessage("RemoveLogo"));

  // radio buttons
  // check boxes
  QCheckBox* ShowTimesCheckBox;// =new JCheckBox(Bundle.getMessage("ShowTimes"));

  // text fields
  JTextField* railroadNameTextField;// =new JTextField(35);
  JTextField* logoTextField;// =new JTextField(35);
  /*private*/ void updateLogoButtons();
  /**
   * We always use the same file chooser in this class, so that the user's
   * last-accessed directory remains available.
   */
  JFileChooser* fc;// = jmri.jmrit.XmlFile.userFileChooser(tr("Images"));
  /*private*/ File* selectFile();
  Logger* log;

 };
}
#endif // TRAINMANIFESTOPTIONFRAME_H
