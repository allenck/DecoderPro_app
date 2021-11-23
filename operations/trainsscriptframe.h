#ifndef TRAINSSCRIPTFRAME_H
#define TRAINSSCRIPTFRAME_H
#include "operationsframe.h"

class File;
class JFileChooser;
namespace Operations
{
 class TrainManager;
 class TrainsScriptFrame : public OperationsFrame
 {
 public:
  TrainsScriptFrame(QWidget* parent =0);
  /*public*/ void initComponents();
  /*public*/ void dispose();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae) ;
  /*public*/ void buttonActionRemoveStartUpScript(QWidget* ae);
  /*public*/ void buttonActionRemoveShutDownScript(QWidget* ae);

 private:
  Logger* log;
  TrainManager* trainManager;// TrainManager.instance();

  // script panels
  JPanel* pStartUpScript;// new JPanel();
  JPanel* pShutDownScript;// new JPanel();
  QScrollArea* startUpScriptPane;
  QScrollArea* shutDownScriptPane;

  // labels
  // major buttons
  JButton* addStartUpScriptButton;// new JButton(Bundle.getMessage("AddScript"));
  JButton* addShutDownScriptButton;// new JButton(Bundle.getMessage("AddScript"));
  JButton* runStartUpScriptButton;// new JButton(Bundle.getMessage("RunScripts"));
  JButton* runShutDownScriptButton;// new JButton(Bundle.getMessage("RunScripts"));
  JButton* saveButton;// new JButton(Bundle.getMessage("Save"));
  /*private*/ void updateStartUpScriptPanel();
  /*private*/ void updateShutDownScriptPanel();
  /*private*/ File* selectFile();
  /*private*/ void enableButtons(bool enabled);
  /*private*/ void runScripts(QStringList scripts);
  /*private*/ void packFrame();
  /**
   * We always use the same file chooser in this class, so that the user's
   * last-accessed directory remains available.
   */
  JFileChooser* fc;// = XmlFile::userFileChooser(tr("PythonScriptFiles"), "py"); // NOI18N

 };
}
#endif // TRAINSSCRIPTFRAME_H
