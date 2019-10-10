#include "positionablepropertiesutil.h"
#include "ui_positionablepropertiesutil.h"
#include "sensoricon.h"
#include "memoryicon.h"
#include <QPainter>
#include <QImage>
#include <QDir>
#include <QCloseEvent>
#include "editor.h"
#include "jtabbedpane.h"
#include "jpanel.h"

//PositionalPropertiesUtil::PositionalPropertiesUtil(QObject *parent) :
//    QObject(parent)
//{
//}
//public class PositionablePropertiesUtil {

//    Frame mFrame = null;
//    JPanel detailpanel = new JPanel();
//    JTabbedPane propertiesPanel;

PositionablePropertiesUtil::PositionablePropertiesUtil(Positionable* p, QWidget* parent):
    QDialog(parent),
    ui(new Ui::PositionablePropertiesUtil)
{
 ui->setupUi(this);
 _parent  = p;
}
void PositionablePropertiesUtil::display()
{
 getCurrentValues();
 //this->_parent = (Positionable*)parent;
Positionable* p = _parent;
// ui->fontComboBox->setCurrentFont(((PositionableLabel*)pop->_parent)->getFont());
 QFont f = font();
 if(qobject_cast<PositionableLabel*>((QObject*)p))
 {
  f = ((PositionableLabel*)p)->getFont();
  ui->fontComboBox->setCurrentFont(((PositionableLabel*)pop->_parent)->getFont());
  fontSize = f.pointSize();
 }
 _fontcolors << "Black"<<"Dark Gray"<<"Gray"<<"Light Gray"<<"White"<<"Red"<<"Orange"<<"Yellow"<<"Green"<<"Blue"<<"Magenta";
 _colors << QColor(Qt::black) << QColor(Qt::darkGray) << QColor(Qt::gray) << QColor(Qt::lightGray) << QColor(Qt::white) << QColor(Qt::red) << QColor(255, 170, 0) << QColor(Qt::yellow ) << QColor(Qt::green) <<QColor(Qt::blue) <<QColor(Qt::magenta)<<QColor();
 _justification << "Left" << "Right" << "Center";
 ui->fontColor->clear();
 ui->backgroundColor->clear();
 ui->borderColorCombo->clear();
 QColor desiredColor = QColor(Qt::black);
 QList<QIcon> images;
 QIcon icon;
 int backCurrentColor = _colors.length()-1; // note: "None" will be added
 int fontCurrentColor = _fontcolors.length()-1;
 int borderColor = _bordercolors.length()-1;
 for(int i=0; i < _fontcolors.size(); i++)
 {
  desiredColor = _colors.at(i);
  images.append(icon = *getColourIcon(desiredColor));
  ui->fontColor->addItem(icon,_fontcolors.at(i), _colors.at(i));
  ui->backgroundColor->addItem(icon, _fontcolors.at(i), _colors.at(i));
  _backgroundcolors << _fontcolors.at(i);
  ui->borderColorCombo->addItem(icon, _fontcolors.at(i), _colors.at(i));
  _bordercolors << _fontcolors.at(i);
  if(desiredColor == defaultBackground)
   backCurrentColor = i;
  if(desiredColor == defaultForeground)
   fontCurrentColor = i;
  if(desiredColor == defaultBorderColor)
   borderColor = i;
 }
 //ui->backgroundColor->addItem(tr("None"), QColor());
 ui->backgroundColor->setCurrentIndex(backCurrentColor);
 ui->fontColor->setCurrentIndex(fontCurrentColor);
 ui->borderColorCombo->setCurrentIndex(borderColor);

 fontSizes<< "6"<< "8"<< "10"<< "11"<< "12"<< "14"<< "16"<<
  "20"<< "24"<< "28"<< "32"<< "36";

 fontSizeChoice = QStringList();
 int currentFontSize=0;
 for (int i = 0; i < fontSizes.length(); i++)
 {
  ui->fontSizeField->addItem(fontSizes.at(i));
  fontSizeChoice.append(fontSizes.at(i));
  if (fontSizes.at(i) == QString("%1").arg(fontSize))
  {
   currentFontSize=i;
   //ui->fontSizeField->setEditText(fontSizes.at(i));
  }
 }
 ui->fontSizeField->setCurrentIndex(currentFontSize);
 ui->bold->setChecked(f.weight() >= QFont::Bold);
 ui->italic->setChecked(f.style() == QFont::StyleItalic);

 //fontSizeChoice.select(currentFontSize);

 if(justification==0x00)
  ui->_justificationCombo->setCurrentIndex(0);  // LEFT
 else if (justification ==0x02)
  ui->_justificationCombo->setCurrentIndex(1);  // RIGHT
 else
  ui->_justificationCombo->setCurrentIndex(2);  // CENTER
 //txtList = new QList<TextDetails>();

 fixedWidth=0;
 fixedHeight=0;
 marginSize=0;
 borderSize=0;
 ui->xPosition->setValue(xPos);
 ui->yPosition->setValue(yPos);
 ui->width->setValue(fixedWidth);
 ui->height->setValue(fixedHeight);

 connect(ui->fontComboBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(preview()));
 connect(ui->fontSizeField, SIGNAL(editTextChanged(QString)), this, SLOT(preview()));
 connect(ui->fontSizeField, SIGNAL(currentIndexChanged(int)), this, SLOT(preview()));
 connect(ui->bold, SIGNAL(toggled(bool)), this, SLOT(preview()));
 connect(ui->italic, SIGNAL(toggled(bool)), this, SLOT(preview()));
 connect(ui->_justificationCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(preview()));
 connect (ui->fontColor, SIGNAL(currentIndexChanged(int)), this, SLOT(preview()));
 connect (ui->backgroundColor, SIGNAL(currentIndexChanged(int)), this, SLOT(preview()));
 connect(ui->textField, SIGNAL(textEdited(QString)), this, SLOT(preview()));
 connect(ui->borderColorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(preview()));
 connect(ui->borderSize, SIGNAL(valueChanged(int)), this, SLOT(preview()));
 connect(ui->marginSize, SIGNAL(valueChanged(int)), this, SLOT(preview()));

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
void PositionablePropertiesUtil::fontApply()
{
 pop->setFont(ui->fontComboBox->font());
 pop->setFontSize(ui->fontSizeField->currentText().toInt());
 if (ui->bold->isChecked()) pop->setFontWeight(QFont::Bold);
 else pop->setFontStyle(QFont::Normal);
 if (ui->italic->isChecked()) pop->setFontStyle(QFont::StyleItalic);
 else pop->setFontStyle(QFont::StyleNormal);
 QColor desiredColor = QColor(Qt::black);
//    try {
 QString selectedColor = _fontcolors[ui->fontColor->currentIndex()];
            //Field f = Color.class.getField(((selectedColor).toUpperCase()).replaceAll(" ", "_"));
 desiredColor = _colors.at(ui->fontColor->currentIndex());
//      }
//      catch (NoSuchFieldException ce) {
//        desiredColor = Color.black;
//      } catch (SecurityException ce) {
//        desiredColor = Color.black;
//      } catch (IllegalAccessException ce) {
//        desiredColor = Color.black;
//      }

    //if (_parent instanceof SensorIcon) {
 if(qobject_cast<SensorIcon*>((QObject*)pop->_parent) != NULL)
 {
  SensorIcon* si = (SensorIcon*) pop->_parent;
  if (si->isIcon())
  {
   PositionableLabel* pp = (PositionableLabel*)pop->_parent;
   pp->setText(txtList->at(0).getText());
   pop->setForeground(txtList->at(0).getForeground());
   pop->setBackgroundColor(txtList->at(0).getBackground());
  }
  else
  {
   si->setActiveText(txtList->at(0).getText());
   si->setTextActive(txtList->at(0).getForeground());
   si->setBackgroundActive(txtList->at(0).getBackground());

   si->setInactiveText(txtList->at(1).getText());
   si->setTextInActive(txtList->at(1).getForeground());
   si->setBackgroundInActive(txtList->at(1).getBackground());

   si->setUnknownText(txtList->at(2).getText());
   si->setTextUnknown(txtList->at(2).getForeground());
   si->setBackgroundUnknown(txtList->at(2).getBackground());

   si->setInconsistentText(txtList->at(3).getText());
   si->setTextInconsistent(txtList->at(3).getForeground());
   si->setBackgroundInconsistent(txtList->at(3).getBackground());
  }
 }
 else
 {
  PositionableLabel* pp = (PositionableLabel*)pop->_parent;
  pp->setText(txtList->at(0).getText());
  pop->setForeground(txtList->at(0).getForeground());
  pop->setBackgroundColor(txtList->at(0).getBackground());
 }

 desiredColor = //colorFromComboBox(borderColorCombo, NULL);
         _colors.at(ui->borderColorCombo->currentIndex());
 pop->setBorderColor(desiredColor);

 pop->setBorderSize(ui->borderSize->value());

 pop->setMargin(ui->marginSize->value());
 ((Positionable*)((SensorIcon*)pop->_parent))->setLocation(ui->xPosition->value(), ui->yPosition->value());
 pop->setFixedWidth(ui->width->value());
 pop->setFixedHeight(ui->height->value());
 switch(ui->_justificationCombo->currentIndex())
 {
  case 0 :    pop->setJustification(0x00);
                    break;
  case 1 :    pop->setJustification(0x02);
                    break;
  case 2 :    pop->setJustification(0x04);
                    break;
 }
 if(qobject_cast<MemoryIcon*>((QObject*)pop->_parent))
 {
  MemoryIcon* pm = (MemoryIcon*) _parent;
//  xPos = pm->getOriginalX();
//  yPos = pm->getOriginalY();
  pm->setOriginalLocation(ui->xPosition->value(),ui->yPosition->value());
 }
 else
 {
//  xPos = ((PositionableLabel*)pop->_parent)->getX();
//  yPos = ((PositionableLabel*)pop->_parent)->getY();
  ((Positionable*)pop->_parent)->setLocation(ui->xPosition->value(),ui->yPosition->value());
 }
 ((PositionableLabel*)pop->_parent)->_editor->addToTarget((Positionable*)pop->_parent);
}

/*private*/ void PositionablePropertiesUtil::undoChanges()
{
 if(pop == nullptr)
  return;
 //if (_parent instanceof SensorIcon) {
 if(qobject_cast<SensorIcon*>((QObject*)pop->_parent)!= NULL)
 {
  SensorIcon* si = (SensorIcon*) pop->_parent;
  if (si->isIcon())
  {
   PositionableLabel* pp = (PositionableLabel*)pop->_parent;
   pp->setText(txtList->at(0).getOrigText());
   pop->setForeground(txtList->at(0).getOrigForeground());
   pop->setBackgroundColor(txtList->at(0).getOrigBackground());
  }
  else
  {
   si->setActiveText(txtList->at(0).getOrigText());
   si->setTextActive(txtList->at(0).getOrigForeground());
   si->setBackgroundActive(txtList->at(0).getOrigBackground());

   si->setInactiveText(txtList->at(1).getOrigText());
   si->setTextInActive(txtList->at(1).getOrigForeground());
   si->setBackgroundInActive(txtList->at(1).getOrigBackground());

   si->setUnknownText(txtList->at(2).getOrigText());
   si->setTextUnknown(txtList->at(2).getOrigForeground());
   si->setBackgroundUnknown(txtList->at(2).getOrigBackground());

   si->setInconsistentText(txtList->at(3).getOrigText());
   si->setTextInconsistent(txtList->at(3).getOrigForeground());
   si->setBackgroundInconsistent(txtList->at(3).getOrigBackground());
  }
 }
 else
 {
  PositionableLabel* pp = (PositionableLabel*)pop->_parent;
  pp->setText(txtList->at(0).getOrigText());
  pop->setForeground(txtList->at(0).getOrigForeground());
  pop->setBackgroundColor(txtList->at(0).getOrigBackground());
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
 if(qobject_cast<MemoryIcon*>((QObject*)pop->_parent))
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
 txtList = new QList<TextDetails>();

 //if (_parent instanceof SensorIcon) {
 if(dynamic_cast<SensorIcon*>(_parent)!= NULL)
 {
  SensorIcon* si = (SensorIcon*) _parent;
  if (si->isIcon())
  {
   txtList->append( TextDetails("Text", pop->getText(), pop->getForeground(), si->getBackground()));
  }
  else
  {
   txtList->append( TextDetails("Active", si->getActiveText(), si->getTextActive(), si->getBackgroundActive()));
   txtList->append( TextDetails("InActive", si->getInactiveText(), si->getTextInActive(), si->getBackgroundInActive()));
   txtList->append( TextDetails("Unknown", si->getUnknownText(), si->getTextUnknown(), si->getBackgroundUnknown()));
   txtList->append( TextDetails("Inconsistent", si->getInconsistentText(), si->getTextInconsistent(), si->getBackgroundInconsistent()));
  }
 }
 else
 {
  txtList->append( TextDetails("Text", pop->getText(), pop->getForeground(), ((PositionableLabel*)pop->_parent)->getBackground()));
 }

 fixedWidth = pop->getFixedWidth();
 fixedHeight = pop->getFixedHeight();
 marginSize = pop->getMargin();
 borderSize = pop->getBorderSize();
 justification = pop->getJustification();
 fontStyle = pop->getFontStyle();
 fontSize = pop->getFontSize();
 if ( (QFont::Bold & fontStyle) == QFont::Bold ) ui->bold->setChecked(true);
 if ( (QFont::StyleItalic & fontStyle) == QFont::StyleItalic ) ui->italic->setChecked(true);
 if (((SensorIcon*)pop->_parent)->isOpaque())
        defaultBackground = ((SensorIcon*)pop->_parent)->getBackground();
 defaultForeground = pop->getForeground();
 defaultBorderColor = pop->getBorderColor();
 //if (_parent instanceof MemoryIcon){
 if(qobject_cast<MemoryIcon*>((QObject*)_parent)!= NULL)
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
void PositionablePropertiesUtil::preview()
{
 QBrush brBkgnd;
 int i = ui->backgroundColor->currentIndex();
 if(i < 0) return;
 if(_colors.at(i).isValid())
   brBkgnd = QBrush(_colors.at(ui->backgroundColor->currentIndex()),Qt::SolidPattern);
 else
   brBkgnd = QBrush(Qt::transparent, Qt::SolidPattern);
 int pointSize = ui->fontSizeField->currentText().toInt();
 int style = QFont::StyleNormal;
 //if(ui->italic->isChecked()) style = QFont::StyleItalic;
 if(ui->bold->isChecked()) style = QFont::Bold;
 QFont f = QFont(ui->fontComboBox->currentFont().family(),pointSize,style,ui->italic->isChecked());
 // Start with a minimal rectangle.
 QSize resultSize = QSize(1,1);
 QImage* resultImage = new QImage(resultSize,QImage::Format_ARGB32_Premultiplied);
 QRect r = QRect(resultImage->rect());

 QPainter painter(resultImage);
 painter.setFont(f);

 QRect eRect =painter.boundingRect(r, Qt::AlignCenter, ui->textField->text());
 painter.end();

 // create a new rect of the size required by the text + borders and margins.
 QRect newRect = QRect(0,0, eRect.width()+ ui->borderSize->value()*2 + ui->marginSize->value()*2, eRect.height()+ui->borderSize->value()*2 + ui->marginSize->value()*2);

 resultImage = new QImage(newRect.width(), newRect.height(),QImage::Format_ARGB32_Premultiplied);
 QPainter painter2(resultImage);
 painter2.setFont(f);
 painter2.fillRect(newRect, brBkgnd);
 //QRectF bRect = painter2.boundingRect(newRect, Qt::AlignCenter, ui->textField->text()); // bounding rectangle of text
    //bRect.adjust(0, -3.0, 0, 0);
 QRect bRect = QRect(0,0, newRect.width()-ui->borderSize->value()+1, newRect.height()-ui->borderSize->value()+1);
 //painter2.fillRect(bRect, brBkgnd);
 painter2.setPen(_colors.at(ui->fontColor->currentIndex()));
 int align;
 switch(ui->_justificationCombo->currentIndex())
 {
  case 0:
   align = Qt::AlignLeft | Qt::AlignVCenter;
   break;
  case 1:
   align = Qt::AlignRight | Qt::AlignVCenter;
   break;
  case 2:
  default:
   align = Qt::AlignCenter;
 }
 painter2.drawText(newRect, align, ui->textField->text());
 if(ui->borderColorCombo->currentText() != "None" && ui->borderSize->value() > 0)
 {
  QBrush borderBrush(_colors.at(ui->borderColorCombo->currentIndex()));
  QPen borderPen(borderBrush, ui->borderSize->value());
  painter2.setPen(borderPen);
  painter2.drawRect(bRect);
 }
 painter2.end();
 QIcon icon = QIcon(QPixmap::fromImage(*resultImage));
 ui->tmp->setPixmap(QPixmap::fromImage(*resultImage));

 //resultImage->save(QDir::homePath()+ "/testtext.png","PNG");

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
 ui->textField->setText(txtList->at(0).getText());
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

#if 0 // TODO
/*public*/ void PositionablePropertiesUtil::display(){

    propertiesPanel = new JTabbedPane();
    getCurrentValues();
    JPanel* exampleHolder = new JPanel();
    //example = new JLabel(text);

    for(int i = 0; i<txtList->size(); i++){
        JPanel* p = new JPanel();
        p.setBorder(BorderFactory.createTitledBorder(txtList.get(i).getDescription()));
        p.add(txtList.get(i).getLabel());
        exampleHolder.add(p);
    }
    //exampleHolder.add(example);
    JPanel* tmp = new JPanel();

    JButton cancel = new JButton("Cancel");
    cancel.addActionListener( new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                undoChanges();
                mFrame.dispose();
            }
        });

    tmp.setLayout(new BoxLayout(tmp, BoxLayout.Y_AXIS));
    tmp.add(propertiesPanel);
    tmp.add(detailpanel);
    tmp.add(exampleHolder);
    textPanel();
    editText();
    borderPanel();
    sizePosition();
    JPanel* _buttonArea = new JPanel();
    _buttonArea.add(cancel);

    JButton applyButton = new JButton("Apply");
    _buttonArea.add(applyButton);
    applyButton.addActionListener(new ActionListener() {
    public void actionPerformed(ActionEvent e) {
        fontApply();
    }
    });
    JButton okButton = new JButton("Okay");
    _buttonArea.add(okButton);
    okButton.addActionListener(new ActionListener() {
    public void actionPerformed(ActionEvent e) {
        fontApply();
        mFrame.dispose();
    }
    });
    tmp.add(_buttonArea);
    exampleHolder.setBackground(_parent.getParent().getBackground());
    mFrame = new JFrame(_parent.getNameString());
    mFrame.add(tmp);
    mFrame.pack();
    mFrame.setVisible(true);
    preview();
}

JComponent _textPanel;
//JLabel example;

ImageIcon[] images;
String[] _fontcolors = {"Black", "Dark Gray", "Gray", "Light Gray", "White", "Red", "Orange", "Yellow", "Green", "Blue", "Magenta"};
String[] _backgroundcolors;
JComboBox fontColor;
JComboBox backgroundColor;
JTextField fontSizeField;

String[] _justification = {"Left", "Right", "Center"};
JComboBox _justificationCombo;

void textPanel(){
    _textPanel = new JPanel();
    _textPanel.setLayout(new BoxLayout(_textPanel, BoxLayout.Y_AXIS));
    JPanel* fontColorPanel = new JPanel();
    fontColorPanel.add(new JLabel("Font Color"));

    JPanel* backgroundColorPanel = new JPanel();
    backgroundColorPanel.add(new JLabel("Background Color"));
    Color defaultLabelBackground=backgroundColorPanel.getBackground();
    _backgroundcolors = new String[_fontcolors.length + 1];
    for (int i = 0;i < _fontcolors.length; i++){
        _backgroundcolors[i] = _fontcolors[i];
    }
    _backgroundcolors[_backgroundcolors.length-1] = "None";

    Integer[] intArray = new Integer[_backgroundcolors.length];
    images = new ImageIcon[_backgroundcolors.length];
    Color desiredColor = Color.black;
    int backCurrentColor = _backgroundcolors.length-1;
    for (int i = 0; i < _backgroundcolors.length; i++) {
        intArray[i] = Integer.valueOf(i);
          try {
            // try to get a color by name using reflection
            Field f = Color.class.getField((_backgroundcolors[i].toUpperCase()).replaceAll(" ", "_"));
            desiredColor = (Color) f.get(null);
          } catch (NoSuchFieldException ce) {
            //Can be considered normal if background is set None
            desiredColor = null;
          } catch (SecurityException ce) {
            //Can be considered normal if background is set None
            desiredColor = null;
          } catch (IllegalAccessException ce) {
            //Can be considered normal if background is set None
            desiredColor = null;
          }
        if (desiredColor!=null){
            images[i] = getColourIcon(desiredColor);
            if (desiredColor.equals(defaultBackground))
                backCurrentColor = i;
        }
        else{
            images[i] = getColourIcon(defaultLabelBackground);
            images[i].setDescription(_backgroundcolors[i]);
        }
        if (images[i] != null) {
            images[i].setDescription(_backgroundcolors[i]);
        }
    }
    backgroundColor = new JComboBox(intArray);
    backgroundColor.setRenderer(new ColorComboBoxRenderer());
    backgroundColor.setMaximumRowCount(5);
    backgroundColor.setSelectedIndex(backCurrentColor);
    backgroundColor.addActionListener(PreviewActionListener);
    backgroundColorPanel.add(backgroundColor);
    int fontCurrentColor = 0;
    for (int i = 0; i < _fontcolors.length; i++) {

        intArray[i] = Integer.valueOf(i);
        try {
            Field f = Color.class.getField((_fontcolors[i].toUpperCase()).replaceAll(" ", "_"));
            desiredColor = (Color) f.get(null);
        } catch (Exception ce) {
            log.error("Unable to get font colour from field " + ce);
        }
        if (desiredColor!=null && desiredColor.equals(defaultForeground))
            fontCurrentColor = i;
    }

    fontColor = new JComboBox(intArray);
    fontColor.setRenderer(new ColorComboBoxRenderer());
    fontColor.setMaximumRowCount(5);
    fontColor.setSelectedIndex(fontCurrentColor);
    fontColor.addActionListener(PreviewActionListener);
    fontColorPanel.add(fontColor);

    JPanel* fontSizePanel = new JPanel();
    fontSizePanel.setLayout(new BoxLayout(fontSizePanel, BoxLayout.Y_AXIS));
    fontSizeChoice = new List(6);
    int currentFontSize=0;
    for (int i = 0; i < fontSizes.length; i++){
       fontSizeChoice.add(fontSizes[i]);
       if (fontSizes[i].equals(""+fontSize)){
        currentFontSize=i;
       }
    }

    fontSizeChoice.select(currentFontSize);

    JPanel* FontPanel = new JPanel();
    fontSizeField= new JTextField(""+fontSize, fontSizeChoice.getWidth());
    fontSizeField.addKeyListener(PreviewKeyActionListener);
    fontSizePanel.add(fontSizeField);
    fontSizePanel.add(fontSizeChoice);
    FontPanel.add(fontSizePanel);

    JPanel* Style = new JPanel();
    Style.setLayout(new BoxLayout(Style, BoxLayout.Y_AXIS));
    Style.add(bold);
    Style.add(italic);
    FontPanel.add(Style);
    _textPanel.add(FontPanel);

    JPanel* ColorPanel = new JPanel();
    ColorPanel.setLayout(new BoxLayout(ColorPanel, BoxLayout.Y_AXIS));
    //ColorPanel.add(fontColorPanel);
    //ColorPanel.add(backgroundColorPanel);
    _textPanel.add(ColorPanel);

    JPanel* justificationPanel = new JPanel();
    _justificationCombo = new JComboBox(_justification);

    justificationPanel.add(new JLabel("Justification"));
    justificationPanel.add(_justificationCombo);
    _textPanel.add(justificationPanel);

    _justificationCombo.addActionListener(PreviewActionListener);
    bold.addActionListener(PreviewActionListener);
    italic.addActionListener(PreviewActionListener);
    //fontSizeChoice.addActionListener(PreviewActionListener);
    fontSizeChoice.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent actionEvent) {
            fontSizeField.setText(fontSizeChoice.getSelectedItem());
            preview();
        }
    });

    for(int i = 0; i<txtList.size(); i++){
        final int x = i;

        int fontcolor=0;
        int backcolor=_backgroundcolors.length-1;
        for (int j = 0; j < _backgroundcolors.length; j++) {
            try {
            // try to get a color by name using reflection
                Field f = Color.class.getField((_backgroundcolors[j].toUpperCase()).replaceAll(" ", "_"));
                desiredColor = (Color) f.get(null);
              } catch (NoSuchFieldException ce) {
                desiredColor = null;
              } catch (IllegalAccessException ce) {
                desiredColor = null;
              }
            if (desiredColor!=null){
                if (desiredColor.equals(txtList.get(i).getBackground()))
                    backcolor = j;
                if (desiredColor.equals(txtList.get(i).getForeground()))
                    fontcolor = j;
            }
        }

        final JComboBox txtColor = new JComboBox(intArray);
        JPanel* txtPanel = new JPanel();
        //txtPanel.setLayout(new BoxLayout(txtPanel, BoxLayout.Y_AXIS));
        JPanel* p = new JPanel();
        txtColor.setRenderer(new ColorComboBoxRenderer());
        txtColor.setMaximumRowCount(5);

        txtColor.setSelectedIndex(fontcolor);
        txtColor.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent actionEvent) {
            txtList.get(x).setForeground(colorFromComboBox(txtColor, Color.black));
        }
        });
        p.add(new JLabel("Font Color"));
        p.add(txtColor);
        txtPanel.add(p);
        final JComboBox txtBackColor = new JComboBox(intArray);
        txtBackColor.setRenderer(new ColorComboBoxRenderer());
        txtBackColor.setMaximumRowCount(5);
        txtBackColor.setSelectedIndex(backcolor);
        txtBackColor.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent actionEvent) {
            txtList.get(x).setBackground(colorFromComboBox(txtBackColor, null));
            }
        });
        p = new JPanel();
        p.add(new JLabel("Background Color"));
        p.add(txtBackColor);
        txtPanel.setBorder(BorderFactory.createTitledBorder(txtList.get(i).getDescription()));
        txtPanel.add(p);

        _textPanel.add(txtPanel);

    }
    propertiesPanel.addTab("Font", null, _textPanel, "Font");
}
ActionListener PreviewActionListener = new ActionListener() {
  public void actionPerformed(ActionEvent actionEvent) {
    preview();
  }
};

