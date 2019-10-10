#ifndef POSITIONABLEPROPERTIESUTIL_H
#define POSITIONABLEPROPERTIESUTIL_H

#include <QDialog>
#include "positionablepopuputil.h"
#include <QLabel>

class JTabbedPane;
class TextDetails
{
 public:
  TextDetails(QString desc, QString txt, QColor fore, QColor back)
  {
    text = txt;
    description = desc;
    example = new QLabel(text);
    setForeground(fore);
    setBackground(back);
    origForeground = fore;
    origBackground = back;
    origText = txt;
   }
  QString getOrigText()const  {return origText;}
  QString getText()const  {return text;}
  void setForeground(QColor fore) {origForeground = fore;}
  void setBackground(QColor back) {origBackground = back;}
  QColor getForeground() const {return foreground;}
  QColor getBackground() const {return background;}
  QColor getOrigForeground() const {return origForeground;}
  QColor getOrigBackground() const {return origBackground;}


private:
  QString text;
  QString description;
  QLabel* example;
  QColor foreground;
  QColor background;
  QColor origForeground;
  QColor origBackground;
  QString origText;
  /*private*/ void getCurrentValues();
};

namespace Ui {
class PositionablePropertiesUtil;
}

class PositionablePropertiesUtil : public QDialog
{
    Q_OBJECT
public:
    //explicit PositionablePropertiesUtil(QObject *parent = 0);
    PositionablePropertiesUtil(Positionable *p, QWidget *parent = 0);
    void setCurrentValues();
    const QIcon* getColourIcon(QColor color);
    QColor colorStringToColor(QString sColor);
    /*public*/ void display();

signals:
    
public slots:
 void on_cancel_clicked();
 void on_applyButton_clicked();
 void on_okButton_clicked();

private:
 Ui::PositionablePropertiesUtil *ui;
 PositionablePopupUtil* pop = nullptr;
 void fontApply();
 QList<TextDetails>* txtList = nullptr;
 /*private*/ int fontStyle;
 /*private*/ QColor defaultForeground;
 /*private*/ QColor defaultBackground;
 /*private*/ QColor defaultBorderColor;
 /*private*/ int fixedWidth;//=0;
 /*private*/ int fixedHeight;//=0;
 /*private*/ int marginSize;//=0;
 /*private*/ int borderSize;//=0;
 /*private*/ int justification;
 /*private*/ int fontSize;
 /*private*/ int xPos;
 /*private*/ int yPos;
 /*private*/ void undoChanges();
 void closeEvent(QCloseEvent *);
 /*private*/ void getCurrentValues();
 JTabbedPane* propertiesPanel;

private slots:
 void preview();

protected:
 Positionable* _parent;
 QStringList _fontcolors;
 QList<QColor> _colors;
 QStringList _backgroundcolors;
 QStringList _justification;
 QStringList _bordercolors;
 /*protected*/ QStringList fontSizeChoice;

 /*protected*/ QStringList fontSizes;// = { "6", "8", "10", "11", "12", "14", "16", "20", "24", "28", "32", "36"};
};

#endif // POSITIONABLEPROPERTIESUTIL_H
