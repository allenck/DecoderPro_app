#ifndef AUDIOTABLEFRAME_H
#define AUDIOTABLEFRAME_H
#include "beantableframe.h"
#include "libtables_global.h"

class AudioTablePanel;
class LIBTABLESSHARED_EXPORT AudioTableFrame : public BeanTableFrame
{
 Q_OBJECT
public:
 //explicit AudioTableFrame(QWidget *parent = 0);
 /*public*/ AudioTableFrame(AudioTablePanel* panel,
         QString helpTarget, QWidget *parent = 0);
 /*public*/ void dispose();

signals:

public slots:
private:
 AudioTablePanel* audioPanel;

};

#endif // AUDIOTABLEFRAME_H
