# Visitor pattern

The Visitor is a behavioral design pattern that lets you separate algorithms from the objects on which they operate.

When to use:
 - You need to perform an operation on all elements of a complex object structure (for example, an object tree).
 - To clean up the business logic of auxiliary behaviors.
 - A behavior makes sense only in some classes of a class hierarchy, but not in others.

But:
 - You need to update all visitors each time a class gets added to or removed from the element hierarchy.
 - Visitors might lack the necessary access to the private fields and methods of the elements that they’re supposed to work with.

## Output

> Each restaurant visitor has his own food preferences. For example, on Thursday I just want to have lunch, and on Friday I also want to drink a little alcohol.


Today is Thursday. I'm visiting a Ramen restaurant to dine without drinks. The cost of the dinner = 1000

Today is Thursday. I'm visiting a Sushi restaurant to dine without drinks. The cost of the dinner = 2000

Today is Friday. I'm visiting a Ramen restaurant to dine with drinks. The cost of the dinner = 1500

Today is Friday. I'm visiting a Sushi restaurant to dine with drinks. The cost of the dinner = 2800

> Singleton Chef destroyed!
