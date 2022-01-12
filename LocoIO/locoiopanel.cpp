#include "locoiopanel.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "jtextfield.h"
#include "loconetsystemconnectionmemo.h"
#include "locoiodata.h"
#include "tablecolumnmodel.h"
#include "jtable.h"
#include <QComboBox>
#include "locoio.h"
#include "locoiotablemodel.h"
#include <QMessageBox>

LocoIOPanel::LocoIOPanel(QWidget *parent) :
  LnPanel(parent)
{
 addrField = new JTextField("00");
 subAddrField = new JTextField("00");
 status = new QLabel("<unknown>");
 firmware = new QLabel("<unknown>");
 locobuffer = new QLabel("<unknown>");

 addrSetButton = NULL;
 probeButton = NULL;
 readAllButton = NULL;
 writeAllButton = NULL;
 saveButton = NULL;
 openButton = NULL;
 log = new Logger("LocoIOPanel");
}
/**
 * Panel displaying and programming a LocoIO configuration.
 *
 * @author	Bob Jacobsen Copyright (C) 2002
 * @version	$Revision: 28746 $
 */
///*public*/ class LocoIOPanel extends jmri.jmrix.loconet.swing.LnPanel
//        implements java.beans.PropertyChangeListener {

/**
 *
 */
//private static final long serialVersionUID = 2652944223325097266L;

//    /*public*/ LocoIOPanel() {
//        super();

//    }

