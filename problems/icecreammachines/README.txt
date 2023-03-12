
# Intended solution
Use the union-find data structure to keep track of which islands belong to the
same state. Recall that this data structure is usually implemented using a
disjoint-set forest, so at all times we can identify each state by the island
at the root of the state's tree.

We would like to keep track of which pairs of states contain islands whose
inhabitants distrust each other, and for this purpose we keep an (unordered)
edge set for each state $A$'s root island containing edges to all the root
islands of states $B$ such that some pair of islands in $A$ and $B$ distrust
each other. For example, if $A$ is a state that currently contains islands
$a_1$ and $a_2$, where $a_1$ is at the root of the state's tree in the
disjoint set forest, and $B$ is a state currently only containing the island
$b_1$, then if the inhabitants of the islands $a_2$ and $b_1$ distrust each
other then $a_1$ should have an edge to $b_1$, and vice versa.

In the beginning, each state only contains a single island and so each island
is at the root of its state's tree. This means that the edge sets should simply
contain all the $M$ pairs of islands given in the input.

However, when two states with root islands $a$ and $b$ are merged, where $a$ is
chosen as the root of the new merged state, then all edges $(b, c)$ should be
replaced by edges $(a, c)$. This is done by simply iterating over all of $b$'s
incident edges, removing them from the sets of both endpoints, and finally
adding the updated edges.

To see why this is efficient enough, note that as long as our union find
implementation uses either union-by-rank or union-by-size when merging two
sets, the number of times any particular island will get a new root island
representing its state is bounded by $\log N$. This implies that the number of
times any particular edge needs to be updated because either of its endpoints
gets a new root island is bounded by $2 \log N$, and hence the time complexity
of updating the edges is $\mathcal{O}(M \log N)$.

Finally we note that with the help of these edge sets we can easily check if
two states contain islands that distrust each other, by using the union find
data structure to find the root island of each state and then checking if there
is an edge between the roots. These checks can be done in
$\mathcal{O}(Q \alpha(N))$, where $\alpha$ is the inverse Ackermann function.

The total time complexity of the algorithm is
$$\mathcal{O}(M \log N + (N+Q) \alpha(N))$$

## Subtasks

$N \leq 500$. In this case there is no need for union find. One solution is to
store an edge for each pair of islands belonging to states that cannot be
merged. When two states are merged, the edge sets (which can simply be
represented using an $N \times N$ adjacency matrix) are updated by
iterating over all islands in the states to be merged and taking the union of
the islands that they distrust.  Then merging two states takes
$\mathcal{O}(N^2)$ time, so the total time complexity is
$\mathcal{O}(N^3+M+Q)$.

$M \leq 500$. This subtask can be solved
by using union find to keep track of state membership, and for each query
we iterate over all pairs $(a_i, b_i)$ of islands that distrust each other
and check if $a_i$ belongs to the same state as the first island in the
query, and $b_i$ belongs to the same state as the second island. The time
complexity is $\mathcal{O}(MQ+(N+Q)\alpha(N))$.

\textbf{It is guaranteed that at most one of the proposals should be
rejected}. Here we can do a binary search over how many proposals to
approve before we have to reject a proposal. To check if the first $q$
proposals can all be approved, we construct a graph $G$ consisting of all
the edges $(a_i, b_i)$ for proposals $1$ through $q$. Then we identify
the connected components in $G$ and check if any component contains a
pair of islands that distrust each other, in which case we can conclude
that the first $q$ proposals can not all be approved. Note that there is
no need for the union find data structure in this solution. The time
complexity is $\mathcal{O}((N+M)\log Q)$.


