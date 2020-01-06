#include "positionablepropertiesutil.h"
#include "jframe.h"
#include "jpanel.h"
#include "jtabbedpane.h"
#include "sensoricon.h"
#include "jtextfield.h"
#include <QGroupBox>
#include <QBoxLayout>
#include "jbutton.h"
#include "flowlayout.h"
#include "jlist.h"
#include "jcombobox.h"
#include "splitbuttoncolorchooserpanel.h"
#include "jspinner.h"
#include "loggerfactory.h"
#include "spinnernumbermodel.h"
#include "memoryicon.h"
#include <QCheckBox>
#include "colorselectionmodel.h"
#include "borderfactory.h"
#include "lineborder.h"
#include "compoundborder.h"
#include "defaultswatchchooserpanel.h"

/**
 * Creates the UI to set the properties of a range of Positionable Icons on
 * (Control) Panels.
 */
//public class PositionablePropertiesUtil {


PositionablePropertiesUtil::PositionablePropertiesUtil(Positionable* p, QWidget* parent) {
 detailpanel = new JPanel();
 _justification = QStringList() << tr("left") << tr("right") << tr("center");
 txtList = QList<TextDetails*>();
 defaultForeground = QColor(Qt::black);
 defaultBorderColor = QColor(Qt::black);
 italic = new QCheckBox(tr("Italic")/*, false*/);
 bold = new QCheckBox(tr("Bold")/*, false*/);
 fontSizes = QStringList() << "6" << "8" << "10" << "11" << "12" << "14" << "16" <<
      "20" << "24" << "28" << "32" << "36";
 previewChangeListener = new PreviewChangeListener(this);

 _parent = p;
}

/*public*/ void PositionablePropertiesUtil::display() {
    propertiesPanel = new JTabbedPane();
    getCurrentValues();
    JPanel* exampleHolder = new JPanel();
    QVBoxLayout* exampleHolderLayout = new QVBoxLayout(exampleHolder);
    //example = new JLabel(text);

    for (int i = 0; i < txtList.size(); i++) {
        QGroupBox* p = new QGroupBox();
        QVBoxLayout* pLayout = new QVBoxLayout(p);
        //p.setBorder(BorderFactory.createTitledBorder(txtList.at(i).getDescription()));
        p->setTitle(txtList.at(i)->getDescription());
        pLayout->addWidget(txtList.at(i)->getLabel()); // add a visual example for each
        exampleHolderLayout->addWidget(p);
    }
    //exampleHolder.add(example);
    JPanel* tmp = new JPanel();
    QVBoxLayout* tmpLayout;
    tmp->setLayout(tmpLayout = new QVBoxLayout()); //tmp, BoxLayout.Y_AXIS));
    tmpLayout->addWidget(propertiesPanel);
    tmpLayout->addWidget(detailpanel);
    tmpLayout->addWidget(exampleHolder);
    textPanel();
    editText();
    borderPanel();
    sizePosition();

    JPanel* _buttonArea = new JPanel();
    FlowLayout* _buttonAreaLayout = new FlowLayout(_buttonArea);
    JButton* cancel = new JButton(tr("Cancel"));
    _buttonAreaLayout->addWidget(cancel);
//    cancel.addActionListener((ActionEvent e) -> {
//        undoChanges();
//        mFrame.dispose();
//    });
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(on_cancel_clicked()));

    JButton* applyButton = new JButton(tr("Apply"));
    _buttonAreaLayout->addWidget(applyButton);
//    applyButton.addActionListener((ActionEvent e) -> {
//        fontApply();
//    });
    connect(applyButton, SIGNAL(clicked(bool)), this, SLOT(fontApply()));

    JButton* okButton = new JButton(tr("OK"));
    _buttonAreaLayout->addWidget(okButton);
//    okButton.addActionListener((ActionEvent e) -> {
//        fontApply();
//        mFrame.dispose();
//    });
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(on_okButton_clicked()));
    tmpLayout->addWidget(_buttonArea);

// TODO:    exampleHolder->setBackground(((PositionableLabel*)_parent)->parent()->getBackground());
    mFrame = new JFrame(_parent->getNameString());
    //mFrameL.add(tmp);
    mFrame->setCentralWidget(tmp);
    mFrame->pack();
    mFrame->setVisible(true);
    preview();
}


/**
 * Create and fill in the Font (Decoration) tab of the UI.
 */
