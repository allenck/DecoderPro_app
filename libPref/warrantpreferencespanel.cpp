#include "warrantpreferencespanel.h"
#include "instancemanager.h"
#include "fileutil.h"
#include "file.h"
#include "signalspeedmap.h"
#include <QBoxLayout>
#include "warrantpreferences.h"
#include <QLabel>
#include "flowlayout.h"
#include <QComboBox>
#include "jtextfield.h"
#include "rosterentry.h"
#include "inputdialog.h"
#include "warrantroute.h"
#include "warrantframe.h"
#include <QGroupBox>
#include "jtable.h"
#include <QPair>
#include <QRadioButton>
#include <QButtonGroup>
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include <QMessageBox>
#include "box.h"
#include <QHeaderView>
#include "joptionpane.h"
#include <QSpinBox>
#include <QScrollArea>

//WarrantPreferencesPanel::WarrantPreferencesPanel(QWidget *parent) :
//  PreferencesPanel(parent)
//{
//}
///*public*/ class WarrantPreferencesPanel extends QWidget* implements PreferencesPanel, ItemListener {

// /*private*/ static final long serialVersionUID = 7088050123933847146L;
/*static*/ int WarrantPreferencesPanel::STRUT_SIZE = 10;


/*public*/ WarrantPreferencesPanel::WarrantPreferencesPanel(QWidget *parent)
 :    QWidget(parent)
{
 _isDirty = false;
 _interpretation = SignalSpeedMap::PERCENT_NORMAL;

 initGUI();
}

/*private*/ void WarrantPreferencesPanel::initGUI()
{
 QVBoxLayout* thisVLayout;
    this->setLayout(thisVLayout = new QVBoxLayout); //(this, BoxLayout.PAGE_AXIS));
 QHBoxLayout* thisHLayout = new QHBoxLayout();
 thisVLayout->addLayout(thisHLayout);

 setMinimumSize(600,300);

 QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
 sizePolicy.setHorizontalStretch(1);
 sizePolicy.setVerticalStretch(1);
 sizePolicy.setHeightForWidth(false); //this->sizePolicy().hasHeightForWidth());
 this->setSizePolicy(sizePolicy);
 QScrollArea* scrollArea = new QScrollArea();
 scrollArea->setWidgetResizable(true);
 QWidget* scrollPane = new QWidget();
 QVBoxLayout* scrollPaneLayout = new QVBoxLayout(scrollPane);
 QWidget* leftPanel = new QWidget();
 QVBoxLayout* leftPanelLayout;
 sizePolicy = QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(false);
 leftPanel->setSizePolicy(sizePolicy);
 leftPanel->setLayout(leftPanelLayout = new QVBoxLayout); //(leftPanel, BoxLayout.PAGE_AXIS));
 QWidget* rightPanel = new QWidget();
 QVBoxLayout* rightPanelLayout;
 rightPanel->setLayout(rightPanelLayout = new QVBoxLayout) ; //(rightPanel, BoxLayout.PAGE_AXIS));
 sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 sizePolicy.setHorizontalStretch(1);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(false);
 rightPanel->setSizePolicy(sizePolicy);
 leftPanelLayout->addWidget(layoutScalePanel());
 leftPanelLayout->addWidget(searchDepthPanel(true));
 _timeIncre =  new QSpinBox();
 _timeIncre->setValue(750);
 _timeIncre->setMinimum(200);
 _timeIncre->setMaximum(10000);
 leftPanelLayout->addWidget(timeIncrementPanel(true, _timeIncre));
 _rampIncre =  new JTextField(6);
 leftPanelLayout->addWidget(throttleIncrementPanel(true, _rampIncre));
 leftPanelLayout->addWidget(throttleScalePanel(true));
 rightPanelLayout->addWidget(speedNamesPanel());
 rightPanelLayout->addWidget(Box::createGlue());
 //rightPanelLayout->addWidget(interpretationPanel());
 //rightPanelLayout->addWidget(Box::createGlue());
 rightPanelLayout->addWidget(appearancePanel());
 //    _rampIncre.addActionListener(new ActionListener() {
 //        /*public*/ void actionPerformed(ActionEvent e) {
 //            String text = _rampIncre.getText();
 //            bool showdialog = false;
 //            try {
 //                float incr = float.parsefloat(text);
 //                showdialog = (incr<0.002f || incr>0.2f);
 //            } catch (NumberFormatException nfe) {
 //                showdialog = true;
 //            }
 //            if (showdialog) {
 //                JOptionPane.showMessageDialog(NULL, tr("rampIncrWarning", text),
 //                        tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
 //            }
 //        }
 //    });
     connect(_rampIncre, SIGNAL(leaveField()), this, SLOT(on_rampIncre_leaveField()));
 QWidget* panel = new QWidget();
 QHBoxLayout* panelLayout;
 panel->setLayout(panelLayout = new QHBoxLayout); //(panel, BoxLayout.LINE_AXIS));
 panelLayout->addWidget(leftPanel);
 panelLayout->addWidget(rightPanel);
 //thisLayout->addWidget(panel);
 scrollPaneLayout->addWidget(panel);
 scrollArea->setWidget(scrollPane);
 thisHLayout->addWidget(scrollArea);
 //adjustSize();
}

QSize WarrantPreferencesPanel::minimumSizeHint()
{
 return QSize(600, 200);
}

