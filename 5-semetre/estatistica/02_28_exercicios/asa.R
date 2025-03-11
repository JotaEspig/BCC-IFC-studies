library("readxl")


catln <- function(...) cat(..., "\n")


data <- read_excel("data.xls")

ids <- seq_len(nrow(data))

cat("PESO\n")

SD <- 19.8
z <- 1.96
error_margin <- 5
# n0 <- (z^2 * (prob) * (1 - (prob))) / (error_margin^2)
n0 <- (z^2 * SD^2) / (error_margin^2)
sample_size <- n0 / (1 + ((n0 / nrow(data))))
catln("N_0: ", n0)
catln("Tamanho populacional: ", nrow(data))
catln("Dimensionamento da amostra: ", sample_size)

samp_ids <- sample(ids, size = sample_size, replace = FALSE, prob = NULL)
data <- data[-1, ] # Remove first line (header)
data <- data[samp_ids, ]

print(data, n = Inf)

catln("Média: ", mean(data$PESO))
catln("Variância: ", var(data$PESO))
catln("Desvio padrão: ", sd(data$PESO))
catln("Margen de erro: ", mean(data$PESO) - error_margin, " - ",
      mean(data$PESO) + error_margin)
