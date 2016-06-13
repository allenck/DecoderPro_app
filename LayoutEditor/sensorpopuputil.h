#ifndef SENSORPOPUPUTIL_H
#define SENSORPOPUPUTIL_H
#include "positionablepopuputil.h"
#include <QActionGroup>

class ColorMenuAction : public QAction
{
 Q_OBJECT
 public:
 ColorMenuAction(QString name, QColor color, int type, QObject* parent) : QAction(name, parent)
 {
  _type = type;
  _name = name;
  _color = color;
 }

  QString getName() {return _name;}
  int getType(){return _type;}
  QColor getColor() {return _color;}
 private:
  QString _name;
  int _type;
  QColor _color;
};

class SensorPopupUtil : public PositionablePopupUtil
{
    Q_OBJECT
public:
 explicit SensorPopupUtil(Positionable *parent, QObject* textComp);
 /*public*/ void setTextJustificationMenu(QMenu* popup);
 /*public*/ void setTextOrientationMenu(QMenu* popup) ;
 /*public*/ void setFixedTextMenu(QMenu* popup) ;
 /*public*/ void setTextMarginMenu(QMenu* popup);
 /*public*/ void setTextBorderMenu(QMenu* popup);
 /*public*/ void setTextFontMenu(QMenu* popup);
 /*protected*/ void makeColorMenu(QMenu* colorMenu, int type);

signals:
    
public slots:
 void on_colorMenuEntry_selected(ColorMenuAction* act);
private:
 Positionable *parent;
protected:
 /*protected*/ void addColorMenuEntry(QMenu* menu, QActionGroup* colorButtonGroup,
                       /*final*/ QString name, /*final*/ QColor color, /*final*/ int colorType);

    
};

#endif // SENSORPOPUPUTIL_H