QSize WarrantPreferencesPanel::sizeHint()
{
 return QSize(600, 200);
}

///*private*/ void WarrantPreferencesPanel::setGUI()
//{
// _preferences->apply();
//}

/*private*/ QWidget* WarrantPreferencesPanel::layoutScalePanel()
{
    QWidget* panel = new QWidget();
    QVBoxLayout* panelLayout;
    panel->setLayout(panelLayout = new QVBoxLayout); //(panel, BoxLayout.PAGE_AXIS));
    ScaleData* sd;
    _layoutScales = new QComboBox/*<ScaleData>*/();
    sd = new ScaleData("G", 20.3);
    _layoutScales->addItem(sd->toString(), VPtr<ScaleData>::asQVariant(sd));
    sd = new ScaleData("L", 38);
    _layoutScales->addItem(sd->toString(), VPtr<ScaleData>::asQVariant(sd));
    sd =new ScaleData("O", 43);
    _layoutScales->addItem(sd->toString(), VPtr<ScaleData>::asQVariant(sd));
    sd = new ScaleData("S", 64);
    _layoutScales->addItem(sd->toString(), VPtr<ScaleData>::asQVariant(sd));
    sd = new ScaleData("OO", 76.2);
    _layoutScales->addItem(sd->toString(), VPtr<ScaleData>::asQVariant(sd));
    sd = new ScaleData("HO", 87.1);
    _layoutScales->addItem(sd->toString(), VPtr<ScaleData>::asQVariant(sd));
    sd = new ScaleData("TT", 120);
    _layoutScales->addItem(sd->toString(), VPtr<ScaleData>::asQVariant(sd));
    sd = new ScaleData("N", 160);
    _layoutScales->addItem(sd->toString(), VPtr<ScaleData>::asQVariant(sd));
    sd = new ScaleData("Z", 220);
    _layoutScales->addItem(sd->toString(), VPtr<ScaleData>::asQVariant(sd));
    sd = new ScaleData("T", 480);
    _layoutScales->addItem(sd->toString(), VPtr<ScaleData>::asQVariant(sd));
    ScaleData* sc = makeCustomItem(WarrantPreferences::getDefault()->getScale());
    _layoutScales->addItem(sc->toString(), VPtr<ScaleData>::asQVariant(sc));
    if (_layoutScales->currentIndex()<0) {
        _layoutScales->setCurrentIndex(_layoutScales->findData(VPtr<ScaleData>::asQVariant( sc)));
    }
    QSize dim = _layoutScales->sizeHint();
    dim.setWidth( 3*dim.width()/2);
    _layoutScales->resize(dim);
    //_layoutScales->addItemListener(this);
    connect(_layoutScales, SIGNAL(currentIndexChanged(int)), this, SLOT(itemStateChanged(int)));
    _layoutScales->setToolTip(tr("Needed to compute speed and distance for warrants"));
    QLabel* label= new QLabel(tr("Layout Scale"));
    label->setToolTip(tr("Needed to compute speed and distance for warrants"));
    panelLayout->addWidget(label);
    QWidget* p = new QWidget();
    FlowLayout* pLayout = new FlowLayout(p);
    pLayout->addWidget(_layoutScales);
//        p.add(Box.createVerticalGlue());
    panelLayout->addWidget(p);
    return panel;
}

/*private*/ ScaleData* WarrantPreferencesPanel::makeCustomItem(float scale)
{
 int cnt = 0;
 while (cnt <_layoutScales->count())
 {
  if (VPtr<ScaleData>::asPtr(_layoutScales->itemData(cnt))->scale == scale)
  {
     // _layoutScales->setCurrentIndex(_layoutScales->getItemAt(cnt));
   _layoutScales->setCurrentIndex(cnt);
   return new CustomDialog("custom", 0.0);
  }
  cnt++;
 }
 _layoutScales->setCurrentIndex(-1);
 return new CustomDialog(tr("custom"), scale);
}

/*public*/ void WarrantPreferencesPanel::itemStateChanged(/*ItemEvent e*/int item)
{
 WarrantPreferences* _preferences = WarrantPreferences::getDefault();

// if (e.getStateChange()==ItemEvent.SELECTED)
// {
 ScaleData* sd = VPtr<ScaleData>::asPtr(_layoutScales->itemData(item));
 //if (sd instanceof CustomDialog)
 if(qobject_cast<CustomDialog*>(sd) != NULL)
 {
  bool ok = false;
  while (!ok)
  {
   float scale = 0.0;
//          QString str = JOptionPane.showInputDialog(this, tr("customInput"),
//                  tr("customTitle"), JOptionPane.QUESTION_MESSAGE);
   QString str;
   InputDialog dlg("Enter the scale of your layout.",str, NULL,this);
   bool bok;
   if(dlg.exec() == QDialog::Accepted)
   {
    str = dlg.value();
   }
//    try
//    {
    if (str==NULL)
    {
     sd->scale = 0.0;
     makeCustomItem(_preferences->getScale());
     ok = true;
    }
    else
    {
     scale = str.toFloat();
     if (scale <= 1.0f)
     {
         throw new NumberFormatException();
     }
     sd->scale = scale;
     _preferences->setScale(scale);
     _isDirty = true;
     ok = true;
    }
    if(!bok)
    {
      //              JOptionPane.showMessageDialog(this, tr("customError", str),
      //                      tr("customTitle"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Scale??:1"), tr("\"%1\" is not a positive number greater than 1.").arg(str));
    }
   }
  }
  else
  {
   _preferences->setScale(sd->scale);
   _isDirty = true;
  }
 }
