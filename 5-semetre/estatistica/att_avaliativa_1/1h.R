data <- read.csv("seguro.csv", header = TRUE, sep = ";", dec = ",")

boxplot(renda ~ instrucao,
        data = data,
        col = c("lightblue", "lightgreen", "lightpink"),
        main = "Distribuição da Renda por Instrução",
        xlab = "Instrução",
        ylab = "Renda",
        border = "black")
