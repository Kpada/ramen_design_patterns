# Adapter pattern

The adapter pattern allows the interface of an existing class to be used as another interface. It is often used to make existing classes work with others without modifying their source code.

When to use:
- You want to use a third party class, but its interface doesn't match the rest of your application code.
- You need to use several existing subclasses, but they lack some common functionality, and you cannot extend the superclass.

But:
 - Complicates the program code due to the introduction of additional classes.

## Output

> I'm going to eat a sausage using a fork

Got utensils (fork)

The sausage has been eaten

> I'm going to eat ramen using chopsticks

Got utensils (chopsticks)

The ramen has been eaten

> I'm going to eat ramen using a fork

Fork to Chopshicks adapter. Calling 'TakeChopsticks'.

Got utensils (chopsticks)

The ramen has been eaten