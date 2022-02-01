#ifndef FEMALESOCKETOPERATION_H
#define FEMALESOCKETOPERATION_H
#include <QString>
#include <qobject.h>

/**
 * An enum with the values "is" and "is not"
 *
 * @author Daniel Bergqvist 2019
 */
/*public*/ /*enum*/class FemaleSocketOperation //: public QObject
{
  //Q_OBJECT
 public:

 enum TYPES {Remove, InsertBefore, InsertAfter, MoveUp, MoveDown};
//    Remove(Bundle.getMessage("FemaleSocketOperation_Remove")),
//    InsertBefore(Bundle.getMessage("FemaleSocketOperation_InsertBefore")),
//    InsertAfter(Bundle.getMessage("FemaleSocketOperation_InsertAfter")),
//    MoveUp(Bundle.getMessage("FemaleSocketOperation_MoveUp")),
//    MoveDown(Bundle.getMessage("FemaleSocketOperation_MoveDown"));

//    private final String _text;

//    private FemaleSocketOperation(String text) {
//        this._text = text;
//    }

    //@Override
    /*public*/ static QString toString(FemaleSocketOperation::TYPES t) {
        switch(t)
        {
        case Remove:
         return QString("Remove socket");
        case InsertBefore:
         return QString("Insert new socket before");
        case InsertAfter:
         return QString("Insert new socket after");
        case MoveUp:
         return QString("Move socket up");
        case MoveDown:
         return QString("Move socket down");
        }
    }
 /*public*/ static QList<TYPES> values(){
  QList<FemaleSocketOperation::TYPES> vals= {Remove, InsertBefore, InsertAfter, MoveUp, MoveDown};
  return vals;
 }

};
#endif // FEMALESOCKETOPERATION_H