//}

//class ScaleData {
//    float scale;
//    QString scaleName;
 ScaleData::ScaleData(QString scaleName, float scale)
 {
     this->scale = scale;
     this->scaleName = scaleName;
 }
 //@Override
 /*public*/ QString ScaleData::toString()
 {
  return tr("%1 scale, %2 : 1").arg(scaleName).arg( scale);
 }
//};

//class CustomDialog : public ScaleData {
 CustomDialog::CustomDialog(QString scaleName, float scale) : ScaleData(scaleName, scale)
 {
     //super(scaleName, scale);
 }
// //@Override
 /*public*/ QString CustomDialog::toString() {
     if (scale < 1.0f) {
         return tr("custom");
     }
     return ScaleData::toString();
 }
//};

/*private*/ QWidget* WarrantPreferencesPanel::searchDepthPanel(bool vertical)
 {
  _searchDepth = new QSpinBox();//JSpinner(new SpinnerNumberModel(20, 1, 50, 1));
  _searchDepth->setValue(20);
  _searchDepth->setMinimum(1);
  _searchDepth->setMaximum(50);
  _searchDepth->setSingleStep(1);
  int searchDepthPref = WarrantPreferences::getDefault()->getSearchDepth();
  if (searchDepthPref >= 1 && searchDepthPref <= 50) {
      _searchDepth->setValue(searchDepthPref);
  }
  QWidget* p = new QWidget();
  p->setLayout(new QVBoxLayout);
  p->layout()->addWidget(WarrantRoute::makeTextBoxPanel(vertical, _searchDepth, "SearchDepth", "Upper limit for the number of OBlocks in a warrant route"));
  p->setToolTip(tr("Upper limit for the number of OBlocks in a warrant route"));
  return p;
}

/*private*/ QWidget* WarrantPreferencesPanel::throttleScalePanel(bool vertical)
 {
  _throttleScale =  new JTextField(5);
  _throttleScale->setText(QString::number(WarrantPreferences::getDefault()->getThrottleScale()));
  QWidget* p = new QWidget();
  QVBoxLayout* pLayout = new QVBoxLayout(p);
  pLayout->addWidget(WarrantRoute::makeTextBoxPanel(vertical, _throttleScale, tr("Throttle Setting/Speed Factor"), "Ratio that calibrates the throttle setting to run trains at scale speed. (default value 0.7)"));
  _throttleScale->setColumns(8);
  p->setToolTip(tr("Ratio that calibrates the throttle setting to run trains at scale speed. (default value 0.7)"));
  return p;
}

/*private*/ QWidget* WarrantPreferencesPanel::speedNamesPanel()
 {
 QGroupBox* panel = new QGroupBox();
 panel->setContentsMargins(0,0,0,0);
 QVBoxLayout* panelLayout = new QVBoxLayout(panel);
//    panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(java.awt.Color.BLACK),
//            tr("Aspect Speed Name to Value Mapping"),
//            javax.swing.border.TitledBorder.CENTER,
//            javax.swing.border.TitledBorder.TOP));
//    panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
 panel->setTitle(tr("Aspect Speed Name to Value Mapping"));

 _speedNameMap =  QList<QPair<QString, float> >();
 QMapIterator<QString, float> it = WarrantPreferences::getDefault()->getSpeedNameEntryIterator();
 while (it.hasNext())
 {
  it.next();
  //Entry<String, float> ent = it.next();
  _speedNameMap.append(QPair<QString, float>(it.key(), it.value()));
 }
 _speedNameModel =  new SpeedNameTableModel(this);
 _speedNameTable = new JTable(_speedNameModel);
 _speedNameTable->setMinimumHeight(100);
 _speedNameTable->horizontalHeader()->setStretchLastSection(true);
 _speedNameTable->createDefaultColumnsFromModel();
 for (int i=0; i<_speedNameModel->columnCount(QModelIndex()); i++)
 {
  int width = _speedNameModel->getPreferredWidth(i);
  _speedNameTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
 }
 InsertActionListener* insertAction = new InsertActionListener(this);
//    {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            insertSpeedNameRow();
//        }
//    };
 DeleteActionListener* deleteAction = new DeleteActionListener(this);
//    {
//        /*public*/ void actionPerformed(ActionEvent e) {
//           deleteSpeedNameRow();
//        }
//    };
 panelLayout->addWidget(tablePanel(_speedNameTable, "Every Speed Name used in your Signal System's aspects must be a row in this table", insertAction, deleteAction));
 panelLayout->addWidget(interpretationPanel());
 return panel;
}

 InsertActionListener::InsertActionListener(WarrantPreferencesPanel *panel)
 {
  this->panel = panel;
 }
 void InsertActionListener::actionPerformed(JActionEvent */*e*/)
 {
  panel->insertSpeedNameRow();
 }
 DeleteActionListener::DeleteActionListener(WarrantPreferencesPanel *panel)
 {
  this->panel = panel;
 }
 void DeleteActionListener::actionPerformed(JActionEvent *e)
 {
  panel->deleteSpeedNameRow();
 }

