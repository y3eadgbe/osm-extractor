# OSM-extractor
Extract graphs from OpenStreetMap datasets

### Description
OSM-extractor converts OpenStreetMap(http://www.openstreetmap.org/) XML data into a graph file.

To build:
```
$ make
```

To run:
```
$ ./main.rb file.osm
```
or
```
$ ./main-bzip2.rb file.osm.bz2
```
The program will generate a file named `file.graph`.

### Requirement
 * Google Sparse Hash (https://github.com/sparsehash/sparsehash)
 
### Input File Format (OSM XML)
Please see here(http://wiki.openstreetmap.org/wiki/OSM_XML).
