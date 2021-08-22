# Proxy pattern

The proxy is a structural design pattern that allows you to replace real objects with custom placeholder objects. These objects intercept calls to the original object, allowing you to do something before or after passing the call to the original.

When to use:
 - Lazy initialization (virtual proxy).
 - Access protection (protection proxy).
 - Logging requests (logging proxy).
 - Object caching (smart reference).

But:
 - Complicates the program code due to the introduction of additional classes.
 - Increases the response time from the service.

## Output

> I'm going to have dinner: ramen and beer. In this country you can drink alcohol from the age of 20. I'm 29.

Someone's drinking beer

Someone's eating ramen

> A schoolboy entered the restaurant. He's 17. He is not allowed to drink beer.

Drink beer failed: Sorry, you're too young

Someone's eating ramen