ChangeListener SpinnerChangeListener = new ChangeListener() {
  public void stateChanged(ChangeEvent actionEvent) {
    preview();
  }
};

FocusListener textFieldFocus = new FocusListener(){
    public void focusGained(FocusEvent e) { }

    public void focusLost(FocusEvent e) {
        JTextField tmp = (JTextField) e.getSource();
        if(tmp.getText().equals("")){
            tmp.setText("0");
            preview();
        }
    }
};

KeyListener PreviewKeyActionListener = new KeyListener() {
  public void keyTyped(KeyEvent E) { }
  public void keyPressed(KeyEvent E){ }
  public void keyReleased(KeyEvent E) {
    JTextField tmp = (JTextField) E.getSource();
    if(!tmp.getText().equals("")){
        preview();
    }
  }
};

JComboBox borderColorCombo;
javax.swing.JSpinner borderSizeTextSpin;
javax.swing.JSpinner marginSizeTextSpin;

void borderPanel(){
    Color desiredColor =null;
    JPanel* borderPanel = new JPanel();

    Integer[] intArray = new Integer[_backgroundcolors.length];
    int borderCurrentColor =_backgroundcolors.length-1;
    for (int i = 0; i < (_backgroundcolors.length-1); i++) {
        intArray[i] = Integer.valueOf(i);
        try {
            Field f = Color.class.getField((_fontcolors[i].toUpperCase()).replaceAll(" ", "_"));
            desiredColor = (Color) f.get(null);
        } catch (Exception ce) {
            log.error("Unable to convert the selected font color to a color " + ce);
        }
        if (desiredColor!=null && desiredColor.equals(defaultBorderColor)){
            borderCurrentColor = i;
        }
    }
    //Last colour on the background is none.
    intArray[_backgroundcolors.length-1] = Integer.valueOf(_backgroundcolors.length-1);
    borderColorCombo = new JComboBox(intArray);
    borderColorCombo.setRenderer(new ColorComboBoxRenderer());
    borderColorCombo.setMaximumRowCount(5);
    borderColorCombo.setSelectedIndex(borderCurrentColor);
    borderColorCombo.addActionListener(PreviewActionListener);

    JPanel* borderColorPanel = new JPanel();
    borderColorPanel.add(new JLabel("Border Color"));
    borderColorPanel.add(borderColorCombo);

    JPanel* borderSizePanel = new JPanel();
    borderSizeTextSpin = getSpinner(borderSize, "Border Size");
    borderSizeTextSpin.addChangeListener(SpinnerChangeListener);
    borderSizePanel.add(new JLabel("Border Size"));
    borderSizePanel.add(borderSizeTextSpin);

    JPanel* marginSizePanel = new JPanel();
    marginSizeTextSpin = getSpinner(marginSize, "Margin Size");
    marginSizeTextSpin.addChangeListener(SpinnerChangeListener);

    marginSizePanel.add(new JLabel("Margin Size"));
    marginSizePanel.add(marginSizeTextSpin);

    borderPanel.setLayout(new BoxLayout(borderPanel, BoxLayout.Y_AXIS));
    borderPanel.add(borderColorPanel);
    borderPanel.add(borderSizePanel);
    borderPanel.add(marginSizePanel);

    propertiesPanel.addTab("Border", null, borderPanel, "Border");

}

