#include "decoratorpanel.h"
#include "editor.h"
#include "spinnernumbermodel.h"
#include <QColorDialog>
#include <QVBoxLayout>
#include <QButtonGroup>
#include "sensoricon.h"
#include "positionablepopuputil.h"
#include "jtextfield.h"
#include "flowlayout.h"
#include <QGroupBox>
#include "dataflavor.h"
#include "positionablelabelxml.h"
#include <QDrag>

//DecoratorPanel::DecoratorPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
*  ItemPanel for text labels
*/
///*public*/ class DecoratorPanel extends JPanel implements ChangeListener, ItemListener {

/*static*/ /*final*/ QStringList DecoratorPanel::JUSTIFICATION = QStringList() <<  tr("left") << tr("center") << tr("right");

/*static*/ /*final*/ QStringList DecoratorPanel::STYLES = QStringList() << tr("plain") <<tr("bold") << tr("italic") <<tr("bold/italic");

/*static*/ /*final*/ QStringList DecoratorPanel::FONTSIZE = QStringList() << "6" <<  "8" <<  "10" <<  "11" <<  "12" <<  "14" <<  "16" << "20" <<  "24" <<  "28" <<  "32" <<  "36";

/*public*/ DecoratorPanel::DecoratorPanel(Editor* editor, QWidget *parent) : QWidget(parent)
{
 _editor = editor;
 setLayout(new QVBoxLayout(this/*, BoxLayout.Y_AXIS*/));
}

//static class AJComboBox extends JComboBox {
//    int _which;
AJComboBox::AJComboBox(QStringList items, int which)
{
 //super(items);
 addItems(items);
 _which = which;
}
//};

/*private*/ QWidget* DecoratorPanel::makeBoxPanel(QString caption, AJComboBox* box) {
    QWidget* panel = new QWidget();
    panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
    panel->layout()->addWidget(new QLabel((caption)));
//    box->addItemListener(this);
    AJListener* ajl = new AJListener();
    ajl->init(box,this);
    connect(box, SIGNAL(currentIndexChanged(int)), ajl, SLOT(actionPerformed()));
    panel->layout()->addWidget(box);
    return panel;
}

//static class AJSpinner extends JSpinner {
//    int _which;

AJSpinner::AJSpinner(SpinnerModel* model, int which)
{
    //super(model);
    _which = which;
}
//};

//static class AJRadioButton extends JRadioButton {
//int which;

AJRadioButton::AJRadioButton(QString text, int w) : QRadioButton(text)
{
 //super(text);
 which = w;
}
//};

/*private*/ QWidget* DecoratorPanel::makeSpinPanel(QString caption, AJSpinner* spin) {
    QWidget* panel = new QWidget();
    panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
    panel->layout()->addWidget(new QLabel((caption)));
    //spin->addChangeListener(this);
    AJListener* ajl = new AJListener();
    ajl->init(spin,this);
    connect(spin, SIGNAL(valueChanged(int)), ajl, SLOT(actionPerformed()));
    panel->layout()->addWidget(spin);
    return panel;
}

