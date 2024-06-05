pessoa(joao).
pessoa(maria).
pessoa(pedro).
pessoa(marcos).
pessoa(joana).
pessoa(ricardo).
pessoa(bruno).
pessoa(victor).

% sexo(X, S) significa X é do sexo S
sexo(joao, m).
sexo(maria, f).
sexo(pedro, m).
sexo(marcos, m).
sexo(joana, f).
sexo(ricardo, m).
sexo(bruno, m).
sexo(victor, m).

% pai(X, Y) significa X é pai de Y
pai(joao, maria).
pai(joao, pedro).
pai(joao, marcos).
pai(joao, joana).
pai(pedro, ricardo).
pai(pedro, bruno).
pai(bruno, victor).

% irmao(X, Y) significa X é irmão de Y
irmao(X, Y) :- pai(Z, X), pai(Z, Y), sexo(X, m), X \== Y.

% irma(X, Y) significa X é irma de Y
irma(X, Y) :- pai(Z, X), pai(Z, Y), sexo(X, f), X \== Y.

% neto(X, Y) significa X é neto de Y
neto(X, Y) :- pai(Y, Z), pai(Z, X), sexo(X, m).

% neta(X, Y) significa X é neta de Y
neta(X, Y) :- pai(Y, Z), pai(Z, X), sexo(X, f).

% bisneto(X, Y) significa X é bisneto de Y
bisneto(X, Y) :- pai(Z, X), neto(Z, Y), sexo(X, m).

% bisneta(X, Y) significa X é bisneta de Y
bisneta(X, Y) :- pai(Z, X), neto(Z, Y), sexo(X, f).

% comando para descobrir bisneto de joao: bisneto(X, joao).
