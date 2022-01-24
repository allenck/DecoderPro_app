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
#include "bufferedimage.h"
#include "drawsquares.h"
#include "imagepanel.h"
#include <QComboBox>
#include "displayframe.h"
#include "loggerfactory.h"
#include "jmricolorchooser.h"
#include "box.h"
#include "itempanel.h"
#include "colorutil.h"
#include "lememoryicon.h"
#include "memoryinputicon.h"
#include "memorycomboicon.h"
#include "memoryspinnericon.h"
#include "textitempanel.h"
#include "jcolorchooser.h"
#include <QSignalMapper>
#include "colorselectionmodel.h"
#include "fontpanel.h"
#include "colorchooserpanel.h"
#include "colormodel.h"
#include "defaultswatchchooserpanel.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include "borderfactory.h"
#include "compoundborder.h"
//#include "previewpanel.h"
#include <QStringList>
#include "jmricolorchooser.h"

//DecoratorPanel::DecoratorPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
*  ItemPanel for text labels
*/
///*public*/ class DecoratorPanel extends JPanel implements ChangeListener, ItemListener {

/*static*/ /*final*/ QStringList DecoratorPanel::JUSTIFICATION = QStringList() <<  tr("Left") << tr("Center") << tr("Right");

/*static*/ /*final*/ QStringList DecoratorPanel::STYLES = QStringList() << tr("Plain") <<tr("bold") << tr("Italic") <<tr("Bold/Italic");

/*static*/ /*final*/ QStringList DecoratorPanel::FONTSIZE = QStringList() << "6" <<  "8" <<  "10" <<  "11" <<  "12" <<  "14" <<  "16" << "20" <<  "24" <<  "28" <<  "32" <<  "36";

/*public*/ DecoratorPanel::DecoratorPanel(Editor* editor, QWidget *parent) : JPanel(parent)
{
 _editor = editor;
 setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));
 QColor bkgrnd = _editor->getTargetPanel()->getBackground();
 _chooser = new JColorChooser(bkgrnd);
 _chooser = JmriColorChooser::extendColorChooser(_chooser);
 _previewPanel = new JPanel();
 _previewPanel->setLayout(new QVBoxLayout());//_previewPanel, BoxLayout.Y_AXIS));
 _previewPanel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black, 1)));
 _previewPanel->layout()->addWidget(Box::createVerticalStrut(STRUT));
 _previewPanel->layout()->addWidget(Box::createVerticalStrut(STRUT));
 _previewPanel->setBackground(bkgrnd);
 _sample = new QHash<QString, PositionableLabel*>();
 _buttonGroup = new QButtonGroup();
 _selectedState = "Text";
}

/*private*/ JPanel* DecoratorPanel::makeBoxPanel(QString caption, JComboBox* box) {
    JPanel* panel = new JPanel();
    panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
    panel->layout()->addWidget(new JLabel((caption)));
    box->addItemListener((ItemListener*)this);
    panel->layout()->addWidget(box);
    return panel;
}

/*private*/ JPanel* DecoratorPanel::makeSpinPanel(QString caption, JSpinner* spin) {
    JPanel* panel = new JPanel();
    panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
    panel->layout()->addWidget(new JLabel((caption)));
    spin->addChangeListener((ChangeListener*)this);
    panel->layout()->addWidget(spin);
    return panel;
}

/*protected*/ JPanel* DecoratorPanel::getPreviewPanel() {
    return _previewPanel;
}

/* Called by Palette's TextItemPanel i.e. make a new panel item to drag */
/*protected*/ void DecoratorPanel::initDecoratorPanel(DragDecoratorLabel* sample) {
 sample->setDisplayLevel(Editor::LABELS);
 sample->setBackground(_editor->getTargetPanel()->getBackground());
 _previewPanel->layout()->addWidget(sample);
 sample->setText("sample");
 _util = sample->getPopupUtility();
 PositionableLabel* l = new PositionableLabel("sample", _editor);
 _sample->insert("Text", l);
 QWidget* textPanel;
 if(_util == nullptr)
  _util = l->getPopupUtility();
 this->layout()->addWidget(textPanel = makeTextPanel("Text", sample, TEXT_FONT));
// l->setPopupUtility(_util);
// getDragJTextField()->setUtil(_util);


 _label = new PositionableLabel("sample",_editor);

 makeFontPanels();
}

