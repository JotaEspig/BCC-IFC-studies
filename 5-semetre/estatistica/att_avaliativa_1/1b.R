data <- read.csv("seguro.csv", header = TRUE, sep = ";")
t <- table(data$instrucao)

barplot(t, main = "Escolaridade", xlab = "Escolaridade", ylab = "Frequência", ylim=c(0,60))
