% vi:syntax=prolog
% -*- mode: prolog -*-

%deployment(_) :- fail.
%in_namespace(_, _) :- fail.
%label(_, _) :- fail.
%namespace(_) :- fail.
%service(_) :- fail.

:- use_module(library(pprint)).
:- consult("../state/1-facts").

service_eligible(_).

service_graph(UID, service_box(uid(UID), name(Name), labels(Labels))) :-   % „G ist der Servicegraph zu S“
    object_name(UID, Name),
    findall(X, label(UID, X), Labels).

deployment_graph(UID, deployment_box(uid(UID), name(Name), labels(Labels))) :-
    object_name(UID, Name),
    findall(X, label(UID, X), Labels).

namespace_graph(UID, namespace_box(uid(UID), name(Name), items(Items))) :-
    object_name(UID, Name),
    findall(X, (in_namespace(S, Name), service(S), service_graph(S, X), service_eligible(S)), SS),
    findall(X, (in_namespace(D, Name), deployment(D), deployment_graph(D, X)), DS),
    append([SS, DS], Items).

graph(G) :-
    findall(X, (namespace(N), namespace_graph(N, X)), G).

printgraph :-
    graph(G),
    prolog_pretty_print:print_term(k8s_deployment(G), []).
