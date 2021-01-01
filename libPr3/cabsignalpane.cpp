#include "cabsignalpane.h"
#include "xtablecolumnmodel.h"
#include <QMenu>
#include "jtogglebutton.h"
#include "jlabel.h"
#include "dcclocoaddressselector.h"
#include "rosterentrycombobox.h"
#include "instancemanager.h"
#include "cabsignalmanager.h"
#include <QBoxLayout>
#include "defaultcabsignalmanager.h"
#include <QButtonGroup>
#include <QRadioButton>
#include <QSignalMapper>
#include <rosterentry.h>
#include "loggerfactory.h"
#include "flowlayout.h"
#include "globalrosterentrycombobox.h"
#include <QGroupBox>
#include <QHeaderView>

/**
 * Pane for sending Cab Signal data via block lookup
 * @author Steve Young Copyright (C) 2018
 * @author Paul Bender Copyright (C) 2019
 * @see CabSignalTableModel
 * @since 4.13.4
 */
///*public*/ class CabSignalPane extends jmri.util.swing.JmriPanel implements CabSignalListListener {


//@Override
/*public*/ void CabSignalPane::initComponents() {
    JmriPanel::initComponents();
    slotModel = new CabSignalTableModel(5,
        CabSignalTableModel::MAX_COLUMN); // row, column
    init();
}


/*public*/ void CabSignalPane::init() {
//        JTable* slotTable = new JTable(slotModel) {
//            // Override JTable Header to implement table header tool tips.
//            //@Override
//            /*protected*/ JTableHeader createDefaultTableHeader() {
//                return new JTableHeader(columnModel) {
//                    //@Override
//                    /*public*/ QString getToolTipText(MouseEvent e) {
//                        try {
//                            java.awt.Point p = e.getPoint();
//                            int index = columnModel.getColumnIndexAtX(p.x);
//                            int realIndex = columnModel.getColumn(index).getModelIndex();
//                            return CabSignalTableModel.columnToolTips[realIndex];
//                        } catch (RuntimeException e1) {
//                            //catch null pointer exception if mouse is over an empty line
//                        }
//                        return null;
//                    }
//                };
//            }
//        };

 slotTable = new JTable(slotModel);
tcm = new XTableColumnModel(slotTable);
 // Use XTableColumnModel so we can control which columns are visible
 slotTable->setColumnModel(tcm);
 slotTable->createDefaultColumnsFromModel();
 QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
 sizePolicy.setHorizontalStretch(2);
 sizePolicy.setVerticalStretch(1);
 slotTable->setSizePolicy(sizePolicy);

 QSignalMapper* cabSigColMenuMapper = new QSignalMapper(this);
 connect(cabSigColMenuMapper, SIGNAL(mapped(QObject*)), this, SLOT(on_cabSigColMenuMapper(QObject*)));

 for (int i = 0; i < slotTable->getColumnCount(); i++)
 {
     int colnumber=i;
     QString colName = slotTable->getColumnName(colnumber);
     QAction* showcol = new QAction(colName);
     showcol->setData(colnumber);
     showcol->setCheckable(true);
     colMenuList.append(showcol);
     cabSigColMenu->addAction(showcol); // cabsig columns
     connect(showcol, SIGNAL(triggered(bool)), cabSigColMenuMapper, SLOT(map()));
     cabSigColMenuMapper->setMapping(showcol, showcol);
 }

 for (int i = 0; i < CabSignalTableModel::MAX_COLUMN; i++)
 {
  int colnumber=i;
      TableColumn* column  = tcm->getColumnByModelIndex(colnumber);

  //if (Arrays.stream(CabSignalTableModel.startupColumns).anyMatch(j -> j == colnumber))
  bool bMatch = false;
  foreach( int j, CabSignalTableModel::startupColumns)
  {
    if(j == colnumber)
    {
     bMatch = true;
     break;
    }
  }
  if(bMatch)
  {
      colMenuList.at(colnumber)->setChecked(true);
      tcm->setColumnVisible(column, true);
  } else {
      colMenuList.at(colnumber)->setChecked(false);
      tcm->setColumnVisible(column, false);
  }
#if 0
  colMenuList.at(colnumber).addActionListener(new ActionListener() {
      //@Override
      /*public*/ void actionPerformed(ActionEvent e) {
          TableColumn column  = tcm->getColumnByModelIndex(colnumber);
          bool     visible = tcm->isColumnVisible(column);
          tcm->setColumnVisible(column, !visible);
      }
  });
#endif
 }
#if 0
 slotTable->setAutoCreateRowSorter(true);

 /*final*/ TableRowSorter<CabSignalTableModel*> sorter = new TableRowSorter<CabSignalTableModel>(slotModel);
 slotTable->setRowSorter(sorter);
#endif
 slotTable->setRowHeight(26);

 // configure items for GUI
 slotModel->configureTable(slotTable);
#if 0  // see on_cabSigColMenuMapper
 tcm->getColumnByModelIndex(CabSignalTableModel::REVERSE_BLOCK_DIR_BUTTON_COLUMN).setCellRenderer(
     new ButtonRenderer() );
 tcm->getColumnByModelIndex(CabSignalTableModel::REVERSE_BLOCK_DIR_BUTTON_COLUMN).setCellEditor(
     new ButtonEditor( new JButton() ) );

 tcm.getColumnByModelIndex(CabSignalTableModel.NEXT_ASPECT_ICON).setCellRenderer(
     tableSignalAspectRenderer() );
#endif
//        slotScroll = new JScrollPane(slotTable);
//        slotScroll.setPreferredSize(new Dimension(400, 200));
 slotTable->resize(400,200);

 this->setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));

 // add event displays
 JPanel* p1 = new JPanel();
 //p1.setLayout(new BorderLayout());
 QVBoxLayout* p1Layout = new QVBoxLayout(p1);

 JPanel* toppanelcontainer = new JPanel();
 // toppanelcontainer.setLayout(new BoxLayout(toppanelcontainer, BoxLayout.X_AXIS));
 QHBoxLayout* toppanelcontainerLayout = new QHBoxLayout(toppanelcontainer);

 masterPauseButton= new JToggleButton();
 masterPauseButton->setSelected(false); // cabdata on
 refreshMasterPauseButton();
 masterPauseButton->setVisible(true);