/*public*/ void DecoratorPanel::initDecoratorPanel(Positionable* pos)
{
 Positionable* item = pos->deepClone();		// copy of PositionableLabel being edited
 QString text = ("sample");
 if (qobject_cast<PositionableLabel*>(pos->self())) {
     _isOpaque = item->getSaveOpaque();
     item->rotate(0);
     text = ((PositionableLabel*) item)->getUnRotatedText();

     PositionableLabel* p = (PositionableLabel*) pos;
     if (p->isRotated()) {
         _isOpaque = pos->getSaveOpaque();
     } else {
         _isOpaque = pos->isOpaque();
     }
 } else {
     _isOpaque = pos->isOpaque();
 }
 _util = item->getPopupUtility();
 JPanel* samplePanel = new JPanel(new FlowLayout());
 samplePanel->layout()->addWidget(Box::createHorizontalStrut(STRUT));
 samplePanel->setBackground(_editor->getTargetPanel()->getBackground());

 if (qobject_cast<SensorIcon*>(pos->self()) && !((SensorIcon*)pos->self())->isIcon())
 {
  SensorIcon* si = (SensorIcon*) pos;
  if (!si->isIcon() && si->isText())
  {
   PositionableLabel* sample = new PositionableLabel(si->getActiveText(), _editor);
   sample->setForeground(si->getTextActive());
   sample->setBackground(si->getBackgroundActive());
   sample->setPopupUtility(_util);
   _sample->insert("Active", sample);
   samplePanel->layout()->addWidget(sample);
   samplePanel->layout()->addWidget(Box::createHorizontalStrut(STRUT));
   this->layout()->addWidget(makeTextPanel("Active", sample, ACTIVE_FONT));

   sample = new PositionableLabel(si->getInactiveText(), _editor);
   sample->setForeground(si->getTextInActive());
   sample->setBackground(si->getBackgroundInActive());
   sample->setPopupUtility(_util);
   _sample->insert("InActive", sample);
   samplePanel->layout()->addWidget(sample);
   samplePanel->layout()->addWidget(Box::createHorizontalStrut(STRUT));
   this->layout()->addWidget(makeTextPanel("InActive", sample, INACTIVE_FONT));

   sample = new PositionableLabel(si->getUnknownText(), _editor);
   sample->setForeground(si->getTextUnknown());
   sample->setBackground(si->getBackgroundUnknown());
   sample->setPopupUtility(_util);
   _sample->insert("Unknown", sample);
   samplePanel->layout()->addWidget(sample);
   samplePanel->layout()->addWidget(Box::createHorizontalStrut(STRUT));
   this->layout()->addWidget(makeTextPanel("Unknown", sample, UNKOWN_FONT));

   sample = new PositionableLabel(si->getInconsistentText(), _editor);
   sample->setForeground(si->getTextInconsistent());
   sample->setBackground(si->getBackgroundInconsistent());
   sample->setPopupUtility(_util);
   _sample->insert("Inconsistent", sample);
   samplePanel->layout()->addWidget(sample);
   this->layout()->addWidget(makeTextPanel("Inconsistent", sample, INCONSISTENT_FONT));
  }   // else a non-text SensorIcon cannot be decorated.
 }
 else { // not a SensorIcon
   PositionableLabel* sample = new PositionableLabel(text, _editor);
   sample->setPopupUtility(_util);
   sample->setForeground(pos->getForeground());
   sample->setBackground(pos->getBackground());
   _util->setBackgroundColor(pos->getBackground());
   sample->setOpaque(true);
   _sample->insert("Text", sample);
   samplePanel->layout()->addWidget(sample);
   this->layout()->addWidget(makeTextPanel("Text", sample, TEXT_FONT));
  }
  samplePanel->layout()->addWidget(Box::createHorizontalStrut(STRUT));
  _previewPanel->layout()->addWidget(samplePanel);
  makeFontPanels();
  item->setVisible(false);		// otherwise leaves traces for PositionableJPanels
}
#if 0
/*public*/ void PreviewScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
 QList<QGraphicsItem*> itemList = items(/*QPointF(event->pos().x(), event->pos().y())*/);
 if(!itemList.isEmpty())
 {
  item = itemList.at(2);
  if(item && event->buttons() != 0)
  {
    if(panel->_sample->size() > 0)
    {
     PositionableLabel* pos = panel->_sample->values().at(0);
     ((DragDecoratorLabel*)pos)->mousePressEvent(convertMouseEvent( event));
    }
  }
 }
 else
  item = nullptr;
}

/*public*/ void PreviewScene::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
 if(item)
 {
  if(panel->_sample->size() > 0)
  {
   PositionableLabel* pos = panel->_sample->values().at(0);
//   pos->mouseMoveEvent(event);
  }
 }
}

/*private*/ QMouseEvent* PreviewScene::convertMouseEvent(QGraphicsSceneMouseEvent *evt)
{
 QPointF scenePos = evt->pos();
 QPointF screenPos = evt->screenPos();
 return new QMouseEvent(evt->type(), screenPos, evt->button(), evt->buttons(), evt->modifiers());
}

/*public*/ void PreviewScene::setImage(QImage* img) {
    back = (BufferedImage*) img;
//    repaint();
    bkgnd = QPixmap::fromImage(*back);
    QRectF rect = this->sceneRect();

    bkgnd = bkgnd.scaled(QSize(rect.width(), rect.height()), Qt::KeepAspectRatioByExpanding);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, bkgnd);
//    this->setPalette(palette);
    views().at(0)->setBackgroundBrush(QBrush(bkgnd));
    update();
}
#endif
//static class AJSpinner extends JSpinner {
//    int _which;
AJSpinner::AJSpinner(SpinnerModel* items, int which, QWidget* parent)
 : JSpinner(/*items,*/ parent)
{
 _which = which;
 SpinnerNumberModel* nm = (SpinnerNumberModel*)items;
 setValue(nm->getValue().toInt());
 setMinimum(nm->getMinimum().toInt());
 setMaximum(nm->getMaximum().toInt());
 setSingleStep(nm->getStepSize().toInt());
}
//};
//static class AJSpinner extends JSpinner {
//    int _which;

//AJSpinner::AJSpinner(SpinnerModel* model, int which)
//{
//    //super(model);
//    _which = which;
//}
//};

//static class AJRadioButton extends JRadioButton {
//int which;

//AJRadioButton::AJRadioButton(QString text, int w) : QRadioButton(text)
//{
// //super(text);
// _which = w;
// //_state = state;
// connect(this, SIGNAL(clicked(bool)), this, SLOT(onClick()));
//}


