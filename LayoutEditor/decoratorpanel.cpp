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

/*public*/ DecoratorPanel::DecoratorPanel(Editor* editor, DisplayFrame *paletteFrame, QWidget *parent) : QWidget(parent)
{
  _editor = editor;
  setLayout(new QVBoxLayout(this/*, BoxLayout.Y_AXIS*/));
  _paletteFrame = paletteFrame;
  setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));
  QColor panelBackground;// = _editor->getTargetPanel()->getBackground(); // start using Panel background color
  QBrush br = _editor->getTargetPanel()->views().at(0)->backgroundBrush();
  panelBackground = br.color();
  // create array of backgrounds, _currentBackground already set and used
  _backgrounds = ItemPanel::makeBackgrounds(nullptr,  panelBackground);
  _chooser = new JColorChooser(panelBackground);
  DefaultSwatchChooserPanel* p = new DefaultSwatchChooserPanel();
  //p->installChooserPanel(_chooser);
  _chooser->addChooserPanel(p);

  _samples = new QMap<QString, PositionableLabel*>();
  _buttonGroup = new QButtonGroup(this);

  _previewPanel = new ImagePanel();
  QVBoxLayout* _previewPanelLayout;
  _previewPanel->setLayout(_previewPanelLayout = new QVBoxLayout()); //new BorderLayout());
  _previewPanel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black, 1),
          tr("Preview")));
  
  _previewPanelLayout->addWidget(Box::createVerticalStrut(STRUT), 0, Qt::AlignTop);//BorderLayout.PAGE_START);
  _previewPanelLayout->addWidget(Box::createVerticalStrut(STRUT), 0, Qt::AlignBottom);//, BorderLayout.PAGE_END);

  _samplePanel = new QWidget();
  QHBoxLayout* _samplePanelLayout = new QHBoxLayout(_samplePanel);
  _samplePanel->setMinimumHeight(80);
  _samplePanelLayout->addWidget(Box::createHorizontalStrut(STRUT));
  //_samplePanel.setOpaque(false);
  listener = new DPChangeListener(this);

  _scene = new PreviewScene(this);
  _scene->setSceneRect(-10, -10, 200, 100);
  _sampleView = new QGraphicsView(_scene);
  _sampleView->setMinimumHeight(80);
  _sampleView->setMinimumWidth(200);
  _sampleView->setBackgroundBrush(panelBackground);
  QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
  sizePolicy.setHorizontalStretch(1);
  sizePolicy.setVerticalStretch(1);
  _sampleView->setSizePolicy(sizePolicy);
}

