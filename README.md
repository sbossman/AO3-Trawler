# AO3-Trawler
This project was made as a part of Data Structures and Algorithms (DSA) 2023 Fall Semester.


## Summary
This project compares storing a graph as an adjacency list versus as an adjacency matrix. It connects two fanfictions/works to each other based on the shared tags. The titles are used as nodes and tags as edges (ie all fics with the same tag are connected to each other). Then, two fanfictions are connected to each other through these shared tags.

## Inputs
A `RawTaglist.csv` is required to be placed within the `data` folder. From there, running the makefile with the `build` instruction will build all relevant executables. Running the `run-clean` command, first with input `1` (to create an optimized edge list so there are no parallel edges), followed by input `2` and `MAX` will create the other CSV files necessary to create the graph. Then, running `run-graph` will compare the two graph data structure creation times.

If you wish to independently scrape for the fanfictions, view `sitemap.txt` (located in the `data` folder) to see the sitemap used to scrape the data with Webscraper.io.

### Guide to the CSV files
1. `RawTaglist.csv` - this is the csv with the raw data from Webscraper.io. To see the sitemap used to get this data, go to `sitemap.txt` (located within `/data/`)
2. `EdgeList.csv` - this is an edge list of all the fanfictions, as well as what tags connect them. These fanfictions are stored as integers instead of strings for storage simplification.
3. `ReducedEdgeList.csv` - this is the same as `Edgelist.csv` except with the parallel edges taken out.
4. `IntToTitleTranslator.csv` - this CSV file has the IDs (ints) as the first value, and then the title they are associated with as the second number
5. `IntToTagTranslator.csv` - this CSV file contains the IDs (ints) as the first value, and then the tag it is associated with as the second number.