javax.swing.JSpinner xPositionTextSpin;
javax.swing.JSpinner yPositionTextSpin;
javax.swing.JSpinner widthSizeTextSpin;
javax.swing.JSpinner heightSizeTextSpin;
JCheckBox autoWidth;

void editText(){
    JPanel* editText = new JPanel();
    editText.setLayout(new BoxLayout(editText, BoxLayout.Y_AXIS));
    for(int i = 0; i<txtList.size(); i++){
        final int x = i;
        JPanel* p = new JPanel();
        p.setBorder(BorderFactory.createTitledBorder(txtList.get(i).getDescription()));
        JLabel txt = new JLabel("Text Value ");
        JTextField textField = new JTextField(txtList.get(i).getText(), 20);
        textField.addKeyListener(new KeyListener() {
              public void keyTyped(KeyEvent E) { }
              public void keyPressed(KeyEvent E){ }
              public void keyReleased(KeyEvent E) {
                JTextField tmp = (JTextField) E.getSource();
                txtList.get(x).setText(tmp.getText());
                preview();
              }
            });
        p.add(txt);
        p.add(textField);
        editText.add(p);
    }
    propertiesPanel.addTab("Edit Text", null, editText, "Text");
}

void sizePosition(){

    JPanel* posPanel = new JPanel();

    JPanel* xyPanel = new JPanel();
    xyPanel.setLayout(new BoxLayout(xyPanel, BoxLayout.Y_AXIS));
    JPanel* xPanel = new JPanel();
    JLabel txt = new JLabel("x = ");
    xPositionTextSpin = getSpinner(xPos, "x position");
    xPositionTextSpin.addChangeListener(SpinnerChangeListener);
    xPanel.add(txt);
    xPanel.add(xPositionTextSpin);

    JPanel* yPanel = new JPanel();
    txt = new JLabel("y = ");
    yPositionTextSpin = getSpinner(yPos, "y position");
    yPositionTextSpin.addChangeListener(SpinnerChangeListener);
    yPanel.add(txt);
    yPanel.add(yPositionTextSpin);


    xyPanel.add(xPanel);
    xyPanel.add(yPanel);

    JPanel* sizePanel = new JPanel();
    sizePanel.setLayout(new BoxLayout(sizePanel, BoxLayout.Y_AXIS));
    JPanel* widthPanel = new JPanel();
    widthSizeTextSpin = getSpinner(fixedWidth, "width");
    widthSizeTextSpin.addChangeListener(SpinnerChangeListener);
    /*widthSizeText = new JTextField(""+fixedWidth, 10);
    widthSizeText.addKeyListener(PreviewKeyActionListener);*/
    txt = new JLabel("Width = ");
    widthPanel.add(txt);
    widthPanel.add(widthSizeTextSpin);

    JPanel* heightPanel = new JPanel();
    /*heightSizeText = new JTextField(""+fixedHeight, 10);
    heightSizeText.addKeyListener(PreviewKeyActionListener);*/
    heightSizeTextSpin = getSpinner(fixedHeight, "height");
    heightSizeTextSpin.addChangeListener(SpinnerChangeListener);
    txt = new JLabel("Height = ");
    heightPanel.add(txt);
    heightPanel.add(heightSizeTextSpin);

    sizePanel.add(widthPanel);
    sizePanel.add(heightPanel);


    posPanel.add(xyPanel);
    posPanel.add(sizePanel);
    posPanel.setLayout(new BoxLayout(posPanel, BoxLayout.Y_AXIS));

    propertiesPanel.addTab("Size & Position", null, posPanel, "Size");
}
void fontApply(){
    pop.setFontSize(Integer.parseInt(fontSizeField.getText()));
    if (bold.isSelected()) pop.setFontStyle(Font.BOLD, 0);
    else pop.setFontStyle(0, Font.BOLD);
    if (italic.isSelected()) pop.setFontStyle(Font.ITALIC, 0);
    else pop.setFontStyle(0, Font.ITALIC);
    Color desiredColor = Color.black;
    try {
            String selectedColor = _fontcolors[fontColor.getSelectedIndex()];
            Field f = Color.class.getField(((selectedColor).toUpperCase()).replaceAll(" ", "_"));
            desiredColor = (Color) f.get(null);
      } catch (NoSuchFieldException ce) {
        desiredColor = Color.black;
      } catch (SecurityException ce) {
        desiredColor = Color.black;
      } catch (IllegalAccessException ce) {
        desiredColor = Color.black;
      }

    if (_parent instanceof SensorIcon) {
        SensorIcon si = (SensorIcon) _parent;
        if (si.isIcon()){
            PositionableLabel pp = (PositionableLabel)_parent;
            pp.setText(txtList.get(0).getText());
            pop.setForeground(txtList.get(0).getForeground());
            pop.setBackgroundColor(txtList.get(0).getBackground());
        } else {
            si.setActiveText(txtList.get(0).getText());
            si.setTextActive(txtList.get(0).getForeground());
            si.setBackgroundActive(txtList.get(0).getBackground());

            si.setInactiveText(txtList.get(1).getText());
            si.setTextInActive(txtList.get(1).getForeground());
            si.setBackgroundInActive(txtList.get(1).getBackground());

            si.setUnknownText(txtList.get(2).getText());
            si.setTextUnknown(txtList.get(2).getForeground());
            si.setBackgroundUnknown(txtList.get(2).getBackground());

            si.setInconsistentText(txtList.get(3).getText());
            si.setTextInconsistent(txtList.get(3).getForeground());
            si.setBackgroundInconsistent(txtList.get(3).getBackground());
        }
    } else {
        PositionableLabel pp = (PositionableLabel)_parent;
        pp.setText(txtList.get(0).getText());
        pop.setForeground(txtList.get(0).getForeground());
        pop.setBackgroundColor(txtList.get(0).getBackground());
    }

    desiredColor = colorFromComboBox(borderColorCombo, null);
    pop.setBorderColor(desiredColor);

    pop.setBorderSize(((Number)borderSizeTextSpin.getValue()).intValue());

    pop.setMargin(((Number)marginSizeTextSpin.getValue()).intValue());
    _parent.setLocation(((Number)xPositionTextSpin.getValue()).intValue(), ((Number)yPositionTextSpin.getValue()).intValue());
    pop.setFixedWidth(((Number)widthSizeTextSpin.getValue()).intValue());
    pop.setFixedHeight(((Number)heightSizeTextSpin.getValue()).intValue());
    switch(_justificationCombo.getSelectedIndex()){
        case 0 :    pop.setJustification(0x00);
                    break;
        case 1 :    pop.setJustification(0x02);
                    break;
        case 2 :    pop.setJustification(0x04);
                    break;
    }
}

