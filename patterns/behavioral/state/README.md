# State pattern

The State is a behavioral design pattern that lets an object alter its behavior when its internal state changes. It appears as if the object changed its class.

When to use:
 - Use the State pattern when you have an object that behaves differently depending on its current state, the number of states is enormous, and the state-specific code changes frequently.
 - Use the pattern when you have a class polluted with massive conditionals that alter how the class behaves according to the current values of the class’s fields
 - Use State when you have a lot of duplicate code across similar states and transitions of a condition-based state machine.

But:
 - Applying the pattern can be overkill if a state machine has only a few states or rarely changes.

## Output

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
