data <- read.csv("seguro.csv", header = TRUE, sep = ";", dec = ",")

hist(data$renda,
     breaks = 10,
     col = "lightblue",
     main = "Distribuição de Renda",
     xlab = "Renda",
     ylab = "Frequência"
)

boxplot(data$renda,
     col = "lightgreen",
     main = "Boxplot de Renda",
     xlab = "Renda",
     ylab = "Frequência"
)
