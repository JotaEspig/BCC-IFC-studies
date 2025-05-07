data <- read.csv("seguro.csv", header = TRUE, sep = ";")
t <- table(data$sinistro)

porcentagem <- prop.table(t) * 100

tabela <- data.frame(
  Sinistro = names(t),
  Frequencia = as.vector(t),
  Porcentagem = round(as.vector(porcentagem), 2)
)

print(tabela)
