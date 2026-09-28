# Design Log — Project 2

(500–800 words total. See spec §5 for what each section must cover.)

## Growth factor and amortized cost
The growth factor I chose was 2. This means the capacity will double everytime a reallocation happens. This means it will go from capacity 0, to 1, to 2, 4, etc. In the growth factor test, I test up to size 5, which covers capacities 0,1,2,4. 

## Rule of Five evidence
Since Conversation has the pointer data_ it needs the Rule of Five since it needs all 5 of the methods in order to manage the memory. The default destructor will not free the memory. The copy constructor builds a new object and does a deep copy from the old object to the new object. The deep copy makes sure that all elements are copied over where the copy owns the memory addresses instead of stealing from the old object. Copy assignment takes an existing object and does the same deep copy from the old object to the new. The test proves this works using the assert(copyConversation.begin() != conversation.begin());
line. Move constructor creates a new object which steals the address from the old object. The old pointer data_ is set to null to ensure the old object is closed off. Move assignment does the same for an existing object.

## Sentinel scanner: bounded pending_ proof



## What I would change differently