void PositionablePropertiesUtil::textPanel()
{
 _textPanel = new JPanel();
 QVBoxLayout* _textPanelLayout;
 _textPanel->setLayout(_textPanelLayout =new QVBoxLayout()); //_textPanel, BoxLayout.Y_AXIS));
 JPanel* fontColorPanel = new JPanel();
 FlowLayout* fontColorPanelLayout = new FlowLayout(fontColorPanel);
 fontColorPanelLayout->addWidget(new JLabel(tr("Font Color") + ": "));

 JPanel* fontSizePanel = new JPanel();
 QVBoxLayout* fontSizePanelLayout;
 fontSizePanel->setLayout(fontSizePanelLayout = new QVBoxLayout());//fontSizePanel, BoxLayout.Y_AXIS));
 fontSizeChoice = new JList(fontSizes);

 fontSizeChoice->setSelectedValue("" + fontSize, true);
 fontSizeChoice->setSelectionMode(QAbstractItemView::SingleSelection/*ListSelectionModel::SINGLE_SELECTION*/);
//    JScrollPane listScroller = new JScrollPane(fontSizeChoice);
//    listScroller.setPreferredSize(new Dimension(60, 80));

 JPanel* FontPanel = new JPanel();
 QVBoxLayout* FontPanelLayout = new QVBoxLayout(FontPanel);
 fontSizeField = new JTextField("" + QString::number(fontSize), fontSizeChoice->width());
//    fontSizeField.addKeyListener(previewKeyActionListener);
 connect(fontSizeField, SIGNAL(textChanged(QString)), this, SLOT(on_fontSizeField(QString)));
 fontSizePanelLayout->addWidget(fontSizeField);
 fontSizePanelLayout->addWidget(/*listScroller*/fontSizeChoice);
 FontPanelLayout->addWidget(fontSizePanel);

 JPanel* Style = new JPanel();
 QVBoxLayout* StyleLayout;
 Style->setLayout(StyleLayout = new QVBoxLayout());//Style, BoxLayout.Y_AXIS));
 bold = new QCheckBox(tr("Bold"));
 italic = new QCheckBox(tr("Italic"));
 StyleLayout->addWidget(bold);
 StyleLayout->addWidget(italic);
 FontPanelLayout->addWidget(Style);
 _textPanelLayout->addWidget(FontPanel);

 JPanel* justificationPanel = new JPanel();
 QHBoxLayout* justificationPanelLayout = new QHBoxLayout(justificationPanel);
 _justificationCombo = new JComboBox(_justification);
 switch (justification) {
     case 0x00:
         _justificationCombo->setCurrentIndex(0);
         break;
     case 0x02:
         _justificationCombo->setCurrentIndex(1);
         break;
     default:
         _justificationCombo->setCurrentIndex(2);
         break;
 }
 justificationPanelLayout->addWidget(new JLabel(tr("Justification") + ": "));
 justificationPanelLayout->addWidget(_justificationCombo);
 _textPanelLayout->addWidget(justificationPanel);

 //_justificationCombo.addActionListener(previewActionListener);
 connect(_justificationCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(preview()));
 //bold.addActionListener(previewActionListener);
 connect(bold, SIGNAL(clicked(bool)), this, SLOT(preview()));
 //italic.addActionListener(previewActionListener);
 connect(italic, SIGNAL(clicked(bool)), this, SLOT(preview()));
 //fontSizeChoice.addActionListener(previewActionListener);
 connect(fontSizeChoice, SIGNAL(clicked(QModelIndex)), this, SLOT(on_FontSizeChoice(QModelIndex)));
//    fontSizeChoice.getSelectionModel().addListSelectionListener((ListSelectionEvent e) -> {
//        fontSizeField.setText(fontSizeChoice.getSelectedValue());
//        preview();
//    });


 for (int i = 0; i <  txtList.size(); i++)
 { // repeat 4 times for sensor icons, or just once
     /*final*/ int x = i;
  QGroupBox* txtPanel = new QGroupBox();
  FlowLayout* txtPanelLayout = new FlowLayout(txtPanel);
  defaultForeground = _parent->getForeground();
  JColorChooser* txtColorChooser = new JColorChooser(defaultForeground);
  txtColorChooser->setPreviewPanel(new JPanel()); // remove the preview panel
  QVector<AbstractColorChooserPanel*> txtColorPanels = QVector<AbstractColorChooserPanel*>() << (AbstractColorChooserPanel*) (new SplitButtonColorChooserPanel());
  txtColorChooser->setChooserPanels(&txtColorPanels);
  txtColorChooser->getSelectionModel()->addChangeListener(previewChangeListener);
  txtPanelLayout->addWidget(txtColorChooser);
//        txtColorChooser->getSelectionModel()->addChangeListener((ChangeEvent ce) -> {
//            txtList.at(x).setForeground(txtColorChooser->getColor());
//        });
  txtColorChooser->getSelectionModel()->addChangeListener(new TCChangeListener(x, txtColorChooser, this));

  JPanel* p = new JPanel();
  QVBoxLayout* pLayout = new QVBoxLayout(p);
  pLayout->addWidget(new JLabel(tr("Font Color") + ": "));
  pLayout->addWidget(txtColorChooser);

  txtPanelLayout->addWidget(p);

  defaultBackground = _parent->getBackground();
  JColorChooser* txtBackColorChooser = new JColorChooser(defaultBackground);
  txtBackColorChooser->setPreviewPanel(new JPanel()); // remove the preview panel
  QVector<AbstractColorChooserPanel*> txtBackColorPanels = QVector<AbstractColorChooserPanel*>() <<  (AbstractColorChooserPanel*)(new SplitButtonColorChooserPanel());
  txtBackColorChooser->setChooserPanels(&txtBackColorPanels);
  txtBackColorChooser->getSelectionModel()->addChangeListener(previewChangeListener);
  txtPanelLayout->addWidget(txtBackColorChooser);
//        txtBackColorChooser->getSelectionModel()->addChangeListener((ChangeEvent ce) -> {
//            txtList.at(x).setBackground(txtBackColorChooser.getColor());
//        });
  txtBackColorChooser->getSelectionModel()->addChangeListener(new TCBChangeListener(x, txtBackColorChooser, this));
  p = new JPanel();
  pLayout = new QVBoxLayout(p);
  pLayout->addWidget(new JLabel(tr("Background color") + ": "));
  pLayout->addWidget(txtBackColorChooser);

  QString _borderTitle =  txtList.at(i)->getDescription();
  if (_borderTitle == (tr("Example"))) {
      _borderTitle = tr("Text Decoration"); // replace default label by an appropriate one for text decoration box on Font tab
  }
  //txtPanel.setBorder(BorderFactory.createTitledBorder(_borderTitle));
  txtPanel->setTitle(_borderTitle);
  txtPanelLayout->addWidget(p);

  _textPanelLayout->addWidget(txtPanel);

 }
 propertiesPanel->addTab(tr("Font"), QIcon(), _textPanel, tr("Set Font Size & Decoration"));
}

