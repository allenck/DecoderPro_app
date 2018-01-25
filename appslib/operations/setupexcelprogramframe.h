#ifndef SETUPEXCELPROGRAMFRAME_H
#define SETUPEXCELPROGRAMFRAME_H
#include "operationsframe.h"
#include <QCheckBox>
#include <QPushButton>
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
  QPushButton* addButton;//= new JButton(Bundle.getMessage("Add"));
  QPushButton* testButton;// = new JButton(Bundle.getMessage("Test"));
  QPushButton* saveButton;// = new JButton(Bundle.getMessage("ButtonSave"));

  // directory
  QGroupBox* pDirectoryName;// = new JPanel();
  QVBoxLayout* pDirectoryNameLayout;
 protected:
  /*protected*/ File* selectFile(QString directoryName);

 friend class SetupExcelProgramManifestFrame;
 };
}
#endif // SETUPEXCELPROGRAMFRAME_H
