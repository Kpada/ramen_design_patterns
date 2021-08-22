# Template Method pattern

The template Method is a behavioral design pattern that defines the skeleton of an algorithm in the superclass but lets subclasses override specific steps of the algorithm without changing its structure.

When to use:
 - You want to let clients extend only particular steps of an algorithm, but not the whole algorithm or its structure.
 - You have several classes that contain almost identical algorithms with some minor differences. As a result, you might need to modify all classes when the algorithm changes.

But:
- Some clients may be limited by the provided skeleton of an algorithm.
- You might violate the Liskov Substitution Principle by suppressing a default step implementation via a subclass.
- Template methods tend to be harder to maintain the more steps they have.

## Output

> Eating dinner consists of the same steps. However, depending on the dish or restaurant, the implementation of these steps may differ.


> I'm going to eat Ramen

Wash hands

Make the order

Itadakimasu

Take chopsticks

Eat

Finish

> I'm going to eat KFC

Wash hands

Make the order

Eat

Finish

Clear the table
