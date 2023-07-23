# Factory method pattern

The Factory Method pattern is a creational design pattern that provides an
interface for creating objects, but allows subclasses to alter the type of
objects that will be created.

When to use:

* You don't know the types and dependencies of objects with which your
code should work.
* You want to enable users to extend parts of your framework orlibrary.
* You want to save system resources by reusing already created objects instead
of spawning new ones.

But:

* It can lead to the creation of a bunch of parallel class hierarchies. For each
product class, you will need to create its creator subclass.

## Output

It's dinner time. I'm so hungry. I don't know what exactly I want to eat.I'm
just going to visit the nearest restaurant and order their best meal.

> [Me] Hello. I don't know what type of restaurant this is. I don't know what
dishes you serve. Give me your best meal, please.

This is Curry!

> [Me] That was very tasty. Thank you.