/*public*/ void DecoratorPanel::initDecoratorPanel(Positionable* pos)
{
 _chooser = new QColorDialog(_editor->getTargetPanel()->backgroundBrush().color());
 _chooser->setOptions(QColorDialog::ShowAlphaChannel | QColorDialog::NoButtons);
 if(pos != NULL)
  _chooser->setCurrentColor(((PositionableLabel*)pos)->getForeground());
 connect(_chooser, SIGNAL(currentColorChanged(QColor)), this, SLOT(currentColorChanged(QColor)));
 //QWidget* samplePanel = new QWidget();
 QVBoxLayout* samplePanelLayout= new QVBoxLayout;
 //samplePanel->setLayout(samplePanelLayout = new QVBoxLayout);
 QFrame* preview = new QFrame();
 //QSizePolicy previewSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
 QVBoxLayout* previewLayout;
 preview->setLayout(previewLayout = new QVBoxLayout);//(preview/*, BoxLayout.Y_AXIS*/));
    //preview.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black, 1)));
 preview->setObjectName("myObject");
 preview->setStyleSheet("#myObject { border: 2px solid black; }");

 previewLayout->addStrut(STRUT);
 previewLayout->addLayout(samplePanelLayout);
 previewLayout->addStrut(STRUT);
//    preview.setBackground(_editor.getTargetPanel().getBackground());
//    samplePanel.setBackground(_editor.getTargetPanel().getBackground());
 text = tr("sample");
 _sample = new QHash <QString, PositionableLabel*>();
 _buttonGroup = new QButtonGroup();
 Positionable* item;		// copy of PositionableLabel being edited
 if (pos==NULL)
 {
  item = (Positionable*)new PositionableLabel("crap", _editor);
  _util = ((PositionableLabel*)item)->getPopupUtility();
 }
 else
 {
  item = ((PositionableLabel*)pos)->deepClone();
  //if (pos instanceof PositionableLabel)
  if(qobject_cast<PositionableLabel*>(pos) != NULL)
  {
   PositionableLabel* item = (PositionableLabel*)pos->deepClone();
   _isOpaque = ((PositionableLabel*)item)->getSaveOpaque();
   ((PositionableLabel*)item)->rotate(0);
   PositionablePopupUtil* u = ((PositionableLabel*)item)->getPopupUtility();
   text = ((PositionableLabel*)item)->getUnRotatedText();
   _util = ((PositionableLabel*)item)->getPopupUtility();

   PositionableLabel* p = (PositionableLabel*)pos;
   if (p->isRotated())
   {
    _isOpaque = ((PositionableLabel*)pos)->getSaveOpaque();
   }
   else
   {
    _isOpaque = ((PositionableLabel*)pos)->isOpaque();
   }
  }
  else
  {
   _isOpaque = ((PositionableLabel*)pos)->isOpaque();
   //_util = pos.getPopupUtility().clone(pos);
   _util = ((PositionableLabel*)item)->getPopupUtility();
  }
 }
 //samplePanel->layout()->addWidget(Box.createHorizontalStrut(STRUT));
 samplePanelLayout->addStrut(STRUT);
 //if (pos instanceof SensorIcon)
 if(qobject_cast<SensorIcon*>(pos)!= NULL)
 {
  SensorIcon* si = (SensorIcon*)pos;
  if (!si->isIcon() && si->isText())
  {
    PositionableLabel* sample = new PositionableLabel(si->getActiveText(), _editor);
    sample->setForeground(si->getTextActive());
    sample->setBackground(si->getBackgroundActive());
    sample->setPopupUtility(_util);
    _sample->insert("Active", sample);
    samplePanelLayout->addWidget(sample);
    //samplePanel->layout()->addWidget(Box.createHorizontalStrut(STRUT));
    samplePanelLayout->addStrut(STRUT);
    this->layout()->addWidget(makeTextPanel("Active", sample, ACTIVE_FONT));

    sample = new PositionableLabel(si->getInactiveText(), _editor);
    sample->setForeground(si->getTextInActive());
    sample->setBackground(si->getBackgroundInActive());
    sample->setPopupUtility(_util);
    _sample->insert("InActive", sample);
    samplePanelLayout->addWidget(sample);
    samplePanelLayout->addStrut(STRUT);
    this->layout()->addWidget(makeTextPanel("InActive", sample, INACTIVE_FONT));

    sample = new PositionableLabel(si->getUnknownText(), _editor);
    sample->setForeground(si->getTextUnknown());
    sample->setBackground(si->getBackgroundUnknown());
    sample->setPopupUtility(_util);
    _sample->insert("Unknown", sample);
    samplePanelLayout->addWidget(sample);
    samplePanelLayout->addStrut(STRUT);
    this->layout()->addWidget(makeTextPanel("Unknown", sample, UNKOWN_FONT));

    sample = new PositionableLabel(si->getInconsistentText(), _editor);
    sample->setForeground(si->getTextInconsistent());
    sample->setBackground(si->getBackgroundInconsistent());
    sample->setPopupUtility(_util);
    _sample->insert("Inconsistent", sample);
    samplePanelLayout->addWidget(sample);
    this->layout()->addWidget(makeTextPanel("Inconsistent", sample, INCONSISTENT_FONT));
  }
 }
#if 1
 else
 {
  PositionableLabel* sample;
  if (pos==NULL)
  {
   sample = new DragDecoratorLabel(text, _editor, this);
   sample->setLevel(Editor::LABELS);
   sample->setPopupUtility(_util);
  }
  else
  {
   sample = new PositionableLabel(text, _editor);
   sample->setPopupUtility(_util);
   sample->setForeground(((PositionableLabel*)pos)->getForeground());
   sample->setBackground(((PositionableLabel*)pos)->getBackground());
      _util->setBackgroundColor(((PositionableLabel*)pos)->getBackground());
      sample->setOpaque(true);
     }
     _sample->insert("Text", sample);
     samplePanelLayout->addWidget(sample);
     this->layout()->addWidget(makeTextPanel("Text", sample, TEXT_FONT));
    }
#endif
    samplePanelLayout->addStrut(STRUT);

    QWidget* fontPanel = new QWidget();
    fontPanel->setLayout(new FlowLayout);
    _fontSizeBox = new AJComboBox(FONTSIZE, SIZE);
    fontPanel->layout()->addWidget(makeBoxPanel("Font Size", _fontSizeBox));
    int row = 4;
    for (int i=0; i<FONTSIZE.count(); i++) {
        if (_util->getFontSize()==FONTSIZE.at(i).toInt())
        {
            row = i;
            break;
        }
    }
    _fontSizeBox->setCurrentIndex(row);

    _fontStyleBox = new AJComboBox(STYLES, STYLE);
    fontPanel->layout()->addWidget(makeBoxPanel("Font Style", _fontStyleBox));
    _fontStyleBox->setCurrentIndex(_util->getFont().style());

    _fontJustBox = new AJComboBox(JUSTIFICATION, JUST);
    fontPanel->layout()->addWidget(makeBoxPanel("Justification", _fontJustBox));
    switch (_util->getJustification()){
        case PositionablePopupUtil::LEFT:     row = 0;
                        break;
    case PositionablePopupUtil::RIGHT:    row = 2;
                        break;
    case PositionablePopupUtil::CENTRE:   row = 1;
                        break;
        default     :   row = 2;
    }
    _fontJustBox->setCurrentIndex(row);
    this->layout()->addWidget(fontPanel);


    QWidget* sizePanel = new QWidget();
    sizePanel->setLayout(new FlowLayout);
    SpinnerNumberModel* model = new SpinnerNumberModel(_util->getBorderSize(),0,100,1);
    _borderSpin = new AJSpinner(model, BORDER);
    sizePanel->layout()->addWidget(makeSpinPanel(tr("Border Size"), _borderSpin));
    model = new SpinnerNumberModel(_util->getMargin(),0,100,1);
    _marginSpin = new AJSpinner(model, MARGIN);
    sizePanel->layout()->addWidget(makeSpinPanel(tr("Margin Size"), _marginSpin));
    model = new SpinnerNumberModel(_util->getFixedWidth(),0,1000,1);
    _widthSpin = new AJSpinner(model, FWIDTH);
    sizePanel->layout()->addWidget(makeSpinPanel(tr("Fixed Width"), _widthSpin));
    model = new SpinnerNumberModel(_util->getFixedHeight(),0,1000,1);
    _heightSpin = new AJSpinner(model, FHEIGHT);
    sizePanel->layout()->addWidget(makeSpinPanel(tr("Fixed Height"), _heightSpin));
    this->layout()->addWidget(sizePanel);

    QWidget* colorPanel = new QWidget();
    colorPanel->setLayout(new FlowLayout);
    colorPanel->layout()->addWidget(makeButton(new AJRadioButton(tr("Border Color"), BORDER_COLOR)));
    //colorPanel->layout()->addWidget(makeButton(new AJRadioButton(ItemPalette.rbp.getString("transparentBack"), TRANSPARENT_COLOR)));
    AJRadioButton* button = new AJRadioButton(tr("Transparent Background"), TRANSPARENT_COLOR);
//    button->addActionListener(new ActionListener() {
//        JRadioButton button ;
//        /*public*/ void actionPerformed(ActionEvent a) {
//            if (button.isSelected()) {
//                _isOpaque = false;
//                _util.setBackgroundColor(NULL);
//                updateSamples();
//            }
//        }
//        ActionListener init(JRadioButton b) {
//            button = b;
//            return this;
//        }
//    }.init(button));
    connect(button, SIGNAL(toggled(bool)), this, SLOT(AJRadioButton_toggled(bool)));
    _buttonGroup->addButton(button);
    colorPanel->layout()->addWidget(button);
    this->layout()->addWidget(colorPanel);

//    _chooser->getSelectionModel()->addChangeListener(this);
//    _chooser->setPreviewPanel(preview);
    this->layout()->addWidget(_chooser);
    ((QVBoxLayout*)this->layout())->addWidget(preview,0,Qt::AlignCenter);
    updateSamples();
    item->setVisible(false);		// otherwise leaves traces for PositionableJPanels
}
void DecoratorPanel::AJRadioButton_toggled(bool b)
{
 if (b)
 {
  _isOpaque = false;
  _util->setBackgroundColor(QColor());
  updateSamples();
 }
}

