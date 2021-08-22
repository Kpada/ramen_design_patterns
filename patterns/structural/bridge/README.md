# Bridge pattern

The bridge is a structural design pattern that separates one or more classes into two separate hierarchies - abstraction and implementation, allowing you to change them independently of each other.

When to use:
- You want to split up a monolithic class that contains several different implementations of some functionality (for example, if the class can work with different database systems).
- A class needs to be extended into two independent planes.
- You want the implementation to be changeable at runtime.

But:
 - Complicates the program code due to the introduction of additional classes.


## Output

It's lunchtime. I'm eating Udon noodles.

It's lunchtime. I'm eating Ramen noodles.

It's dinnertime. I'm eating Udon noodles and drinking beer =)

It's dinnertime. I'm eating Ramen noodles and drinking beer =)