#if 0
 masterPauseButton.addActionListener (new ActionListener () {
     //@Override
     /*public*/ void actionPerformed(ActionEvent e) {
         refreshMasterPauseButton();
     }
 });
#endif
 connect(masterPauseButton, SIGNAL(clicked(bool)), this, SLOT(refreshMasterPauseButton()));
 toppanelcontainerLayout->addWidget(masterPauseButton,1, Qt::AlignVCenter);

 QGroupBox* locoSelectContainer = new QGroupBox();
 QHBoxLayout* locoSelectContainerLayout = new QHBoxLayout(locoSelectContainer);

 textLocoLabel->setText(tr("New Locomotive:"));
 textLocoLabel->setVisible(true);

 locoSelector->setToolTip(tr("Address of a new Locomotive to add"));
 locoSelector->setVisible(true);
 textLocoLabel->setLabelFor(locoSelector);

 locoSelectContainerLayout->addWidget(textLocoLabel);
 locoSelectContainerLayout->addWidget(locoSelector);
#if 0 // TODO:
 locoSelector.addKeyListener(new KeyListener() {
     //@Override
     /*public*/ void keyPressed(KeyEvent e) {
         // if we start typing, set the selected index of the locoRosterbox to nothing.
         locoRosterBox.setSelectedIndex(0);
     }

     //@Override
     /*public*/ void keyTyped(KeyEvent e) {
     }

     //@Override
     /*public*/ void keyReleased(KeyEvent e) {
     }
 });
#endif
 locoRosterBox = new GlobalRosterEntryComboBox();
 locoRosterBox->setNonSelectedItem("");

//        locoRosterBox.addPropertyChangeListener("selectedRosterEntries", (PropertyChangeEvent pce) -> {
//            locoSelected();
//        });
 connect(locoRosterBox, SIGNAL(currentIndexChanged(int)), this, SLOT(locoSelected()));
 locoRosterBox->setCurrentIndex(0);
 locoRosterBox->setVisible(true);
 locoSelectContainerLayout->addWidget(locoRosterBox);

 addLocoButton->setText(tr("Add"));
 addLocoButton->setVisible(true);
 addLocoButton->setToolTip(tr("Add Cab Signal"));
//        addLocoButton.addActionListener((ActionEvent e) -> {
//            addLocoButtonActionPerformed(e);
//        });
 connect(addLocoButton, SIGNAL(clicked(bool)), this, SLOT(addLocoButtonActionPerformed()));
 locoSelectContainerLayout->addWidget(addLocoButton);

 resetLocoButton->setText(tr("Reset"));
 resetLocoButton->setVisible(true);
 resetLocoButton->setToolTip(tr("Reset locomotive information"));
