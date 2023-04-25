# Lógica para Ciência da Computação - João Nunes de Souza
## Capítulo 5 INDUÇÃO

Princípio da indução finita:
<b>[base + passo] => Para todo n, A(n)</b>

#### Primeira forma da indução:
    1. Base da indução, A(1) é verdadeira
    2. Passo de indução, se A(n) é verdadeira, então A(n+1) é verdadeira também
    
#### Segunda forma da indução:
    1. Base da indução, A(1) é verdadeira
    2. Passo de indução, se para todo k; 1 <= k <= n, A(k) é verdadeira,
    então A(n+1) é verdadeira também

### Princípio da Indução na Lógica
Seja B[E] uma asserção que se refere a uma fórmula E. Se as propriedades 1 e 2
são verdadeiras, então Para todo E, B[E].
    1. Base da indução, Para todo símbolo proposicional P, B[P]. B[true] é
    verdadeira e B[false] é verdadeira
    2. Passo da indução, Sejam duas fórmulas G e H. Se B[G] e B[H] são
    verdadeiras, então B[¬H], B[GvH], B[G&H], B[G->H], B[G<->H] são verdadeiras

<b>[Base lógica, Passo lógico] => [Para toda fórmula E, B[E]]</b>
A demonstração dessa proposição é feita utilizando a segunda forma do príncipio
da indução finita.

#### Demonstração da proposição
Considere a asserção A(n) = {B[E] para toda fórmula E | comp[E]=n}. Isso
significa que {Para todo E, B[E]} (eq) {Para todo n, A(n)}.
A demonstração do princípio se consiste em demonstrar a implicação:
[{Ba + Pa} => Para todo n, A(n)] => [{B-log + P-log} => Para todo E, B[E]] (eq)
[[{Ba + Pa} => Para todo n, A(n)] e {B-log + P-log}] => Para todo E, B[E].

Agora sabendo que {Para todo n, A(n)} (eq) {Para todo E, B[E]}, reduzimos a
implicação:
[[{Ba + Pa} => Para todo n, A(n)] e {B-log + P-log}] => Para todo n, A(n)
Agora, para demonstrar essa implicação, é preciso supor o antecedente e
demonstrar o consequênte. Portanto:
[{Ba + Pa} => Para todo n, A(n)] e {B-log + P-log}.

Em seguida, como sabemos que o consequênte dessa implicação:
{Ba + Pa} => Para todo n, A(n)
é o mesmo do que da implicação do princípio, basta demonstrar que:
{B-log + P-log} => {Ba + Pa}
onde se tem:
- B-log = B[P], B[false] é verdadeira e B[true] é verdadeira
- P-log = Sejam G e H fórmulas, se B[G] e B[H], então B[¬G], B[GvH], B[G&H],
  B[G->H] e B[G<->H]
- Ba = A(1) é verdadeira
- Pa = Para todo k; 1 <= k <= n, se A(k) é verdadeira, então A(n+1) também é.

Considerando isso, temos:
A(n) <=> B[E] para toda fórmula E | comp[E] = n
e
A(1) <=> B[E] para toda fórmula E | comp[E] = 1, i.e. B[P]

Como comp[E]=1 <=> P, então B-log (eq) Ba, logo resta provar que P-log => Pa
- P-log = {B[G] e B[H]} => {B[¬H], B[GvH], B[G&H], B[G->H] e B[G<->H]}
- Pa = A(k), 1 <= k <= n => A(n+1)
Temos que P-log => Pa e
{{B[G] e B[H]}=>{B[¬H], B[GvH], B[G&H], B[G->H], B[G<->H]} e {A(k), 1<=k<=n}}
=> A(n+1)
Note que agora precisamos supor o antecedente e demonstrar A(n+1).
Partindo de: A(n) <=> B[E] | comp[E]=n
Temos que: A(k), 1<=k<=n <=> B[G] e B[H] | comp[G]<=n e comp[H]<=n
Então, como temos:




