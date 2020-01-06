#ifndef POSITIONABLEPROPERTIESUTIL_H
#define POSITIONABLEPROPERTIESUTIL_H

#include <QDialog>
#include "positionablepopuputil.h"
#include "jlabel.h"
#include "changelistener.h"
#include "jcolorchooser.h"

class PreviewChangeListener;
class Logger;
class JLabel;
class JColorChooser;
class JSpinner;
class JPanel;
class JFrame;
class QCheckBox;
class QGroupBox;
class JComboBox;
class JList;
class JTextField;
class JTabbedPane;
class TextDetails
{
 public:
  TextDetails(QString desc, QString txt, QColor fore, QColor back)
  {
   if (txt.isNull()) {
       text = "";
       // contents of icon state labels <active> are entered in SensorIcon.java
   } else {
       text = txt;
   }
    description = desc;
    example = new JLabel(text);
    f= example->font();
    pointSize = f.pointSize();
    setForeground(fore);
    setBackground(back);
    origForeground = fore;
    origBackground = back;
    origText = txt;
   }
  QString getOrigText() const {return origText;}
  QString getText() const {return text;}
  QString getDescription() const {return description;}
  void setForeground(QColor fore)
  {
      foreground = fore;
      //example->setForeground(fore);
      setAttributes();
  }

  void setBackground(QColor back) {
      background = back;
//      if (back.isValid()) {
//          example->setOpaque(true);
//          example->setBackground(back);
//      } else {
//          example->setOpaque(false);
//      }
      setAttributes();
  }
  void setText(QString txt) {
      text = txt;
      example->setText(txt);
      setAttributes();
  }
  void setFont(QFont f) {this->f = f;}
  void setBorderSize(int w) {borderSize = w;}
  void setBorderColor(QColor c) {this->borderColor = c;}
  QColor getForeground() const {return foreground;}
  QColor getBackground() const {return background;}
  QColor getOrigForeground() const {return origForeground;}
  QColor getOrigBackground()const  {return origBackground;}
  JLabel* getLabel() const {return example;}


private:
  QString text;
  QString description;
  JLabel* example;
  QColor foreground;
  QColor background;
  QColor origForeground;
  QColor origBackground;
  QString origText;
  int borderSize;
  QColor borderColor;
  int pointSize;
  int margin;
  QFont f;
  /*private*/ void setAttributes()
  {
   QString styleSheet = "QLabel {";
   styleSheet.append(QString("background-color: rgba(%1,%2,%3,%4); color: rgb(%5,%6,%7);").arg(background.red()).arg(background.green()).arg(background.blue()).arg(background.alpha()).arg(foreground.red()).arg(foreground.green()).arg(foreground.blue()));
   if(borderSize)
   {
    styleSheet.append(QString("border-style: outset; border-width: %1px;").arg(borderSize));
    styleSheet.append(QString("border-color: rgb(%1,%2,%3);").arg(borderColor.red()).arg(borderColor.green()).arg(borderColor.blue()));
   }
   else
    styleSheet.append("border: none;");
   QStringList styles = QStringList() << "plain" << "bold" <<  "Italic" << "Bold/Italic";
   styleSheet.append(QString("font-size: %1pt;").arg(pointSize));

   styleSheet.append(QString("margin: %1px;").arg(margin));

   styleSheet.append("}");
  // f.setPointSize(f.pointSize()+1);
  // JLabel:: setFont(f);
  // f.setPointSize(f.pointSize()-1);
   example->setFont(f);
   example->setStyleSheet(styleSheet);
  }
  friend class PositionablePropertiesUtil;
};

