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
/*public*/ /*abstract*/ class Category : public QObject, Comparable<Category> {
 Q_OBJECT
 public:
    /**
     * A item on the layout, for example turnout, sensor and signal mast.
     */
    /*public*/ static /*final*/ Item* ITEM;// = new Item();

    /**
     * Common.
     */
    /*public*/ static /*final*/ Common* COMMON;// = new Common();

    /**
     * Other things.
     */
    /*public*/ static /*final*/ Other* OTHER;// = new Other();

    /**
     * Get all the registered Categories
     * @return a list of categories
     */
    /*public*/ static QList<Category*> values();

    /**
     * Register a category
     * @param category the category
     */
    /*public*/ static void registerCategory(Category* category);
  /*public*/  QString name();
  /*public*/ /*final*/ QString toString() ;
  /*public*/ int order();
  /*public*/ bool equals(QObject* o);
  /*public*/ int hashCode();
  /*public*/ int compareTo(Category* c);

 private:
    /*private*/ static /*volatile*/ QList<Category*>* _categories;

    /*private*/ /*final*/ QString _name;
    /*private*/ /*final*/ QString _description;
    /*private*/ /*final*/ int _order;

 protected:
    /*protected*/ Category(QString name, QString description, int order);

};
    /*public*/ /*static*/ /*final*/ class Item : public Category {
     public:
        /*public*/ Item(): Category("ITEM", tr("Item"), 100){
            //super("ITEM", Bundle.getMessage("CategoryItem"), 100);
        }
    };


    /*public*/ /*static*/ /*final*/ class Common : public Category {
     public:
        /*public*/ Common() : Category("COMMON", tr("Common"), 200){
            //super("COMMON", Bundle.getMessage("CategoryCommon"), 200);
        }
    };


    /*public*/ /*static*/ /*final*/ class Other : public Category {
     public:
        /*public*/ Other() : Category("OTHER", tr("Other"), 300) {
            //super("OTHER", Bundle.getMessage("CategoryOther"), 300);
        }
    };



#endif // CATEGORY_H
