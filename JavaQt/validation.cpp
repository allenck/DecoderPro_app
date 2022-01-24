#include "validation.h"
#include <QValidator>
#include "jinputvalidatorpreferences.h"

/*public*/ Validation::Validation(Type type, QString message) {
 this->type = type;
 this->message = message;
}

/*public*/ Validation::Validation(Type type, QString string, /*@javax.annotation.Nonnull*/ JInputValidatorPreferences *jivp) {
 this->type = type;
 this->message = string;
 this->preferences = jivp;
}

/*public*/ Validation::Type Validation::getType() {
 return type;
}

/*public*/ QString Validation::getMessage() {
 return message;
}
/**
 * Get the Unicode characters for the displayed icon.
 *
 * @return the icon text
 */
//@Nonnull
/*public*/ QString Validation::getIcon() {
    return preferences->getIcon(type);
}

/**
 * Get the color the icon is displayed in.
 *
 * @return the color to use
 */
//@Nonnull
/*public*/ QColor Validation::getColor() {
    return preferences->getColor(type);
}

/**
 * Get the font used to render the icon.
 *
 * @return the font to use
 */
//@Nonnull
/*public*/ QFont Validation::getFont() {
    return preferences->getFont();
}

/**
 * Set the preferences to use with this Validation.
 *
 * @param preferences the preferences to set
 */
// package private
void Validation::setPreferences(/*@Nonnull*/ JInputValidatorPreferences* preferences) {
    this->preferences = preferences;
}
#if 0
//@Override
/*public*/ int hashCode() {
    int hash = 5;
    hash = 79 * hash + Objects.hashCode(this.type);
    hash = 79 * hash + Objects.hashCode(this.message);
    return hash;
}

@Override
public boolean equals(Object obj) {
    if (this == obj) {
        return true;
    }
    if (obj == null) {
        return false;
    }
    if (getClass() != obj.getClass()) {
        return false;
    }
    return this.hashCode() == obj.hashCode();
}
#endif