void cancelButton(){
    mFrame.dispose();
}


void preview(){
    int attrs = Font.PLAIN;
    if (bold.isSelected())
        attrs = Font.BOLD;
    if (italic.isSelected())
        attrs |= Font.ITALIC;

    Font newFont = new Font(_parent.getFont().getName(), attrs,  Integer.parseInt(fontSizeField.getText()));

    Color desiredColor;

    desiredColor = colorFromComboBox(borderColorCombo, null);
    Border borderMargin = BorderFactory.createEmptyBorder(0, 0, 0, 0);
    int margin = ((Number)marginSizeTextSpin.getValue()).intValue();
    Border outlineBorder = BorderFactory.createEmptyBorder(0, 0, 0, 0);
    if(desiredColor!=null) {
        outlineBorder = new LineBorder(desiredColor, ((Number)borderSizeTextSpin.getValue()).intValue());
    } else {
        outlineBorder = BorderFactory.createEmptyBorder(0, 0, 0, 0);
    }
    int hoz=0;
    switch(_justificationCombo.getSelectedIndex()){
        case 0 :    hoz = (0x02);
                    break;
        case 1 :    hoz = (0x04);
                    break;
        case 2 :    hoz = (0x00);
                    break;
    }

    for(int i = 0; i<txtList.size(); i++){
        JLabel tmp = txtList.get(i).getLabel();
        if (tmp.isOpaque()){
            borderMargin = new LineBorder(tmp.getBackground(), margin);
        } else{
            borderMargin = BorderFactory.createEmptyBorder(margin, margin, margin, margin);
        }
        tmp.setFont(newFont);
        tmp.setHorizontalAlignment(hoz);
        tmp.setBorder(new CompoundBorder(outlineBorder, borderMargin));
        tmp.setSize(new Dimension(maxWidth(tmp), maxHeight(tmp)));
        tmp.setPreferredSize(new Dimension(maxWidth(tmp), maxHeight(tmp)));

    }
    mFrame.pack();
}

