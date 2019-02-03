#ifndef IMAGEPANEL_H
#define IMAGEPANEL_H

#include <QFrame>
#include "bufferedimage.h"
#include <QPainter>
#include <QGroupBox>

class Logger;
class ImagePanel : public QGroupBox
{
 Q_OBJECT
public:
 explicit ImagePanel(QWidget *parent = nullptr);
 /*public*/ void setImage(QImage* img);

signals:

public slots:

private:
 /*private*/ BufferedImage* back;// = null;
 /*private*/ BufferedImage* clip;// = null;
/*private*/ static /*final*/ Logger* log;// = LoggerFactory::getLogger("ImagePanel");
 void paintEvent(QPaintEvent*);
 QPixmap bkgnd;
};

#endif // IMAGEPANEL_H
