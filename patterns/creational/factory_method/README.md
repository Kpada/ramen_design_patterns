# Factory method pattern

The factory method pattern is a creational pattern that uses factory methods to deal with the problem of creating objects without having to specify the exact class of the object that will be created. This is done by creating objects by calling a factory method—either specified in an interface and implemented by child classes, or implemented in a base class and optionally overridden by derived classes—rather than by calling a constructor.

When to use:
 - You don't know the types and dependencies of objects with which your code should work.
 - You want to enable users to extend parts of your framework or library
 - You want to save system resources by reusing already created objects instead of spawning new ones.

But:
 - Can lead to the creation of a bunch of parallel class hierarchies. For each product class, you will need to create its creator subclass.

## Output

It's dinner time. I'm so hungry. I don't know what exactly I want to eat. I'm just going to visit the closest restaurant and order their best meal.

> [Me] Hello. I don't know that kind of restaurant is this. I don't know what dishes you have. Give me your best meal, please.

This is Ramen!

> [Me] It was very tasty. Thanks.