/*private*/ QWidget* DecoratorPanel::makeTextPanel(QString caption, PositionableLabel* sample, int state) {
    QGroupBox* panel = new QGroupBox();
//    panel->setBorder(BorderFactory.createTitledBorder(ItemPalette.rbp.getString(caption)));
    QVBoxLayout* panelLayout;
    panel->setLayout(panelLayout = new QVBoxLayout(/*panel, BoxLayout.Y_AXIS*/));
//    QWidget* p = new QWidget();
//    p->setLayout(new FlowLayout);
    FlowLayout* pLayout = new FlowLayout;
    JTextField* textField = new JTextField(sample->getText(), 25);
#if 0
    textField->addKeyListener(new KeyListener() {
        JLabel sample;
        KeyListener init(JLabel s) {
            sample = s;
            return this;
        }
        /*public*/ void keyTyped(KeyEvent E) { }
        /*public*/ void keyPressed(KeyEvent E){ }
        /*public*/ void keyReleased(KeyEvent E) {
          JTextField tmp = (JTextField) E.getSource();
          sample->setText(tmp.getText());
        }
      }.init(sample));
#endif
    TextFieldListener* keylistener = new TextFieldListener();
    keylistener->init(textField, sample, this);
    connect(textField, SIGNAL(textEdited(QString)), keylistener, SLOT(actionPerformed()));
    pLayout->addWidget(textField);
    panelLayout->addLayout(pLayout);

    //p = new QWidget();
    //p->setLayout(new FlowLayout);
 pLayout = new FlowLayout;
 AJRadioButton* b;
 pLayout->addWidget(b = makeButton(new AJRadioButton(tr("Font Color"), state)));
 b->setChecked(true);
 _selectedButton = TEXT_FONT;
 pLayout->addWidget(makeButton(new AJRadioButton(tr("Background Color"), state+10)));
 panelLayout->addLayout(pLayout);

 return panel;
}
TextFieldListener* TextFieldListener::init(JTextField* textField, JLabel *sample, DecoratorPanel *panel)
{
 this->sample = sample;
 this->panel = panel;
 this->textField = textField;
 return this;
}
void TextFieldListener::actionPerformed(ActionEvent *e)
{
 sample->setText(textField->text());
 panel->text = textField->text();
}


