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


### Chain of Responsibility

> What can I buy in this restaurant? My money = 100.

Your money = 100, price = 1000. You can NOT buy ramen

Your money = 100, price = 500. You can NOT buy gyoza

Your money = 100, price = 750. You can NOT buy beer

You can NOT buy udon. We don't have it. This is a ramen restaurant.

> What can I buy in this restaurant? Money = 1000.

Your money = 1000, price = 1000. You can buy ramen

Your money = 1000, price = 500. You can buy gyoza

Your money = 1000, price = 750. You can buy beer

You can NOT buy udon. We don't have it. This is a ramen restaurant.


### Command

> We're visiting a ramen restaurant. We're going to order 2 bowls or ramen

Cooking Ramen

Cooking Ramen

> A friend of mine also decided to order some gyoza

Cooking Gyoza

> But we don't have enough money and cannot afford these gyoza. So we asked the waiter for a cancelation

Stop cooking Gyoza


### Mediator

> We want to notify every restaurant when someone has ordered a meal. If the restaurant sees others' orders, they will increase their advertising budget and we will get more money :)

Miso Ramen ordered from Ramen Restaurant

Mediator notified that someone ordered Miso Ramen

Mediator is notifying the Udon restaurant that they're  losing clients...

Udon Restaurant: we should increase the ad budget.

### Memento

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


### State

> There is a promo in our restaurant. We give you free gyoza after every 3 ramen orders

> New context state: N5State10StateRamenE.

order 1: 
Ramen: Cooking ramen

order 2: 
Ramen: Cooking ramen

order 3: 
Ramen: Cooking ramen

> New context state: N5State15StateBonusGyozaE.

Gyoza: Cooking bonus gyoza

Gyoza: restore the previous state

> New context state: N5State10StateRamenE.

order 4: 
Ramen: Cooking ramen


### Strategy

> Each dish has a different cooking strategy. But there is only one way to order a dish.


> The new context's strategy: N8Strategy13StrategyRamenE.

Cooking ramen

> The new context's strategy: N8Strategy13StrategyGyozaE.

Cooking gyoza


### Template Method

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


### Visitor

> Each restaurant visitor has his own food preferences. For example, on Thursday I just want to have lunch, and on Friday I also want to drink a little alcohol.


Today is Thursday. I'm visiting a Ramen restaurant to dine without drinks. The cost of the dinner = 1000

Today is Thursday. I'm visiting a Sushi restaurant to dine without drinks. The cost of the dinner = 2000

Today is Friday. I'm visiting a Ramen restaurant to dine with drinks. The cost of the dinner = 1500

Today is Friday. I'm visiting a Sushi restaurant to dine with drinks. The cost of the dinner = 2800

> Singleton Chef destroyed!


### Observer

> Due to the global crisis, the country ran out of stocks of ramen. But when the stocks are restored, we want to notify our customers immediately.

Ramen stocks restored!

A ramen fan named Nik received a message from the Observer.

> I'm going to visit a ramen restaurant immideately!

A ramen fan named Alex received a message from the Observer.

> I'm going to visit a ramen restaurant immideately!