void PositionablePropertiesUtil::on_FontSizeChoice(QModelIndex index)
{
 fontSizeField->setText(index.data().toString());
 preview();
}

void PositionablePropertiesUtil::on_fontSizeField(QString str)
{
 if(str != "")
  preview();
}

void PositionablePropertiesUtil::closeEvent(QCloseEvent *e)
{
 e->accept();
 undoChanges();
}

void PositionablePropertiesUtil::on_cancel_clicked()
{
 undoChanges();
 reject();
 //close();
 //setVisible(false);
}
void PositionablePropertiesUtil::on_applyButton_clicked()
{
 fontApply();
}
void PositionablePropertiesUtil::on_okButton_clicked()
{
 fontApply();
 accept();
 //close();
 //setVisible(false);

}


/**
 * Create and fill in the Border tab of the UI.
 */
void PositionablePropertiesUtil::borderPanel() {
    JPanel* borderPanel = new JPanel();

    borderColorChooser = new JColorChooser(defaultBorderColor);
    QVector<AbstractColorChooserPanel*> borderColorPanels = QVector<AbstractColorChooserPanel*>() <<(AbstractColorChooserPanel*) (new SplitButtonColorChooserPanel());
    borderColorChooser->setChooserPanels(&borderColorPanels);
    borderColorChooser->setPreviewPanel(new JPanel()); // remove the preview panel

    previewChangeListener = new PreviewChangeListener(this);
    borderColorChooser->getSelectionModel()->addChangeListener(previewChangeListener);

    JPanel* borderColorPanel = new JPanel();
    QHBoxLayout* borderColorPanelLayout = new QHBoxLayout(borderColorPanel);
    borderColorPanelLayout->addWidget(new JLabel(tr("Border Color") + ": "));
    borderColorPanelLayout->addWidget(borderColorChooser);

    JPanel* borderSizePanel = new JPanel();
    FlowLayout* borderSizePanelLayout = new FlowLayout(borderSizePanel);
    borderSizeTextSpin = getSpinner(borderSize, tr("Border Size"));
    //borderSizeTextSpin.addChangeListener(spinnerChangeListener);
    connect(borderSizeTextSpin, SIGNAL(valueChanged(int)), this, SLOT(preview()));
    borderSizePanelLayout->addWidget(new JLabel(tr("Border Size") + ": "));
    borderSizePanelLayout->addWidget(borderSizeTextSpin);

    JPanel* marginSizePanel = new JPanel();
    FlowLayout* marginSizePanelLayout = new FlowLayout(marginSizePanel);
    marginSizeTextSpin = getSpinner(marginSize, tr("Margin Size"));
    //marginSizeTextSpin.addChangeListener(spinnerChangeListener);
    connect(marginSizeTextSpin, SIGNAL(valueChanged(int)), this, SLOT(preview()));

    marginSizePanelLayout->addWidget(new JLabel(tr("Margin Size") + ": "));
    marginSizePanelLayout->addWidget(marginSizeTextSpin);

    QVBoxLayout* borderPanelLayout;
    borderPanel->setLayout(borderPanelLayout = new QVBoxLayout());//borderPanel, BoxLayout.Y_AXIS));
    borderPanelLayout->addWidget(borderColorPanel);
    borderPanelLayout->addWidget(borderSizePanel);
    borderPanelLayout->addWidget(marginSizePanel);

    propertiesPanel->addTab(tr("Border"), QIcon(), borderPanel, tr("Set Border & Margin"));

}

