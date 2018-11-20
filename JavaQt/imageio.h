#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <QObject>

class Logger;
class BufferedImage;
class File;
class ImageIO : public QObject
{
 Q_OBJECT
public:
 /*public*/ static BufferedImage* read(File* input); /*throws IOException*/

private:
 explicit ImageIO(QObject *parent = nullptr);
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ImageIO");

signals:

public slots:
};

#endif // IMAGEIO_H