class PositionablePropertiesUtil : public QDialog
{
    Q_OBJECT
public:
    //explicit PositionablePropertiesUtil(QObject *parent = 0);
    PositionablePropertiesUtil(Positionable *p, QWidget *parent = 0);
    /*public*/ void display();
    /*public*/ int maxHeight(JLabel* tmp);

signals:
    
public slots:
    void on_cancel_clicked();
    void fontApply();
    void on_okButton_clicked();

private:
    JFrame* mFrame = nullptr;
    JPanel* detailpanel;// = new JPanel();
    JTabbedPane* propertiesPanel;
    /*private*/ void getCurrentValues();
    Positionable* _parent;
    QWidget* _textPanel;
    JTextField* fontSizeField;
    /*private*/ void undoChanges();
    QStringList _justification;// = QStringList() << tr("left"), Bundle.getMessage("right"), Bundle.getMessage("center")};
    JComboBox* _justificationCombo;
    /*private*/ JColorChooser* borderColorChooser = nullptr;
    JSpinner* borderSizeTextSpin;
    JSpinner* marginSizeTextSpin;
    void textPanel();
    void borderPanel();
    void editText();
    void sizePosition();
    PositionablePopupUtil* pop;
    int maxWidth(JLabel* tmp);
    /*private*/ int fontStyle;
    /*private*/ QColor defaultForeground;// = Color.black;
    /*private*/ QColor defaultBackground;
    /*private*/ QColor defaultBorderColor;// = Color.black;
    /*private*/ int fixedWidth = 0;
    /*private*/ int fixedHeight = 0;
    /*private*/ int marginSize = 0;
    /*private*/ int borderSize = 0;
    /*private*/ int justification;
    /*private*/ int fontSize;
    /*private*/ int xPos;
    /*private*/ int yPos;
    /*private*/ QList<TextDetails*> txtList;// = null;

    /*private*/ /*final*/ QCheckBox* italic;// = new QCheckBox(tr("Italic"), false);
    /*private*/ /*final*/ QCheckBox* bold;// = new QCheckBox(tr("Bold"), false);
    JSpinner* getSpinner(int value, QString tooltip);
    static Logger* log;
    void closeEvent(QCloseEvent *e);
    PreviewChangeListener* previewChangeListener;
    JSpinner* xPositionTextSpin;
    JSpinner* yPositionTextSpin;
    JSpinner* widthSizeTextSpin;
    JSpinner* heightSizeTextSpin;
private slots:
 void preview();
 void on_applyButton_clicked();
 void on_textChanged(QWidget*);
 void on_fontSizeField(QString);
 void on_FontSizeChoice(QModelIndex);
protected:
 /*protected*/ JList* fontSizeChoice;
 /*protected*/ QStringList fontSizes;// = QStringList() << "6", "8", "10", "11", "12", "14", "16",
//     "20", "24", "28", "32", "36"};

 friend class PreviewChangeListener;
 friend class TCChangeListener;
 friend class TCBChangeListener;
};

class PreviewChangeListener : public ChangeListener
{
  Q_OBJECT
  PositionablePropertiesUtil* util;
 public:
  PreviewChangeListener(PositionablePropertiesUtil* util) {this->util = util;}
 public slots:
  void stateChanged(ChangeEvent* e)
  {
   util->preview();
  }
};

class TCChangeListener : public ChangeListener
{
 Q_OBJECT
 int x;
 PositionablePropertiesUtil* util;
 JColorChooser* txtColorChooser;
public:
 TCChangeListener(int x, JColorChooser* txtColorChooser, PositionablePropertiesUtil* util)
 {
  this->x = x;
  this->txtColorChooser = txtColorChooser;
  this->util = util;
 }
public slots:
 void stateChanged(ChangeEvent* /*e*/)
 {
  util->txtList.at(x)->setForeground(txtColorChooser->getColor());
 }
};

class TCBChangeListener : public ChangeListener
{
 Q_OBJECT
 int x;
 PositionablePropertiesUtil* util;
 JColorChooser* txtColorChooser;
public:
 TCBChangeListener(int x, JColorChooser* txtColorChooser, PositionablePropertiesUtil* util)
 {
  this->x = x;
  this->txtColorChooser = txtColorChooser;
  this->util = util;
 }
public slots:
 void stateChanged(ChangeEvent* /*e*/)
 {
  util->txtList.at(x)->setBackground(txtColorChooser->getColor());
 }
};

#endif // POSITIONABLEPROPERTIESUTIL_H
