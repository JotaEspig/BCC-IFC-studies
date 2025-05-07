data <- read.csv("seguro.csv", header = TRUE, sep = ";", dec = ",")

estatisticas_renda <- function(x) {
  media <- mean(x, na.rm = TRUE)
  mediana <- median(x, na.rm = TRUE)
  quartis <- quantile(x, probs = c(0.25, 0.75), na.rm = TRUE)
  desvio_padrao <- sd(x, na.rm = TRUE)
  coef_variacao <- (desvio_padrao / media) * 100
  
  return(c(
    Média = round(media, 2),
    Mediana = round(mediana, 2),
    Q1 = round(quartis[1], 2),
    Q3 = round(quartis[2], 2),
    Desvio_Padrão = round(desvio_padrao, 2),
    Coef_Variação = round(coef_variacao, 2)
  ))
}

estat_por_instrucao <- by(data$renda, data$instrucao, estatisticas_renda)

estat_df <- do.call(rbind, estat_por_instrucao)
print(estat_df)
