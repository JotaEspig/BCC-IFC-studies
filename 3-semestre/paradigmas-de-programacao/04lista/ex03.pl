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