/**
 * Create and fill in the Contents tab of the UI (Text Label objects).
 */
void PositionablePropertiesUtil::editText() {
    JPanel* editText = new JPanel();
    QVBoxLayout* editTextLayout;
    editText->setLayout(editTextLayout = new QVBoxLayout());//editText, BoxLayout.Y_AXIS));
    QSignalMapper* mapper = new QSignalMapper(this);
    for (int i = 0; i < txtList.size(); i++) {
        /*final*/ int x = i;
        QGroupBox* p = new QGroupBox();
        QVBoxLayout* pLayout = new QVBoxLayout(p);
        QString _borderTitle = txtList.at(i)->getDescription();
        if (_borderTitle==(tr("Example"))) {
            _borderTitle = tr("Values"); // replace label provided by Ctor by an appropriate one for text string box on Contents tab
        }
        //p.setBorder(BorderFactory.createTitledBorder(_borderTitle));
        p->setTitle(_borderTitle);

        JLabel* txt = new JLabel(tr("Text to display") + ": ");
        JTextField* textField = new JTextField(txtList.at(i)->getText(), 20);
#if 0 // TODO:
        textField.addKeyListener(new KeyListener() {
            @Override
            public void keyTyped(KeyEvent E) {
            }

            @Override
            public void keyPressed(KeyEvent E) {
            }

            @Override
            public void keyReleased(KeyEvent E) {
                JTextField tmp = (JTextField) E.getSource();
                txtList.at(x).setText(tmp.getText());
                preview();
            }
        });
#endif
        textField->setData(x);
        mapper->setMapping(textField,textField);
        connect(textField, SIGNAL(textChanged(QString)), mapper, SLOT(map()));
        pLayout->addWidget(txt);
        pLayout->addWidget(textField);
        editTextLayout->addWidget(p);
    }
    connect(mapper, SIGNAL(mapped(QWidget*)), this, SLOT(on_textChanged(QWidget*)) );
    propertiesPanel->addTab(tr("Contents"), QIcon(), editText, tr("Edit Text Contents"));
}

/*private*/ void PositionablePropertiesUtil::on_textChanged(QWidget * w)
{
 JTextField* txtField = (JTextField*)w;
 int x = txtField->getDatat().toInt();
 txtList.at(x)->setText(txtField->text());
 preview();
}

/**
 * Create and fill in the Size &amp; Position tab of the UI.
 */
