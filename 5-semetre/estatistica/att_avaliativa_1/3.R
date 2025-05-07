data <- read.csv("seguro.csv", header = TRUE, sep = ";", dec = ",")

# set seed
set.seed(12345)

# Amostragem ASA
amostra <- data[sample(1:nrow(data), 18, replace=FALSE), ]
tabela <- data.frame(
  ID = amostra$ID,
  Idade = amostra$idade
)
print(tabela)
cat("Media estimada: ", mean(amostra$idade), "\n")
cat("Margem de erro: ", 6, "\n")
cat("Intervalo de confiança: ", mean(amostra$idade) - 6, " a ", mean(amostra$idade) + 6, "\n")
cat("Média verdadeira: ", mean(data$idade), "\n")
print(amostra$idade)
