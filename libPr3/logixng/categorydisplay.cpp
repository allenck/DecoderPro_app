#include "categorydisplay.h"

/**
 * Defines the category Display
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/ final class CategoryDisplay extends Category {

    /**
     * An item related to panels.
     */
    /*public*/ /*static*/ /*final*/ CategoryDisplay CategoryDisplay::DISPLAY = CategoryDisplay();


    /*public*/ CategoryDisplay::CategoryDisplay() : Category("DISPLAY", "Display", 200){
        //super("DISPLAY", tr("CategoryDisplay"), 200, parent);
    }

    /*public*/ /*static*/ void CategoryDisplay::registerCategory() {
        if (!Category::values().contains(DISPLAY)) {
            Category::registerCategory(DISPLAY);
        }
    }
