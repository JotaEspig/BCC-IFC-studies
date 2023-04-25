# Quadro para coisas sem contexto

Demonstração:

((A -> B) & C) -> B (eq)

C -> A

1    ((A -> B) & C) -> B
------------------------
2       ((A -> B) & C)  (A)
3       ((A->B)&C)->B   (1,R)
4       B               (2,3,->E)
5       (A->B)          (2,&E)
6       C               (2,&E)
7       A               (4,5,->E)
8   C->A    (2-7,->I)