//QString AJRadioButton::getState() {
//    return _state;
//}
//};




/*protected*/ void DecoratorPanel::fontChange() {
    _selectedButton = FOREGROUND_BUTTON;
    _fontButton->setChecked(true);
//    _chooser->setColor(_util->getForeground());
    _chooser->setColor(_util->getForeground());
    log->debug("fontChange");
    updateSamples();
 }

#if 0
/*private*/ void DecoratorPanel::finishInit(bool addCaption) {
 _selectedButton = FOREGROUND_BUTTON;
 if (addCaption) {
     _selectedState = "SensorStateActive";
 } else {
     _selectedState = "Text";
 }
 JPanel* colorButtons = makeColorPanel(addCaption);
 makeColorChooser();
 JPanel panel = makeFontPanel();
 if (addCaption) {
     JPanel p = new JPanel();
     p.add(new JLabel(Bundle.getMessage("StateTextBlurb1")));
     panel.add(p);
 }
 this.add(panel);
 if (addCaption) {
     JPanel p = new JPanel();
     p.add(new JLabel(Bundle.getMessage("StateTextBlurb3")));
     this.add(p);
 }
 JPanel textEditPanel = new JPanel();
 textEditPanel.setLayout(new BoxLayout(textEditPanel, BoxLayout.Y_AXIS));
/*        textEditPanel.setBorder(BorderFactory.createTitledBorder(
         BorderFactory.createLineBorder(Color.black, 1),
         Bundle.getMessage("EditText")));  */
 textEditPanel.layout()->addWidget(_textEditComponent);
 this->layout()->addWidget(textEditPanel);
 this->layout()->addWidget(_previewPanel);
 this->layout()->addWidget(colorButtons);
 this->layout()->addWidget(_chooser);
}
#endif

/*private*/ void DecoratorPanel::makeFontPanels()
{
 JPanel* fontPanel = new JPanel(new FlowLayout());
 _fontSizeBox = new AJComboBox(FONTSIZE, SIZE);
 connect(_fontSizeBox, SIGNAL(itemStateChanged(ItemEvent*)), this, SLOT(itemStateChanged(ItemEvent*)));
 fontPanel->layout()->addWidget(makeBoxPanel(tr("Font Size"), _fontSizeBox));
 int row = 4;
 for (int i = 0; i < FONTSIZE.length(); i++) {
     if (_util->getFontSize() ==FONTSIZE.at(i).toInt()) {
         row = i;
         break;
     }
 }
 _fontSizeBox->setCurrentIndex(row);

 _fontStyleBox = new AJComboBox(STYLES, STYLE);
 connect(_fontStyleBox, SIGNAL(itemStateChanged(ItemEvent*)), this, SLOT(itemStateChanged(ItemEvent*)));
 fontPanel->layout()->addWidget(makeBoxPanel(tr("Font Style"), _fontStyleBox));
 QString style = fontStyle(_util->getFont());
 _fontStyleBox->setCurrentText(style);

 _fontJustBox = new AJComboBox(JUSTIFICATION, JUST);
 connect(_fontJustBox, SIGNAL(itemStateChanged(ItemEvent*)), this, SLOT(itemStateChanged(ItemEvent*)));
 fontPanel->layout()->addWidget(makeBoxPanel(tr("Justification"), _fontJustBox));
 switch (_util->getJustification()) {
     case PositionablePopupUtil::LEFT:
         row = 0;
         break;
     case PositionablePopupUtil::RIGHT:
         row = 2;
         break;
     case PositionablePopupUtil::CENTRE:
         row = 1;
         break;
     default:
         row = 2;
 }
 _fontJustBox->setCurrentIndex(row);
 this->layout()->addWidget(fontPanel);

 JPanel* sizePanel = new JPanel(new FlowLayout());
 SpinnerNumberModel* model = new SpinnerNumberModel(_util->getBorderSize(), 0, 100, 1);
 _borderSpin = new AJSpinner(model, BORDER);
 connect(_borderSpin, SIGNAL(stateChanged(ChangeEvent*)), SLOT(stateChanged(ChangeEvent*)));
 sizePanel->layout()->addWidget(makeSpinPanel("Border Size", _borderSpin));
 model = new SpinnerNumberModel(_util->getMargin(), 0, 100, 1);
 _marginSpin = new AJSpinner(model, MARGIN);
 connect(_marginSpin, SIGNAL(stateChanged(ChangeEvent*)), SLOT(stateChanged(ChangeEvent*)));
 sizePanel->layout()->layout()->addWidget(makeSpinPanel("Margin Size", _marginSpin));
 model = new SpinnerNumberModel(_util->getFixedWidth(), 0, 1000, 1);
 _widthSpin = new AJSpinner(model, FWIDTH);
 connect(_widthSpin, SIGNAL(stateChanged(ChangeEvent*)), SLOT(stateChanged(ChangeEvent*)));
 sizePanel->layout()->addWidget(makeSpinPanel("Fixed Width", _widthSpin));
 model = new SpinnerNumberModel(_util->getFixedHeight(), 0, 1000, 1);
 _heightSpin = new AJSpinner(model, FHEIGHT);
 connect(_heightSpin, SIGNAL(stateChanged(ChangeEvent*)), SLOT(stateChanged(ChangeEvent*)));
 sizePanel->layout()->addWidget(makeSpinPanel("Fixed Height", _heightSpin));
 this->layout()->addWidget(sizePanel);

 JPanel* colorPanel = new JPanel(new QVBoxLayout());
 colorPanel->layout()->addWidget(makeButton(new AJRadioButton(tr("Border Color"), BORDER_COLOR)));
 //colorPanel.add(makeButton(new AJRadioButton(Bundle.getMessage("transparentBack"), TRANSPARENT_COLOR)));
 QRadioButton* button = new AJRadioButton(tr("Transparent Background"), TRANSPARENT_COLOR);
// button.addActionListener(new ActionListener() {
//     JRadioButton button;

//     public void actionPerformed(ActionEvent a) {
 connect(button, &QRadioButton::toggled, [=]{
         if (button->isChecked()) {
             _isOpaque = false;
             _util->setBackgroundColor(QColor());
             updateSamples();
             updateDragJText();
         }
     });

//     ActionListener init(JRadioButton b) {
//         button = b;
//         return this;
//     }
// }.init(button));
 _buttonGroup->addButton(button);
 colorPanel->layout()->addWidget(button);
 this->layout()->addWidget(colorPanel);

 _chooser->getSelectionModel()->addChangeListener((ChangeListener*)this);
 _chooser->setPreviewPanel(_previewPanel);
 this->layout()->addWidget(_chooser);
 updateSamples();
 updateDragJText();
}

