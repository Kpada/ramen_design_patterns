# Builder pattern

The builder pattern is a design pattern designed to provide a flexible solution to various object creation problems in object-oriented programming. The intent of the Builder design pattern is to separate the construction of a complex object from its representation.

When to use:
 - Allows you to create products step by step.
 - Allows you to use the same code to create different products.
 - Isolates complex product assembly code from its business logic.

But:
 - Complicates the program code due to the introduction of additional classes.
 - The client will be tied to specific builder classes, since the director's interface may not have a method to get the result.

## Output

It's dinner time. I'm so hungry. I'm going to visit my favorite ramen restaurant. They have so many possible options. Fortunately, I don't need to explain to the waiter what I want for each possible parameter. I can just use their menu.

> [Me] I want to have a big tonkotsu ramen with gyoza and beer.

This is my ramen:
Type = Tonkonsu, Weight = 1000, Purgency = Hot, Beverage = Beer, Gyoza = 10, Fork = No
