#ifndef DRAWSQUARES_H
#define DRAWSQUARES_H

#include <QObject>

class BufferedImage;
class Logger;
class DrawSquares : public QObject
{
 Q_OBJECT
protected:
 explicit DrawSquares(QObject *parent = nullptr);
public:
 /*public*/ static BufferedImage* getImage(int width, int height, int dim, QColor color1, QColor color2);

signals:

public slots:

private:
 static Logger* log;
};

#endif // DRAWSQUARES_H