int maxWidth(JLabel tmp) {
    int max = 0;
    if (((Number)widthSizeTextSpin.getValue()).intValue()!=0) {
        max = ((Number)widthSizeTextSpin.getValue()).intValue();
        max += ((Number)borderSizeTextSpin.getValue()).intValue()*2;
    } else {
        if(tmp.getText().trim().length()>0 ) {
            max = tmp.getFontMetrics(tmp.getFont()).stringWidth(tmp.getText());
        }
        if (pop!=null) {
            max += ((Number)marginSizeTextSpin.getValue()).intValue()*2;
            max += ((Number)borderSizeTextSpin.getValue()).intValue()*2;
        }
    }
    return max;
}

public int maxHeight(JLabel tmp) {
    int max = 0;
    if (((Number)heightSizeTextSpin.getValue()).intValue()!=0) {
        max = ((Number)heightSizeTextSpin.getValue()).intValue();
        max += ((Number)borderSizeTextSpin.getValue()).intValue()*2;
    } else {
        if(tmp.getText().trim().length()>0 ) {
            max = tmp.getFontMetrics(tmp.getFont()).getHeight();
        }
        if (pop!=null) {
            max += ((Number)marginSizeTextSpin.getValue()).intValue()*2;
            max += ((Number)borderSizeTextSpin.getValue()).intValue()*2;
        }
    }

    return max;
}
PositionablePopupUtil pop;

