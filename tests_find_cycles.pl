:- ensure_loaded('find_cycles.pl').
:- use_module(library(plunit)).

run_cycle_test(Graph, Expected) :-
    (   find_cycle(Graph, Cycle)
    ->  (   Cycle = Expected
        ->  format('PASSED: ~w -> ~w~n', [Graph, Cycle])
        ;   format('FAILED: ~w | Expected: ~w, Got: ~w~n', [Graph, Expected, Cycle]),
            fail
        )
    ;   (   Expected == none
        ->  format('PASSED: ~w -> no cycle~n', [Graph])
        ;   format('FAILED: ~w | Expected: ~w, Got: no cycle~n', [Graph, Expected]),
            fail
        )
    ).

:- begin_tests(find_cycle).

test(empty_graph) :-
    run_cycle_test([], none).
test(single_node) :-
    run_cycle_test([], none).
test(linear_graph) :-
    run_cycle_test([(1,2),(2,3),(3,4)], none).
test(simple_cycle) :-
    run_cycle_test([(1,2),(2,1)],
    [1,2,1]).
test(cyclic_graph) :-
    run_cycle_test([(1,2),(2,3),(3,1)],
    [1,2,3,1]).
test(disconnected_graph) :-
    run_cycle_test([(1,2),(3,4)], none).
test(graph_with_cycle) :-
    run_cycle_test([(1,2),(1,3),(3,4),(4,5),(5,1)],
    [1,3,4,5,1]).
test(multiple_cycles) :-
    run_cycle_test([(1,2),(2,1),(2,3),(3,4),(4,2)],
    [1,2,1]).
test(tree_structure) :-
    run_cycle_test([(1,2),(1,3),(2,4),(2,5),(3,6)], none).
test(complex_cycle) :-
    run_cycle_test([(1,2),(2,3),(3,4),(4,5),(5,2),(1,6)],
    [1,2,3,4,5,2]).
test(our_graph) :-
    run_cycle_test([(1,5),(1,2),(5,3),(5,7),(2,4),(4,1),(2,6),(3,1),(6,4)],
    [1,5,3,1]).

:- end_tests(find_cycle).
