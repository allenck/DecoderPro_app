#ifndef SETUPEXCELPROGRAMFRAME_H
#define SETUPEXCELPROGRAMFRAME_H
#include "operationsframe.h"
#include <QCheckBox>
#include "jbutton.h"
#include "jtextfield.h"
#include <QGroupBox>
#include <QVBoxLayout>

class File;
namespace Operations
{
 class SetupExcelProgramFrame : public OperationsFrame
 {
 public:
  SetupExcelProgramFrame(QWidget* parent = 0);
  /*public*/ void initComponents();

 private:
  QCheckBox* generateCheckBox;// = new JCheckBox();
  // text windows
  JTextField* fileNameTextField;// = new JTextField(30);

  // major buttons
  JButton* addButton;//= new JButton(Bundle.getMessage("Add"));
  JButton* testButton;// = new JButton(Bundle.getMessage("Test"));
  JButton* saveButton;// = new JButton(Bundle.getMessage("ButtonSave"));

  // directory
  JPanel* pDirectoryName;// = new JPanel();
  QVBoxLayout* pDirectoryNameLayout;
 protected:
  /*protected*/ File* selectFile(QString directoryName);

 friend class SetupExcelProgramManifestFrame;
 };
}
#endif // SETUPEXCELPROGRAMFRAME_H
