# Quadro para coisas sem contexto

H   := (P & (P -> Q)) -> Q
~H  := ~((P & (P -> Q)) -> Q)
     = ~(~(P & (~P v Q)) v Q)
     = P & (~P v Q) & ~Q
~Hc := {P, {~P, Q}, ~Q}

Resolução:
.1 {P}
.2 {~P, Q}
.3 {~Q}
.4 {Q} Res(.1, .2)
.5 {}  Res(.3, .4)
Logo, temos que que ~H é uma contradição, portanto para toda I, I[H]=T

====

Det := determinado
Int := inteligente
Atl := Atleta
Per := Perdedor
AmT := Amante Tenis

(Det & Atl) -> ~Per <=> ~(Det & Alt) v ~Per
                    <=> ~Det v ~Alt v ~Per

~H := ~((Det & Int & ((Det & Atl) -> ~Per) & (AmT -> Atl) & (Int -> AmT)) -> ~Per)
<=> ~(~(G) v ~Per)
<=> G & Per
<=> (Det & Int & (~(Det & Atl) v ~Per) & (~Amt v Atl) & (~Int v AmT)) & Per
<=> Det & Int & (~Det v ~Atl v ~Per) & (~Amt v Atl) & (~Int v AmT) & Per

.1 {Det}
.2 {Int}
.3 {~Det, ~Atl, ~Per}
.4 {~AmT, Atl}
.5 {~Int, AmT}
.6 {Per}
.7 {~Atl, ~Per} Res(.1, .3)
.8 {~Atl} Res(.6, .7)
.9 {~AmT} Res(.4, .8)
.10 {~Int} Res(.5, .9)
.11 {} Res(.2, .10)
Logo H é uma tautologia

H := ~(~P) <-> P
~H = ~((P -> P) & (P -> P))
<=>  ~((~P v P) & (~P v P))
<=>  ~(~P v P) v ~(~P v P)
<=>  (P & ~P) v (P & ~P)
<=>  (P v (P & ~P)) & (~P v (P & ~P))
<=>  ((P v P) & (P v ~P)) & ((~P v P) & (~P v ~P))
<=>  (P v P) & (P v ~P) & (~P v P) & (~P v ~P)
.1 {P}
.2 {P, ~P}
.3 {~P, P}
.4 {~P}
.5 {P} Res(.1, .2)
.6 {P} Res(.3, .5)
.7 {} Res(.4, .6)
logo H é uma tautologia
