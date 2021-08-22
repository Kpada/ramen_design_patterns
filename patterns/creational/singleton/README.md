# Singleton pattern

The singleton pattern is a software design pattern that restricts the instantiation of a class to one "single" instance.

When to use:
 - Ensures there is a single instance of the class.
 - Provides a global access point to the instance.
 - Implements lazy initialization of a singleton object.

But:
 - Violates the principle of sole responsibility of the class.
 - Disguises a bad design.
 - Multithreading problems.
 - Requires constant creation of Mock objects when unit testing.

## Output

I'm visiting a ramen restaurant. There is only one chef is working here. Regardless of the number of visitors, only this chef can prepare the order.
He is a singleton.

> Singleton Chef created!

> Visitor2 is ordering ramen.

ramen created

Someone is eating ramen

> Visitor1 is ordering gyoza.

gyoza created

Someone is eating gyoza

> Visitor3 is ordering udon.

udon created

Someone is eating udon

> Singleton Chef destroyed!
