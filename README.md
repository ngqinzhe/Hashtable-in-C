
### Simple Hashtable written in C to store key-value pairs, handles collisions using linked lists.

Supports functions such as: 
```
createNode(char* key, int value)
```
Returns a node pointer that contains a key-value pair.

```
insert(node* n, Hashtable* hashtable)
```
Inserts a node into the hashtable. Returns a Hashtable pointer, by taking in a node pointer as an input and a Hashtable pointer.

```
delete(node*n, Hashtable* hashtable)
```
Deletes a node from the hashtable. Returns a Hashtable pointer, by taking in a node pointer as an input and a Hashtable pointer.

```
printTable(Hashtable* hashtable)
```
Prints the entire hashtable. Takes in a Hashtable pointer as input.

```
getValue(char* key)
```
Returns a value of the key value pair, takes in a string as an input. 