/*public*/ void PreviewScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
 QList<QGraphicsItem*> itemList = items(/*QPointF(event->pos().x(), event->pos().y())*/);
 if(!itemList.isEmpty())
 {
  item = itemList.at(2);
  if(item && event->buttons() != 0)
  {
    if(panel->_samples->size() > 0)
    {
     PositionableLabel* pos = panel->_samples->values().at(0);
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
  if(panel->_samples->size() > 0)
  {
   PositionableLabel* pos = panel->_samples->values().at(0);
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

AJRadioButton::AJRadioButton(QString text, int w, QString state) : QRadioButton(text)
{
 //super(text);
 _which = w;
 _state = state;
}


QString AJRadioButton::getState() {
    return _state;
}
//};

/*private*/ JPanel* DecoratorPanel::makeSpinPanel(QString caption, AJSpinner* spin, ChangeListener* listener) {
    JPanel* panel = new JPanel();
    panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
    panel->layout()->addWidget(new QLabel((caption)));
    //spin->addChangeListener(this);
    connect(spin, SIGNAL(stateChanged(ChangeEvent*)), listener, SLOT(stateChanged(ChangeEvent*)));
    panel->layout()->addWidget(spin);
    return panel;
}

/* Called by Palette's TextItemPanel i.e. make a new panel item to drag */
/*protected*/ void DecoratorPanel::initDecoratorPanel(DragDecoratorLabel* sample) {
 this->sample = sample;
    sample->setDisplayLevel(Editor::LABELS);
    //sample->setBackground(_editor->getTargetPanel()->getBackground());
//    QColor c;
//    QBrush b = _editor->editPanel->backgroundBrush();
//    if(b == Qt::NoBrush)
//     c = QColor(Qt::white);
//    c = b.color();
//    sample->setBackground(c);
    _util = sample->getPopupUtility();
    _samples->insert("Text", sample);
    _selectedState = "Text";
    _isPositionableLabel = true;
    makeFontPanels();
    this->layout()->addWidget(makeTextPanel("Text", sample, true));

//    _samplePanel->layout()->addWidget(sample);
    _samplePanel->setVisible(false);
    _scene->addItem(sample->getItem());
    _scene->update();

//    log->debug(tr("DragDecoratorLabel size %1 | panel size %2").arg(sample->sizeHint()).arg(_samplePanel->sizeHint()));
    finishInit(true);
}

/*public*/ void DecoratorPanel::initDecoratorPanel(Positionable* pos)
{
// Positionable* item = pos->deepClone(); // need copy of PositionableJPanel in PopupUtility
// _util = item->getPopupUtility();
// item->remove();      // don't need copy any more. Removes ghost image of PositionableJPanels
 _util = pos->getPopupUtility();
 _isPositionableLabel = (qobject_cast<PositionableLabel*>(pos->self()));
 makeFontPanels();

 if (qobject_cast<SensorIcon*>(pos->self()) && !((SensorIcon*)pos->self())->isIcon())
 {
  SensorIcon* si = (SensorIcon*) pos;
  if (!si->isIcon() && si->isText())
  {
   PositionableLabel* sample = new PositionableLabel(si->getActiveText(), _editor);
   sample->setForeground(si->getTextActive());
   sample->setBackground(si->getBackgroundActive());
   doPopupUtility("Active", sample, true); // NOI18N

   sample = new PositionableLabel(si->getInactiveText(), _editor);
   sample->setForeground(si->getTextInActive());
   sample->setBackground(si->getBackgroundInActive());
   doPopupUtility("InActive", sample, true); // NOI18N

   sample = new PositionableLabel(si->getUnknownText(), _editor);
   sample->setForeground(si->getTextUnknown());
   sample->setBackground(si->getBackgroundUnknown());
   doPopupUtility("Unknown", sample, true); // NOI18N

   sample = new PositionableLabel(si->getInconsistentText(), _editor);
   sample->setForeground(si->getTextInconsistent());
   sample->setBackground(si->getBackgroundInconsistent());
   doPopupUtility("Inconsistent", sample, true); // NOI18N
  }   // else a non-text SensorIcon cannot be decorated.
 }
 else
 { // not a SensorIcon
  PositionableLabel* sample = new PositionableLabel("", _editor);
  sample->setForeground(_util->getForeground());
  sample->setBackground(_util->getBackground());
  PositionablePopupUtil* util = sample->getPopupUtility();
  util->setHasBackground(_util->hasBackground());
  bool addtextField;
  if (qobject_cast<PositionableLabel*>(pos->self()))
  {
   sample->setText(((PositionableLabel*)pos->self())->getUnRotatedText());
   if (qobject_cast<MemoryIcon*>(pos->self())) {
       addtextField = false;
   } else {
       addtextField = true;
   }
  }
  else
  {
      // To display PositionableJPanel types as PositionableLabels, set fixed sizes.
      util->setFixedWidth(pos->getWidth() - 2*_util->getBorderSize());
      util->setFixedHeight(pos->getHeight() - 2*_util->getBorderSize());
      if (qobject_cast<MemoryInputIcon*>(pos->self())) {
          JTextField* field = (JTextField*)((MemoryInputIcon*)pos)->getTextComponent();
          sample->setText(field->text());
          addtextField = false;
      } else if (qobject_cast<MemoryComboIcon*>(pos->self())) {
          QComboBox* box = (QComboBox*)((MemoryComboIcon*)pos->self())->getTextComponent();
          sample->setText(box->currentText());
          addtextField = false;
      } else if (qobject_cast<MemorySpinnerIcon*>(pos->self())) {
          JTextField* field = (JTextField*)((MemorySpinnerIcon*)pos)->getTextComponent();
          sample->setText(field->text());
          addtextField = false;
      } else {
          addtextField = true;
          log->error(tr("Unknown Postionable Type %1").arg((pos->self())->metaObject()->className()));
      }
  }
  doPopupUtility("Text", sample, addtextField);
  if (log->isDebugEnabled()) {
      log->debug(tr("util width= %1 height= %2 POS width= %3 height= %4").arg(
              util->getFixedWidth()).arg( util->getFixedHeight()).arg( pos->getWidth()).arg( pos->getHeight()));
  }
 }
 finishInit(false);
}
/*protected*/ void DecoratorPanel::fontChange() {
    _selectedButton = FOREGROUND_BUTTON;
    _fontButton->setChecked(true);
//    _chooser->setColor(_util->getForeground());
    _chooser->setColor(_util->getForeground());
    log->debug("fontChange");
    updateSamples();
 }

/*private*/ void DecoratorPanel::finishInit(bool addBgCombo) {
   _chooser = JmriColorChooser::extendColorChooser(_chooser);
//   _chooser->addChooserPanel(new ColorChooserPanel(new ColorModel()));
//   DefaultSwatchChooserPanel* panel = new DefaultSwatchChooserPanel();
//   _chooser->getChooserPanels()->replace(1,panel);
//   panel->installChooserPanel(_chooser);
   //_chooser->setChooserPanels(_chooser->getChooserPanels());
    setSuppressRecentColor(true);
    _chooser->getSelectionModel()->addChangeListener(listener);
    _chooser->setPreviewPanel(new JPanel());
    layout()->addWidget(_chooser);
    ((QVBoxLayout*)_previewPanel->layout())->addWidget(_samplePanel, 0, Qt::AlignCenter);// BorderLayout.CENTER);
//    ((QVBoxLayout*)_previewPanel->layout())->addWidget(_sampleView, 0, Qt::AlignCenter);
    // add a SetBackground combo
    if (addBgCombo)
    {
     layout()->addWidget(makeBgButtonPanel(_previewPanel, nullptr, _backgrounds)); // no listener on this variant
    }
    layout()->addWidget(_previewPanel);
    _previewPanel->hide();
    ((QVBoxLayout*)layout())->addWidget(_sampleView, 1, Qt::AlignHCenter);
    _previewPanel->setImage(_backgrounds->at(0));
    _previewPanel->update();        // force redraw
    // after everything created, set selections
//    _fontPanel.setFontSelections();
    updateSamples();
}

/*private*/ void DecoratorPanel::doPopupUtility(QString type, PositionableLabel* sample, bool editText) {
    PositionablePopupUtil* util = sample->getPopupUtility();
    util->setJustification(_util->getJustification());
    util->setHorizontalAlignment(_util->getJustification());
    int size = _util->getFixedWidth();
    if (_isPositionableLabel) {
        util->setFixedWidth(size);
    }
    size = _util->getFixedHeight();
    if (_isPositionableLabel) {
        util->setFixedHeight(size);
    }
    util->setMargin(_util->getMargin());
    util->setBorderSize(_util->getBorderSize());
    util->setBorderColor(_util->getBorderColor());
    QFont f = util->getFont();
//    util->setFont(util->getFont().deriveFont(_util->getFontStyle()));
    util->setFontSize(_util->getFontSize());
    util->setFontStyle(_util->getFontStyle());
    util->setOrientation(_util->getOrientation());
    bool back = (sample->getBackground() != QColor());
    util->setHasBackground(back);
    sample->setOpaque(back);
    sample->updateSize();

    _samples->insert(type, sample);
    _selectedState = type;
    this->layout()->addWidget(makeTextPanel(type, sample, editText));
    _samplePanel->layout()->addWidget(sample);
    _samplePanel->layout()->addWidget(Box::createHorizontalStrut(STRUT));
}

/*private*/ void DecoratorPanel::makeFontPanels()
{
//    ActionListener fontAction = ((ActionEvent event) -> {
//        fontChange(); // callback
//    });
 FontActionListener* fontAction = new FontActionListener(this);

 _fontPanel = new FontPanel(_util, fontAction);
 this->layout()->addWidget(_fontPanel);
 if(sample)
 {
    connect(_fontPanel, SIGNAL(fontSizeChanged(int)), sample, SLOT(setFontSize(int)));
    connect(_fontPanel, SIGNAL(fontFaceChanged(QString)), sample, SLOT(setFontFamily(QString)));
    connect(_fontPanel, SIGNAL(fontStyleChanged(int)), sample, SLOT(setFontStyle(int)));
 }
 connect(_chooser->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 JPanel* sizePanel = new JPanel();
 FlowLayout* sizePanelLayout = new FlowLayout(sizePanel);
 SpinnerNumberModel* model = new SpinnerNumberModel(_util->getBorderSize(), 0, 100, 1);
 _borderSpin = new AJSpinner(model, BORDER);
 sizePanelLayout->addWidget(makeSpinPanel(tr("Border Size"), _borderSpin, listener));
 model = new SpinnerNumberModel(_util->getMargin(), 0, 100, 1);
 _marginSpin = new AJSpinner(model, MARGIN);
 sizePanelLayout->addWidget(makeSpinPanel(tr("Margin Size"), _marginSpin, listener));
 if (_isPositionableLabel)
 {
  //_util->setFixedWidth(sample->width());
   model = new SpinnerNumberModel(_util->getFixedWidth(), 0, 1000, 1);
   _widthSpin = new AJSpinner(model, FWIDTH);
   sizePanelLayout->addWidget(makeSpinPanel(tr("Fixed Width"), _widthSpin, listener));
   model = new SpinnerNumberModel(_util->getFixedHeight(), 0, 1000, 1);
   _heightSpin = new AJSpinner(model, FHEIGHT);
   sizePanelLayout->addWidget(makeSpinPanel(tr("Fixed Height"), _heightSpin, listener));
 }
 this->layout()->addWidget(sizePanel);
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

/*private*/ QWidget* DecoratorPanel::makeTextPanel(QString state, JLabel* sample, bool addTextField) {
    JPanel* panel = new JPanel();
    // use NamedBeanBundle property for basic beans like "Turnout" I18N
    if ("Active" == (state)) {
        bundleCaption = tr("Active"); // "SensorStateActive"
    } else if ("InActive" == (state)) {
        bundleCaption = tr("Inactive"); // "SensorStateInactive"
    } else if ("Unknown" == (state)) {
        bundleCaption = tr("Unknown"); // "BeanStateUnknown"
    } else if ("Inconsistent" == (state)) {
        bundleCaption = tr("Inconsistent"); // "BeanStateInconsistent"
    } else {
        //bundleCaption = state;
     if(state == "Text")
      bundleCaption = tr("Text Decoration");
     else
      bundleCaption = state;
    }
    panel->setLayout(new QVBoxLayout()); //panel, BoxLayout.Y_AXIS));
    panel->setBorder(BorderFactory::createTitledBorder((bundleCaption)));
    //panel->setTitle(bundleCaption);
    QWidget* p = new QWidget();
    p->setLayout(new FlowLayout());
    if (addTextField) {
        JTextField* textField = new JTextField(sample->getText(), 25);
#if 0
        textField.addKeyListener(new KeyListener() {
            JLabel sample;

            KeyListener init(JLabel s) {
                sample = s;
                return this;
            }

            @Override
            public void keyTyped(KeyEvent evt) {
            }

            @Override
            public void keyPressed(KeyEvent evt) {
            }

            @Override
            public void keyReleased(KeyEvent evt) {
                JTextField tmp = (JTextField) evt.getSource();
                sample.setText(tmp.getText());
                updateSamples();
            }
        }.init(sample));
#endif
        TextFieldListener* listener = new TextFieldListener(textField, sample, this);
        connect(textField, SIGNAL(textChanged(QString)), listener, SLOT(textFieldChanged(QString)));
        p->layout()->addWidget(textField);
    }

    panel->layout()->addWidget(p);

    p = new QWidget();
    p->setLayout(new FlowLayout());
    _mapper = new QSignalMapper(this);
    _fontButton = makeColorRadioButton(tr("Font Color"), FOREGROUND_BUTTON, state);
    p->layout()->addWidget(_fontButton);

    _backgroundButton = makeColorRadioButton(tr("Background color"), BACKGROUND_BUTTON, state);
    p->layout()->addWidget(_backgroundButton);

    button = makeColorRadioButton(tr("Transparent Background"), TRANSPARENT_BUTTON, state);
    p->layout()->addWidget(button);

    _borderButton = makeColorRadioButton(tr("Border Color"), BORDERCOLOR_BUTTON, state);
    p->layout()->addWidget(_borderButton);
    connect(_mapper, SIGNAL(mapped(QWidget*)), this, SLOT(mappedButton(QWidget*)));

    panel->layout()->addWidget(p);
    return panel;
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

#if 0
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
      self->_chooser->setCurrentColor(self->_samples->value("Text")->getForeground());
   break;
  case DecoratorPanel::ACTIVE_FONT:
   //_sample->value("Active")->setForeground(_chooser->currentColor());
      self->_chooser->setCurrentColor(self->_samples->value("Active")->getForeground());
   break;
  case DecoratorPanel::INACTIVE_FONT:
   //_sample->value("InActive")->setForeground(_chooser->currentColor());
      self->_chooser->setCurrentColor(self->_samples->value("InActive")->getForeground());
   break;
  case DecoratorPanel::UNKOWN_FONT:
   //_sample->value("Unknown")->setForeground(_chooser->currentColor());
      self->_chooser->setCurrentColor(self->_samples->value("Unknown")->getForeground());
   break;
  case DecoratorPanel::INCONSISTENT_FONT:
   //_sample->value("Inconsistent")->setForeground(_chooser->currentColor());
      self->_chooser->setCurrentColor(self->_samples->value("Inconsistent")->getForeground());
   break;
  case DecoratorPanel::TEXT_BACKGROUND:
//   _sample->value("Text")->setBackground(_chooser->currentColor());
//   util->setBackgroundColor(_chooser->currentColor());
//   _isOpaque = true;
   self->_chooser->setCurrentColor(self->_samples->value("Text")->getBackground());
   break;
  case DecoratorPanel::ACTIVE_BACKGROUND:
//   _sample->value("Active")->setBackground(_chooser->currentColor());
//   _sample->value("Active")->setOpaque(true);
//   _isOpaque = true;
      self->_chooser->setCurrentColor(self->_samples->value("Active")->getBackground());
   break;
  case DecoratorPanel::INACTIVE_BACKGROUND:
//   _sample->value("InActive")->setBackground(_chooser->currentColor());
//   _sample->value("InActive")->setOpaque(true);
//   _isOpaque = true;
      self->_chooser->setCurrentColor(self->_samples->value("InActive")->getBackground());
   break;
  case DecoratorPanel::UNKOWN_BACKGROUND:
//   _sample->value("Unknown")->setBackground(_chooser->currentColor());
//   _sample->value("Unknown")->setOpaque(true);
//   _isOpaque = true;
      self->_chooser->setCurrentColor(self->_samples->value("Unknown")->getBackground());
   break;
  case DecoratorPanel::INCONSISTENT_BACKGROUND:
//   _sample->value("Inconsistent")->setBackground(_chooser->currentColor());
//   _sample->value("Inconsistent")->setOpaque(true);
//   _isOpaque = true;
      self->_chooser->setCurrentColor(self->_samples->value("Inconsistent")->getBackground());
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
#endif

/*private*/ AJRadioButton* DecoratorPanel::makeColorRadioButton(QString caption, int which, QString state) {
    button = new AJRadioButton((caption), which, state);
//    button.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            if (button.isSelected()) {
//                _selectedButton =button._which;
//                _selectedState = button._state;
//                PositionableLabel pos =_samples.get(_selectedState);
//                PositionablePopupUtil util = pos.getPopupUtility();
//                switch (button._which) {
//                    case FOREGROUND_BUTTON:
//                        _chooser.setColor(util.getForeground());
//                        break;
//                    case BACKGROUND_BUTTON:
//                        if (util.hasBackground()) {
//                            _chooser.setColor(util.getBackground());
//                        }
//                        util.setHasBackground(true);
//                        pos.setOpaque(true);
//                        break;
//                    case BORDERCOLOR_BUTTON:
//                        _chooser.setColor(util.getBorderColor());
//                        break;
//                    case TRANSPARENT_BUTTON:
//                        util.setHasBackground(false);
//                        _util.setHasBackground(false);
//                        pos.setOpaque(false);
//                        break;
//                    default:    // TRANSPARENT_BUTTON
//               }
//                log.debug("Button actionPerformed Colors opaque= {} _state= {} _which= {}",
//                        pos.isOpaque(), button._state, button._which);
//                updateSamples();
//            }
//        }
//    });
    connect(button, SIGNAL(clicked(bool)), _mapper, SLOT(map()));
    _buttonGroup->addButton(button);
    _mapper->setMapping(button, button);
    return button;
}
void DecoratorPanel::mappedButton(QWidget* b)
{
 button = (AJRadioButton*)b;
 if (button->isChecked())
 {
     _selectedButton =button->_which;
     _selectedState = button->_state;
     PositionableLabel* pos =_samples->value(_selectedState);
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
     log->debug(tr("Button actionPerformed Colors opaque= %1 _state= %2 _which= %3").arg(
             pos->isOpaque()?"true":"false").arg(button->_state).arg(button->_which));
     updateSamples();
 }
}

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
 QListIterator<PositionableLabel*> it(_samples->values());
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
    if (_paletteFrame != nullptr) {
        index = _paletteFrame->getPreviewBg();
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
     if (_paletteFrame != nullptr) {
         _paletteFrame->setPreviewBg(previewBgSet);
     }
     // load background image
     log->debug(tr("Palette Decorator setImage called %1").arg(previewBgSet));
     preview1->setImage(imgArray->at(previewBgSet));
     // preview.setOpaque(false); // needed?
     preview1->update();        // force redraw
     _scene->setImage(imgArray->at(previewBgSet));
     _scene->update();
 } else {
     log->debug("imgArray is empty");
 }

}
// called when editor changed
/*protected*/ QVector<BufferedImage*>* DecoratorPanel::getBackgrounds() {
    return _backgrounds;
}
// called when editor changed
/*protected*/ void DecoratorPanel::setBackgrounds(QVector<BufferedImage*>*  imgArray) {
    _backgrounds = imgArray;
    _previewPanel->setImage(imgArray->at(0));
    _previewPanel->update();        // force redraw
}

/*public*/ void DecoratorPanel::stateChanged(ChangeEvent* e)
{
 PositionablePopupUtil* util = getPositionablePopupUtil();
 QObject* obj = e->getSource();
 //if (obj instanceof AJSpinner)
 if(qobject_cast<AJSpinner*>(obj)!= NULL )
 {
  int num = ((AJSpinner*)obj)->value();
  QColor c;
  switch (((AJSpinner*)obj)->_which)
  {
   case BORDER:
        util->setBorderSize(num);
        sample->setBorderSize(num);
        _selectedButton = BORDERCOLOR_BUTTON;
        _chooser->setColor(_util->getBorderColor());
        break;
   case MARGIN:
        util->setMargin(num);
        sample->setMargin(num);
        _selectedButton = BACKGROUND_BUTTON;
        c = _util->getBackground();
        if (c.isValid())
        {
         _chooser->setColor(c);
        }
        break;
   case FWIDTH:
        util->setFixedWidth(num);
        sample->setFixedWidth(num);
        _selectedButton = BACKGROUND_BUTTON;
        _backgroundButton->setChecked(true);
        c = _util->getBackground();
        if (c.isValid()) {
            _chooser->setColor(c);
        }
       break;
   case FHEIGHT:
        util->setFixedHeight(num);
        sample->setFixedHeight(num);
        _selectedButton = BACKGROUND_BUTTON;
        _backgroundButton->setChecked(true);
        c = _util->getBackground();
        if (c.isValid()) {
            _chooser->setColor(c);
        }
        break;
  default:
      log->warn(tr("Unexpected _which %1  in stateChanged").arg(((AJSpinner*) obj)->_which));
      break;
  }
  updateSamples();

 }
 else
 {
  log->debug(tr("stateChanged colors _selectedState= %1 _selectedButton= %2").arg(
          _selectedState).arg(_selectedButton));
  colorChange();
 }
}

/*private*/ void DecoratorPanel::colorChange()
{
    PositionableLabel* pos =_samples->value(_selectedState);
    PositionablePopupUtil* util = pos->getPopupUtility();
    switch (_selectedButton) {
        case FOREGROUND_BUTTON:
            if ("Text" == (_selectedState)) {
                _util->setForeground(_chooser->getColor());
            }
            util->setForeground(_chooser->getColor());
            break;
        case BACKGROUND_BUTTON:
            if ("Text" == (_selectedState)) {
                _util->setBackgroundColor(_chooser->getColor());
            }
            util->setBackgroundColor(_chooser->getColor());
            pos->setOpaque(true);
            break;
        case TRANSPARENT_BUTTON:
            if ("Text" == (_selectedState)) {
                _util->setBackgroundColor(QColor());
            }
            util->setBackgroundColor(QColor());
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
    PositionableLabel* sample = _samples->value("Active");
    icon->setActiveText(sample->getText());
    icon->setBackgroundActive(sample->getBackground());
    icon->setTextActive(sample->getForeground());

    sample = _samples->value("InActive");
    icon->setInactiveText(sample->getText());
    icon->setBackgroundInActive(sample->getBackground());
    icon->setTextInActive(sample->getForeground());

    sample = _samples->value("Unknown");
    icon->setUnknownText(sample->getText());
    icon->setBackgroundUnknown(sample->getBackground());
    icon->setTextUnknown(sample->getForeground());

    sample = _samples->value("Inconsistent");
    icon->setInconsistentText(sample->getText());
    icon->setBackgroundInconsistent(sample->getBackground());
    icon->setTextInconsistent(sample->getForeground());
 }
 else
 {
    PositionableLabel* sample = _samples->value("Text");
    ((PositionableLabel*)pos)->setBackground(sample->getBackground());
    ((PositionableLabel*)pos)->setForeground(sample->getForeground());
    //if (pos instanceof PositionableLabel)
    if(qobject_cast<PositionableLabel*>(pos->self())!= NULL)
    {
     ((PositionableLabel*)pos)->setText(_samples->value("Text")->getText());
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
            PositionableLabel* sample = _samples->value("Active");
            if (sample->isOpaque()) {
                icon->setBackgroundActive(sample->getBackground());
            } else {
                icon->setBackgroundActive(QColor());
            }
            icon->setTextActive(sample->getForeground());
            icon->setActiveText(sample->getText());

            sample = _samples->value("InActive");
            icon->setInactiveText(sample->getText());
            if (sample->isOpaque()) {
                icon->setBackgroundInActive(sample->getBackground());
            } else {
                icon->setBackgroundInActive(QColor());
            }
            icon->setTextInActive(sample->getForeground());

            sample = _samples->value("Unknown");
            icon->setUnknownText(sample->getText());
            if (sample->isOpaque()) {
                icon->setBackgroundUnknown(sample->getBackground());
            } else {
                icon->setBackgroundUnknown(QColor());
            }
            icon->setTextUnknown(sample->getForeground());

            sample = _samples->value("Inconsistent");
            icon->setInconsistentText(sample->getText());
            if (sample->isOpaque()) {
                icon->setBackgroundInconsistent(sample->getBackground());
            } else {
                icon->setBackgroundInconsistent(QColor());
            }
            icon->setTextInconsistent(sample->getForeground());
        } else {
            PositionableLabel* sample = _samples->value("Text");
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
            util->setHasBackground(_util->hasBackground());
            util->setFont(_util->getFont());
            util->setFixedWidth(_util->getFixedWidth());
            util->setFixedHeight(_util->getFixedHeight());
            util->setMargin(_util->getMargin());
            util->setBorderSize(_util->getBorderSize());
            if (log->isDebugEnabled()) {
                log->debug(tr("setAttributes(pos) opaque= %1 hasBackground= %2 background= %3").arg(pos->isOpaque()).arg(util->hasBackground()?"true":"false").arg(ColorUtil::colorToString(util->getBackground())));
                PositionablePopupUtil* u = pos->getPopupUtility();
                log->debug(tr("setAttributes text sample opaque= %1 hasBackground= {} background= %2").arg(sample->isOpaque()?"true":"false").arg(u->hasBackground()?"true":"false").arg( ColorUtil::colorToString(u->getBackground())));
            }
        }
        //pos->invalidate();
        pos->updateScene();
}

/*public*/ void DecoratorPanel::setSuppressRecentColor(bool b) {
 QListIterator<PositionableLabel*> iter(_samples->values());
 while (iter.hasNext()) {
     iter.next()->getPopupUtility()->setSuppressRecentColor(b);
 }
 _util->setSuppressRecentColor(b);
}

void DecoratorPanel::propertyChange(PropertyChangeEvent* evt)
{
 QString propertyName = evt->getPropertyName();
}

/*private*/ /*final*/ /*static*/ Logger* DecoratorPanel::log = LoggerFactory::getLogger("DecoratorPanel");
