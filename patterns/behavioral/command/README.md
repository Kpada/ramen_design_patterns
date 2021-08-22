# Command pattern

The command is a behavioral design pattern that turns a request into a stand-alone object that contains all information about the request. This transformation lets you pass requests as a method arguments, delay or queue a request’s execution, and support undoable operations.

When to use:
 - You want to parametrize objects with operations.
 - You want to queue operations, schedule their execution, or execute them remotely.
 - You want to implement reversible operations.

But:
 - The code may become more complicated since you’re introducing a whole new layer between senders and receivers.

## Output

> We're visiting a ramen restaurant. We're going to order 2 bowls or ramen

Cooking Ramen

Cooking Ramen

> A friend of mine also decided to order some gyoza

Cooking Gyoza

> But we don't have enough money and cannot afford these gyoza. So we asked the waiter for a cancelation