/*private*/ QWidget* WarrantPreferencesPanel::appearancePanel()
 {
  QGroupBox* panel = new QGroupBox();
//    panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(java.awt.Color.BLACK),
//            tr("LabelAppearanceTable"),
//            javax.swing.border.TitledBorder.CENTER,
//            javax.swing.border.TitledBorder.TOP));
  panel->setTitle(tr("Head Appearance to Speed Name "));
  QVBoxLayout* panelLayout;
  panel->setLayout(panelLayout=new QVBoxLayout); //(panel, BoxLayout.PAGE_AXIS));

  _appearanceMap = QList<QPair<QString, QString>* >();
  //Iterator<Entry<String, String>> it = _preferences->getAppearanceEntryIterator();
  QMapIterator<QString, QString> it = WarrantPreferences::getDefault()->getAppearanceEntryIterator();
  while (it.hasNext())
  {
   //Entry<String, String> ent = it.next();
   it.next();
   _appearanceMap.append(new QPair<QString, QString>(it.key(), it.value()));
  }
  _appearanceModel = new AppearanceTableModel(this);
  _appearanceTable = new JTable(_appearanceModel);
  _appearanceTable->setMinimumHeight(100);
  _appearanceTable->horizontalHeader()->setStretchLastSection(true);

  for (int i=0; i<_appearanceModel->columnCount(QModelIndex()); i++)
  {
   int width = _appearanceModel->getPreferredWidth(i);
   _appearanceTable->createDefaultColumnsFromModel();
   _appearanceTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
  }
  panelLayout->addWidget(tablePanel(_appearanceTable, "Map SignalHead appearance to Speed Name. Every SignalHead appearance must be a row in this table", NULL, NULL));
  return panel;
}

/*static*/ /*private*/ QWidget* WarrantPreferencesPanel::tablePanel(JTable* table, QString toolTip, ActionListener* insertAction, ActionListener* removeAction)
 {
 QWidget* tablePanel = new QWidget();
 //tablePanel->setContentsMargins(0,0, 0, 0);
 QHBoxLayout* tablePanelLayout;
 tablePanel->setLayout(tablePanelLayout =new QHBoxLayout);//(tablePanel, BoxLayout.LINE_AXIS));
 //JScrollPane scrollPane = new JScrollPane(table);
 int height = table->getRowHeight(0);
 QSize dim = table->sizeHint();
 dim.setHeight(  dim.height()*5);
 //scrollPane.getViewport().setPreferredSize(dim);
 table->setToolTip(toolTip);
 //scrollPane.setToolTipText(tr(toolTip));
 tablePanelLayout->addWidget(table);
 tablePanelLayout->addStrut(STRUT_SIZE);

 QWidget* buttonPanel = new QWidget();
 FlowLayout* buttonPanelLayout;
 buttonPanel->setLayout(buttonPanelLayout =new FlowLayout); //(buttonPanel, BoxLayout.PAGE_AXIS));

 if (insertAction!=NULL) {
     QPushButton* insertButton =  new QPushButton(tr("Insert Row"));
     //insertButton.addActionListener(insertAction);
     connect(insertButton, SIGNAL(clicked()), insertAction, SLOT(actionPerformed()));
     buttonPanelLayout->addWidget(insertButton);
     //buttonPanelLayout.adds(Box.createVerticalStrut(2*STRUT_SIZE));
 }

 if (removeAction!=NULL) {
     QPushButton* deleteButton =  new QPushButton(tr("Delete Row"));
     //deleteButton.addActionListener(removeAction);
     connect(deleteButton, SIGNAL(clicked()), removeAction, SLOT(actionPerformed()));
     buttonPanelLayout->addWidget(deleteButton);
 }
 tablePanelLayout->addWidget(buttonPanel);
 return tablePanel;
}

/*private*/ void WarrantPreferencesPanel::insertSpeedNameRow()
 {
  int row = _speedNameTable->currentIndex().row();
  if (row<0) {
//        JOptionPane.showMessageDialog(NULL, tr("selectRow"),
//                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(NULL, tr("warning"), tr("Select a row from the table to add or delete a row"));
      return;
  }
  _speedNameMap.append(QPair<QString, float>("", 0.0));
  _speedNameModel->fireTableDataChanged();
}

/*private*/ void WarrantPreferencesPanel::deleteSpeedNameRow()
 {
  int row = _speedNameTable->getSelectedRow();
  if (row < 0) {
      JOptionPane::showMessageDialog(nullptr, tr("Select a row from the table to add or delete a row"),
              tr("Warning"), JOptionPane::WARNING_MESSAGE);
      return;
  }
  _speedNameMap.removeAt(row);
  _speedNameModel->fireTableDataChanged();
}

