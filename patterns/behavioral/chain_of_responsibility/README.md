# Chain of Responsibility pattern

Chain of Responsibility is a behavioral design pattern that lets you pass requests along a chain of handlers. Upon receiving a request, each handler decides either to process the request or to pass it to the next handler in the chain

When to use:
 - Your program is expected to process different kinds of requests in various ways, but the exact types of requests and their sequences are unknown beforehand.
 - It’s essential to execute several handlers in a particular order
 - The set of handlers and their order are supposed to change at runtime

But:
 - Some requests may end up unhandled

## Output

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