//        resetLocoButton.addActionListener((ActionEvent e) -> {
//            locoSelector.reset();
//            locoRosterBox.setSelectedIndex(0);
//        });
 connect(resetLocoButton,SIGNAL(clicked(bool)), this, SLOT(onResetLocoButton()));

 locoSelectContainerLayout->addWidget(resetLocoButton);
// TODO:        locoSelectContainer.setBorder(javax.swing.BorderFactory.createEtchedBorder());

 locoSelectContainer->setVisible(true);
 toppanelcontainerLayout->addWidget(locoSelectContainer, 0, Qt::AlignVCenter);

 p1Layout->addWidget(toppanelcontainer, 0, Qt::AlignTop);//BorderLayout.PAGE_START);
 p1Layout->addWidget(/*slotScroll*/slotTable);//BorderLayout.CENTER);
 this->layout()-> addWidget(p1);

 QSize p1size = QSize(450, 200);
 p1->setMinimumSize(p1size);

 p1->setVisible(true);
 log->debug(tr("class name %1 ").arg(this->metaObject()->className()));
}

void CabSignalPane::onResetLocoButton()
{
 locoSelector->reset();
 locoRosterBox->setCurrentIndex(0);
}

void CabSignalPane::on_cabSigColMenuMapper(QObject* obj)
{
 QAction* act = (QAction*)obj;
 int colnumber = act->data().toInt();

 TableColumn* column  = tcm->getColumnByModelIndex(colnumber);
 //bool visible = tcm->isColumnVisible(column);
  bool visible = slotTable->isColumnHidden(colnumber);
  slotTable->setColumnHidden(colnumber, !visible);
  tcm->setColumnVisible(column, !visible);
}

/*private*/ void CabSignalPane::refreshMasterPauseButton(){
    if (masterPauseButton->isSelected()) { // is paused
        masterPauseButton->setText(tr("Resume Signal Data"));
        masterPauseButton->setToolTip(tr("Cab Signal data is off. Click to Resume data and notify all active Cab Signals"));
        slotModel->setPanelPauseButton( true );
    }
    else { // pause relased, go back to normal
        masterPauseButton->setText(tr("Pause Signal Data "));
        masterPauseButton->setToolTip(tr("Cab Signal data is on. Click to Pause data and notify all active Cab Signals"));
        slotModel->setPanelPauseButton( false );
    }
}

//@Override
/*public*/ QString CabSignalPane::getTitle() {
    return tr("Cab Signals");
}

/*public*/ CabSignalPane::CabSignalPane(QWidget *parent) : JmriPanel(parent)
{
    //super();
 setObjectName("CabSignalPane");
 //tcm = new XTableColumnModel();

 cabSigColMenu = new QMenu(tr("Signal Data Columns"));

 colMenuList = QList<QAction*>();
 cabSigColMenuList = QList<QAction*>();
 textLocoLabel = new JLabel();
 locoSelector = new DccLocoAddressSelector();
 addLocoButton = new QPushButton();
 resetLocoButton = new QPushButton();

 cabSignalManager = (AbstractCabSignalManager*)InstanceManager::getNullableDefault("CabSignalManager");
 if(cabSignalManager == nullptr){
    log->info("creating new DefaultCabSignalManager");
    InstanceManager::store(new DefaultCabSignalManager(),"CabSignalManager");
    cabSignalManager = (AbstractCabSignalManager*)InstanceManager::getNullableDefault("CabSignalManager");
 }
 if (cabSignalManager != nullptr) {
     cabSignalManager->addCabSignalListListener(this);
 }
}

/**
 * Creates a Menu List
 */
