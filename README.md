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
[Waiter] Sure. This is the best ramen in our city.

Miso Ramen created. 
Weight = 500, Fork = false

> [Me] I cannot use chopsticks. May I have a fork?

Miso Ramen: set fork = true

Eating Miso Ramen: 
Weight = 400, Fork = true


Unexpectedly, a friend of mine came into the restaurant...

> [FoM] Hi. What are you eating?
[Me] Miso Ramen
[FoM] Waiter, I'd like to have the same ramen.

Miso Ramen created. 
Weight = 400, Fork = true

> [FoM] Waiter, my bowl is not full.
[Waiter] Yes. You asked for the same. This is the same.
[FoM] o_O
[Me] o_O

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
Visitor2 is ordering ramen.

ramen created

Someone is eating ramen

> Visitor1 is ordering gyoza.

gyoza created

Someone is eating gyoza

> Visitor3 is ordering udon.

udon created

Someone is eating udon

> Singleton Chef destroyed!

## [Structural patterns](patterns/structural)
