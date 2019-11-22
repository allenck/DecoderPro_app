#ifndef PATH_H
#define PATH_H

#include <QObject>
#include "block.h"
#include "beansetting.h"
#include <QVector>
class BeanSetting;
class Block;
class LIBPR3SHARED_EXPORT Path : public QObject
{
    Q_OBJECT
public:
    explicit Path(QObject *parent = 0);
    /**
     * Convenience constructor to set the destination/source block
     * and directions in one call.
     */
    /*public*/ Path(Block* dest, int toBlockDirection, int fromBlockDirection, QObject *parent = 0);
    /**
     * Convenience constructor to set the destination/source block,
     * directions and a single setting element in one call.
     */
    /*public*/ Path(Block* dest, int toBlockDirection, int fromBlockDirection, BeanSetting* setting, QObject *parent = 0);
    /*public*/ virtual void addSetting(BeanSetting* t);
    /*public*/ QList<BeanSetting*> getSettings();
    /*public*/ void removeSetting(BeanSetting* t);
    /*public*/ void clearSettings();
    /*public*/ void setBlock(Block* b);
    /*public*/ Block* getBlock();
    /*public*/ int getToBlockDirection();
    /*public*/ void setToBlockDirection(int d);

    /*public*/ int getFromBlockDirection();
    /*public*/ void setFromBlockDirection(int d);
    /**
     * Check that the Path can be traversed.
     * This means that any path elements are set to the
     * proper state, e.g. that the Turnouts on this path
     * are set to the proper CLOSED or OPEN status.
     * @return true if the path can be traversed; always true
     * if no path elements (BeanSettings) are defined.
     */

    /*public*/ bool checkPathSet();
#if 0
    /**
     * Direction not known or not specified. May also
     * represent "stopped", in the sense of not moving in any direction.
     */
    /*public*/ const static /*final*/ int NONE  =0x00000;
    /**
     * Northward
     */
    /*public*/ const static /*final*/ int NORTH =0x00010;
    /**
     * Southward
     */
    /*public*/ const static /*final*/ int SOUTH =0x00020;
    /**
     * Eastward
     */
    /*public*/ const static /*final*/ int EAST  =0x00040;
    /**
     * Westward
     */
    /*public*/ const static /*final*/ int WEST  =0x00080;
    /**
     * North-East
     */
    /*public*/ const static /*final*/ int NORTH_EAST = NORTH | EAST;
    /**
     * South-East
     */
    /*public*/ const static /*final*/ int SOUTH_EAST = SOUTH | EAST;
    /**
     * South-West
     */
    /*public*/ const static /*final*/ int SOUTH_WEST = SOUTH | WEST;
    /**
     * North-West
     */
     /*public*/ const static /*final*/ int NORTH_WEST = NORTH | WEST;
    /**
     * Clockwise
     */
    /*public*/ const static /*final*/ int CW    =0x00100;
    /**
     * Counter-clockwise
     */
    /*public*/ const static /*final*/ int CCW   =0x00200;
    /**
     * Leftward, e.g. on a schematic diagram or CTC panel
     */
    /*public*/ const static /*final*/ int LEFT  =0x00400;
    /**
     * Rightward, e.g. on a schematic diagram or CTC panel
     */
    /*public*/ const static /*final*/ int RIGHT =0x00800;
    /**
     * Upward, e.g. on a schematic diagram or CTC panel
     */
    /*public*/ const static /*final*/ int UP    =0x01000;
    /**
     * Downward, e.g. on a schematic diagram or CTC panel
     */
    /*public*/ const static /*final*/ int DOWN  =0x02000;
#endif
 enum DIR
 {
  NONE = 0x00000,
  NORTH = 0x00010,
  SOUTH = 0x00020,
  EAST = 0x00040,
  WEST = 0x00080,
  NORTH_EAST = NORTH | EAST,
  SOUTH_EAST = SOUTH | EAST,
  SOUTH_WEST = SOUTH | WEST,
  NORTH_WEST = NORTH | WEST,
  CW = 0x00100,
  CCW = 0x00200,
  LEFT = 0x00400,
  RIGHT = 0x00800,
  UP = 0x01000,
  DOWN = 0x02000
 };
 Q_ENUM(DIR)
    /**)
     * Decode the direction constants into a human-readable
     * form.
     * This should eventually be internationalized.
     */
    static /*public*/ QString decodeDirection(int d);
    /*public*/ void setLength(float l);
    /*public*/ float getLength();
    /*public*/ float getLengthMm() ;
    /*public*/ float getLengthCm();
    /*public*/ float getLengthIn() ;
    /*public*/ bool equals(QObject* obj);
    /*public*/ QString toString();
    /*public*/ static int computeDirection(QPointF p1, QPointF p2);
    /*public*/ static int reverseDirection(int inDir);

signals:
    
public slots:
    
private:
    /*private*/ QVector<BeanSetting*>* _beans;// = new QVector<BeanSetting>();
    /*private*/ Block* _block = nullptr;
    /*private*/ int _toBlockDirection;
    /*private*/ int _fromBlockDirection;
    static /*private*/ void appendOne(QString b, QString t);
    float _length  = 0.0f;
    void common();
};

#endif // PATH_H
