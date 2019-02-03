#include "objects.h"
#include "exceptions.h"

//Objects::Objects()
//{

//}

/**
 * Checks that the specified object reference is not {@code null} and
 * throws a customized {@link NullPointerException} if it is. This method
 * is designed primarily for doing parameter validation in methods and
 * constructors with multiple parameters, as demonstrated below:
 * <blockquote><pre>
 * public Foo(Bar bar, Baz baz) {
 *     this.bar = Objects.requireNonNull(bar, "bar must not be null");
 *     this.baz = Objects.requireNonNull(baz, "baz must not be null");
 * }
 * </pre></blockquote>
 *
 * @param obj     the object reference to check for nullity
 * @param message detail message to be used in the event that a {@code
 *                NullPointerException} is thrown
 * @param <T> the type of the reference
 * @return {@code obj} if not {@code null}
 * @throws NullPointerException if {@code obj} is {@code null}
 */
template<class T>
/*public*/ /*static <T>*/ T requireNonNull(T obj, QString message) {
    if (obj == nullptr)
        throw NullPointerException(message);
    return obj;
}
