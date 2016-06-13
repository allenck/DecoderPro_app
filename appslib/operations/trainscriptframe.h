#ifndef TRAINSCRIPTFRAME_H
#define TRAINSCRIPTFRAME_H

#include "operationsframe.h"

class File;
class QLabel;
class JFileChooser;
namespace Operations
{
 class Train;
 class TrainEditFrame;
 class TrainManager;
 class TrainManagerXml;
 class TrainScriptFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  TrainScriptFrame(QWidget* parent = 0);
  /*public*/ void initComponents(TrainEditFrame* parent);
 public slots:
  /*public*/ void buttonActionRemoveBuildScript(QWidget* ae);
  /*public*/ void buttonActionPerformed(QWidget* ae);
  /*public*/ void buttonActionRemoveAfterBuildScript(QWidget* ae);
  /*public*/ void buttonActionRemoveMoveScript(QWidget* ae);
  /*public*/ void buttonActionRemoveTerminationScript(QWidget* ae);

 private:
  Logger* log;
  /**
   * We always use the same file chooser in this class, so that the user's
   * last-accessed directory remains available.
   */
  JFileChooser* fc;// = jmri.jmrit.XmlFile.userFileChooser(Bundle.getMessage("PythonScriptFiles"), "py"); // NOI18N
  TrainManager* manager;
  TrainManagerXml* managerXml;

  Train* _train;// =NULL;

  // script panels
  QWidget* pBuildScript;// =new JPanel();
  QWidget* pAfterBuildScript;// =new JPanel();
  QWidget* pMoveScript;// =new JPanel();
  QWidget* pTerminationScript;// =new JPanel();
  QScrollArea* buildScriptPane;
  QScrollArea* afterBuildScriptPane;
  QScrollArea* moveScriptPane;
  QScrollArea* terminationScriptPane;

  // labels
  QLabel* trainName;// =new JLabel();
  QLabel* trainDescription;// =new JLabel();

  // major buttons
  QPushButton* addBuildScriptButton;// =new JButton(Bundle.getMessage("AddScript"));
  QPushButton* addAfterBuildScriptButton;// =new JButton(Bundle.getMessage("AddScript"));
  QPushButton* addMoveScriptButton;// =new JButton(Bundle.getMessage("AddScript"));
  QPushButton* addTerminationScriptButton;// =new JButton(Bundle.getMessage("AddScript"));

  QPushButton* runBuildScriptButton;// =new JButton(Bundle.getMessage("RunScripts"));
  QPushButton* runAfterBuildScriptButton;// =new JButton(Bundle.getMessage("RunScripts"));
  QPushButton* runMoveScriptButton;// =new JButton(Bundle.getMessage("RunScripts"));
  QPushButton* runTerminationScriptButton;// =new JButton(Bundle.getMessage("RunScripts"));

  QPushButton* saveTrainButton;// =new JButton(Bundle.getMessage("SaveTrain"));
  /*private*/ void updateBuildScriptPanel();
  /*private*/ void updateAfterBuildScriptPanel();
  /*private*/ void updateMoveScriptPanel();
  /*private*/ void updateTerminationScriptPanel();
  /*private*/ void runScripts(QStringList scripts);
  /*private*/ File* selectFile();
  /*private*/ void enableButtons(bool enabled);

 };
}
#endif // TRAINSCRIPTFRAME_H