QString DecoratorPanel::fontStyle(QFont f)
{
 ///*static*/ /*final*/ QStringList DecoratorPanel::STYLES = QStringList() << tr("plain") <<tr("bold") << tr("italic") <<tr("bold/italic");
 QString style = tr("plain");
 if(f.bold() && f.italic()) style = "bold/italic";
 else if(f.bold()) style = "bold";
 else if(f.italic()) style = "italic";
 return style;
}

/*private*/ JPanel* DecoratorPanel::makeTextPanel(QString caption, JLabel* sample, int state) {
       JPanel* panel = new JPanel();
       panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
       panel->setBorder(BorderFactory::createTitledBorder((caption)));
       JPanel* p = new JPanel(new FlowLayout());
       _dragJTextField = new DragJTextField(sample->getText(), 25, _editor, _util);
       _util->setTextComponent(_dragJTextField);
#if 0
       textField.addKeyListener(new KeyListener() {
           JLabel sample;

           KeyListener init(JLabel s) {
               sample = s;
               return this;
           }

           public void keyTyped(KeyEvent E) {
           }

           public void keyPressed(KeyEvent E) {
           }

           public void keyReleased(KeyEvent E) {
               JTextField tmp = (JTextField) E.getSource();
               sample.setText(tmp.getText());
           }
       }.init(sample));
#endif
       p->layout()->addWidget(_dragJTextField);
       panel->layout()->addWidget(p);

       p = new JPanel(new FlowLayout);
       AJRadioButton* button;
       p->layout()->addWidget(makeButton(button = new AJRadioButton(tr("Font Color"),state)));
       p->layout()->addWidget(makeButton(new AJRadioButton(tr("Background Color"), state + 10)));
       panel->layout()->addWidget(p);

       return panel;
   }


///*private*/ void DecoratorPanel::doPopupUtility(QString type, PositionableLabel* sample, bool editText) {
//    PositionablePopupUtil* util = sample->getPopupUtility();
//    util->setJustification(_util->getJustification());
//    util->setHorizontalAlignment(_util->getJustification());
//    int size = _util->getFixedWidth();
//    if (_isPositionableLabel) {
//        util->setFixedWidth(size);
//    }
//    size = _util->getFixedHeight();
//    if (_isPositionableLabel) {
//        util->setFixedHeight(size);
//    }
//    util->setMargin(_util->getMargin());
//    util->setBorderSize(_util->getBorderSize());
//    util->setBorderColor(_util->getBorderColor());
//    QFont f = util->getFont();
////    util->setFont(util->getFont().deriveFont(_util->getFontStyle()));
//    util->setFontSize(_util->getFontSize());
//    util->setFontStyle(_util->getFontStyle());
//    util->setOrientation(_util->getOrientation());
//    bool back = (sample->getBackground() != QColor());
//    util->setHasBackground(back);
//    sample->setOpaque(back);
//    sample->updateSize();

//    _samples->insert(type, sample);
//    _selectedState = type;
//    this->layout()->addWidget(makeTextPanel(type, sample, editText));
//    _samplePanel->layout()->addWidget(sample);
//    _samplePanel->layout()->addWidget(Box::createHorizontalStrut(STRUT));
//}



void DecoratorPanel::AJRadioButton_toggled(bool b)
{
 if (b)
 {
  _isOpaque = false;
  _util->setBackgroundColor(QColor());
  updateSamples();
  updateDragJText();
 }
}



TextFieldListener::TextFieldListener(JTextField* textField, JLabel *sample, DecoratorPanel *panel)
{
 this->sample = sample;
 this->panel = panel;
 this->textField = textField;
}

void TextFieldListener::textFieldChanged(QString txt)
{
 sample->setText(txt);
 panel->text = textField->text();
 panel->updateSamples();
}

