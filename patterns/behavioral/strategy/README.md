# Strategy pattern

The Strategy is a behavioral design pattern that lets you define a family of algorithms, put each of them into a separate class, and make their objects interchangeable.

When to use:
 - You want to use different variants of an algorithm within an object and be able to switch from one algorithm to another during runtime.
 - You have a lot of similar classes that only differ in the way they execute some behavior.
 - To isolate the business logic of a class from the implementation details of algorithms that may not be as important in the context of that logic.
 - Your class has a massive conditional operator that switches between different variants of the same algorithm

But:
 - If you only have a couple of algorithms and they rarely change, there’s no real reason to overcomplicate the program with new classes and interfaces that come along with the pattern.
 - Clients must be aware of the differences between strategies to be able to select a proper one.
 - A lot of modern programming languages have functional type support that lets you implement different versions of an algorithm inside a set of anonymous functions. Then you could use these functions exactly as you’d have used the strategy objects, but without bloating your code with extra classes and interfaces.

## Output

> Each dish has a different cooking strategy. But there is only one way to order a dish.


> The new context's strategy: N8Strategy13StrategyRamenE.

Cooking ramen

> The new context's strategy: N8Strategy13StrategyGyozaE.

Cooking gyoza
