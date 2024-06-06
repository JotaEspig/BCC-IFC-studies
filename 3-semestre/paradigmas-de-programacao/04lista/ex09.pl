aluno(joao).
aluno(maria).
aluno(ana).
aluno(antonio).

nota(joao, 10.0).
nota(maria, 7.0).
nota(ana, 3.0).
nota(antonio, 6.9).

passou(X) :- aluno(X), nota(X, Z), Z >= 7.