/*private*/ QWidget* WarrantPreferencesPanel::interpretationPanel()
 {
 _interpretation = WarrantPreferences::getDefault()->getInterpretation();
 //QWidget* buttonPanel = new QWidget();
FlowLayout* buttonPanelLayout = new FlowLayout;
//buttonPanel->setLayout(buttonPanelLayout =new FlowLayout);//(buttonPanel, BoxLayout.LINE_AXIS));
 QButtonGroup* group = new QButtonGroup();
 makeButton(buttonPanelLayout, group, "% Normal", "Value is percentage of current speed as recorded with unrestricted signal aspect", SignalSpeedMap::PERCENT_NORMAL);
 makeButton(buttonPanelLayout, group, "% Throttle", "Value is percentage of the full throttle setting  (requires Roster is speed matched)", SignalSpeedMap::PERCENT_THROTTLE);
 makeButton(buttonPanelLayout, group, "Miles per hour", "Value is scale miles per hour (requires calibrated addresses)", SignalSpeedMap::SPEED_MPH);
 makeButton(buttonPanelLayout, group, "Kilometers per hour", "Value is scale kilometers per hour (requires calibrated addresses)", SignalSpeedMap::SPEED_KMPH);
 QWidget* panel = new QWidget();
 QVBoxLayout* panelLayout;
 panel->setLayout(panelLayout =new QVBoxLayout); //(panel, BoxLayout.PAGE_AXIS));
 //QWidget* p = new QWidget();
 QHBoxLayout* pLayout = new QHBoxLayout(/*p*/);
 QLabel* label= new QLabel(tr("Interpretation of Speed Name Value "));
 label->setToolTip(tr("Choose how the code should interpret Speed Name Values"));
 panel->setToolTip(tr("Choose how the code should interpret Speed Name Values"));
 pLayout->addWidget(label);
 panelLayout->addLayout(pLayout);
 panelLayout->addLayout(buttonPanelLayout); // /*Box.CENTER_ALIGNMENT*/0, Qt::AlignCenter);
 return panel;
}

/*private*/ void WarrantPreferencesPanel::makeButton(FlowLayout* panelLayout, QButtonGroup* group, QString name, QString tooltip, int interp)
{
 QRadioButton* button = new QRadioButton((name));
 group->addButton(button);
 panelLayout->addWidget(button);
 button->setToolTip(tooltip);
// button.addActionListener(new ActionListener() {
//     int value;
//     JRadioButton but;
//     /*public*/ void actionPerformed(ActionEvent e) {
//         if (but.isSelected()) {
//             _interpretation = value;
//         }
//     }
//     ActionListener init(JRadioButton b, int num) {
//         but = b;
//         value = num;
//         return this;
//     }
// }.init(button, interp));
 ButtonActionListener* bal = new ButtonActionListener();
 bal->init(button,interp,this);
 if (_interpretation==interp)
 {
  button->setChecked(true);
 }
}
ButtonActionListener* ButtonActionListener::init(QRadioButton *b, int num, WarrantPreferencesPanel* panel)
{
 but = b;
 value = num;
 this->panel = panel;
 connect(b, SIGNAL(clicked()), this, SLOT(actionPerformed()));
 return this;
}
void ButtonActionListener::actionPerformed(JActionEvent *e)
{
 if (but->isChecked())
 {
  panel->_interpretation = value;
  panel->_isDirty = true;
 }
}

/*private*/ QWidget* WarrantPreferencesPanel::timeIncrementPanel(bool vertical, QSpinBox* _timeIncre)
{

 _timeIncre->setValue(WarrantPreferences::getDefault()->getTimeIncrement());
 QWidget* p = new QWidget();
 QVBoxLayout* pLayout = new QVBoxLayout(p);
 pLayout->addWidget(WarrantFrame::makeTextBoxPanel(vertical, _timeIncre, tr("Ramp Step Time (milliseconds)"), "Length of time in milliseconds between each speed change when ramping speed"));
 p->setToolTip(tr("Length of time in milliseconds between each speed change when ramping speed"));
 return p;
}

/*private*/ QWidget* WarrantPreferencesPanel::throttleIncrementPanel(bool vertical, JTextField* _rampincre)
{
 _rampIncre->setText(QString::number(WarrantPreferences::getDefault()->getThrottleIncrement()));
 QWidget* incrPanel = new QWidget();
 QHBoxLayout* incrPanelLayout = new QHBoxLayout(incrPanel);
 incrPanelLayout->addWidget(_rampIncre);
 incrPanelLayout->addWidget(new QLabel(tr("Percent")));
 QWidget* p = new QWidget();
 QVBoxLayout* pLayout = new QVBoxLayout(p);
 pLayout->addWidget(WarrantFrame::makeTextBoxPanel(vertical, incrPanel, tr("Ramp Step throttle increment"),"Throttle setting increment for each speed change when ramping speed"));
 p->setToolTip(tr("Throttle setting increment for each speed change when ramping speed"));
 return p;
}

void WarrantPreferencesPanel::on_rampIncre_leaveField()
{
 QString text = _rampIncre->text();
 bool showdialog = false;
 bool bok;
     float incr = text.toFloat(&bok);
     showdialog = (incr<0.002f || incr>0.2f);
     if(!bok)
     {
     showdialog = true;
 }
 if (showdialog)
 {
//     JOptionPane.showMessageDialog(NULL, tr("rampIncrWarning", text),
//             tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(NULL, tr("Warning"), tr("%1 is an extreme amount for step increment.  A value between .03 and .10 is more reasonable.").arg(text));
 }
}


/* alternative UI test
private QWidget* throttleIncrementPanel(bool vertical) {
    QWidget* panel = new QWidget();
    panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
    panelLayout->addWidget(new JLabel("Ramp step amount"));
    QWidget* p = new QWidget();
    p.add(new javax.swing.JSpinner(new javax.swing.SpinnerNumberModel(1,1,20,1 )));
    p.add(new JLabel(" steps, in"));
    panelLayout->addWidget(p);
    p = new QWidget();
    String[] modes = {"14", "28", "128"};
    p.add(new JComboBox<String>(modes));
    p.add(new JLabel(" stepmode"));
    panelLayout->addWidget(p);
    return panel;
}*/