/*private*/ AJRadioButton* DecoratorPanel::makeButton(AJRadioButton* button) {
//        button.addActionListener(new ActionListener() {
//            AJRadioButton button;

//            public void actionPerformed(ActionEvent a) {
 connect(button, &AJRadioButton::clicked, [=]{
                if (button->isChecked()) {
                    _selectedButton = button->_which;
                }
//                emit stateChanged(new ChangeEvent(this));
            });

//            ActionListener init(AJRadioButton b) {
//                button = b;
//                return this;
//            }
//        }.init(button));
    _buttonGroup->addButton(button);
    connect(button, SIGNAL(stateChanged(ChangeEvent*)), this, SLOT(stateChanged(ChangeEvent*)));
    return button;
}
#if 0
void DecoratorPanel::mappedButton(QWidget* b)
{
 button = (AJRadioButton*)b;
 if (button->isChecked())
 {
     _selectedButton =button->_which;
//     _selectedState = button->_state;
     PositionableLabel* pos =_sample->value(_selectedState);
     PositionablePopupUtil* util = pos->getPopupUtility();
     switch (button->_which)
     {
         case FOREGROUND_BUTTON:
             _chooser->setColor(util->getForeground());
             break;
         case BACKGROUND_BUTTON:
             if (util->hasBackground()) {
                 _chooser->setColor(util->getBackground());
             }
             util->setHasBackground(true);
             pos->setOpaque(true);
             break;
         case BORDERCOLOR_BUTTON:
             _chooser->setColor(util->getBorderColor());
             break;
         case TRANSPARENT_BUTTON:
             util->setHasBackground(false);
             _util->setHasBackground(false);
             pos->setOpaque(false);
             break;
         default:    // TRANSPARENT_BUTTON
      break;
    }
//     log->debug(tr("Button actionPerformed Colors opaque= %1 _state= %2 _which= %3").arg(
//             pos->isOpaque()?"true":"false").arg(button->_state).arg(button->_which));
     updateSamples();
 }
}
#endif
#if 0
/*public*/ void DecoratorPanel::AJRBListener()
{
//public void actionPerformed(ActionEvent a) {
    if (button->isChecked()) {
        _selectedButton =button->_which;
        _selectedState = button->_state;
        PositionableLabel* pos =_samples->value(_selectedState);
        PositionablePopupUtil* util = pos->getPopupUtility();
        switch (button->_which) {
            case FOREGROUND_BUTTON:
                _chooser->setColor(util->getForeground());
                break;
            case BACKGROUND_BUTTON:
                if (util->hasBackground()) {
                    _chooser->setColor(util->getBackground());
                }
                util->setHasBackground(true);
                pos->setOpaque(true);
                break;
            case BORDERCOLOR_BUTTON:
                _chooser->setColor(util->getBorderColor());
                break;
            case TRANSPARENT_BUTTON:
                util->setHasBackground(false);
                _util->setHasBackground(false);
                pos->setOpaque(false);
                break;
            default:    // TRANSPARENT_BUTTON
                break;
       }
        log->debug(tr("Button actionPerformed Colors opaque= %1 _state= %2 _which= %3").arg(
                pos->isOpaque()?"true":"false").arg(button->_state).arg(button->_which));
        updateSamples();
    }
}
#endif
/*private*/ void DecoratorPanel::updateSamples()
{
 PositionablePopupUtil* util = getPositionablePopupUtil();
 int mar = util->getMargin();
 int bor = util->getBorderSize();
#if 1
    Border* outlineBorder;
    if (bor==0) {
        outlineBorder = BorderFactory::createEmptyBorder(0, 0, 0, 0);
    }else {
        outlineBorder = new LineBorder(util->getBorderColor(), bor);
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
#if 1
        Border* borderMargin;
        if (_isOpaque){
            borderMargin = new LineBorder(sam->getBackground(),mar);
        } else{
            borderMargin = BorderFactory::createEmptyBorder(mar, mar, mar, mar);
        }
        ((Positionable*)sam)->setBorder(new CompoundBorder(outlineBorder, borderMargin));
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
  //sam->invalidate();
  sam->updateScene();
 }
}

void DecoratorPanel::updateDragJText()
{
 QString ss = "QLineEdit{";
 if(_util->_textComponent->isOpaque())
   ss.append(QString("background: %1; color: %2; ").arg(_util->getBackground().name()).arg(_util->getForeground().name()));
 else
  ss.append(QString("color: %2; ").arg(_util->getForeground().name()));
 if(_util->getBorderSize() > 0)
 {
  ss.append(QString("border-width: %1px; border-style: solid; border-color: %2;").arg(_util->getBorderSize()).arg(_util->getBorderColor().name()));
 }
 else
  ss.append(QString("border-width: %1px; ").arg(0));
 ss.append(QString("margin: %1px; "). arg(_util->getMargin()));
 QString fs;
 switch(_util->getFontStyle())
 {
 case 1:
  fs.append("bold ");
  break;
 case 2:
  fs.append("italic");
  break;
 case 3:
  fs.append("bold italic");
  break;
 case 0:
 default:
  break;
 }
 ss.append(QString("font: %1; ").arg(fs));
 ss.append(QString("font-family: %1; font-size: %2px; ").arg("\"Times New Roman\"").arg(_util->getFontSize()));
 if(_util->getMargin() >0)
  ss.append(QString("padding: %1px ").arg(_util->getMargin()));
 if(_util->getFixedHeight() > 0)
  ss.append(QString("max-height: %1px ").arg(_util->getFixedHeight()));
 if(_util->getFixedWidth() > 0)
  ss.append(QString("max-width: %1px ").arg(_util->getFixedWidth()));

 ss.append("}");
 log->debug(ss);
 _dragJTextField->setStyleSheet(ss);
}

