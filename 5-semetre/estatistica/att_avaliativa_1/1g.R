data <- read.csv("seguro.csv", header = TRUE, sep = ";", dec = ",")

data$renda_categoria <- cut(data$renda,
    breaks = c(-Inf, 1.9, 3.9, 6.9, Inf),
    labels = c("Até 1,9", "2.0 a 3.9", "4.0 a 6.9", "7.0 ou mais"),
    right = TRUE)

freq_abs <- table(data$renda_categoria)

freq_rel <- prop.table(freq_abs) * 100

tabela_renda <- data.frame(Faixa = names(freq_abs),
    Frequencia = as.vector(freq_abs),
    Porcentagem = round(as.vector(freq_rel), 1))

print(tabela_renda)
