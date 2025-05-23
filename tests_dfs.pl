:- ensure_loaded('dfs.pl').
:- use_module(library(plunit)).

run_dfs_test(Graph, N, Expected) :-
    length(Visited, N),
    maplist(=(not_visited), Visited),
    dfs(1, N, Graph, Visited, Result),

    (   permutation(Expected, Result)
    ->  format('PASSED: ~w -> ~w~n', [Graph, Result])
    ;   format('FAILED: ~w | Expected: ~w, Got: ~w~n', [Graph, Expected, Result]),
        fail
    ).

:- begin_tests(dfs).

test(empty_graph) :-
    run_dfs_test([], 0, []).
test(single_node) :-
    run_dfs_test([], 1, [1]).
test(linear_graph) :-
    run_dfs_test([(1,2),(2,3),(3,4)], 4,
    [1,2,3,4]).
test(cyclic_graph) :-
    run_dfs_test([(1,2),(2,3),(3,1),(1,4)], 4,
    [1,2,3,4]).
test(disconnected_graph) :-
    run_dfs_test([(1,2),(3,4)], 4,
    [1,2,3,4]).
test(custom_graph) :-
    run_dfs_test([(1,2),(1,3),(3,4),(3,5),(4,5),(5,1),(5,6)], 6,
    [1,2,3,4,5,6]).
test(linear_unordered_graph) :-
    run_dfs_test([(2,3),(1,2),(3,4)], 4,
    [2,3,4,1]).
test(binary_tree) :-
    run_dfs_test([(1,5),(1,2),(5,3),(5,7),(2,4),(2,6)], 7,
    [1,5,3,7,2,4,6]).
test(graph_with_back_edges) :-
    run_dfs_test([(1,2),(2,3),(3,4),(4,2),(3,5)], 5,
    [1,2,3,4,5]).
test(diamond_graph) :-
    run_dfs_test([(1,2),(1,3),(2,4),(3,4)], 4,
    [1,2,4,3]).
test(two_cycles_graph) :-
    run_dfs_test([(1,2),(2,1),(3,4),(4,3)], 4,
    [1,2,3,4]).
test(star_graph) :-
    run_dfs_test([(5,1),(5,2),(5,3),(5,4)], 5,
    [5,1,2,3,4]).
test(zigzag_tree) :-
    run_dfs_test([(1,5),(1,2),(5,4),(2,3)], 5,
    [1,5,4,2,3]).
test(complete_graph_k3) :-
    run_dfs_test([(1,2),(1,3),(2,1),(2,3),(3,1),(3,2)], 3,
    [1,2,3]).
test(cycle_with_tail) :-
    run_dfs_test([(1,2),(2,3),(3,1),(3,4),(4,5)], 5,
    [1,2,3,4,5]).
test(jumpy_tree) :-
    run_dfs_test([(1,2),(1,3),(2,4),(2,5),(3,6),(3,7)], 7,
    [1,2,4,5,3,6,7]).
test(complex_multi_cycle_graph) :-
    run_dfs_test([(1,2),(2,3),(3,1),(2,4),(4,5),(5,6),(6,4),(5,7)], 7,
    [1,2,3,4,5,6,7]).
test(bridge_graph) :-
    run_dfs_test([(1,2),(2,3),(3,4),(4,5),(3,5),(1,5)], 5,
    [1,2,3,4,5]).
test(sparse_tree) :-
    run_dfs_test([(1,2),(1,3),(2,4),(3,5)], 5,
    [1,2,4,3,5]).
test(multi_component_graph) :-
    run_dfs_test([(1,2),(3,4),(5,6),(6,7)], 7,
    [1,2,3,4,5,6,7]).
test(clover_graph) :-
    run_dfs_test([(1,2),(2,1),(1,3),(3,1),(1,4),(4,1)], 4,
    [1,2,3,4]).
test(fork_and_cycle_graph) :-
    run_dfs_test([(1,2),(1,3),(2,4),(3,4),(4,5),(5,2)], 5,
    [1,2,4,5,3]).
test(complex_cyclic_graph) :-
    run_dfs_test([(1,5),(1,2),(5, 3),(5,7),(2,4),(2,6),(3,1)], 7,
    [1,5,3,7,2,4,6]).

:- end_tests(dfs).
