# Dinamic and Statick Planing

## Search of conflict appointments in matrix 

Analysis of the properties of the bipartite graph shows that together with the mandatory assignments in it we can identify "conflicting", whose hit in the solution (basic or initial version of the solution is done randomly) inevitably leads to free vertices (not included in solution), and hence to additional steps in the formation of the final solution.
    The localization of conflicting assignments is realized on the basis of the equivalent transformation of the initial graph, which is an isomorphic transformation, which consists in the target permutation of rows and columns of the connectivity matrix. In developing the algorithm, the following obvious statements were taken into account, which do not require proof.

**Proposition 1**

   Since each line of the CU is a reflection of the possible distribution of resource requests, the change of two lines of the CU with memorization of the new location of the requests does not affect the qualitative characteristics of the CU and the initial graph.

**Proposition 2**

  Since each column of the CU is a reflection of the claim for applications to capture this resource, the change of places of the two columns of the CU with memorization of the new location of resources does not affect the qualitative characteristics of the CU and the initial graph.

**Theorem 3**

   If after the equivalent transformation of the CU it is possible to obtain the term rank of the CU equal to the rank of the CU, then all applications have destinations corresponding to "1" of the main diagonal and: a complete combination is found, one of the solutions to the problem of assigning applications

**Theorem 4**

   If in the matrix MS [i, j], i = 1..N, j = 1..N we can select the submatrix MM [k, l], k = 1..T, l = (N-S + 1). .N, where S + T> N and MM = 0 (0 is the zero matrix), then the assignment problem does not have a complete solution.

## Algoritm of changing matrix

If in the connectivity matrix displaying a bivariate graph, one can select the zero submatrix and place it in the upper right corner and there is a condition a + b> = n, then the matrix symmetric to it must be zeroed out because the ones are conflicting values.
First iteration: go through the row of the boolean matrix with min the sum of units. We change this row with the first row of the matrix. We find the sum of units by columns only for those where the first line is 1 and choose the maximum amount. This column is swapped with the first column.
Cut off 1 row and the first column.
We repeat the iteration.

## Functions

`int min_row(int**& m, int from)` – search for row where minimum sum of units, starting from the `from` row and return it's number.
 
`int max_collumn(int**& m,int from)` – search for row where maximun collumn of units and which starts from `1`, starting from the `from` collumn and return it's number.
 
`void replace(int**& m)` – do transformation with matrix `m` with help of `min_row` and `max_collumn`. Remember start numbers of rows and collumns.

`void replace_w(int**& m)` – do transformation with matrix `m` with help of `min_row` and `max_collumn` without remembering start numbers of rows and collumns.
	
`bool check_conflicts(int**& m, int r, int c)` - checking conflicts appointments. Take matrix and check symmetrical row to `r` starts from `c` element and if it's 1 sets zero. Return true if set even one zero else return false.

`void find_zero_matrix(int**& m)` - zero all matrix and show does it has conflicts.

`bool find_zero_matrix_short(int**& m)` - return true if matrix has conflicts else false.


## Usege

It can be use to find conflicts in matrix.
Also you can determine the probability of conflicting assignments when changing the occupancy of the matrix "1" connectivity from 1% to 100% for a given dimension.

## Examples

Let we create matrix with some size and percent of occupancy.

Code

```
	int size;
    int percent;
    cin >> size;
    cin >> percent;

    int** mat = create_matrix(size, percent);
    p(mat);
```

Output

![example 1](/images/1.png)

Next, use `replace` to construct a matrix so that the zero matrix appeared on top

Code

```
	    replace(mat);
```

Output

![example 2](/images/2.png)

With help of `find_zero_matrix` we zero all conflicts.

Code

```
    find_zero_matrix(mat);
    p(mat);
```
Output

![example 3](/images/3.png)

Next, we try to find probability conflicts for matrix of size `size` and percent of occupancy `percent`. We create 100 matrix and use our algoritm.

Code

```
	int size;
    int percent;
    cin >> size;
    cin >> percent;
    double d = 0;
    for (int i = 0; i < 100; i++) {
        int** mat = create_matrix(size, percent);
        replace_w(mat);
        if (find_zero_matrix_short(mat))
            d++;

    }
    cout << d / 100;
    cout << endl;
```
Output

![example 4](/images/4.png)

Finaly, we try to find probability conflicts for matrix of size `size`. We create 100 matrix and use our algoritm starting from 1% to 100%.

Code

```
	int size;
    cin >> size;
    double d;
    for (int n = 0; n < 100; n++) {
        d = 0;
        for (int i = 0; i < 100; i++) {
            int** mat = create_matrix(size, n);
            replace_w(mat);
            if (find_zero_matrix_short(mat))
                d++;
        }
        cout << n << "%=> " << d/100 << "||";

    }
    cout << endl;
```
Output

![example 5](/images/5.png)

Remember that you can have another result because of random.