//@Override
/*public*/ QList<QMenu*> CabSignalPane::getMenus() {
    QList<QMenu*> menuList = QList<QMenu*>();

    menuList.append(cabSigColMenu);

    QMenu* iconMenu = new QMenu(tr("Aspect Icon"));
    QActionGroup* offsetGroup = new QActionGroup(this);

    QAction* offset0MenuItem = new QAction(tr("%1 deg").arg(0));
    offset0MenuItem->setCheckable(true);
    QAction* offset1MenuItem = new QAction(tr("%1 deg").arg(90));
    offset1MenuItem->setCheckable(true);
    QAction* offset2MenuItem = new QAction(tr("%1 deg").arg(180));
    offset2MenuItem->setCheckable(true);
    QAction* offset3MenuItem = new QAction(tr("%1 deg").arg(270));
    offset3MenuItem->setCheckable(true);

    offsetGroup->addAction(offset0MenuItem);
    offsetGroup->addAction(offset1MenuItem);
    offsetGroup->addAction(offset2MenuItem);
    offsetGroup->addAction(offset3MenuItem);

    iconMenu->addAction(offset0MenuItem);
    iconMenu->addAction(offset1MenuItem);
    iconMenu->addAction(offset2MenuItem);
    iconMenu->addAction(offset3MenuItem);

    menuList.append(iconMenu);

    _rotationOffset = 0; // startup
    offset0MenuItem->setChecked(true);
#if 0
    ActionListener iconMenuListener = ae -> {
        if ( offset0MenuItem.isSelected() ) {
            _rotationOffset = 0;
        }
        else if ( offset1MenuItem.isSelected() ) {
            _rotationOffset = 1;
        }
        else if ( offset2MenuItem.isSelected() ) {
            _rotationOffset = 2;
        }
        else if ( offset3MenuItem.isSelected() ) {
            _rotationOffset = 3;
        }
        notifyCabSignalListChanged();
    };
    offset0MenuItem.addActionListener(iconMenuListener);
    offset1MenuItem.addActionListener(iconMenuListener);
    offset2MenuItem.addActionListener(iconMenuListener);
    offset3MenuItem.addActionListener(iconMenuListener);
#endif
    QSignalMapper* mapper = new QSignalMapper();
      mapper->setMapping(offset0MenuItem, 0);
      mapper->setMapping(offset1MenuItem, 90);
      mapper->setMapping(offset2MenuItem, 180);
      mapper->setMapping(offset3MenuItem, 270);
      connect(offset0MenuItem, SIGNAL(toggled(bool)), mapper, SLOT(map()));
      connect(offset1MenuItem, SIGNAL(toggled(bool)), mapper, SLOT(map()));
      connect(offset2MenuItem, SIGNAL(toggled(bool)), mapper, SLOT(map()));
      connect(offset3MenuItem, SIGNAL(toggled(bool)), mapper, SLOT(map()));
      connect(mapper, SIGNAL(mapped(int)), this, SLOT(onOffset(int)));
    return menuList;
}

void CabSignalPane::onOffset(int i)
{
 _rotationOffset = i;
}

/*public*/ void CabSignalPane::addLocoButtonActionPerformed(/*ActionEvent e*/) {
    if (locoSelector->getAddress() == nullptr) {
        return;
    }
    LocoAddress* locoaddress = locoSelector->getAddress();
    // create and inform CabSignal state of master pause / resume
    cabSignalManager->getCabSignal(locoaddress)->setMasterCabSigPauseActive( masterPauseButton->isSelected() );
}

/*public*/ void CabSignalPane::locoSelected() {
    if (locoRosterBox->getSelectedRosterEntries()->length() == 1) {
        locoSelector->setAddress(locoRosterBox->getSelectedRosterEntries()->at(0)->getDccLocoAddress());
    }
}


/*private*/ TableCellRenderer* tableSignalAspectRenderer() {
#if 0 // TODO:
    return new TableCellRenderer() {
        JLabel f = new JLabel();
        //@Override
        /*public*/ Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected,
            boolean hasFocus, int row, int column) {
            f.setIcon(null);
            if ( !value.toString().isEmpty() ) {
                // value gets passed as a string so image can be rotated here
                NamedIcon tmpIcon = new NamedIcon(value.toString(), value.toString() );
                tmpIcon.setRotation( tmpIcon.getRotation() + _rotationOffset,slotScroll);
                //  double d = mastIcon.reduceTo(28, 28, 0.01d);
                f.setIcon(tmpIcon);
            }
            f.setText("");
            f.setHorizontalAlignment(JLabel.CENTER);
            if (isSelected) {
                f.setBackground( table.getSelectionBackground() );
            } else {
                f.setBackground(null);
            }
            return f;
        }
    };
#endif
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString CabSignalPane::getHelpTarget() {
    return "package.jmri.jmrit.cabsignals.CabSignalPane";
}

//@Override
/*public*/ void CabSignalPane::dispose() {
    cabSignalManager->removeCabSignalListListener(this);
    slotTable = nullptr;
    slotModel->dispose();
    cabSignalManager = nullptr;
    JmriPanel::dispose();
}

// Cab Signal List Listener interface

//@Override
/*public*/ void CabSignalPane::notifyCabSignalListChanged(){
    slotModel->fireTableDataChanged();
}

/*private*/ /*static*/ /*final*/ Logger* CabSignalPane::log = LoggerFactory::getLogger("CabSignalPane");