/*private*/ AJRadioButton* DecoratorPanel::makeButton(AJRadioButton* button)
{
// button->layout()->addWidgetActionListener(new ActionListener() {
//        AJRadioButton button ;
//        /*public*/ void actionPerformed(ActionEvent a) {
//            if (button.isSelected()) {
//                _selectedButton = button.which;
//            }
//        }
//        ActionListener init(AJRadioButton b) {
//            button = b;
//            return this;
//        }
//    }.init(button));
 AJRBActionListener* al = new AJRBActionListener();
 al->init(button, this);
 connect(button, SIGNAL(clicked()), al, SLOT(actionPerformed()));
 _buttonGroup->addButton(button);
 return button;
}
/*public*/ void AJRBActionListener::actionPerformed(/*ActionEvent a*/)
{
 if (button->isChecked())
 {
  self->_selectedButton = button->which;
  switch(button->which)
  {
  case DecoratorPanel::TEXT_FONT:
//   _sample->value("Text")->setForeground(_chooser->currentColor());
//   util->setForeground(_chooser->currentColor());
      self->_chooser->setCurrentColor(self->_sample->value("Text")->getForeground());
   break;
  case DecoratorPanel::ACTIVE_FONT:
   //_sample->value("Active")->setForeground(_chooser->currentColor());
      self->_chooser->setCurrentColor(self->_sample->value("Active")->getForeground());
   break;
  case DecoratorPanel::INACTIVE_FONT:
   //_sample->value("InActive")->setForeground(_chooser->currentColor());
      self->_chooser->setCurrentColor(self->_sample->value("InActive")->getForeground());
   break;
  case DecoratorPanel::UNKOWN_FONT:
   //_sample->value("Unknown")->setForeground(_chooser->currentColor());
      self->_chooser->setCurrentColor(self->_sample->value("Unknown")->getForeground());
   break;
  case DecoratorPanel::INCONSISTENT_FONT:
   //_sample->value("Inconsistent")->setForeground(_chooser->currentColor());
      self->_chooser->setCurrentColor(self->_sample->value("Inconsistent")->getForeground());
   break;
  case DecoratorPanel::TEXT_BACKGROUND:
//   _sample->value("Text")->setBackground(_chooser->currentColor());
//   util->setBackgroundColor(_chooser->currentColor());
//   _isOpaque = true;
   self->_chooser->setCurrentColor(self->_sample->value("Text")->getBackground());
   break;
  case DecoratorPanel::ACTIVE_BACKGROUND:
//   _sample->value("Active")->setBackground(_chooser->currentColor());
//   _sample->value("Active")->setOpaque(true);
//   _isOpaque = true;
      self->_chooser->setCurrentColor(self->_sample->value("Active")->getBackground());
   break;
  case DecoratorPanel::INACTIVE_BACKGROUND:
//   _sample->value("InActive")->setBackground(_chooser->currentColor());
//   _sample->value("InActive")->setOpaque(true);
//   _isOpaque = true;
      self->_chooser->setCurrentColor(self->_sample->value("InActive")->getBackground());
   break;
  case DecoratorPanel::UNKOWN_BACKGROUND:
//   _sample->value("Unknown")->setBackground(_chooser->currentColor());
//   _sample->value("Unknown")->setOpaque(true);
//   _isOpaque = true;
      self->_chooser->setCurrentColor(self->_sample->value("Unknown")->getBackground());
   break;
  case DecoratorPanel::INCONSISTENT_BACKGROUND:
//   _sample->value("Inconsistent")->setBackground(_chooser->currentColor());
//   _sample->value("Inconsistent")->setOpaque(true);
//   _isOpaque = true;
      self->_chooser->setCurrentColor(self->_sample->value("Inconsistent")->getBackground());
   break;
  case DecoratorPanel::TRANSPARENT_COLOR:
//   util->setBackgroundColor(QColor());
//   _isOpaque = false;
   break;
  case DecoratorPanel::BORDER_COLOR:
//   util->setBorderColor(_chooser->currentColor());
//      self->_chooser->setCurrentColor(self->_sample->value("Text")->getBorderColor());
   break;

  }
 }
}
AJRBActionListener* AJRBActionListener::init(AJRadioButton* b, DecoratorPanel* self) {
    this->self = self;
    button = b;
    return this;
}

