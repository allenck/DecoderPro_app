#ifndef CATEGORY_H
#define CATEGORY_H
#include "comparable.h"
#include <QObject>

class Other;
class Common;
class Item;
/**
 * The category of expressions and actions.
 * <P>
 * It's used to group expressions or actions then the user creates a new
 * expression or action.
 * <P>
 * This class is intended to be an Enum, but implemented as an abstract class
 * to allow adding more categories later without needing to change this class.
 * For example, external programs using JMRI as a lib might want to add their
 * own categories.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
class Item;
class Common;
class Other;
/*public*/ /*abstract*/ class Category //: public QObject//, Comparable<Category>
{
 //Q_OBJECT
 protected:
  /*protected*/ Category(QString name, QString description, int order/*, QObject* parent = nullptr*/) ;

 public:
  /*public*/  static /*final*/ Item ITEM;// = new Item();
  /*public*/  static /*final*/ Common COMMON;// = new Common();
  /*public*/  static /*final*/ Other OTHER;// = new Other();

  /*public*/  QString name() const;
  /*public*/  /*final*/ QString toString();
  /*public*/  int order();
  /*public*/ bool equals(Category o);
  /*public*/  uint hashCode();
  /*public*/ QString description() const;
  /*public*/  int compareTo(Category c);
  /*public*/  static QList<Category> values();
  /*public*/  static void registerCategory(Category category);

 private:
  /*private*/ static /*volatile*/ QList<Category> _categories;

  /*private*/ /*final*/ QString _name;
  /*private*/ /*final*/ QString _description;
  /*private*/ /*final*/ int _order;
  friend class TreeEditor;
};
  inline bool operator==(const Category &e1, const Category &e2)
  {
    return e2.name() == (e1.name());
  }

  inline uint qHash(const Category &key, uint seed=0)
  {
      return qHash(key.name(), seed);
  }





/*public*/  /*static*/ /*final*/ class Item : public Category {
public:
    /*public*/  Item() : Category("ITEM", QString("Item"), 100){
        //super("ITEM", Bundle.getMessage("CategoryItem"), 100);
    }
};

/*public*/  /*static*/ /*final*/ class Common : public Category {
public:
    /*public*/  Common() : Category("COMMON", QString("Common"), 200){
        //super("COMMON", Bundle.getMessage("CategoryCommon"), 200);
    }
};

/*public*/  /*static*/ /*final*/ class Other : public Category {
public:
    /*public*/  Other() : Category("OTHER", QString("Other"),300) {
        //super("OTHER", Bundle.getMessage("CategoryOther"), 300);
    }
};
#endif // CATEGORY_H