/**
 * Create panel element containing [Set background:] drop down list.
 * Special version for Decorator, no access to shared variable previewBgSet.
 * @see jmri.jmrit.catalog.PreviewDialog#setupPanel()
 * @see ItemPanel
 *
 * @param preview1 ImagePanel containing icon set
 * @param preview2 not used, matches method in ItemPanel
 * @param imgArray array of colored background images
 * @return a JPanel with label and drop down
 */
/*private*/ QWidget* DecoratorPanel::makeBgButtonPanel(/*@Nonnull*/ ImagePanel* preview1, ImagePanel* /*preview2*/, QVector<BufferedImage*>* imgArray) {
 this->imgArray = imgArray;
 this->preview1 = preview1;
    _bgColorBox = new QComboBox();
    _bgColorBox->addItem(tr("Panel Bg Color")); // PanelColor key is specific for CPE, too long for combo
    _bgColorBox->addItem(tr("White"));
    _bgColorBox->addItem(tr("LightGray"));
    _bgColorBox->addItem(tr("DarkGray"));
    _bgColorBox->addItem(tr("Checkers"));
    int index;
    if (_frame != nullptr) {
        index = _frame->getPreviewBg();
    } else {
        index = 0;
    }
    _bgColorBox->setCurrentIndex(index);
//    _bgColorBox.addActionListener((ActionEvent e) -> {
//        if (imgArray != null) {
//            // index may repeat
//            int previewBgSet = _bgColorBox.getSelectedIndex(); // store user choice
//            if (_paletteFrame != null) {
//                _paletteFrame.setPreviewBg(previewBgSet);
//            }
//            // load background image
//            log.debug("Palette Decorator setImage called {}", previewBgSet);
//            preview1.setImage(imgArray[previewBgSet]);
//            // preview.setOpaque(false); // needed?
//            preview1.revalidate();        // force redraw
//        } else {
//            log.debug("imgArray is empty");
//        }
//    });
    connect(_bgColorBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_bgColorBox()));
    QWidget* backgroundPanel = new QWidget();
    backgroundPanel->setLayout(new QVBoxLayout()); //backgroundPanel, BoxLayout.Y_AXIS));
    QWidget* pp = new QWidget();
    pp->setLayout(new QHBoxLayout(/*FlowLayout.CENTER)*/));
    pp->layout()->addWidget(new QLabel(tr("Set Background")));
    pp->layout()->addWidget(_bgColorBox);
    ((QVBoxLayout*)backgroundPanel->layout())->addWidget(pp, 0, Qt::AlignHCenter);
    backgroundPanel->setMaximumSize(backgroundPanel->sizeHint());
    return backgroundPanel;
}

void DecoratorPanel::on_bgColorBox()
{
 if (imgArray != nullptr) {
     // index may repeat
     int previewBgSet = _bgColorBox->currentIndex(); // store user choice
     if (_frame != nullptr) {
         _frame->setPreviewBg(previewBgSet);
     }
     // load background image
     log->debug(tr("Palette Decorator setImage called %1").arg(previewBgSet));
     preview1->setImage(imgArray->at(previewBgSet));
     // preview.setOpaque(false); // needed?
     preview1->update();        // force redraw
//     _scene->setImage(imgArray->at(previewBgSet));
//     _scene->update();
 } else {
     log->debug("imgArray is empty");
 }

}
// called when editor changed
/*protected*/ QVector<BufferedImage*>* DecoratorPanel::getBackgrounds() {
    return _backgrounds;
}

// called when editor changed
///*protected*/ void DecoratorPanel::setBackgrounds(QVector<BufferedImage*>*  imgArray) {
//    _backgrounds = imgArray;
//    _previewPanel->setImage(imgArray->at(0));
//    _previewPanel->update();        // force redraw
//}

