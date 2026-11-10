# dashc — DSL para dashboards com gráficos

Compilador de uma linguagem de domínio específico (DSL) que descreve dashboards.
Recebe um arquivo de texto com a estrutura do dashboard e arquivos **CSV** ou
**JSON** como fonte de dados, e gera um **HTML** único com os gráficos em
[Highcharts](https://www.highcharts.com/).

Implementado em C com **flex** (léxico) e **bison** (sintático).
A gramática livre de contexto está em [`gramatica.txt`](gramatica.txt).

## Compilar e usar

Requer `gcc`, `make`, `flex` e `bison`.

```sh
make                # gera o executável ./dashc
make exemplos       # compila exemplos/*.dash para exemplos/*.html
```

```sh
./dashc painel.dash                       # gera painel.html e abre no navegador padrão
./dashc painel.dash --nao-abrir           # só gera o arquivo
./dashc painel.dash -o saida.html
./dashc painel.dash vendas=outro.csv      # define/substitui o arquivo da fonte "vendas"
```

Os caminhos das fontes declaradas no `.dash` são relativos ao próprio arquivo
`.dash`; os passados na linha de comando (`nome=arquivo`) são relativos ao
diretório atual, e o formato é deduzido da extensão.

Os dados são processados (filtro, agregação, ordenação) em tempo de compilação
e embutidos no HTML. O HTML carrega o Highcharts de uma CDN, então precisa de
internet para exibir os gráficos.

## A linguagem

```
dashboard "Painel de Vendas" {
    tema: auto;                 # claro | escuro | auto (segue o sistema)
    colunas: 2;                 # colunas da grade (1 a 6)

    fonte vendas = csv("dados/vendas.csv");
    fonte clima  = json("dados/clima.json", "blumenau.mensal");

    texto "Um parágrafo de texto livre.";

    indicador "Receita total" {
        dados: vendas;
        valor: soma(receita);
        prefixo: "R$ ";
        decimais: 0;
    }

    secao "Regiões" {
        grafico barra "Receita por região" {
            dados: vendas;
            x: regiao;
            y: soma(receita) como "Receita";
            filtro: mes != "Jan" e receita > 1000;
            ordenar: soma(receita) desc;
            limite: 5;
        }
    }
}
```

### Fontes de dados

| Forma | Descrição |
|---|---|
| `fonte n = csv("arq.csv");` | CSV com cabeçalho. Separador `,`, `;` ou tabulação (detectado). Com `;`, aceita decimais com vírgula (`1.234,56`). |
| `fonte n = json("arq.json");` | Array de objetos na raiz (ou o primeiro array de um objeto raiz). |
| `fonte n = json("arq.json", "a.b");` | Array de objetos no caminho `a.b`. |

### Elementos

| Elemento | Descrição |
|---|---|
| `grafico <tipo> "Título" { ... }` | Tipos: `linha`, `barra` (horizontal), `coluna`, `area`, `pizza`, `rosca`, `dispersao`. |
| `indicador "Título" { ... }` | Número em destaque. Indicadores seguidos formam uma faixa. |
| `texto "..." ;` | Parágrafo. |
| `secao "Título" { ... }` | Agrupa elementos sob um subtítulo (pode aninhar). |

### Propriedades

| Propriedade | Vale em | Descrição |
|---|---|---|
| `dados: fonte;` | ambos | Fonte de dados (obrigatória). |
| `x: coluna;` | gráfico | Categorias (ou eixo X numérico em `dispersao`). Obrigatória. |
| `y: série, série...;` | gráfico | Uma ou mais séries. Obrigatória. |
| `valor: agregação;` | indicador | Valor exibido. Obrigatória. |
| `filtro: expr;` | ambos | Mantém só as linhas em que a expressão é verdadeira. |
| `ordenar: série [asc\|desc];` | gráfico | Ordena os pontos. |
| `limite: N;` | gráfico | Mantém os N primeiros pontos (após ordenar). |
| `titulo_x`, `titulo_y: "..."` | gráfico | Títulos dos eixos. |
| `prefixo`, `sufixo: "..."` | ambos | Texto antes/depois dos valores (ex.: `"R$ "`, `" %"`). |
| `decimais: N;` | ambos | Casas decimais (0 a 6). |
| `largura: N;` | gráfico | Quantas colunas da grade o gráfico ocupa. |
| `altura: N;` | gráfico | Altura em pixels (padrão 320). |
| `empilhado: sim\|nao;` | barra, coluna, area | Empilha as séries. |
| `cores: "#hex", ...;` | gráfico | Substitui a paleta padrão. |

### Séries e expressões

Uma série é uma expressão, opcionalmente dentro de uma agregação e com um nome:

```
y: receita;                                  # uma linha da fonte = um ponto
y: soma(receita) como "Receita",             # agrupa pelas categorias de x
   soma(receita - custo) como "Lucro";
```

- Agregações: `soma`, `media`, `minimo`, `maximo`, `contagem(expr)` (valores não
  vazios) e `contagem()` (linhas). Com agregação, as linhas são agrupadas pelo
  valor de `x`. Não é possível misturar séries agregadas e não agregadas.
- Operadores, da menor para a maior precedência: `ou`, `e`, `nao`,
  comparações (`== != < <= > >=`), `+ -`, `* /`, `-` unário. Também valem
  `||`, `&&` e `!`.
- Operandos: números, strings (`"Sul"`) e nomes de coluna. Colunas com espaços
  ou com nome de palavra reservada estrita vão entre colchetes:
  `[Receita Total]`, `[e]`.
- Células vazias são nulas: operações aritméticas com nulo resultam em nulo, e
  agregações ignoram valores não numéricos. Booleanos de JSON viram os textos
  `"true"` e `"false"`.
- Comentários: `# ...`, `// ...` e `/* ... */`.

## Estrutura do projeto

```
gramatica.txt      gramática livre de contexto da linguagem
src/lexer.l        analisador léxico (flex)
src/parser.y       analisador sintático (bison), constrói a AST
src/ast.[ch]       árvore sintática abstrata
src/dados.[ch]     leitores de CSV e JSON
src/semantico.[ch] análise semântica e avaliação de expressões
src/gerador.[ch]   geração do HTML + Highcharts
src/main.c         linha de comando e encadeamento das fases
exemplos/          dois dashboards de exemplo com seus dados
```

Erros léxicos, sintáticos e semânticos são reportados com arquivo e linha, e
nenhum HTML é gerado quando há erro:

```
painel.dash:6:40: erro sintático: não esperava y, esperava ';'
painel.dash:8: erro: coluna 'lucro' não existe na fonte 'v' (colunas: mes, regiao, receita, custo)
```
