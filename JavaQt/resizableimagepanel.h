#ifndef RESIZABLEIMAGEPANEL_H
#define RESIZABLEIMAGEPANEL_H

#include "component.h"
#include <QImage>


class SwingPropertyChangeSupport;
class Logger;
class QImage;
class QLabel;
class ResizableImagePanel : public Component
{
 Q_OBJECT
public:
 explicit ResizableImagePanel(QWidget *parent = 0);
 /*public*/ static /*final*/ QString IMAGE_PATH;// = "imagePath";
 /*public*/ ResizableImagePanel(QString imagePath, QWidget *parent = 0);
 /*public*/ ResizableImagePanel(QString imagePath, int w, int h, QWidget *parent);
 /*public*/ virtual void setBackground(QColor bckCol);
 /*public*/ void setResizingContainer(bool b);
 /*public*/ bool isResizingContainer();
 /*public*/ bool isRespectingAspectRatio();
 /*public*/ void setRespectAspectRatio(bool b);
 /*public*/ QString getImagePath();
 /*public*/ void setImagePath(QString s);
 /*public*/ QImage getScaledImage();
 SwingPropertyChangeSupport* pcs;

signals:

public slots:

private:
 /*private*/ QString _imagePath;
 /*private*/ QImage image;// = null;  BufferedImage
 /*private*/ QImage scaledImage;// = null;
 /*private*/ bool _resizeContainer;// = false;
 /*private*/ bool _respectAspectRatio;// = true;
 bool toResize;// = false;
 static /*private*/ QColor BackGroundColor;// = Color.BLACK;
 /*final*/ static QSize smallDim;// = new Dimension(10, 10);
 Logger* log;
 void common();
 /*private*/ void resizeContainer(QSize d);
 /*private*/ void resizeContainer();
 /*private*/ void setScaledImage();

protected:
 /*protected*/ QLabel* bgImg;// = null;
 /*protected*/ void paintEvent(QPaintEvent* e);

};


#endif // RESIZABLEIMAGEPANEL_H
