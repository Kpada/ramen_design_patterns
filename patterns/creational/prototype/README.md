# Prototype pattern

The prototype pattern is a creational design pattern in software development. It is used when the type of objects to create is determined by a prototypical instance, which is cloned to produce new objects.

When to use:
 - Allows you to clone objects without being bound to their specific classes.
 - Less repetitive object initialization code.
 - It Speeds up the creation of objects.
 - It is an alternative to creating subclasses for constructing complex objects.

But:
 - It is difficult to clone compound objects that have references to other objects.

## Output

> [Me] Hi. I will have a Ramen.

> [Waiter] Sure. This is the best ramen in our city.

Miso Ramen created. 
Weight = 500, Fork = false

> [Me] I cannot use chopsticks. May I have a fork?

Miso Ramen: set fork = true

Eating Miso Ramen: 
Weight = 400, Fork = true


Unexpectedly, a friend of mine came into the restaurant...

> [FoM] Hi. What are you eating?

> [Me] Miso Ramen

> [FoM] Waiter, I'd like to have the same ramen.

Miso Ramen created. 
Weight = 400, Fork = true

> [FoM] Waiter, my bowl is not full.

> [Waiter] Yes. You asked for the same. This is the same.

> [FoM] o_O

> [Me] o_O

Eating Miso Ramen: 
Weight = 300, Fork = true

Miso Ramen destroyed. 
Weight = 300, Fork = true

Miso Ramen destroyed. 
Weight = 400, Fork = true
