# Flyweight pattern

The Flyweight is a structural design pattern that allows more objects to fit into the allocated RAM. The flyweight saves memory by sharing the common state of objects among themselves, instead of storing the same data in each object.

When to use:
 - There is not enough RAM to support all the necessary objects.

But:
 - Complicates the program code due to the introduction of additional classes.

## Output

> We are going to develop an app for ramen lovers. We will map the best restaurants in the country. Obviouly, each restaurant has 2 types of data: shared data (its address) and unique data (its name and type).To avoid duplicates and save memory resourese we will use flyweighs.

Creating the factory

> There are 3 flyweights and 3 shared states.

> 1) [Russia / Moscow / 103132 / The Kremlin]

> 2) [Russia / Moscow / 109651 / Pererva, 42]

> 3) [Russia / St. Petersburg / 190000 / Saint Isaac's Cathedral]

Adding a restaurant to the map...

> FlyWeight Factory: the flyweight is found, reuse it.

> FlyWeight operation: shared ([Russia / Moscow / 109651 / Pererva, 42]) and unique ([Best-Ramen / Ramen]) state.

Adding a restaurant to the map...

> FlyWeight Factory: cannot find a flyweight, creating a new one.

> FlyWeight operation: shared ([Russia / Moscow / 123456 / Untitled street, 42]) and unique ([Ku-Ramen / Ramen]) state.

Adding a restaurant to the map...

> FlyWeight Factory: the flyweight is found, reuse it.

> FlyWeight operation: shared ([Russia / Moscow / 123456 / Untitled street, 42]) and unique ([Best-Gyoza / Gyoza]) state.

Adding a restaurant to the map...

> FlyWeight Factory: the flyweight is found, reuse it.

> FlyWeight operation: shared ([Russia / Moscow / 123456 / Untitled street, 42]) and unique ([Best-Udon / Udon]) state.

> There are 4 flyweights and 4 shared states.

> 1) [Russia / Moscow / 103132 / The Kremlin]

> 2) [Russia / Moscow / 109651 / Pererva, 42]

> 3) [Russia / Moscow / 123456 / Untitled street, 42]

> 4) [Russia / St. Petersburg / 190000 / Saint Isaac's Cathedral]
