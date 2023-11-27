# AO3-Trawler
This project was made as a part of Data Structures and Algorithms (DSA) 2023 Fall Semester.


## Summary
This connects two fanfictions/works to each other based on the shared tags. It creates a graph of fanfictions using titles as nodes and tags as edges (ie all fics with the same tag are connected to each other). Then, two fanfictions are connected to each other through these shared tags.

## Required Inputs
Fanfictions are stored in a CSV file. Three separate CSV files contain information about the fanfiction data set:
1. Edgelist - this is an edgelist of all the fanfictions, as well as what tags connect them. These fanfictions are stored as integers instead of strings for storage simplification.
2. ID to Title Translator - this CSV file has the IDs (ints) as the first value, and then the title they are associated with as the second number
3. ID to Tag Translator - this CSV file contains the IDs (ints) as the first value, and then the tag it is associated with as the second number.'

Because the number of edges is so large (about 18.5 million), the edgelist and translator files are not available in this repo. Examples of the CSV files can be seen within the `test` folder, accompanied by an image of the graph they represent.