/**
 * Compare GUI vaules with Preferences.  When different, update Preferences
 * and set _isDirty flag.
 */
/*private*/ void WarrantPreferencesPanel::setValues()
{
 WarrantPreferences* _preferences = WarrantPreferences::getDefault();
 int depth = _preferences->getSearchDepth();
 depth =_searchDepth->value();
 if (_preferences->getSearchDepth() != depth)
 {
     _preferences->setSearchDepth(depth);
     _isDirty = true;
 }

 if (_preferences->getInterpretation()!=_interpretation)
 {
     _preferences->setInterpretation(_interpretation);
     _isDirty = true;
 }

 int time = _preferences->getTimeIncrement();

 time =_timeIncre->value();
 if (time < 200)
 {
  time = 200;
//            JOptionPane.showMessageDialog(NULL, tr("timeWarning"),
//                    tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(NULL, tr("Warning"), tr("between speed changes must be at least 200 milliseconds."));
   _timeIncre->setValue(_preferences->getTimeIncrement());
  }
  if (_preferences->getTimeIncrement() != time)
  {
   _preferences->setTimeIncrement(time);
   _isDirty = true;
  }

  float scale = _preferences->getThrottleIncrement();
  bool bok;
  scale = _rampIncre->text().toFloat(&bok);
  if(!bok)
  {
   _rampIncre->setText(QString::number(_preferences->getThrottleIncrement()));
  }
  if (_preferences->getThrottleIncrement() != scale)
  {
      _preferences->setThrottleIncrement(scale);
      _isDirty = true;
  }

  scale = _preferences->getThrottleScale();
  scale = _throttleScale->text().toFloat(&bok);
  if(!bok)
  {
  _throttleScale->setText(QString::number(_preferences->getThrottleScale()));
  }
  if (_preferences->getThrottleScale() != scale)
  {
      _preferences->setThrottleScale(scale);
      _isDirty = true;
  }

  bool different = false;
//    javax.swing.table.TableCellEditor tce = _speedNameTable.getCellEditor();
//    if (tce!=NULL) {
//        tce.stopCellEditing();
//    }
  if (_preferences->getSpeedNamesSize() != _speedNameMap.size()) {
      different = true;
  }
  else
  {
   for (int i=0; i<_speedNameMap.size(); i++)
   {
    QPair<QString, float> dp = _speedNameMap.value(i);
    QString name = dp.first;
    if (_preferences->getSpeedNameValue(name)==NULL || _preferences->getSpeedNameValue(name)!= dp.second)
    {
        different = true;
        break;
    }
   }
  }
  if (different)
  {
   _preferences->setSpeedNames(_speedNameMap);
   _isDirty = true;
  }

  different = false;
//    tce = _appearanceTable.getCellEditor();
//    if (tce!=NULL) {
//        tce.stopCellEditing();
//    }
  if (_preferences->getAppearancesSize() != _appearanceMap.size())
  {
      different = true;
  }
  else
  {
   for (int i=0; i<_appearanceMap.size(); i++)
   {
    QPair<QString, QString>* dp = _appearanceMap.at(i);
    QString name = dp->first;
    if (_preferences->getAppearanceValue(name)==NULL || _preferences->getAppearanceValue(name)!= dp->second)
    {
     different = true;
     break;
    }
   }
 }
 if (different)
 {
    _preferences->setAppearances(_appearanceMap);
    _isDirty = true;
 }
}
#if 0
/*private*/ QWidget* WarrantPreferencesPanel::applyPanel()
{
 QWidget* panel = new QWidget();
 FlowLayout* panelLayout = new FlowLayout(panel);
 QPushButton* applyB = new QPushButton(tr("Apply"));
//    applyB.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            setValues();
//            if (_isDirty) {
//                _preferences->apply();
//            }
//        }
//    });
 connect(applyB, SIGNAL(clicked()), this, SLOT(on_applyB_clicked()));
 panelLayout->addWidget(new QLabel(tr("Apply new preferences now.")));
 panelLayout->addWidget(applyB);
 return panel;
}

void WarrantPreferencesPanel::on_applyB_clicked()
{
 setValues();
 if (_isDirty)
 {
  WarrantPreferences::getDefault()->apply();
 }
}
#endif

/**
 * Get the Preferences Item identifier.
 *
 * Multiple PreferencePanels can be displayed as tabs in a single item.
 * Preferences items are listed in the menu on the left of the preferences
 * window.
 *
 * @return the preferences item identifier.
 */
/*public*/ QString WarrantPreferencesPanel::getPreferencesItem() {
    return "WARRANTS"; // NOI18N
}

/**
 * Get the text for the Preferences Item in the preferences window list of
 * preferences categories.
 *
 * Multiple PreferencePanels can be displayed as tabs in a single item.
 * Preferences items are listed in the menu on the left of the preferences
 * window.
 *
 * @return the text for the preferences item.
 */
/*public*/ QString WarrantPreferencesPanel::getPreferencesItemText() {
    return tr("Warrant Preferences");
}

/**
 * Get the title for the tab containing this preferences item.
 *
 * @return a tab title
 */
/*public*/ QString WarrantPreferencesPanel::getTabbedPreferencesTitle() {
    return NULL;
}

/**
 * Text displayed above the preferences panel
 *
 * This label is only displayed if the preferences panel is in a tabbed set
 * of preferences. This label can contain multiple lines.
 *
 * @return label text
 */
/*public*/ QString WarrantPreferencesPanel::getLabelKey() {
    return NULL;
}