/*private*/ void DecoratorPanel::updateSamples()
{
 PositionablePopupUtil* util = getPositionablePopupUtil();
 int mar = util->getMargin();
 int bor = util->getBorderSize();
#if 0
    Border outlineBorder;
    if (bor==0) {
        outlineBorder = BorderFactory.createEmptyBorder(0, 0, 0, 0);
    }else {
        outlineBorder = new LineBorder(util.getBorderColor(), bor);
    }
#endif
 QFont font = _util->getFont();
 int just = util->getJustification();
 QListIterator<PositionableLabel*> it(_sample->values());
 while (it.hasNext())
 {
  PositionableLabel* sam = it.next();
  sam->setOpaque(_isOpaque);
  sam->setFont(font);
#if 0
        Border borderMargin;
        if (_isOpaque){
            borderMargin = new LineBorder(sam->getBackground(),mar);
        } else{
            borderMargin = BorderFactory.createEmptyBorder(mar, mar, mar, mar);
        }
        sam->setBorder(new CompoundBorder(outlineBorder, borderMargin));
#endif
  if(bor > 0)
  {
   sam->setFrameStyle(QFrame::Box);
   sam->setLineWidth(bor);
  }
  sam->setMargin(mar);
  sam->setBackgroundColor(util->getBackground());
  switch (just)
  {
   case PositionablePopupUtil::LEFT:
        sam->setHorizontalAlignment(JLabel::LEFT);
        break;
   case PositionablePopupUtil::RIGHT:
        sam->setHorizontalAlignment(JLabel::RIGHT);
        break;
   default:
        sam->setHorizontalAlignment(JLabel::CENTER);
  }
  sam->setStyleSheet();
  sam->updateSize();
  sam->invalidate();
 }
}

