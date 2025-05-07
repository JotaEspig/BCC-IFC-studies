data <- read.csv("seguro.csv", header = TRUE, sep = ";")
t <- table(data$sinistro, data$estado)

porcentagem <- prop.table(t) * 100

print(t)
