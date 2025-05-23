:- initialization(main).

main :-
    Graph = [(1,5),(1,2),(5,3),(5,7),(2,4),(4,1),(2,6),(3,1),(6,4)],
    (find_cycle(Graph, Cycle) ->
        write(Cycle)
    ;
        write('No cycles found')
    ).

find_cycle(Graph, Cycle) :-
    member((Start,_), Graph),
    path(Start, Graph, [Start], Cycle).

path(Node, Graph, Visited, Cycle) :-
    member((Node, Next), Graph),
    (member(Next, Visited) ->
        reverse([Next|Visited], Cycle),
        append(_, [Next|_], Visited)
    ;
        path(Next, Graph, [Next|Visited], Cycle)
    ).