/*public*/ void DecoratorPanel::stateChanged(ChangeEvent* e)
{
 PositionablePopupUtil* util = getPositionablePopupUtil();
 QObject* obj = e->getSource();
 //if (obj instanceof AJSpinner)
 if(qobject_cast<AJSpinner*>(obj)!= NULL )
 {
  int num = ((AJSpinner*)obj)->value();
  switch (((AJSpinner*)obj)->_which)
  {
   case BORDER:
        util->setBorderSize(num);
        break;
   case MARGIN:
        util->setMargin(num);
        break;
   case FWIDTH:
        util->setFixedWidth(num);
        break;
   case FHEIGHT:
        util->setFixedHeight(num);
        break;
  }
 }
 else
 {
  switch (_selectedButton)
  {
   case TEXT_FONT:
    _sample->value("Text")->setForeground(_chooser->currentColor());
    util->setForeground(_chooser->currentColor());
    break;
   case ACTIVE_FONT:
    _sample->value("Active")->setForeground(_chooser->currentColor());
    break;
   case INACTIVE_FONT:
    _sample->value("InActive")->setForeground(_chooser->currentColor());
    break;
   case UNKOWN_FONT:
    _sample->value("Unknown")->setForeground(_chooser->currentColor());
    break;
   case INCONSISTENT_FONT:
    _sample->value("Inconsistent")->setForeground(_chooser->currentColor());
    break;
   case TEXT_BACKGROUND:
    _sample->value("Text")->setBackground(_chooser->currentColor());
    _util->setBackgroundColor(_chooser->currentColor());
    _isOpaque = true;
    break;
   case ACTIVE_BACKGROUND:
    _sample->value("Active")->setBackground(_chooser->currentColor());
    _sample->value("Active")->setOpaque(true);
    util->setBackgroundColor(_chooser->currentColor());
    _isOpaque = true;
    break;
   case INACTIVE_BACKGROUND:
    _sample->value("InActive")->setBackground(_chooser->currentColor());
    _sample->value("InActive")->setOpaque(true);
    util->setBackgroundColor(_chooser->currentColor());
    _isOpaque = true;
    break;
   case UNKOWN_BACKGROUND:
    _sample->value("Unknown")->setBackground(_chooser->currentColor());
    _sample->value("Unknown")->setOpaque(true);
    util->setBackgroundColor(_chooser->currentColor());
    _isOpaque = true;
    break;
   case INCONSISTENT_BACKGROUND:
    _sample->value("Inconsistent")->setBackground(_chooser->currentColor());
    _sample->value("Inconsistent")->setOpaque(true);
    util->setBackgroundColor(_chooser->currentColor());
    _isOpaque = true;
    break;
   case TRANSPARENT_COLOR:
    util->setBackgroundColor(QColor());
    _sample->value("Text")->setOpaque(false);
    _isOpaque = false;
    break;
   case BORDER_COLOR:
    util->setBorderColor(_chooser->currentColor());
    break;
    }
}
 updateSamples();
}