private void undoChanges(){
    if (_parent instanceof SensorIcon) {
        SensorIcon si = (SensorIcon) _parent;
        if (si.isIcon()){
            PositionableLabel pp = (PositionableLabel)_parent;
            pp.setText(txtList.get(0).getOrigText());
            pop.setForeground(txtList.get(0).getOrigForeground());
            pop.setBackgroundColor(txtList.get(0).getOrigBackground());
        } else {
            si.setActiveText(txtList.get(0).getOrigText());
            si.setTextActive(txtList.get(0).getOrigForeground());
            si.setBackgroundActive(txtList.get(0).getOrigBackground());

            si.setInactiveText(txtList.get(1).getOrigText());
            si.setTextInActive(txtList.get(1).getOrigForeground());
            si.setBackgroundInActive(txtList.get(1).getOrigBackground());

            si.setUnknownText(txtList.get(2).getOrigText());
            si.setTextUnknown(txtList.get(2).getOrigForeground());
            si.setBackgroundUnknown(txtList.get(2).getOrigBackground());

            si.setInconsistentText(txtList.get(3).getOrigText());
            si.setTextInconsistent(txtList.get(3).getOrigForeground());
            si.setBackgroundInconsistent(txtList.get(3).getOrigBackground());
        }
    } else {
        PositionableLabel pp = (PositionableLabel)_parent;
        pp.setText(txtList.get(0).getOrigText());
        pop.setForeground(txtList.get(0).getOrigForeground());
        pop.setBackgroundColor(txtList.get(0).getOrigBackground());
    }
    pop.setJustification(justification);
    pop.setFixedWidth(fixedWidth);
    pop.setFixedHeight(fixedHeight);
    pop.setMargin(marginSize);
    pop.setBorderSize(borderSize);
    pop.setFontStyle(0, fontStyle);
    pop.setFontSize(fontSize);
    pop.setBorderColor(defaultBorderColor);
    _parent.setLocation(xPos, yPos);
}

