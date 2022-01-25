#ifndef IS_ISNOT_ENUM_H
#define IS_ISNOT_ENUM_H
/**
 * An enum with the values "is" and "is not"
 *
 * @author Daniel Bergqvist 2019
 */
/*public*/ enum Is_IsNot_Enum {

    Is(Bundle.getMessage("IsIsNotEnum_Is")),
    IsNot(Bundle.getMessage("IsIsNotEnum_IsNot"));

    private final String _text;

    private Is_IsNot_Enum(String text) {
        this._text = text;
    }

    @Override
    public String toString() {
        return _text;
    }

};
#endif // IS_ISNOT_ENUM_H