/*public*/ PositionablePopupUtil* DecoratorPanel::getPositionablePopupUtil()
{
 return _util;
}

/*public*/ void DecoratorPanel::getText(Positionable* pos)
{
 //if (pos instanceof SensorIcon && ((SensorIcon)pos).isText())
 if((qobject_cast<SensorIcon*>(pos)!=NULL) &&(((SensorIcon*)pos)->isText()) )
 {
    SensorIcon* icon = (SensorIcon*)pos;
    PositionableLabel* sample = _sample->value("Active");
    icon->setActiveText(sample->getText());
    icon->setBackgroundActive(sample->getBackground());
    icon->setTextActive(sample->getForeground());

    sample = _sample->value("InActive");
    icon->setInactiveText(sample->getText());
    icon->setBackgroundInActive(sample->getBackground());
    icon->setTextInActive(sample->getForeground());

    sample = _sample->value("Unknown");
    icon->setUnknownText(sample->getText());
    icon->setBackgroundUnknown(sample->getBackground());
    icon->setTextUnknown(sample->getForeground());

    sample = _sample->value("Inconsistent");
    icon->setInconsistentText(sample->getText());
    icon->setBackgroundInconsistent(sample->getBackground());
    icon->setTextInconsistent(sample->getForeground());
 }
 else
 {
    PositionableLabel* sample = _sample->value("Text");
    ((PositionableLabel*)pos)->setBackground(sample->getBackground());
    ((PositionableLabel*)pos)->setForeground(sample->getForeground());
    //if (pos instanceof PositionableLabel)
    if(qobject_cast<PositionableLabel*>(pos)!= NULL)
    {
     ((PositionableLabel*)pos)->setText(_sample->value("Text")->getText());
    }
 }
 ((PositionableLabel*)pos)->setPopupUtility(_util);
}

/*public*/ bool DecoratorPanel::isOpaque()
{
 return _isOpaque;
}

/*public*/ void DecoratorPanel::itemStateChanged(ItemEvent* e)
{
 PositionablePopupUtil* util = getPositionablePopupUtil();
 QObject* obj = e->getSource();
 //if (obj instanceof AJComboBox)
 if(qobject_cast<AJComboBox*>(obj)!= NULL)
 {
  QString size;
  int style;
  int weight;
  int just;
  switch (((AJComboBox*)obj)->_which)
  {
   case SIZE:
    size = ((AJComboBox*)obj)->currentText();
    util->setFontSize(size.toFloat());
    break;
   case STYLE:
    style = 0;
    weight = QFont::Normal;
    switch (((AJComboBox*)obj)->currentIndex())
    {
     case 0:
      style = /*Font.PLAIN*/QFont::StyleNormal;
      weight = QFont::Normal;
      break;
     case 1:
      style = QFont::StyleNormal;
      weight = QFont::Bold;
      break;
     case 2:
      style = QFont::StyleItalic;
      weight = QFont::Normal;
      break;
     case 3:
      //style = (Font.BOLD | Font.ITALIC);
      style = QFont::StyleItalic;
      weight = QFont::Bold;
      break;
     }
     util->setFontStyle(style);
     util->setFontWeight(weight);
     break;
    case JUST:
     just = 0;
     switch (((AJComboBox*)obj)->currentIndex())
     {
      case 0:
        just = PositionablePopupUtil::LEFT;
        break;
      case 1:
        just = PositionablePopupUtil::CENTRE;
        break;
      case 2:
        just = PositionablePopupUtil::RIGHT;
        break;
   }
   util->setJustification(just);
   break;
  }
  //updateSamples();
 }
 else if(qobject_cast<AJSpinner*>(obj) != NULL)
 {
     int bor;
     int mar;
     switch(((AJSpinner*)obj)->_which)
     {
     case BORDER:
      bor = ((AJSpinner*)obj)->value();
      util->setBorderSize(bor);
      break;
     case MARGIN:
      mar = ((AJSpinner*)obj)->value();
      util->setMargin(mar);
      break;
     }
 }

 updateSamples();
}
#if 1
/**
* Export a Positionable item from panel
*/
//class DragDecoratorLabel : public PositionableLabel //implements DragGestureListener, DragSourceListener, Transferable {

