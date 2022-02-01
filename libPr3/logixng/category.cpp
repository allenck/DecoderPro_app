#include "category.h"
#include <QHash>

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
///*public*/ /*abstract*/ class Category : public QObject, Comparable<Category> {

    /**
     * A item on the layout, for example turnout, sensor and signal mast.
     */
    /*public*/ /*static*/ /*final*/ Item* Category::ITEM = new Item();

    /**
     * Common.
     */
    /*public*/ static /*final*/ Common* COMMON = new Common();

    /**
     * Other things.
     */
    /*public*/ static /*final*/ Other* OTHER = new Other();

    /**
     * Get all the registered Categories
     * @return a list of categories
     */
    /*public*/ /*static*/ QList<Category*> Category::values() {
        if (_categories == nullptr) {
            /*synchronized(Category.class)*/ {
                if (_categories == nullptr) {
                    // It's not often any item is added to this list so we use CopyOnWriteArrayList
                    _categories = new QList<Category*>();//CopyOnWriteArrayList<>();
                    registerCategory(ITEM);
                    registerCategory(COMMON);
                    registerCategory(OTHER);
                }
            }
        }
        //return Collections::unmodifiableList(_categories);
        return QList<Category*>(*_categories);
    }

    /**
     * Register a category
     * @param category the category
     */
    /*public*/ /*static*/ void Category::registerCategory(Category* category) {
        // Ensure that the _categories variable is initialized
        values();

        _categories->append(category);
    }


    /*protected*/Category:: Category(QString name, QString description, int order, QObject* parent) : QObject(parent) {
        _name = name;
        _description = description;
        _order = order;
    }

    /*public*/  QString Category::name() {
        return _name;
    }

    //@Override
    /*public*/ /*final*/ QString Category::toString() {
        return _description;
    }

    /*public*/ int Category::order() {
        return _order;
    }

    //@Override
    /*public*/ bool Category::equals(QObject* o) {
        if (qobject_cast<Category*>(o)) {
            Category* c = (Category*)o;
            return _description == (c->_description) && _name == (c->_name);
        }
        return false;
    }

    //@Override
    /*public*/ int Category::hashCode() {
        //return _description.hashCode();
     //return QHash<QString>(_description);
     return 0;
    }

    //@Override
    /*public*/ int Category::compareTo(Category* c){
        if (_order < c->order()) return -1;
        if (_order > c->order()) return 1;
        return 0;
    }

//};
//    /*public*/ /*static*/ /*final*/ class Item : public Category {

//        /*public*/ Item(): Category("ITEM", tr("Item")){
//            //super("ITEM", Bundle.getMessage("CategoryItem"), 100);
//        }
//    };


//    /*public*/ /*static*/ /*final*/ class Common : public Category {

//        /*public*/ Common() : Category("COMMON", tr("Common")){
//            //super("COMMON", Bundle.getMessage("CategoryCommon"), 200);
//        }
//    };


//    /*public*/ /*static*/ /*final*/ class Other : public Category {

//        /*public*/ Other() : Category("OTHER", tr("Other")) {
//            //super("OTHER", Bundle.getMessage("CategoryOther"), 300);
//        }
//    };
