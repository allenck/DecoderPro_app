#ifndef TABLEROWORCOLUMN_H
#define TABLEROWORCOLUMN_H
#include <QtCore>

/**
 * Enum for row or column.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
/*public*/  /*enum*/class TableRowOrColumn  : public QObject{
  Q_OBJECT
 public:
  enum TYPE{Row, Column};
//    Row(Bundle.getMessage("TableRowOrColumn_Row"),Bundle.getMessage("TableRowOrColumn_Row_lowercase")),
//    Column(Bundle.getMessage("TableRowOrColumn_Column"), Bundle.getMessage("TableRowOrColumn_Column_lowercase"));

    /*private*/ /*final*/ QString _text;
    /*private*/ /*final*/ QString _textLowerCase;

    /*private*/ TableRowOrColumn(QString text, QString textLowerCase) {
        this->_text = text;
        this->_textLowerCase = textLowerCase;
        if(text == "Row")
         _type = Row;
        else _type = Column;
    }
    TYPE _type;
 public:
    TableRowOrColumn(TableRowOrColumn::TYPE t)
    {
     switch (t) {
     case Row:
      _text = Row;
      _textLowerCase = "row";
      _type = Row;
      break;
     case Column:
      _text= "Column";
      _textLowerCase = "row";
      _type = Column;
      break;
     default:
      _text = "?";
      _textLowerCase= "?";
      break;
     }
    }

    //@Override
    /*public*/ static QString toString(TYPE t) {
     if(t==Row) return "Row";
     else
      return "Column";

    }

    /*public*/ TYPE type()
    {
     return _type;
    }


    /*public*/static   QString toStringLowerCase(TYPE t) {
        if(t==Row) return "row";
        else
         return "column";
    }

    /*public*/ static TableRowOrColumn::TYPE getOpposite(TYPE t) {
        if (t==Row) {
            return Column;
        } else {
            return Row;
        }
    }
};
#endif // TABLEROWORCOLUMN_H