/*public*/ void DecoratorPanel::stateChanged(ChangeEvent* e)
{
// if(qobject_cast<ColorSelectionModel*>(e->getSource()))
// {
//  colorChange();
//  return;
// }
 PositionablePopupUtil* util = getPositionablePopupUtil();
 QObject* obj = e->getSource();
 if (qobject_cast<AJSpinner*>(obj)) {
     int num = ((AJSpinner*) obj)->value();
     switch (((AJSpinner*) obj)->_which) {
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
 } else {
     switch (_selectedButton) {
         case TEXT_FONT:
             _sample->value("Text")->setForeground(_chooser->getColor());
             util->setForeground(_chooser->getColor());
             break;
         case ACTIVE_FONT:
             _sample->value("Active")->setForeground(_chooser->getColor());
             break;
         case INACTIVE_FONT:
             _sample->value("InActive")->setForeground(_chooser->getColor());
             break;
         case UNKOWN_FONT:
             _sample->value("Unknown")->setForeground(_chooser->getColor());
             break;
         case INCONSISTENT_FONT:
             _sample->value("Inconsistent")->setForeground(_chooser->getColor());
             break;
         case TEXT_BACKGROUND:
             _sample->value("Text")->setBackground(_chooser->getColor());
             util->setBackgroundColor(_chooser->getColor());
             _isOpaque = true;
             break;
         case ACTIVE_BACKGROUND:
             _sample->value("Active")->setBackground(_chooser->getColor());
             _sample->value("Active")->setOpaque(true);
             _isOpaque = true;
             break;
         case INACTIVE_BACKGROUND:
             _sample->value("InActive")->setBackground(_chooser->getColor());
             _sample->value("InActive")->setOpaque(true);
             _isOpaque = true;
             break;
         case UNKOWN_BACKGROUND:
             _sample->value("Unknown")->setBackground(_chooser->getColor());
             _sample->value("Unknown")->setOpaque(true);
             _isOpaque = true;
             break;
         case INCONSISTENT_BACKGROUND:
             _sample->value("Inconsistent")->setBackground(_chooser->getColor());
             _sample->value("Inconsistent")->setOpaque(true);
             _isOpaque = true;
             break;
         case TRANSPARENT_COLOR:
             util->setBackgroundColor(QColor());
             _isOpaque = false;
             break;
         case BORDER_COLOR:
             util->setBorderColor(_chooser->getColor());
             break;
     }
 }

 updateSamples();
 updateDragJText();
}

/*private*/ void DecoratorPanel::colorChange()
{
    PositionableLabel* pos =_sample->value(_selectedState);
//    PositionablePopupUtil* util = pos->getPopupUtility();
    switch (_selectedButton) {
        case FOREGROUND_BUTTON:
            if ("Text" == (_selectedState)) {
                _util->setForeground(_chooser->getColor());
            }
            _util->setForeground(_chooser->getColor());
            break;
        case BACKGROUND_BUTTON:
            if ("Text" == (_selectedState)) {
                _util->setBackgroundColor(_chooser->getColor());
            }
            _util->setBackgroundColor(_chooser->getColor());
            pos->setOpaque(true);
            break;
        case TRANSPARENT_BUTTON:
            if ("Text" == (_selectedState)) {
                _util->setBackgroundColor(QColor());
            }
            _util->setBackgroundColor(QColor());
            pos->setOpaque(false);
            break;
        case BORDERCOLOR_BUTTON:
            _util->setBorderColor(_chooser->getColor());
            break;
        default:
            log->warn(tr("Unexpected color change for state %1, button# %2").arg(_selectedState).arg(_selectedButton));
            break;
    }
    log->debug(tr("colorChange Colors opaque= %1 _selectedState= %2 _selectedButton= %3").arg(
            pos->isOpaque()?"true":"false").arg(_selectedState).arg(_selectedButton));
    updateSamples();
    updateDragJText();
}

/*public*/ PositionablePopupUtil* DecoratorPanel::getPositionablePopupUtil()
{
 return _util;
}

/*public*/ void DecoratorPanel::getText(Positionable* pos)
{
 //if (pos instanceof SensorIcon && ((SensorIcon)pos).isText())
 if((qobject_cast<SensorIcon*>(pos->self())!=NULL) &&(((SensorIcon*)pos)->isText()) )
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
    if(qobject_cast<PositionableLabel*>(pos->self())!= NULL)
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
#if 0
/*public*/ void DecoratorPanel::itemStateChanged(ItemEvent* e)
{
 PositionablePopupUtil* util = getPositionablePopupUtil();
 QObject* obj = e->getSource();
 //if (obj instanceof AJComboBox)
 if(qobject_cast<AJSpinner*>(obj)!= NULL)
 {
  QString size;
  int style;
  int weight;
  int just;
  switch (((AJSpinner*)obj)->_which)
  {
   case SIZE:
    size = ((AJSpinner*)obj)->currentText();
    util->setFontSize(size.toFloat());
    break;
   case STYLE:
    style = 0;
    weight = QFont::Normal;
    switch (((AJSpinner*)obj)->currentIndex())
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
     switch (((AJSpinner*)obj)->currentIndex())
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
#endif
#if 1
/**
* Export a Positionable item from panel
*/
//class DragDecoratorLabel : public PositionableLabel //implements DragGestureListener, DragSourceListener, Transferable {

//    DataFlavor dataFlavor;

/*public*/ DPDragDecoratorLabel::DPDragDecoratorLabel(QString s, Editor* editor, QObject* parent) : PositionableLabel(s, editor,(Positionable*)parent)
{
 //super(s, editor);
//        DragSource dragSource = DragSource.getDefaultDragSource();
//        dragSource.createDefaultDragGestureRecognizer(this,
//                    DnDConstants.ACTION_COPY, this);
//        try {
            dataFlavor = new DataFlavor(Editor::POSITIONABLE_FLAVOR);
//        } catch (ClassNotFoundException* cnfe) {
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
    /*public*/ QList<DataFlavor*> DPDragDecoratorLabel::getTransferDataFlavors() {
        //if (log.isDebugEnabled()) log.debug("DragPositionable.getTransferDataFlavors ");
    return  QList<DataFlavor*>() <<  dataFlavor ;
    }
    /*public*/ bool DPDragDecoratorLabel::isDataFlavorSupported(DataFlavor* flavor) {
        //if (log.isDebugEnabled()) log.debug("DragPositionable.isDataFlavorSupported ");
        return dataFlavor==(flavor);
    }
//    /*public*/ Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException,IOException {
//        if (!isDataFlavorSupported(flavor)) {
//            return NULL;
//        }
//        return _sample->value("Text").deepClone();
//    }
void DPDragDecoratorLabel::mousePressEvent(QGraphicsSceneMouseEvent *e)
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
QString DPDragDecoratorLabel::mimeData()
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
/*public*/ void DecoratorPanel::setAttributes(Positionable* pos) {
 if (qobject_cast<SensorIcon*>(pos->self())  && !((SensorIcon*)pos)->isIcon()) {
     SensorIcon* icon = (SensorIcon*) pos;
     PositionableLabel* sample = _sample->value("Active");
     if (sample->isOpaque()) {
         icon->setBackgroundActive(sample->getBackground());
     } else {
         icon->setBackgroundActive(QColor());
     }
     icon->setTextActive(sample->getForeground());
     icon->setActiveText(sample->getText());

     sample = _sample->value("InActive");
     icon->setInactiveText(sample->getText());
     if (sample->isOpaque()) {
         icon->setBackgroundInActive(sample->getBackground());
     } else {
         icon->setBackgroundInActive(QColor());
     }
     icon->setTextInActive(sample->getForeground());

     sample = _sample->value("Unknown");
     icon->setUnknownText(sample->getText());
     if (sample->isOpaque()) {
         icon->setBackgroundUnknown(sample->getBackground());
     } else {
         icon->setBackgroundUnknown(QColor());
     }
     icon->setTextUnknown(sample->getForeground());

     sample = _sample->value("Inconsistent");
     icon->setInconsistentText(sample->getText());
     if (sample->isOpaque()) {
         icon->setBackgroundInconsistent(sample->getBackground());
     } else {
         icon->setBackgroundInconsistent(QColor());
     }
     icon->setTextInconsistent(sample->getForeground());
 } else {
     PositionableLabel* sample = _sample->value("Text");
     pos->setForeground(sample->getForeground());
     if ( qobject_cast<PositionableLabel*>(pos->self()) &&
         !(qobject_cast<MemoryIcon*>(pos->self())== nullptr)) {
         ((PositionableLabel*) pos)->setText(sample->getText());
     }
     PositionablePopupUtil* util = pos->getPopupUtility();
     if (sample->isOpaque()) {
         util->setBackgroundColor(sample->getBackground());
     } else {
         util->setBackgroundColor(QColor());
     }
     //util->setHasBackground(_util->hasBackground());
     util->setFont(_util->getFont());
     util->setFixedWidth(_util->getFixedWidth());
     util->setFixedHeight(_util->getFixedHeight());
     util->setMargin(_util->getMargin());
     util->setBorderSize(_util->getBorderSize());
//     if (log->isDebugEnabled()) {
//         log->debug(tr("setAttributes(pos) opaque= %1 hasBackground= %2 background= %3").arg(pos->isOpaque()).arg(util->hasBackground()?"true":"false").arg(ColorUtil::colorToString(util->getBackground())));
//         PositionablePopupUtil* u = pos->getPopupUtility();
//         log->debug(tr("setAttributes text sample opaque= %1 hasBackground= {} background= %2").arg(sample->isOpaque()?"true":"false").arg(u->hasBackground()?"true":"false").arg( ColorUtil::colorToString(u->getBackground())));
//     }
 }
 //pos->invalidate();
 pos->updateScene();
}

///*public*/ void DecoratorPanel::setSuppressRecentColor(bool b) {
// QListIterator<PositionableLabel*> iter(_sample->values());
// while (iter.hasNext()) {
//     iter.next()->getPopupUtility()->setSuppressRecentColor(b);
// }
// _util->setSuppressRecentColor(b);
//}

void DecoratorPanel::propertyChange(PropertyChangeEvent* evt)
{
 QString propertyName = evt->getPropertyName();
}

/*public*/ void DecoratorPanel::itemStateChanged(ItemEvent* e) {
    PositionablePopupUtil* util = getPositionablePopupUtil();
    QObject* obj = e->getSource();
    if (qobject_cast<AJComboBox*>(obj)) {
        switch (((AJComboBox*) obj)->_which) {
            case SIZE:
            {
                QString size = ((AJComboBox*) obj)->currentText();
                util->setFontSize(size.toFloat());
                break;
            }
            case STYLE:
            {
                int style = 0;
                switch (((AJComboBox*) obj)->currentIndex()) {
                    case 0:
                        style = Font::PLAIN;
                        break;
                    case 1:
                        style = Font::BOLD;
                        break;
                    case 2:
                        style = Font::ITALIC;
                        break;
                    case 3:
                        style = (Font::BOLD | Font::ITALIC);
                        break;
                }
                util->setFontStyle(style);
                break;
            }
            case JUST:
            {
                int just = 0;
                switch (((AJComboBox*) obj)->currentIndex()) {
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
        }
        updateSamples();
        updateDragJText();
    }
}


///*public*/ void DecoratorPanel::mousePressEvent(QMouseEvent *event)
//{
// if(event->button()&Qt::LeftButton)
// {
//  dr = new QDrag(this);
//  QMimeData *data = new QMimeData;
//  QByteArray s_mimeData = mimeData();
//  log->debug(tr("xmldata: %1").arg(s_mimeData.data()));
//  data->setData("object/x-myApplication-object", s_mimeData);
//  // Assign ownership of the QMimeData object to the QDrag object.
//  dr->setMimeData(data);
//  dr->exec();
// }
//}

/*public*/ DragJTextField* DecoratorPanel::getDragJTextField()
{
 return _dragJTextField;
}

///*public*/ QByteArray DecoratorPanel::mimeData()
//{
// QByteArray xmldata;
// PositionableLabel* l = new PositionableLabel();
// l->setPopupUtility(nullptr);
// l->setLevel(Editor::LABELS);
// PositionableLabelXml* xml = new PositionableLabelXml();
// QDomElement e = xml->store((QObject*)l);
// xml->doc.appendChild(e);
// xmldata.append(xml->doc.toString());
// log->info(tr("xml data: %1").arg(xml->doc.toString()));
// return xmldata;
//}
/*private*/ /*final*/ /*static*/ Logger* DecoratorPanel::log = LoggerFactory::getLogger("DecoratorPanel");
