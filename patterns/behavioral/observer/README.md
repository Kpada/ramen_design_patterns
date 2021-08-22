# Observer pattern

Thr Observer is a behavioral design pattern that lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they’re observing.

When to use:
 - Changes to the state of one object may require changing other objects, and the actual set of objects is unknown beforehand or changes dynamically.
 - Some objects in your app must observe others, but only for a limited time or in specific cases.

But:
 - Subscribers are notified in random order.

## Output

> Due to the global crisis, the country ran out of stocks of ramen. But when the stocks are restored, we want to notify our customers immediately.

Ramen stocks restored!

A ramen fan named Nik received a message from the Observer.

> I'm going to visit a ramen restaurant immideately!

A ramen fan named Alex received a message from the Observer.

> I'm going to visit a ramen restaurant immideately!