void PositionablePropertiesUtil::sizePosition() {
 JPanel* posPanel = new JPanel();
 QVBoxLayout* posPanelLayout = new QVBoxLayout(posPanel);

 JPanel* xyPanel = new JPanel();
 QVBoxLayout* xyPanelLayout;
 xyPanel->setLayout(xyPanelLayout = new QVBoxLayout());//xyPanel, BoxLayout.Y_AXIS));
 JPanel* xPanel = new JPanel();
 QHBoxLayout* xPanelLayout = new QHBoxLayout(xPanel);
 JLabel* txt = new JLabel(" X: ");
 xPositionTextSpin = getSpinner(xPos, "x position");
 //xPositionTextSpin.addChangeListener(spinnerChangeListener);
 connect(xPositionTextSpin, SIGNAL(valueChanged(int)), this, SLOT(preview()));
 xPanelLayout->addWidget(txt);
 xPanelLayout->addWidget(xPositionTextSpin);

 JPanel* yPanel = new JPanel();
 QHBoxLayout* yPanelLayout = new QHBoxLayout(yPanel);
 txt = new JLabel(" Y: ");
 yPositionTextSpin = getSpinner(yPos, "y position");
 //yPositionTextSpin.addChangeListener(spinnerChangeListener);
 connect(yPositionTextSpin, SIGNAL(valueChanged(int)), this, SLOT(preview()));
 yPanelLayout->addWidget(txt);
 yPanelLayout->addWidget(yPositionTextSpin);

 xyPanelLayout->addWidget(xPanel);
 xyPanelLayout->addWidget(yPanel);

 JPanel* sizePanel = new JPanel();
 QVBoxLayout* sizePanelLayout;
 sizePanel->setLayout(sizePanelLayout = new QVBoxLayout());//sizePanel, BoxLayout.Y_AXIS));
 JPanel* widthPanel = new JPanel();
 FlowLayout* widthPanelLayout = new FlowLayout(widthPanel);
 widthSizeTextSpin = getSpinner(fixedWidth, tr("Width"));
 //widthSizeTextSpin.addChangeListener(spinnerChangeListener);
 connect(widthSizeTextSpin, SIGNAL(valueChanged(int)), this, SLOT(preview()));
 /*widthSizeText = new JTextField(""+fixedWidth, 10);
  widthSizeText.addKeyListener(previewKeyActionListener);*/
 txt = new JLabel(tr("Width") + ": ");
 widthPanelLayout->addWidget(txt);
 widthPanelLayout->addWidget(widthSizeTextSpin);

 JPanel* heightPanel = new JPanel();
 FlowLayout* heightPanelLayout = new FlowLayout(heightPanel);
 /*heightSizeText = new JTextField(""+fixedHeight, 10);
  heightSizeText.addKeyListener(previewKeyActionListener);*/
 heightSizeTextSpin = getSpinner(fixedHeight, tr("Height"));
 //heightSizeTextSpin.addChangeListener(spinnerChangeListener);
 connect(heightSizeTextSpin, SIGNAL(valueChanged(int)), this, SLOT(preview()));
 txt = new JLabel(tr("Height") + ": ");
 heightPanelLayout->addWidget(txt);
 heightPanelLayout->addWidget(heightSizeTextSpin);

 sizePanelLayout->addWidget(widthPanel);
 sizePanelLayout->addWidget(heightPanel);

 posPanelLayout->addWidget(xyPanel);
 posPanelLayout->addWidget(sizePanel);
 //posPanel.setLayout(new BoxLayout(posPanel, BoxLayout.Y_AXIS));

 propertiesPanel->addTab(tr("Size & Position"), QIcon(), posPanel,tr("Set Size & Position"));
}

void PositionablePropertiesUtil::fontApply()
{
 pop->setFontSize(fontSizeField->text().toInt());
  if (bold->isChecked()) {
      pop->setFontStyle(/*Font::BOLD*/QFont::Bold, 0);
  } else {
      pop->setFontStyle(0, /*Font.BOLD*/QFont::Bold);
  }
  if (italic->isChecked()) {
      pop->setFontStyle(/*Font.ITALIC*/QFont::StyleItalic, 0);
  } else {
      pop->setFontStyle(0, /*Font.ITALIC*/QFont::StyleItalic);
  }

  QColor desiredColor;
  //if (_parent instanceof SensorIcon)
  if(qobject_cast<SensorIcon*>(_parent->self()))
  {
      SensorIcon* si = (SensorIcon*) _parent->self();
      if (si->isIcon()) {
          PositionableLabel* pp = (PositionableLabel*) _parent->self();
          pp->setText(txtList.at(0)->getText());
          pop->setForeground(txtList.at(0)->getForeground());
          pop->setBackgroundColor(txtList.at(0)->getBackground());
      } else {
          si->setActiveText(txtList.at(0)->getText());
          si->setTextActive(txtList.at(0)->getForeground());
          si->setBackgroundActive(txtList.at(0)->getBackground());

          si->setInactiveText(txtList.at(1)->getText());
          si->setTextInActive(txtList.at(1)->getForeground());
          si->setBackgroundInActive(txtList.at(1)->getBackground());

          si->setUnknownText(txtList.at(2)->getText());
          si->setTextUnknown(txtList.at(2)->getForeground());
          si->setBackgroundUnknown(txtList.at(2)->getBackground());

          si->setInconsistentText(txtList.at(3)->getText());
          si->setTextInconsistent(txtList.at(3)->getForeground());
          si->setBackgroundInconsistent(txtList.at(3)->getBackground());
      }
  } else {
      PositionableLabel* pp = (PositionableLabel*) _parent->self();
      pp->setText(txtList.at(0)->getText());
      pop->setForeground(txtList.at(0)->getForeground());
      pop->setBackgroundColor(txtList.at(0)->getBackground());
  }

  int deg = _parent->getDegrees();
  if (deg != 0) {
      _parent->rotate(0);
  }
  desiredColor = borderColorChooser->getColor();
  pop->setBorderColor(desiredColor);

  pop->setBorderSize(( borderSizeTextSpin->value()));

  pop->setMargin( marginSizeTextSpin->value());
  _parent->setLocation( xPositionTextSpin->value(),  yPositionTextSpin->value());
  pop->setFixedWidth(widthSizeTextSpin->value());
  pop->setFixedHeight( heightSizeTextSpin->value());
  switch (_justificationCombo->currentIndex()) {
      case 0:
          pop->setJustification(0x00);
          break;
      case 1:
          pop->setJustification(0x02);
          break;
      case 2:
          pop->setJustification(0x04);
          break;
      default:
          log->warn(tr("Unhandled combo index: %1").arg(_justificationCombo->currentIndex()));
          break;
  }
  _parent->rotate(deg);

  _parent->updateScene();
}