private void getCurrentValues(){
    pop = _parent.getPopupUtility();
    txtList = new ArrayList<eetails>();

    if (_parent instanceof SensorIcon) {
        SensorIcon si = (SensorIcon) _parent;
        if (si.isIcon()){
            txtList.add(new TextDetails("Text", pop.getText(), pop.getForeground(), _parent.getBackground()));
        } else {
            txtList.add(new TextDetails("Active", si.getActiveText(), si.getTextActive(), si.getBackgroundActive()));
            txtList.add(new TextDetails("InActive", si.getInactiveText(), si.getTextInActive(), si.getBackgroundInActive()));
            txtList.add(new TextDetails("Unknown", si.getUnknownText(), si.getTextUnknown(), si.getBackgroundUnknown()));
            txtList.add(new TextDetails("Inconsistent", si.getInconsistentText(), si.getTextInconsistent(), si.getBackgroundInconsistent()));
        }
    } else {
        txtList.add(new TextDetails("Text", pop.getText(), pop.getForeground(), _parent.getBackground()));
    }

    fixedWidth = pop.getFixedWidth();
    fixedHeight = pop.getFixedHeight();
    marginSize = pop.getMargin();
    borderSize = pop.getBorderSize();
    justification = pop.getJustification();
    fontStyle = pop.getFontStyle();
    fontSize = pop.getFontSize();
    if ( (Font.BOLD & fontStyle) == Font.BOLD ) bold.setSelected(true);
    if ( (Font.ITALIC & fontStyle) == Font.ITALIC ) italic.setSelected(true);
    if (_parent.isOpaque())
        defaultBackground = _parent.getBackground();
    defaultForeground = pop.getForeground();
    defaultBorderColor = pop.getBorderColor();
    if (_parent instanceof MemoryIcon){
        MemoryIcon pm = (MemoryIcon) _parent;
        xPos = pm.getOriginalX();
        yPos = pm.getOriginalY();
    } else {
        xPos = _parent.getX();
        yPos = _parent.getY();
    }
}
private int fontStyle;
private Color defaultForeground;
private Color defaultBackground;
private Color defaultBorderColor;
private int fixedWidth=0;
private int fixedHeight=0;
private int marginSize=0;
private int borderSize=0;
private int justification;
private int fontSize;
private int xPos;
private int yPos;

