# Mediator pattern

The mediator is a behavioral design pattern that lets you reduce chaotic dependencies between objects. The pattern restricts direct communications between the objects and forces them to collaborate only via a mediator object.

When to use:
 - It’s hard to change some of the classes because they are tightly coupled to a bunch of other classes.
 - You can’t reuse a component in a different program because it’s too dependent on other components.
 - You find yourself creating tons of component subclasses just to reuse some basic behavior in various contexts.

But:
 - Over time a mediator can evolve into a God Object.

## Output

> We want to notify every restaurant when someone has ordered a meal. If the restaurant sees others' orders, they will increase their advertising budget and we will get more money :)

Miso Ramen ordered from Ramen Restaurant

Mediator notified that someone ordered Miso Ramen

Mediator is notifying the Udon restaurant that they're  losing clients...

Udon Restaurant: we should increase the ad budget.