void PositionablePropertiesUtil::preview()
{
 int weight = QFont::Normal;
 bool _italic =false;
 if (bold->isChecked()) {
     weight =/* Font.BOLD*/QFont::Bold;
 }
 if (italic->isChecked()) {
   _italic = true;
 }

 QFont newFont = QFont(_parent->getFont().family(), fontSizeField->text().toInt(), weight, _italic);

 QColor desiredColor;

 desiredColor = borderColorChooser->getColor();
 Border* borderMargin;
 int margin = ( marginSizeTextSpin->value());
 Border* outlineBorder;
 if (!desiredColor.isValid()) {
     outlineBorder = new LineBorder(desiredColor,  borderSizeTextSpin->value());
 } else {
     outlineBorder = BorderFactory::createEmptyBorder(0, 0, 0, 0);
 }
 int hoz = 0;
 switch (_justificationCombo->currentIndex()) {
     case 0:
         hoz = (0x02); // left
         break;
     case 1:
         hoz = (0x04); // right
         break;
     case 2:
         hoz = (0x00);  // center
         break;
     default:
         log->warn(tr("Unhandled combo index: %1").arg(_justificationCombo->currentIndex()));
         break;
 }

 for (int i = 0; i < txtList.size(); i++)
 {
  JLabel* tmp = txtList.at(i)->getLabel();
  if (tmp->isOpaque()) {
      borderMargin = new LineBorder(tmp->getBackground(), margin);
  } else {
      borderMargin = BorderFactory::createEmptyBorder(margin, margin, margin, margin);
  }
  tmp->setFont(newFont);
  txtList.at(i)->setFont(newFont);
  tmp->setHorizontalAlignment(hoz);
  tmp->setBorder(new CompoundBorder(outlineBorder, borderMargin));
  txtList.at(i)->setBorderSize(margin);
  if(borderSizeTextSpin->value())
   tmp->setStyleSheet(tr("QLabel{border-width: %1px; border-style: solid; border-color: rgb(%2,%3,%4);}").arg(borderSizeTextSpin->value())
                 .arg(desiredColor.red()).arg(desiredColor.green()).arg(desiredColor.blue()));
  else
   tmp->setStyleSheet(tr("QLabel{border: none;}"));
  tmp->setSize(maxWidth(tmp), maxHeight(tmp));
  tmp->resize(QSize(maxWidth(tmp), maxHeight(tmp)));
  txtList.at(i)->setAttributes();
 }
 mFrame->pack();
}

int PositionablePropertiesUtil::maxWidth(JLabel* tmp) {
 int max = 0;
 if ( widthSizeTextSpin->value() != 0) {
     max =  widthSizeTextSpin->value();
     max += borderSizeTextSpin->value() * 2;
 } else {
     if (tmp->text().trimmed().length() > 0) {
         max = tmp->getFontMetrics().width(tmp->text());  //tmp.getFont()).stringWidth(tmp.getText());
     }
     if (pop != nullptr) {
         max += marginSizeTextSpin->value() * 2;
         max += borderSizeTextSpin->value() * 2;
     }
 }
 return max;
}

/*public*/ int PositionablePropertiesUtil::maxHeight(JLabel* tmp) {
 int max = 0;
 if ( heightSizeTextSpin->value() != 0) {
     max = heightSizeTextSpin->value();
     max += borderSizeTextSpin->value() * 2;
 } else {
     if (tmp->text().trimmed().length() > 0) {
         max = tmp->getFontMetrics().height();
     }
     if (pop != nullptr) {
         max += marginSizeTextSpin->value() * 2;
         max += borderSizeTextSpin->value() * 2;
     }
 }

 return max;
}