/*public*/ void LocoIOPanel::initComponents(LocoNetSystemConnectionMemo* memo)
{
 this->memo = memo;
 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));
 ln = memo->getLnTrafficController();
 // creating the table (done here to ensure order OK)
 data = new LocoIOData(addrField->text().toInt(0,16),
         subAddrField->text().toInt(0,16),
         memo->getLnTrafficController());
 model = new LocoIOTableModel(data);
 table = new JTable(model);
 model->setColumnToHoldButton(table, LocoIOTableModel::CAPTURECOLUMN, new QPushButton());
 model->setColumnToHoldButton(table, LocoIOTableModel::READCOLUMN, new QPushButton());
 model->setColumnToHoldButton(table, LocoIOTableModel::WRITECOLUMN, new QPushButton());
 table->resizeColumnsToContents();
 //scroll = new JScrollPane(table);

 //data->SwingPropertyChangeSupport::addPropertyChangeListener(this);
 connect(data, SIGNAL(notifyPropertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
 // table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
// table.setShowHorizontalLines(true);
// table.setAutoCreateColumnsFromModel(true);

 TableColumnModel* tcm = table->getColumnModel();
 // install a ComboBox editor on the OnMode column
 QComboBox* comboOnBox = new QComboBox(); //<String>(data.getLocoIOModeList().getValidModes());
 comboOnBox->addItems(data->getLocoIOModeList()->getValidModes());
 comboOnBox->setEditable(true);
#if 0
 DefaultCellEditor modeEditor = new DefaultCellEditor(comboOnBox);
 tcm.getColumn(LocoIOTableModel.MODECOLUMN).setCellEditor(modeEditor);

 // install a button renderer & editor in the Read, Write and Compare columns
 ButtonRenderer buttonRenderer = new ButtonRenderer();
 tcm.getColumn(LocoIOTableModel.READCOLUMN).setCellRenderer(buttonRenderer);
 tcm.getColumn(LocoIOTableModel.WRITECOLUMN).setCellRenderer(buttonRenderer);
 tcm.getColumn(LocoIOTableModel.CAPTURECOLUMN).setCellRenderer(buttonRenderer);

 TableCellEditor buttonEditor = new ButtonEditor(new QPushButton());
 tcm.getColumn(LocoIOTableModel.READCOLUMN).setCellEditor(buttonEditor);
 tcm.getColumn(LocoIOTableModel.WRITECOLUMN).setCellEditor(buttonEditor);
 tcm.getColumn(LocoIOTableModel.CAPTURECOLUMN).setCellEditor(buttonEditor);
 // ensure the table rows, columns have enough room for buttons and comboBox contents
 table.setRowHeight(new QPushButton("Capture").getPreferredSize().height);
 for (int col = 0; col < LocoIOTableModel.HIGHESTCOLUMN; col++) {
     table.getColumnModel().getColumn(col).setPreferredWidth(model.getPreferredWidth(col));
 }
#endif
 // A pane for SV0, SV1, SV2, the board sub address and the PIC version
 QWidget* p1 = new QWidget();
 QHBoxLayout* p1Layout;
 p1->setLayout(p1Layout = new QHBoxLayout); //(p1, BoxLayout.X_AXIS));
 p1Layout->addWidget(new QLabel("LocoIO address: 0x"));
 addrField->setMaximumSize(addrField->sizeHint());
 subAddrField->setMaximumSize(subAddrField->sizeHint());
 p1Layout->addWidget(addrField);
 p1Layout->addWidget(new QLabel("/"));
 p1Layout->addWidget(subAddrField);
 //p1Layout->addWidget(Box.createGlue());  // -------------------
 probeButton = new QPushButton("Probe");
// probeButton.addActionListener(
//         new ActionListener() {
//             /*public*/ void actionPerformed(ActionEvent a) {
//                 data.setLIOVersion("<Not found>");
//                 LocoIO.probeLocoIOs(ln);
//             }
//         });
 connect(probeButton, SIGNAL(clicked()), this, SLOT(on_probeButtonClicked()));
 p1Layout->addWidget(probeButton);
 //p1Layout->addWidget(Box.createGlue());  // -------------------
 readAllButton = new QPushButton("Read All");
// readAllButton.addActionListener(
//         new ActionListener() {
//             /*public*/ void actionPerformed(ActionEvent a) {
//                 data.readAll();
//             }
//         });
 connect(readAllButton, SIGNAL(clicked()), this, SLOT(on_readAllButtonClicked()));
 p1Layout->addWidget(readAllButton);
 writeAllButton = new QPushButton("Write All");
// writeAllButton.addActionListener(
//         new ActionListener() {
//             /*public*/ void actionPerformed(ActionEvent a) {
//                 data.writeAll();
//             }
//         });
 connect(writeAllButton, SIGNAL(clicked()), this, SLOT(on_writeAllButtonClicked()));
 p1Layout->addWidget(writeAllButton);
 //p1Layout->addWidget(Box.createGlue());  // -------------------
 addrSetButton = new QPushButton("Set address");
 p1Layout->addWidget(addrSetButton);
// addrSetButton.addActionListener(
//         new ActionListener() {
//             /*public*/ void actionPerformed(ActionEvent a) {
//                 addrSet();
//             }
//         });
 connect(addrSetButton, SIGNAL(clicked()), this, SLOT(addrSet()));
 //p1Layout->addWidget(Box.createGlue());  // -------------------

 /*
  openButton = new QPushButton("Load...");
  openButton.setEnabled(false);
  p1Layout->addWidget(openButton);

  saveButton = new QPushButton("Save...");
  saveButton.setEnabled(false);
  p1Layout->addWidget(saveButton);
  */
 QWidget* p2 = new QWidget();
 QHBoxLayout* p2Layout;
 p2->setLayout(p2Layout = new QHBoxLayout); //(p2, BoxLayout.X_AXIS));
 p2Layout->addWidget(new QLabel("Locobuffer rev: "));
 p2Layout->addWidget(locobuffer);
 //p2Layout->addWidget(Box.createGlue());  // -------------------
 p2Layout->addWidget(new QLabel("Status: "));
 p2Layout->addWidget(status);
// p2Layout->addWidget(Box.createGlue());  // -------------------
 p2Layout->addWidget(new QLabel("LocoIO Firmware rev: "));
 p2Layout->addWidget(firmware);

 QWidget* p3 = new QWidget();
 QVBoxLayout* p3Layout;
 p3->setLayout(p3Layout = new QVBoxLayout); //(p3, BoxLayout.Y_AXIS));
 p3Layout->addWidget(p1);
 p3Layout->addWidget(table);

 thisLayout->addWidget(p3);
 thisLayout->addWidget(p2);
#if 0
 // updating the Board address needs to be conveyed to the table
 ActionListener al4UnitAddress = new ActionListener() {
     /*public*/ void actionPerformed(ActionEvent a) {
         try {
             data.setUnitAddress(
                     Integer.valueOf(addrField.getText(), 16).intValue(),
                     Integer.valueOf(subAddrField.getText(), 16).intValue());
         } catch (NullPointerException* e) {
             log->error("Caught NullPointerException", e);
         }
     }
 };
 FocusListener fl4UnitAddress = new FocusListener() {
     /*public*/ void focusGained(FocusEvent event) {
     }

     /*public*/ void focusLost(FocusEvent event) {
         try {
             data.setUnitAddress(
                     Integer.valueOf(addrField.getText(), 16).intValue(),
                     Integer.valueOf(subAddrField.getText(), 16).intValue());
         } catch (NullPointerException* e) {
             log->error("Caught NullPointerException", e);
         }
     }
 };

 addrField.addActionListener(al4UnitAddress);
 subAddrField.addActionListener(al4UnitAddress);
 addrField.addFocusListener(fl4UnitAddress);
 subAddrField.addFocusListener(fl4UnitAddress);
#endif
 connect(addrField, SIGNAL(editingFinished()), this, SLOT(on_al4UnitAddress()));
 connect(subAddrField, SIGNAL(editingFinished()), this, SLOT(on_al4UnitAddress()));
 connect(addrField, SIGNAL(leaveField()), this, SLOT(on_al4UnitAddress()));
 connect(subAddrField, SIGNAL(leaveField()), this, SLOT(on_al4UnitAddress()));

 try {
     data->setUnitAddress(0x51, 0x00);
 } catch (NullPointerException* e) {
     log->error("Caught NullPointerException", e);
 }

}
void LocoIOPanel::on_probeButtonClicked()
{
 data->setLIOVersion("<Not found>");
 LocoIO::probeLocoIOs(ln);
}

void LocoIOPanel::on_readAllButtonClicked()
{
 data->readAll();
}

void LocoIOPanel::on_writeAllButtonClicked()
{
 data->writeAll();
}

/*public*/ QString LocoIOPanel::getHelpTarget() {
    return "package.jmri.jmrix.loconet.locoio.LocoIOFrame";
}

/*public*/ QString LocoIOPanel::getTitle() {
    return LnPanel::getTitle(tr("LocoIO Programmer"));
}
void LocoIOPanel::on_al4UnitAddress()
{
 try
 {
  if(addrField == nullptr || subAddrField == nullptr) throw new NullPointerException("Invalid address");
  data->setUnitAddress(addrField->text().toInt(0,16), subAddrField->text().toInt(0,16));
 }
 catch (NullPointerException* e)
 {
  log->error("Caught NullPointerException", e);
 }
}


/**
 * the SET LOCOIO ADDRESS button was pressed Since this does a broadcast
 * program-all to every LocoIO board on the LocoNet, it needs to be used
 * with caution.
 */
/*protected*/ int LocoIOPanel::cautionAddrSet()
{
 log->info("Caution: Set locoio address is a broadcast operation");
//    return JOptionPane.showOptionDialog(this,
//            "This will set the address of all attached LocoIO boards",
//            "Global operation!",
//            0, JOptionPane.INFORMATION_MESSAGE, NULL,
//            new Object[]{"Cancel", "OK"}, NULL);
 int ret = QMessageBox::warning(this, tr("Warning Global operation!"), tr("This will set the address of all attached LocoIO boards"), QMessageBox::Ok | QMessageBox::Cancel);
 return ret;
}

/*protected*/ void LocoIOPanel::addrSet()
{
 // caution user
 int retval = cautionAddrSet();
 if (retval != 1)
 {
  return; // user cancelled
 }
 int address = addrField->text().toInt(0,16);
 int subAddress = subAddrField->text().toInt(0,16);

 if ((address & 0x7F00) != 0x0100)
 {
  log->warn("High part of address should be 0x01, was "
             + (address & 0x7F00) / 256);
 }
 if ((address & 0x7FFF) == 0x0180)
 {
  log->warn("Only a LocoBuffer can use address 0x80");
 }

 if (subAddress > 126)
 {
  log->warn(tr("subAddress must be [1..126]")
             + ", was " + QString::number(subAddress));
 }
 address = 0x0100 | (address & 0x07F);  // range is [1..79, 81..127]
 subAddress = subAddress & 0x07F;	// range is [1..126]
 LocoIO::programLocoIOAddress(address, subAddress, ln);
}

/*public*/ void LocoIOPanel::propertyChange(PropertyChangeEvent* evt)
{
 // these messages can arrive without a complete
 // GUI, in which case we just ignore them
 if (evt->getPropertyName()==("UnitAddress"))
 {
  int i =  evt->getNewValue().toInt();
  int v = i;
  v = v & 0xFF;
  if (addrField != NULL) {
      addrField->setText(QString::number(v,16));
  }
  if (firmware != NULL) {
      firmware->setText("unknown  ");
  }
 }
 if (evt->getPropertyName()==("UnitSubAddress"))
 {
  int i =  evt->getNewValue().toInt();
  int v = i;
  if (subAddrField != NULL)
  {
   subAddrField->setText(QString::number(v,16));
  }
  if (firmware != NULL)
  {
   firmware->setText("unknown  ");
  }
 }
 if (evt->getPropertyName()==("LBVersionChange"))
 {
  QString v = evt->getNewValue().toString();
  if (locobuffer != NULL)
  {
   locobuffer->setText(" " + v);
  }
 }
 if (evt->getPropertyName()==("LIOVersionChange"))
 {
  QString v =  evt->getNewValue().toString();
  if (firmware != NULL) {
      firmware->setText(v + "    ");
  }
 }
 if (evt->getPropertyName()==("StatusChange"))
 {
  QString v = evt->getNewValue().toString();
  if (status != NULL) {
      status->setText(v + " ");
  }
 }
}


/*public*/ void LocoIOPanel::dispose() {
    // dispose of the model
    model->dispose();
    // take apart the JFrame
    LnPanel::dispose();
    model = NULL;
    table = NULL;
    //scroll = NULL;
    readAllButton = NULL;
    writeAllButton = NULL;
    addrField = NULL;
    subAddrField = NULL;
    status = NULL;
    firmware = NULL;
    locobuffer = NULL;
    saveButton = NULL;
    openButton = NULL;
}
