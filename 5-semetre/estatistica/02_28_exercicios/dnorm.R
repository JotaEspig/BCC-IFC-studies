library("readxl")


printfln <- function(...) cat(..., "\n")


set.seed(1)

# Load the data
data <- read_excel("data.xls")

bla <- dnorm(data$PESO, mean = mean(data$PESO), sd = sd(data$PESO))

plot(data$PESO, bla)
