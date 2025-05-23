:- initialization(main).

main :-
    Graph = [(1,5),(1,2),(5,3),(5,7),(2,4),(2,6)],
    N = 7,
    start_dfs(Graph, N).

start_dfs(Graph, N) :-
    length(Visited, N),
    maplist(=(not_visited), Visited),
    dfs(1, N, Graph, Visited, VisitedOrder),
    write('Traversal order: '), write(VisitedOrder), nl.

dfs(Current, N, _, _, []) :- Current > N, !.
dfs(Current, N, Graph, Visited, VisitedOrder) :-
    Current =< N,
    nth1(Current, Visited, Status),
    (Status == not_visited ->
        explore_vertex(Current, Graph, Visited, UpdatedVisited, CurrentOrder),
        NextIdx is Current + 1,
        dfs(NextIdx, N, Graph, UpdatedVisited, RestOrder),
        append(CurrentOrder, RestOrder, VisitedOrder)
    ;
        NextIdx is Current + 1,
        dfs(NextIdx, N, Graph, Visited, VisitedOrder)
    ).

% Explore the vertex
explore_vertex(Node, Graph, Visited, UpdatedVisited, [Node|VisitedOrder]) :-
    mark_visited(Node, Visited, TempVisited),
    findall(Neighbor, member((Node, Neighbor), Graph), Neighbors),
    explore_neighbors(Neighbors, Graph, TempVisited, UpdatedVisited, VisitedOrder).

mark_visited(1, [_|Rest], [visited|Rest]) :- !.
mark_visited(Index, [Head|Rest], [Head|NewRest]) :-
    Index > 1,
    PrevIndex is Index - 1,
    mark_visited(PrevIndex, Rest, NewRest).

% Explore the vertex's neighbors
explore_neighbors([], _, Visited, Visited, []).
explore_neighbors([Neighbor|Remaining], Graph, Visited, FinalVisited, Order) :-
    nth1(Neighbor, Visited, Status),
    (Status == not_visited ->
        explore_vertex(Neighbor, Graph, Visited, PostVisit, NeighborOrder),
        explore_neighbors(Remaining, Graph, PostVisit, FinalVisited, RemainingOrder),
        append(NeighborOrder, RemainingOrder, Order)
    ;
        explore_neighbors(Remaining, Graph, Visited, FinalVisited, Order)
    ).
