data <- read.csv("seguro.csv", header = TRUE, sep = ";")
t <- table(data$instrucao, data$sinistro)
barplot(t,
        beside = FALSE,
        col = c("lightblue", "lightgreen", "salmon"),
        legend.text = TRUE,
        args.legend = list(title = "Instrução", x = "topright"),
        main = "Distribuição de Instrução por Sinistro",
        xlab = "Sinistro",
        ylab = "Frequência")
