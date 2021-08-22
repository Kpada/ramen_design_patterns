# Ramen Design Patterns

## [Creational patterns](patterns/creational)

### Factory Method

It's dinner time. I'm so hungry. I don't know what exactly I want to eat. I'm just going to visit the closest restaurant and order their best meal.

> [Me] Hello. I don't know that kind of restaurant is this. I don't know what dishes you have. Give me your best meal, please.

This is Ramen!

> [Me] It was very tasty. Thanks.


### Abstract Factory

It's dinner time. I'm so hungry. I don't know what exactly I want to eat. I'm just going to visit a restaurant and order their best meal.

It seems I'm visiting a Ramen restaurant today

> [Me] Hello. I'd like to order some food and a beverage

I'm eating Ramen :)

I'm drinking Beer :)

> [Me] It was very tasty. Thanks


### Builder

It's dinner time. I'm so hungry. I'm going to visit my favorite ramen restaurant. They have so many possible options. Fortunately, I don't need to explain to the waiter what I want for each possible parameter. I can just use their menu.

> [Me] I want to have a big tonkotsu ramen with gyoza and beer.

This is my ramen:
Type = Tonkonsu, Weight = 1000, Purgency = Hot, Beverage = Beer, Gyoza = 10, Fork = No


### Prototype

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


### Singleton

I'm visiting a ramen restaurant. There is only one chef is working here. Regardless of the number of visitors, only this chef can prepare the order.
He is a singleton.

> Singleton Chef created!

> Visitor2 is ordering ramen.

ramen created

Someone is eating ramen

> Visitor1 is ordering gyoza.

gyoza created

Someone is eating gyoza

> Visitor3 is ordering udon.

udon created

Someone is eating udon


## [Structural patterns](patterns/structural)


### Adapter

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


### Bridge

It's lunchtime. I'm eating Udon noodles.

It's lunchtime. I'm eating Ramen noodles.

It's dinnertime. I'm eating Udon noodles and drinking beer =)

It's dinnertime. I'm eating Ramen noodles and drinking beer =)


### Decorator

Just Ramen: Ramen, price = 1000

Added gyoza: Ramen + Gyoza, price = 1500

Added Beer: Ramen + Gyoza + Beer, price = 1850

One beer more: Ramen + Gyoza + Beer + Beer, price = 2200

Ramen & Beer: Ramen + Beer, price = 1350


### Facade

> Ordering at a ramen restaurant is not easy. They usually use vending machines, so you have to: choose a dish (if you can read Japanese), put some money, get a ticket, give it to the chef. This facade will help me not to starve to death.

Chosen miso ramen

Inseted money

Ticket created: miso ramen

Chef got a ticket and started cooking miso ramen


### Proxy

> I'm going to have dinner: ramen and beer. In this country you can drink alcohol from the age of 20. I'm 29.

Someone's drinking beer

Someone's eating ramen

> A schoolboy entered the restaurant. He's 17. He is not allowed to drink beer.

Drink beer failed: Sorry, you're too young

Someone's eating ramen


### Flyweight

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


### Composite

> We're going to visit a restauran. When we finish dinner, we have to pay the check. But how do we calculate who spent how much? Fortunately, the check is a composite.

Price of TotalOrder = 3700

Price of My Order = 2700

Price of My GF's order = 600

Price of My ramen = 1200


## [Behavioral patterns](patterns/behavioral)

