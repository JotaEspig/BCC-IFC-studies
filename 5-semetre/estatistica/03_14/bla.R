# CARREGAR O PACOTE
library(data.table)

# LEITURA DA BASE
dados <- fread(input = "salarios.csv", header = T, na.strings = "NA", data.table = FALSE, dec=",")

# Verificação da leitura
class(dados)
dim(dados)
names(dados)
str(dados)
head(dados)
tail(dados)

sapply(dados, function(x)(sum(is.na(x)))) # contagem de dados faltantes

#------------------
# TABELAS e GRÁFICOS

# Construção de tabela  e gráfico para uma variável qualitativa e uma quantitativa
# Exemplo 1: Salário em USD (salario_USD) por nível de experiência (experiencia = EN, MI, SE, EX) 

tabela.medias <- aggregate(dados$salario_USD, by=list(dados$experiencia), FUN="mean")
colnames(tabela.medias) <- c("Experiencia","Sal_Medio")
tabela.medias 

library(ggplot2)
ggplot(tabela.medias, aes(x=Experiencia, y=Sal_Medio)) + 
  geom_bar(stat="identity")

# Recodifiar a variável experiencia para ficar na ordem menor para maior

dados$experiencia[dados$experiencia == "EN"] = "1:EN"
dados$experiencia[dados$experiencia == "MI"] = "2:MI"
dados$experiencia[dados$experiencia == "SE"] = "3:SE"
dados$experiencia[dados$experiencia == "EX"] = "4:EX"

tabela.medias <- aggregate(dados$salario_USD, by=list(dados$experiencia), FUN="mean")
colnames(tabela.medias) <- c("Experiencia","Sal_Medio")
tabela.medias 

library(ggplot2)
ggplot(tabela.medias, aes(x=Experiencia, y=Sal_Medio)) + 
  geom_bar(stat="identity")

# Construção de gráfico para duas variáveis quantitativas
# Exemplo 2: Resposta dos pacientes a dois tipos de drogas em 5 níveis de dosagem

dose  <- c(20, 30, 40, 45, 60)
drugA <- c(16, 20, 27, 40, 60)
drugB <- c(15, 18, 25, 31, 40)

# Gráfico de linha relacionando dose para resposta da droga A
plot(dose, drugA, type="b")
plot(dose, drugA, type="b", lty=2, pch=17)

# Exemplo 3: Comparando a resposta dos pacientes a dois tipos de drogas por dose

dose  <- c(20, 30, 40, 45, 60)
drugA <- c(16, 20, 27, 40, 60)
drugB <- c(15, 18, 25, 31, 40)

opar <- par(no.readonly=TRUE)
par(lwd=2, cex=1.5, font.lab=2)

plot(dose, drugA, type="b",                                        
     pch=15, lty=1, col="red", ylim=c(0, 60),                         
     main="Droga A vs. Droga B",                                    
     xlab="Dosagem da droga", ylab="Resposta da droga")

lines(dose, drugB, type="b",                                       
      pch=17, lty=2, col="blue")                                        
abline(h=c(30), lwd=1.5, lty=2, col="gray") 
library(Hmisc)                             
minor.tick(nx=3, ny=3, tick.ratio=0.5)      

legend("topleft", inset=.05, title="Drug Type", c("A","B"),
       lty=c(1, 2), pch=c(15, 17), col=c("red", "blue"))

par(opar)

# Exemplo 4: Construir uma tabela para a variável salário (salario_USD)
# Construção de tabela para uma variável quantitativa

library(psych)
# install.packages("psych")

dados$Cat_Salario[dados$salario_USD <100000]  = "G1"
dados$Cat_Salario[dados$salario_USD >=100000 & dados$salario_USD <200000]  = "G2"
dados$Cat_Salario[dados$salario_USD >=200000 & dados$salario_USD <300000]  = "G3"
dados$Cat_Salario[dados$salario_USD >=300000 & dados$salario_USD <400000]  = "G4"
dados$Cat_Salario[dados$salario_USD >=400000]  = "G5"
freq.tabela <- table(dados$Cat_Salario, useNA = "ifany") 
freq.tabela

# Exemplo 5: Construir um gráfico para a variável salário (salario_USD)
# Histograma

library(dplyr)
library(ggplot2)
hist(dados$salario_USD)
hist(dados$salario_USD,
     breaks=6)
hist(dados$salario_USD,
     main="Distribuição Salarial em Data Science",
     xlab="Salários em USD",
     ylab = "número de colaboradores",
     col="darkmagenta",
     xaxt = 'n',
     freq=TRUE)
myTicks = axTicks(1)
axis(1, at = myTicks, labels = formatC(myTicks, format = 'd'))

# Explorando bases nativas do R
# Exemplo 6 - base mtcars

data() # mostra os conjuntos de dados disponíveis
library(help = "datasets")

?mtcars

plot(mtcars$cyl,mtcars$mpg)


# Combinação de gráficos
# Exemplo 7: Quatro gráficos combinados em duas linhas e duas colunas para variáveis da base mtcars

attach(mtcars)
opar <- par(no.readonly=TRUE)
par(mfrow=c(2,2))
plot(wt,mpg, main="Scatterplot of wt vs. mpg")
plot(wt,disp, main="Scatterplot of wt vs. disp")
hist(wt, main="Histogram of wt")
boxplot(wt, main="Boxplot of wt")
par(opar)
detach(mtcars)





