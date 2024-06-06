aluno(joao).
aluno(maria).
aluno(ana).
aluno(antonio).

nota(joao, 10.0).
nota(maria, 7.0).
nota(ana, 3.0).
nota(antonio, 6.9).

frequencia(joao, 90).
frequencia(maria, 75).
frequencia(ana, 50).
frequencia(antonio, 70).

passou(X) :- aluno(X), nota(X, Z), Z >= 7.
passou2(X) :- aluno(X), nota(X, Z), Z >= 7, frequencia(X, Y), Y >= 75.
