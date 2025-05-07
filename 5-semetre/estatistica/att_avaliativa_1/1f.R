printf <- function(name, value) {
  cat(sprintf("%s: %s\n", name, value))
}

data <- read.csv("seguro.csv", header = TRUE, sep = ";", dec = ",")
t <- data$renda

printf("media", mean(t))
printf("mediana", median(t))
printf("moda", as.numeric(names(t)[which.max(t)]))
printf("sd", sd(t))
printf("coeficiente de variação", sd(t) / mean(t) * 100)
printf("1º quartil", quantile(t, 0.25))
printf("3º quartil", quantile(t, 0.75))
