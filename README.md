# thewitness
The Witness puzzle solver in C++

Nomenclature
- Node means any node including a face, a path and a node
- Walkable nodes refers to any nodes which can be routed. I.e. paths and intersections.
- A path refers to any node with only two connections to other intersections.
- An intersections refers to any node with more than two connections to other nodes.
- Exit nodes and a special type of intersection which a route can end on.
- Entry nodes are speciel types of intersection nodes which a route can start from.
- Faces are nodes which cannot be routed, and may contain one of the rules listed below.
- Squares are special face nodes which also have a colour. They must not lie in a zone with a sun or a square of a different colour.
- Suds are special face nodes which also have a colour. There must only be two suns (or one sun and one square) of the same colour in a given zone. There can be more than two suns if there are differnt colours.
- Elimination marks are special face nodes which eliminate one rule violation in a zone.
- Tetrominoes are the only face rules which require a grid. Their zones must be able to contain their shapes.
- Rotatable tetrominoes are as above but the tetriminoes are allows to be rotated in order to fill fit inside the shape drown out by their containing node.
- Triangles TODO

Solver
The solver presented here is a simple maze search using recursion. At the core of it, every possible route is searched in order to find a solution. While this works for small puzzles, the cmplexity of such a search is exponentially proportional to the number of nodes in the puzzle. There are a number of optimizations present however which can aim to reduce the number of paths having to be searched.

Optimizations
Pruning the search area
These optimizations are aimed at pruning the search
One way to cut down the number of branches searched is the prune "dead-end' branches, that is detecting and backtracking as soon as you realise there is no way to get to an exit node. This can be done using flood filling which is has a complexity of n where n is the number of walkable nodes in the system.

Heuristics
