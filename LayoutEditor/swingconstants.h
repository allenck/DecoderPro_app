#ifndef SWINGCONSTANTS_H
#define SWINGCONSTANTS_H
/**
 * A collection of constants generally used for positioning and orienting
 * components on the screen.
 *
 * @author Jeff Dinkins
 * @author Ralph Kar (orientation support)
 */
/*public*/ class SwingConstants {
public:

        /**
         * The central position in an area. Used for
         * both compass-direction constants (NORTH, etc.)
         * and box-orientation constants (TOP, etc.).
         */
        /*public*/ static const int CENTER  = 0;

        //
        // Box-orientation constant used to specify locations in a box.
        //
        /**
         * Box-orientation constant used to specify the top of a box.
         */
        /*public*/ static const int TOP     = 1;
        /**
         * Box-orientation constant used to specify the left side of a box.
         */
        /*public*/ static const int LEFT    = 2;
        /**
         * Box-orientation constant used to specify the bottom of a box.
         */
        /*public*/ static const int BOTTOM  = 3;
        /**
         * Box-orientation constant used to specify the right side of a box.
         */
        /*public*/ static const int RIGHT   = 4;

        //
        // Compass-direction constants used to specify a position.
        //
        /**
         * Compass-direction North (up).
         */
        /*public*/ static const int NORTH      = 1;
        /**
         * Compass-direction north-east (upper right).
         */
        /*public*/ static const int NORTH_EAST = 2;
        /**
         * Compass-direction east (right).
         */
        /*public*/ static const int EAST       = 3;
        /**
         * Compass-direction south-east (lower right).
         */
        /*public*/ static const int SOUTH_EAST = 4;
        /**
         * Compass-direction south (down).
         */
        /*public*/ static const int SOUTH      = 5;
        /**
         * Compass-direction south-west (lower left).
         */
        /*public*/ static const int SOUTH_WEST = 6;
        /**
         * Compass-direction west (left).
         */
        /*public*/ static const int WEST       = 7;
        /**
         * Compass-direction north west (upper left).
         */
        /*public*/ static const int NORTH_WEST = 8;

        //
        // These constants specify a horizontal or
        // vertical orientation. For example, they are
        // used by scrollbars and sliders.
        //
        /** Horizontal orientation. Used for scrollbars and sliders. */
        /*public*/ static const int HORIZONTAL = 0;
        /** Vertical orientation. Used for scrollbars and sliders. */
        /*public*/ static const int VERTICAL   = 1;

        //
        // Constants for orientation support, since some languages are
        // left-to-right oriented and some are right-to-left oriented.
        // This orientation is currently used by buttons and labels.
        //
        /**
         * Identifies the leading edge of text for use with left-to-right
         * and right-to-left languages. Used by buttons and labels.
         */
        /*public*/ static const int LEADING  = 10;
        /**
         * Identifies the trailing edge of text for use with left-to-right
         * and right-to-left languages. Used by buttons and labels.
         */
        /*public*/ static const int TRAILING = 11;
        /**
         * Identifies the next direction in a sequence.
         *
         * @since 1.4
         */
        /*public*/ static const int NEXT = 12;

        /**
         * Identifies the previous direction in a sequence.
         *
         * @since 1.4
         */
        /*public*/ static const int PREVIOUS = 13;
};

#endif // SWINGCONSTANTS_H