private ArrayList <TextDetails> txtList = null;

private JCheckBox italic = new JCheckBox("Italic", false);
private JCheckBox bold = new JCheckBox("Bold", false);

protected List fontSizeChoice;

protected String fontSizes[] = { "6", "8", "10", "11", "12", "14", "16",
"20", "24", "28", "32", "36"};

Color colorFromComboBox(JComboBox select, Color defaultColor){
    Color desiredColor = defaultColor;
    try {
            // try to get a color by name using reflection
            String selectedColor = _backgroundcolors[select.getSelectedIndex()];
            Field f = Color.class.getField((selectedColor.toUpperCase()).replaceAll(" ", "_"));
            desiredColor = (Color) f.get(null);
    } catch (NoSuchFieldException ce) {
        desiredColor = defaultColor;
    } catch (SecurityException ce) {
        desiredColor = defaultColor;
    } catch (IllegalAccessException ce) {
        desiredColor = defaultColor;
    }
    return desiredColor;
}

ImageIcon getColourIcon(Color color){

    int ICON_DIMENSION = 10;
     BufferedImage image = new BufferedImage(ICON_DIMENSION, ICON_DIMENSION,
      BufferedImage.TYPE_INT_RGB);

    Graphics g = image.getGraphics();
   // set completely transparent
    g.setColor(color);
    g.fillRect(0,0, ICON_DIMENSION,ICON_DIMENSION);

    ImageIcon icon = new ImageIcon(image);
    return icon;

}

javax.swing.JSpinner getSpinner(int value, String tooltip){
    SpinnerNumberModel model = new SpinnerNumberModel(0,0,1000,1);
    javax.swing.JSpinner spinX = new javax.swing.JSpinner(model);
    spinX.setValue(value);
    spinX.setToolTipText(tooltip);
    spinX.setMaximumSize(new Dimension(
            spinX.getMaximumSize().width, spinX.getPreferredSize().height));
    return spinX;
}

class ColorComboBoxRenderer extends JLabel
                       implements ListCellRenderer {

    public ColorComboBoxRenderer() {
        setOpaque(true);
        setHorizontalAlignment(LEFT);
        setVerticalAlignment(CENTER);
    }

    public Component getListCellRendererComponent(JList list, Object value, int index,
        boolean isSelected, boolean cellHasFocus) {
        if (value==null) return this;
        int selectedIndex = ((Integer)value).intValue();
        ImageIcon icon = images[selectedIndex];
        String colorString = _backgroundcolors[selectedIndex];

        setIcon(icon);
        setText(colorString);
        return this;
    }
}

static class TextDetails {
    TextDetails(String desc, String txt, Color fore, Color back){
        if (txt == null)
            text = "";
        else
            text = txt;
        description = desc;
        example = new JLabel(text);
        setForeground(fore);
        setBackground(back);
        origForeground = fore;
        origBackground = back;
        origText = txt;
    }

    Color foreground;
    Color background;
    Color origForeground;
    Color origBackground;
    String origText;
    String text;
    JLabel example;
    String description;

    Color getForeground(){ return foreground; }

    Color getBackground() { return background; }

    String getText() { return text; }

    Color getOrigForeground(){ return origForeground; }

    Color getOrigBackground() { return origBackground; }

    String getOrigText() { return origText; }


    String getDescription() { return description; }
    void setForeground(Color fore) {
        foreground = fore;
        example.setForeground(fore);
    }

    void setBackground(Color back) {
        background = back;
        if (back!=null) {
            example.setOpaque(true);
            example.setBackground(back);
        } else
            example.setOpaque(false);
    }

    void setText(String txt) {
        text=txt;
        example.setText(txt);
    }

    JLabel* getLabel() { return example; }

}
#endif
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PositionablePropertiesUtil.class.getName());
//}
