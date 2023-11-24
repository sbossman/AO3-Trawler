# Scratchpad
*Summer's Notes to Herself*

## To Do
1. Modify graph creation to suit our needs
2. CSV -> Graph Creation
3. BFSing

## Creating the Graph
`[first title],[second title],[associated tag]`
- It's kinda weighted, kinda not
- The "weights" are just the tags

Parameters for inserting edge:
1. Fic id (TO)
2. Fic id (FROM)
3. Tag id

## BFS/Connecting Nodes
- BFS for each searching mechanism
- For more efficient, prioritizes works with HIGHER OUT DEGREES
  - How do we order them by outdegree?
  - Can't be a key in a map
  - Would need to sort WHILE creating the graph, probably
  - Somehow I feel like we need a minheap for this
  - Ahahaha we'll work on this later
- For less efficient, BFS and whoever gets put in queue first gets put in queue first

## Potential Improvements
- enabling parallel edges so we can see how connected two works are
- be able to pass in works they liked and it'll yoink tags and find similar works