/**
 * Get the preferences component for display
 *
 * @return the preferences panel
 */
/*public*/ QWidget* WarrantPreferencesPanel::getPreferencesComponent() {
    return this;
}

/**
 * Indicates that this PrefernecesPanel should be stored across application
 * starts by the PreferencesManager
 *
 * This should be true if the implementing class relies on the
 * {@link jmri.ConfigureManager} stores and retrieves the preferences
 * managed by the implementing class on behalf of the implementing class.
 *
 * @return false if the implementing class stores its own preferences
 */
/*public*/ bool WarrantPreferencesPanel::isPersistant()
{
 return false;
}

/**
 * The tooltip to display for a tabbed preferences panel
 *
 * @return tooltip text
 */
/*public*/ QString WarrantPreferencesPanel::getPreferencesTooltip() {
    return tr("Needed to compute speed and distance for warrants");
}


/**
 * Save any changes to preferences.
 *
 * This method is called for every instance of a PreferencesPanel that is
 * loaded by {@link apps.gui3.TabbedPreferences} if {@link #isPersistant()}
 * is false.
 */
/*public*/ void WarrantPreferencesPanel::savePreferences()
{
 setValues();
 if (_isDirty)
 {
  WarrantPreferences::getDefault()->apply();
  WarrantPreferences::getDefault()->save();
  _isDirty = false;
 }
}

/**
 * Indicate that preferences need to be saved.
 *
 * @return true if preferences need to be saved, false otherwise
 */
/*public*/ bool WarrantPreferencesPanel::isDirty() {
    return this->_isDirty;
}

/**
 * Indicate that the preferences will not take effect until restarted.
 *
 * @return true if the application needs to restart
 */
/*public*/ bool WarrantPreferencesPanel::isRestartRequired() {
    return false;
}

//@Override
/*public*/ bool WarrantPreferencesPanel::isPreferencesValid() {
    return true; // no validity checking performed
}

//class QPair<K, V> {
//    K key;
//    V value;

//    QPair(K k, V v) {
//        key = k;
//        value = v;
//    }
//    K getKey() { return key; }
//    void setKey(K k) { key = k; }
//    V getValue() { return value; }
//    void setValue(V v) { value = v; }
//};

/************************* SpeedName Table ******************************/
//class SpeedNameTableModel extends AbstractTableModel {

//    /*private*/ static final long serialVersionUID = 7088050123933847145L;

/*public*/ SpeedNameTableModel::SpeedNameTableModel(WarrantPreferencesPanel* panel)
 : AbstractTableModel()
{
 // super();
 this->panel = panel;
}

/*public*/ int SpeedNameTableModel::columnCount(const QModelIndex &parent) const
{
 return 2;
}

/*public*/ int SpeedNameTableModel::rowCount(const QModelIndex &parent) const
{
 return panel->_speedNameMap.size();
}
//@Override
/*public*/ QVariant SpeedNameTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
  if (section==0)
  {
   return tr("Speed Name");
  }
  return tr("Speed Value");
 }
 return QVariant();
}

//@Override
/*public*/ Qt::ItemFlags SpeedNameTableModel::flags(const QModelIndex &index) const
{
 return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

//@Override
//    /*public*/ Class<?> getColumnClass(int col) {
//        return String.class;
//    }

/*public*/ int SpeedNameTableModel::getPreferredWidth(int col)
{
 if (col==0) {
  return  JTextField(15).getPreferredSize().width();
 }
 return  JTextField(8).getPreferredSize().width();
}
/*public*/ QVariant SpeedNameTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();
  // some error checking
  if (row >= panel->_speedNameMap.size())
  {
   Logger::error("row is greater than aspect speedNames size");
   return "";
  }
  QPair<QString, float> data = panel->_speedNameMap.value(row);
  if (data == QPair<QString, float>())
  {
   Logger::error("Aspect speedName data is NULL!");
   return "";
  }
  if (col==0)
  {
   return data.first;
  }
  return data.second;
 }
 return QVariant();
    }

//@Override
/*public*/ bool SpeedNameTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();
  QPair<QString, float> data = panel->_speedNameMap.value(row);
  QString str = value.toString();
  QString msg = NULL;
  if (str==NULL || data==QPair<QString, float>())
  {
      msg = tr("No data found");
  }
  if (data!=QPair<QString, float>())
  {
   if (col==0)
   {
    data.first = value.toString();
   }
   else
   {
    bool bOk;
    float f = value.toFloat(&bOk);
    if (f < 0)
    {
     msg = tr("%1 is not a valid number for this parameter.").arg(value.toString());
    }
    else
    {
     data.second =(f);
    }
    if(!bOk)
    {
     msg = tr("%1MustBefloat").arg(value.toString());
    }
   }
   if (msg!=NULL)
   {
//                JOptionPane.showMessageDialog(NULL, msg,
//                        tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
    QMessageBox::warning(NULL, tr("Warning"), msg);
    return false;
   }
   else
   {
   fireTableRowsUpdated(row, row);
   return true;
   }
  }
 }
 return false;
}

//};
/************************* appearance Table ******************************/
//class AppearanceTableModel extends AbstractTableModel {
//    /*private*/ static final long serialVersionUID = 7088050123933847144L;

/*public*/ AppearanceTableModel::AppearanceTableModel(WarrantPreferencesPanel* panel) : AbstractTableModel()
{
 //super();
 this->panel = panel;
}

