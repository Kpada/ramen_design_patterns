# Memento pattern

The memento is a behavioral design pattern that lets you save and restore the previous state of an object without revealing the details of its implementation.

When to use:
 - You want to produce snapshots of the object’s state to be able to restore a previous state of the object.
 - Direct access to the object’s fields/getters/setters violates its encapsulation.

But:
 - The app might consume lots of RAM if clients create mementos too often.
 - Caretakers should track the originator’s lifecycle to be able to destroy obsolete mementos.

## Output

> I'm a chef in a ramen restaurant. I want to make the best ramen. I will change the recipe and receive feedback from customers. If the customers are unhappy, we should be able to roll back the recipe to the last successful state.

Originator's initial state = soup, noodles

Caretaker: Saving Originator's state.

> Let's add egg

Originator's new state: soup, noodles, egg

> I've added an egg to the recipe and sales went up

Caretaker: Saving Originator's state.

> Let's add nori

Originator's new state: soup, noodles, egg, nori

> I've added nori to the recipe and sales went up

Caretaker: Saving Originator's state.

> Let's add bacon

Originator's new state: soup, noodles, egg, nori, bacon

> I've added bacon to the recipe and sales dropped. Let's restore the previous state.

Caretaker: List of snapshots

2021-08-22 13:15:15 / soup, noodles

2021-08-22 13:15:16 / soup, noodles, egg

2021-08-22 13:15:17 / soup, noodles, egg, nori

Caretaker is restoring the state from 'soup, noodles, egg, nori, bacon' to 'soup, noodles, egg, nori'

Originator' state restored: soup, noodles, egg, nori