/*private*/ void PositionablePropertiesUtil::undoChanges()
{
 if(pop == nullptr)
  return;
 //if (_parent instanceof SensorIcon) {
 if(qobject_cast<SensorIcon*>(pop->_parent->self())!= NULL)
 {
  SensorIcon* si = (SensorIcon*) pop->_parent;
  if (si->isIcon())
  {
   PositionableLabel* pp = (PositionableLabel*)pop->_parent;
   pp->setText( txtList.at(0)->getOrigText());
   pop->setForeground( txtList.at(0)->getOrigForeground());
   pop->setBackgroundColor( txtList.at(0)->getOrigBackground());
  }
  else
  {
   si->setActiveText(txtList.at(0)->getOrigText());
   si->setTextActive(txtList.at(0)->getOrigForeground());
   si->setBackgroundActive(txtList.at(0)->getOrigBackground());

   si->setInactiveText(txtList.at(1)->getOrigText());
   si->setTextInActive(txtList.at(1)->getOrigForeground());
   si->setBackgroundInActive( txtList.at(1)->getOrigBackground());

   si->setUnknownText( txtList.at(2)->getOrigText());
   si->setTextUnknown( txtList.at(2)->getOrigForeground());
   si->setBackgroundUnknown( txtList.at(2)->getOrigBackground());

   si->setInconsistentText( txtList.at(3)->getOrigText());
   si->setTextInconsistent( txtList.at(3)->getOrigForeground());
   si->setBackgroundInconsistent( txtList.at(3)->getOrigBackground());
  }
 }
 else
 {
  PositionableLabel* pp = (PositionableLabel*)pop->_parent;
  pp->setText( txtList.at(0)->getOrigText());
  pop->setForeground( txtList.at(0)->getOrigForeground());
  pop->setBackgroundColor( txtList.at(0)->getOrigBackground());
 }
 pop->setJustification(justification);
 pop->setFixedWidth(fixedWidth);
 pop->setFixedHeight(fixedHeight);
 pop->setMargin(marginSize);
 pop->setBorderSize(borderSize);
 pop->setFontStyle(0, fontStyle);
 pop->setFontSize(fontSize);
 pop->setBorderColor(defaultBorderColor);
 //((PositionableLabel*)pop->_parent)->setLocation(xPos, yPos);
 if(qobject_cast<MemoryIcon*>(pop->_parent->self()))
 {
  MemoryIcon* pm = (MemoryIcon*) pop->_parent;
//  xPos = pm->getOriginalX();
//  yPos = pm->getOriginalY();
  pm->setOriginalLocation(xPos,yPos);
 }
 else
 {
//  xPos = ((PositionableLabel*)pop->_parent)->getX();
//  yPos = ((PositionableLabel*)pop->_parent)->getY();
  ((Positionable*)pop->_parent)->setLocation(xPos,yPos);
 }
}

/*private*/ void PositionablePropertiesUtil::getCurrentValues()
{
 pop = ((Positionable*)_parent)->getPopupUtility();
 txtList = QList<TextDetails*>();

 //if (_parent instanceof SensorIcon) {
 if(qobject_cast<SensorIcon*>(_parent->self())!= NULL)
 {
  SensorIcon* si = (SensorIcon*) _parent;
  if (si->isIcon())
  {
    txtList.append(new TextDetails("Text", pop->getText(), pop->getForeground(), si->getBackground()));
  }
  else
  {
    txtList.append(new TextDetails("Active", si->getActiveText(), si->getTextActive(), si->getBackgroundActive()));
    txtList.append(new TextDetails("InActive", si->getInactiveText(), si->getTextInActive(), si->getBackgroundInActive()));
    txtList.append(new TextDetails("Unknown", si->getUnknownText(), si->getTextUnknown(), si->getBackgroundUnknown()));
    txtList.append(new TextDetails("Inconsistent", si->getInconsistentText(), si->getTextInconsistent(), si->getBackgroundInconsistent()));
  }
 }
 else
 {
   txtList.append(new TextDetails("Text", pop->getText(), pop->getForeground(), ((PositionableLabel*)pop->_parent)->getBackground()));
 }

 fixedWidth = pop->getFixedWidth();
 fixedHeight = pop->getFixedHeight();
 marginSize = pop->getMargin();
 borderSize = pop->getBorderSize();
 justification = pop->getJustification();
 fontStyle = pop->getFontStyle();
 fontSize = pop->getFontSize();
 if ( (QFont::Bold & fontStyle) == QFont::Bold ) bold->setChecked(true);
 if ( (QFont::StyleItalic & fontStyle) == QFont::StyleItalic ) italic->setChecked(true);
 if (((SensorIcon*)pop->_parent)->isOpaque())
        defaultBackground = ((SensorIcon*)pop->_parent)->getBackground();
 defaultForeground = pop->getForeground();
 defaultBorderColor = pop->getBorderColor();
 //if (_parent instanceof MemoryIcon){
 if(qobject_cast<MemoryIcon*>(_parent->self())!= NULL)
 {
  MemoryIcon* pm = (MemoryIcon*) pop->_parent;
  xPos = pm->getOriginalX();
  yPos = pm->getOriginalY();
 }
 else
 {
  xPos = pop->_parent->getX();
  yPos = pop->_parent->getY();
 }
}
#if 0
const QIcon* PositionablePropertiesUtil::getColourIcon(QColor color)
{
 Q_ASSERT(color.isValid());
 int ICON_DIMENSION = 10;
// BufferedImage image = new BufferedImage(ICON_DIMENSION, ICON_DIMENSION,
// BufferedImage.TYPE_INT_RGB);
 QImage resultImage = QImage(ICON_DIMENSION,ICON_DIMENSION,QImage::Format_ARGB32_Premultiplied);

// Graphics g = image.getGraphics();
 QPainter painter(&resultImage);
//   // set completely transparent
// g.setColor(color);
// g.fillRect(0,0, ICON_DIMENSION,ICON_DIMENSION);
 QBrush brBkgnd = QBrush(QColor(color), Qt::SolidPattern);
//eRect.adjust(0, -3.0, 0, 0);
 painter.fillRect(resultImage.rect(), brBkgnd);
 painter.end();
// ImageIcon icon = new ImageIcon(image);
 QIcon* icon = new QIcon(QPixmap::fromImage(resultImage));
 return icon;
}


