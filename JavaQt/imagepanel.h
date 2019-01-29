#ifndef IMAGEPANEL_H
#define IMAGEPANEL_H

#include <QFrame>
#include "bufferedimage.h"

class Logger;
class ImagePanel : public QFrame
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

};

#endif // IMAGEPANEL_H
