# Scratchpad
*Summer's Notes to Herself*

## To Do
????


## Potential Improvements for Future
- enabling parallel edges so we can see how connected two works are
- be able to pass in works they liked and it'll yoink tags and find similar works

## Done
1. Modify graph creation to suit our needs
2. CSV -> Graph Creation
3. BFSing
4. Test on the massive file
2. Do the first algorithm for connecting two nodes
3. Make it doable with the ids
2. Do the second algorithm for connecting two nodes

## Creating the Graph
`[first title],[second title],[associated tag]`
- It's kinda weighted, kinda not
- The "weights" are just the tags

Parameters for inserting edge:
1. Fic id (TO)
2. Fic id (FROM)
3. Tag id

```
FicCSV fics("Edgelist.csv", "IntToTagTranslator.csv", "IntToTitleTranslator.csv");
fics.doEverything("Fic 1", "Fic2");
// returns Adjacency matrix path, adjacency list path
//         total time, pathing times, matrix times
//         as vector of strings
```