/*public*/ int AppearanceTableModel::columnCount(const QModelIndex &parent) const
{
 return 2;
}

/*public*/ int AppearanceTableModel::rowCount(const QModelIndex &parent) const
{
 return panel->_appearanceMap.size();
}
//@Override
/*public*/ QVariant AppearanceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  if (section==0)
  {
   return tr("Appearance");
  }
  return tr("Speed Name");
 }
 return QVariant();
}

//@Override
/*public*/ Qt::ItemFlags AppearanceTableModel::flags(const QModelIndex &index) const
{
 //return (col!=0);
 if(index.column() > 0)
  return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 else
  Qt::ItemIsEditable  | Qt::ItemIsEnabled;
}
//@Override
//    /*public*/ Class<?> getColumnClass(int col) {
//        return String.class;
//    }

/*public*/ int AppearanceTableModel::getPreferredWidth(int col)
{
 if (col==0)
 {
  return  JTextField(15).getPreferredSize().width();
 }
 return  JTextField(15).getPreferredSize().width();
}

/*public*/ QVariant AppearanceTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();
    // some error checking
    if (row >= panel->_appearanceMap.size()){
        Logger::error("row is greater than appearance names size");
        return "";
    }
    QPair<QString, QString>* data = panel->_appearanceMap.at(row);
    if (data == NULL){
        Logger::error("Appearance name data is NULL!");
        return "";
    }
    if (col==0)
    {
     if(data->first.startsWith("SignalHeadState"))
      return data->first.mid(15);
     return data->first;
    }
    return data->second;
 }
 return QVariant();
}
//@Override
/*public*/ bool AppearanceTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();
    QPair<QString, QString>* data = panel->_appearanceMap.at(row);
    QString str = value.toString();
    QString msg = NULL;
    if (str==NULL || data==NULL) {
        msg = tr("NoData");
    }
    if (data!=NULL) {
        if (col==0) {
            data->first = value.toString();
        } else {
            data->second = value.toString();
        }
        if (msg!=NULL)
        {
//                JOptionPane.showMessageDialog(NULL, msg,
//                        tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
         QMessageBox::warning(NULL, tr("Warning"), msg);
        } else {
            fireTableRowsUpdated(row, row);
        }
    }
 }
 return false;
}
//};
/************************* Throttle Step Increment Table ******************************/
//class StepIncrementTableModel extends AbstractTableModel {
//    /*private*/ static final long serialVersionUID = 7088050123933847143L;

/*public*/ StepIncrementTableModel::StepIncrementTableModel(WarrantPreferencesPanel *panel) : AbstractTableModel()
{
        //super();
 this->panel = panel;
}

/*public*/ int StepIncrementTableModel::columnCount(const QModelIndex &parent) const
{
 return 2;
}

/*public*/ int StepIncrementTableModel::rowCount(const QModelIndex &parent) const
{
 return panel->_stepIncrementMap.size();
}

//@Override
/*public*/ QVariant StepIncrementTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
  if (section==0)
  {
     return tr("Throttle StepMode");
  }
  return tr("rampIncrement");
 }
 return QVariant();
}
//@Override
/*public*/ Qt::ItemFlags StepIncrementTableModel::flags(const QModelIndex &index) const
{
    //return (col!=0);
if(index.column() > 0)
return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
else
return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
//    //@Override
//    /*public*/ Class<?> getColumnClass(int col) {
//        return String.class;
//    }

/*public*/ int StepIncrementTableModel::getPreferredWidth(int col)
{
 if (col==0)
 {
  return  JTextField(15).getPreferredSize().width();
 }
 return  JTextField(5).getPreferredSize().width();
}

/*public*/ QVariant StepIncrementTableModel::data(const QModelIndex &index, int role) const
{
 if(role== Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();
  // some error checking
  if (row >= panel->_stepIncrementMap.size()){
      Logger::error("row is greater than throttle step modes size");
      return "";
  }
  QPair<QString, int>* data = panel->_stepIncrementMap.at(row);
  if (data == NULL)
  {
   Logger::error("Throttle step data is NULL!");
   return "";
  }
  if (col==0) {
      return data->first;
  }
  return data->second;
 }
 return QVariant();
}
//@Override
/*public*/ bool StepIncrementTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();

  QPair<QString, int>* data = panel->_stepIncrementMap.at(row);
  QString str = value.toString();
  QString msg = NULL;
  if (str==NULL || data==NULL)
  {
   msg = tr("NoData");
  }
  if (data!=NULL)
  {
   if (col==0)
   {
    data->first = value.toString();
   }
   else
   {
    bool bOk;
    int f = value.toInt();
    if (f < 1)
    {
     msg = tr("%1 is not a valid number for this parameter.").arg(value.toString());
    }
    else
    {
     data->second = f;
    }
    if(!bOk)
    {
     msg = tr("%1 is not a valid number for this parameter.").arg(value.toString());
    }
   }
   if (msg!=NULL)
   {
//                JOptionPane.showMessageDialog(NULL, msg,
//                        tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
    QMessageBox::warning(NULL, tr("Warning"), msg);
    return false;
   }
   else
   {
    fireTableRowsUpdated(row, row);
   }
  }
  return true;
 }
 return false;
}

/*public*/ QString WarrantPreferencesPanel::className() {return "jmri.jmrit.logix.WarrantPreferencesPanel";}

//}
