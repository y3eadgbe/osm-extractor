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

##### NOTICE
This software is developed for a research purpose.
The code is ad hoc and environment-dependent.
You may need to modify `Makefile` and other files to run the software in your enviroment.

If you have questions about this software, feel free to contact me (http://www-imai.is.s.u-tokyo.ac.jp/~yyano/).

### Requirement
 * Google Sparse Hash (https://github.com/sparsehash/sparsehash)
 
### Input File Format (`.osm`: OSM XML)
Please see here(http://wiki.openstreetmap.org/wiki/OSM_XML).

### Output File Format (`.graph`)
The format is as follows:
```
N
lon_0 lat_0
...
lon_{N-1} lat_{N-1}
M
level_0 u_0 v_0
...
level_{M-1} u_{M-1} v_{M-1}
```

`lon_i` and `lat_i` denote the longitude and latitude of the i-th vertex (0-indexed).
`level_i` is the importance of the i-th edge (from 1 (less important) to 7 (important)).
`u_i` and `v_i` are the start vertex and the end vertex of the i-th edge.