//    DataFlavor dataFlavor;

/*public*/ DragDecoratorLabel::DragDecoratorLabel(QString s, Editor* editor, QObject* parent) : PositionableLabel(s, editor,(Positionable*)parent)
{
 //super(s, editor);
//        DragSource dragSource = DragSource.getDefaultDragSource();
//        dragSource.createDefaultDragGestureRecognizer(this,
//                    DnDConstants.ACTION_COPY, this);
//        try {
            dataFlavor = new DataFlavor(Editor::POSITIONABLE_FLAVOR);
//        } catch (ClassNotFoundException cnfe) {
//            cnfe.printStackTrace();
//        }
    }
    /**************** DragGestureListener ***************/
//    /*public*/ void dragGestureRecognized(DragGestureEvent e) {
//        if (log.isDebugEnabled()) log.debug("DragPositionable.dragGestureRecognized ");
//        //Transferable t = getTransferable(this);
//        e.startDrag(DragSource.DefaultCopyDrop, this, this);
//    }
//    /**************** DragSourceListener ************/
//    /*public*/ void dragDropEnd(DragSourceDropEvent e) {
//        }
//    /*public*/ void dragEnter(DragSourceDragEvent e) {
//        }
//    /*public*/ void dragExit(DragSourceEvent e) {
//        }
//    /*public*/ void dragOver(DragSourceDragEvent e) {
//        }
//    /*public*/ void dropActionChanged(DragSourceDragEvent e) {
//        }
//    /*************** Transferable *********************/
    /*public*/ QList<DataFlavor*> DragDecoratorLabel::getTransferDataFlavors() {
        //if (log.isDebugEnabled()) log.debug("DragPositionable.getTransferDataFlavors ");
    return  QList<DataFlavor*>() <<  dataFlavor ;
    }
    /*public*/ bool DragDecoratorLabel::isDataFlavorSupported(DataFlavor* flavor) {
        //if (log.isDebugEnabled()) log.debug("DragPositionable.isDataFlavorSupported ");
        return dataFlavor==(flavor);
    }
//    /*public*/ Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException,IOException {
//        if (!isDataFlavorSupported(flavor)) {
//            return NULL;
//        }
//        return _sample->value("Text").deepClone();
//    }
void DragDecoratorLabel::mousePressEvent(QMouseEvent *e)
{
 QString text = mimeData();
 if(text != "")
 {
  if(e->button()&Qt::LeftButton)
  {
   QDrag *dr = new QDrag(this);
   QMimeData *data = new QMimeData;
   //data->setText(_dataFlavor->toString());
   data->setText(text);
   // Assign ownership of the QMimeData object to the QDrag object.
   dr->setMimeData(data);
   dr->start();
  }
 }
}
QString DragDecoratorLabel::mimeData()
{
 PositionableLabel* l;
 dataFlavor = new DataFlavor(l = new PositionableLabel(getText(),_editor,parent), "PositionableLabel");
 l->_text = true;
 l->setLevel(Editor::LABELS);
 l->setFont(getFont());
 l->setBackground(getBackground());
 PositionablePopupUtil* util = ((PositionableLabel*)l)->getPopupUtility();
 l->setForeground(getForeground());
 util->setForeground(getForeground());

 PositionableLabelXml* xml = new PositionableLabelXml();
 QDomElement e = xml->store((QObject*)l);
 xml->doc.appendChild(e);
 QString xmldata = xml->doc.toString();
 dataFlavor->setMimeTypeParameter("xml", QString(QUrl::toPercentEncoding(xmldata)));
 return dataFlavor->toString();
}

//}; // end DragDecoratorLabel
#endif
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DecoratorPanel.class.getName());
//}
void DecoratorPanel::currentColorChanged(QColor)
{
 stateChanged(new ChangeEvent(_chooser));
}
