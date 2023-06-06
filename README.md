# SWERC cheat sheet

## TODO:

- testare tangenti cerchi

## Algoritmi

### 1. Geometria

- [x] Geometria di base 2D (rotazioni, traslazioni, dot/cross product, area del poligono, punti all'interno del poligono, linee, segmenti, polar sort)
- [x] Geometria di base 3D (punti, dot/cross product, piani, coordinate su un piano)
- [x] Operazioni sui cerchi (circocentro, intersezioni, tangenti)
- [x] Closest pair
- [x] Convex hull trick
- [x] Convex hull (2D)
- [x] Fast delaunay
- [x] Slow delaunay
- [x] Welzl (minimum enclosing circle)
- [x] Poligon cut
- [ ] Convex hull (3D)
- [ ] (?) Voronoi
- [ ] (?) Polygon union
- [ ] (?) Rotating caliper

### 2. Grafi

- [x] Ponti e punti di articolazione
- [x] Biconnected components
- [x] Blossom (matching)
- [x] Blossom pesato (matching pesato)
- [x] Dominator tree
- [x] Edge coloring
- [x] Eulerian path (su grafo diretto e non diretto)
- [x] Global min cut (Stoer–Wagner algorithm)
- [x] Gomory-Hu tree 
- [x] Algoritmo ungherese
- [x] Min cost max flow
- [x] Max flow
- [x] Max clique
- [x] Stable marriage (Gale-Shapley algorithm)
- [x] Tarjan trick for SPFA

### 3. Matematica

- [x] Berlekamp-Massey
- [x] Dirichlet convolution trick
- [x] Euclide esteso
- [x] FFT
- [x] Fattorizzazione veloce (Pollard's Rho)
- [x] Fast subset convolution (or,and,xor)
- [x] Ricorrenze lineari
- [x] Operazioni sulle matrici (determinante, determinante mod, inversa, inversa mod)
- [X] Modular
- [x] NTT
- [x] Nimber product
- [x] Operazioni sui polinomi (divisione, serie infinita di 1/p(x), valutazione, interpolazione)
- [x] Gaussian elimination (linear solve con mod e senza mod)
- [x] Teorema del resto cinese
- [x] Euler’s totient function
- [ ] Fast matrix multiplication

### 4. Stringhe

- [x] Aho-Corasick
- [x] Hashing
- [x] Knuth-Morris-Pratt
- [x] Manacher
- [x] Palindrome tree
- [x] Rotazione minima lessicografica
- [x] Suffix array + lcp array
- [x] Suffix tree
- [x] Z-algorithm

### 5. Strutture dati

- [x] $T(n)\log(n)$ deletion offline
- [x] Centroid decomposition
- [x] Compressed BBST
- [x] Fast hash table
- [x] Heavy light decomposition (nodi & archi) (+ lca)
- [x] Li chao tree
- [x] Line container
- [x] Link-cut tree (normale, divino, modifica per path non commutativi)
- [x] Mo queries (su array e su albero)
- [x] Segment tree beats
- [x] Persistent segment tree (normale oppure sparso + lazy)
- [x] Sparse table
- [x] Treap (+ lazy propagation)
- [ ] (?) Pairing heap
- [ ] (?) Lower bound su fenwick
- [ ] (?) KD-tree

### 6. Altro

- [x] Divide and conquer DP
- [x] Hornsat
- [x] Knuth optimization DP
- [x] SMAWK
- [x] Simplesso
- [x] Template (con pbds e rope)
- [x] Twosat

### 7. Scarti

- [x] Fast input (per lettura interi)
- [x] XorSat
- [x] Characteristic polynomial (of a matrix)
- [x] Dictionary of basic factors
- [x] Sat (bruteforce O(2^variables*clauses))
- [x] Floyd cycle detection

## Teoria

### 1. Conteggi

- [x] Stirling del primo tipo
- [x] Stirling del secondo tipo
- [x] Derangement
- [x] Catalan
- [x] Burnside's lemma
- [x] Somma potenze quarte

### 2. Grafi

- [x] Relazione generale tra max indipendent set e minimum vertex cover
- [x] Max-flow min-cut theorem
- [x] Konig theorem: max matching e min vertex cover (anche pesato) su grafo bipartito
- [x] Hall theorem: matching perfetto su grafo bipartito
- [x] Erdős–Gallai theorem
- [x] Dilworth theorem e duale: insieme parzialmente ordinati, cammini ricoprenti e anti-catene
- [x] Archi o nodi obbligati in un matching
- [x] Max matching, in caso di parità scelgo min/max cost
- [x] Max matching pesato e min matching pesato
- [x] Min/Max cost ma non per forza max flow
- [x] Number of spanning trees, Cayley's formula and labeled unrooted trees
- [x] BEST theorem: number of eulerian circuits

### 3. Vario

- [x] Subset sum speedup for small weights
- [x] Varianti del nim
- [x] Rango matrice
- [x] Prodotto scalare e vettoriale
- [x] Pick's theorem
- [x] Euler's formula
- [x] Minkowski sum
- [x] Pythagorean triples
- [x] Numeri primi grandi
- [x] Teoria della probabilità (valore atteso, varianza, covarianza)
- [x] Note