void PositionablePropertiesUtil::setCurrentValues()
{
 getCurrentValues();
 ui->fontComboBox->setCurrentFont(((PositionableLabel*)pop->_parent)->getFont());
 QColor desiredColor = QColor(Qt::black);

 int backCurrentColor = _colors.length()-1; // note: "None" will be added
 int fontCurrentColor = _fontcolors.length()-1;
 int borderColor = _bordercolors.length()-1;
 for(int i=0; i < _fontcolors.size(); i++)
 {
  desiredColor = _colors.at(i);
  if(desiredColor == defaultBackground)
   backCurrentColor = i;
  if(desiredColor == defaultForeground)
   fontCurrentColor = i;
  if(desiredColor == defaultBorderColor)
   borderColor = i;
 }
 ui->backgroundColor->addItem(tr("None"), QColor());
 ui->backgroundColor->setCurrentIndex(backCurrentColor);
 ui->fontColor->setCurrentIndex(fontCurrentColor);
 ui->borderColorCombo->setCurrentIndex(borderColor);
 int currentFontSize=0;
 for (int i = 0; i < fontSizes.length(); i++)
 {
  if (fontSizes.at(i) == QString("%1").arg(fontSize))
  {
   currentFontSize=i;
   ui->fontSizeField->setEditText(fontSizes.at(i));
  }
 }
 if(justification==0x00)
  ui->_justificationCombo->setCurrentIndex(0);  // LEFT
 else if (justification ==0x02)
  ui->_justificationCombo->setCurrentIndex(1);  // RIGHT
 else
  ui->_justificationCombo->setCurrentIndex(2);  // CENTER
 ui->xPosition->setValue(xPos);
 ui->yPosition->setValue(yPos);
 ui->width->setValue(fixedWidth);
 ui->height->setValue(fixedHeight);
 ui->borderSize->setValue(borderSize);
 ui->marginSize->setValue(marginSize);
 ui->width->setValue(fixedWidth);
 ui->height->setValue(fixedHeight);
 ui->textField->setText( txtList.at(0).getText());
}

QColor PositionablePropertiesUtil::colorStringToColor(QString sColor)
{
 QColor color(Qt::transparent);
 int i =0;
 foreach(QString s, _fontcolors)
 {
  if(sColor == s)
   return _colors.at(i);
  i++;
 }
 return color;
}
#endif
JSpinner* PositionablePropertiesUtil::getSpinner(int value, QString tooltip) {
        SpinnerNumberModel* model = new SpinnerNumberModel(0, 0, 1000, 1);
        JSpinner* spinX = new JSpinner(model);
        spinX->setValue(value);
        spinX->setToolTip(tooltip);
        spinX->setMaximumSize(QSize(
                spinX->maximumWidth(), spinX->sizeHint().height()));
        return spinX;
    }
/*static*/ Logger* PositionablePropertiesUtil::log = LoggerFactory::getLogger("PositionablePropertiesUtil");
//}
