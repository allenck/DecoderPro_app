#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <QObject>
#include "component.h"

class ColorModel : public QObject
{
 Q_OBJECT
public:
 explicit ColorModel(QObject *parent = nullptr);
 ColorModel(QString name, QStringList labels, QObject *parent);

signals:

public slots:

private:
 /*private*/ /*final*/ QString prefix;
 /*private*/ /*final*/ QStringList labels;
 void setColor(int color, QVector<float> model);
 int getColor(QVector<float> model);
 int getCount();
 int getMinimum(int index);
 int getMaximum(int index);
 float getDefault(int index);
 /*final*/QString getLabel(Component* component, int index);
 /*private*/ static float normalize(int value);
 /*private*/ static int to8bit(float value) ;
 /*final*/ QString getText(Component* component, QString suffix);
 /*final*/ int getInteger(Component* component, QString suffix);

 friend class ColorChooserPanel;
 friend class ColorPanel;
};

#endif // COLORMODEL_H
