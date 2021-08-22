# Decorator pattern

The decorator is a structural design pattern that allows objects to **dynamically** add new functionality by wrapping them in useful "wrappers".

When to use:
 - You need to add responsibilities to objects at runtime, it's invisible to the code that uses them.
 - It is not possible to extend the responsibilities of an object with inheritance.

But:
 - Multiple wrapped objects are difficult to configure.
 - An abundance of tiny classes.

## Output

Just Ramen: Ramen, price = 1000

Added gyoza: Ramen + Gyoza, price = 1500

Added Beer: Ramen + Gyoza + Beer, price = 1850

One beer more: Ramen + Gyoza + Beer + Beer, price = 2200

Ramen & Beer: Ramen + Beer, price = 1350
