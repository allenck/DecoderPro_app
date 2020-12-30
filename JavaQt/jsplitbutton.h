#ifndef JSPLITBUTTON_H
#define JSPLITBUTTON_H

#include "jbutton.h"
#include "eventlistenerlist.h"
#include "actionlistener.h"

class EventListenerList;
class BufferedImage;
class SplitButtonActionListener;
class JSplitButton : public JButton
{
 Q_OBJECT
public:
 explicit JSplitButton(QWidget *parent = nullptr);
 /*public*/ JSplitButton(QString text, QIcon icon, QWidget *parent = nullptr);
 /*public*/ JSplitButton(QString text, QWidget *parent = nullptr);
 /*public*/ JSplitButton(QIcon icon, QWidget *parent= nullptr);
 /*public*/ QMenu* getPopupMenu();
 /*public*/ void setPopupMenu(QMenu* popupMenu);
 /*public*/ int getSeparatorSpacing();
 /*public*/ void setSeparatorSpacing(int separatorSpacing);
 /*public*/ bool isAlwaysDropDown();
 /*public*/ void setAlwaysDropDown(bool alwaysDropDown);
 /*public*/ QColor getArrowColor();
 /*public*/ void setArrowColor(QColor arrowColor);
 /*public*/ QColor getDisabledArrowColor();
 /*public*/ void setDisabledArrowColor(QColor disabledArrowColor);
 /*public*/ int getSplitWidth();
 /*public*/ void setSplitWidth(int splitWidth);
 /*public*/ int getArrowSize();
 /*public*/ void setArrowSize(int arrowSize);
 /*public*/ QImage getImage();
 /*public*/ void setImage(QImage image);
 /*public*/ QImage getDisabledImage();
 /*public*/ void setDisabledImage(QImage image);
 /*public*/ void addButtonActionListener(ActionListener* l);
 /*public*/ void addSplitButtonActionListener(SplitButtonActionListener* l);
 /*public*/ void removeSplitButtonActionListener(SplitButtonActionListener* l);
 /*public*/ void removeButtonActionListener(ActionListener *l);

 /*public*/ void mouseMoved(QMouseEvent* e);
 /*public*/ void mouseExited(QMouseEvent* e);

signals:
 void buttonClicked(JActionEvent*);
 void splitButtonClicked(JActionEvent*);

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0);

private:
 /*private*/ int separatorSpacing = 4;
 /*private*/ int splitWidth = 22;
 /*private*/ int arrowSize = 8;
 /*private*/ bool onSplit;
 /*private*/ QRect splitRectangle;
 /*private*/ QMenu* popupMenu = nullptr;
 /*private*/ bool alwaysDropDown;
 /*private*/ QColor arrowColor;// = Color.BLACK;
 /*private*/ QColor disabledArrowColor;// = Color.GRAY;
 /*private*/ QImage image;
 /*private*/ QImage disabledImage;
 void common();
 /*private*/ BufferedImage rotate(BufferedImage img, int angle);
 /*private*/ void fireButtonClicked(JActionEvent* event);
 /*private*/ void fireSplitbuttonClicked(JActionEvent *event);
 EventListenerList listenerList;

protected:
 /*protected*/ SplitButtonActionListener* splitButtonActionListener = nullptr;
 /*protected*/ void paintEvent(QPaintEvent*);
 /*protected*/ void mouseMoveEvent(QMouseEvent *e);

};

#endif // SPLITBUTTON_H
