#ifndef MEMORYICONCOORDINATEEDIT_H
#define MEMORYICONCOORDINATEEDIT_H
#include "memoryicon.h"
#include "coordinateedit.h"
#include <QAction>

class MemoryIconCoordinateEdit : public CoordinateEdit
{
    Q_OBJECT
public:
    //explicit MemoryIconCoordinateEdit(QObject *parent = 0);
    /*public*/ void init(QString title, MemoryIcon* pos, bool showName);
    /*public*/ /*static*/ QAction* getCoordinateEditAction(/*final*/ MemoryIcon* pos, QWidget* parent);
    /*public*/ void initSetXY();

signals:
    
public slots:
    //void onSetXYAction();
    void on_setXYOkButton_clicked();
    void on_setXYCancelButton_clicked();

private:
    MemoryIcon* pl; 			// positional label tracked by this frame
    int oldX;
    int oldY;
    double oldD;
    QString oldStr;

};
class SetXYAbstractAction : public QAction
{
 Q_OBJECT
  MemoryIcon* pos;
  QWidget* parent;
public:
  SetXYAbstractAction( MemoryIcon* pos, QWidget* parent);

public slots:
  void onSetXYAction();
};

#endif // MEMORYICONCOORDINATEEDIT_H
