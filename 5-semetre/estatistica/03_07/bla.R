library(tibble)
library(dplyr)

catln <- function(...) cat(..., "\n")


plotDNorm <- function(data) {
    catln("Mean salary: ", mean(data$salario_USD))

    old_options <- options(scipen = 999)
    on.exit(options(old_options)) # Restores the old options

    dn <- dnorm(data$salario_USD, mean = mean(data$salario_USD), sd = sd(data$salario_USD))
    plot(data$salario_USD, dn, xlab = "Salary Mean", ylab = "Density", main = "Density of Salary")
}


data <- read.csv("salarios.csv", sep = ";")
data <- as_tibble(data)

# list all pais_empreg, excluding duplicates
ordered <- data %>%
  group_by(pais_empreg) %>%
  mutate(count = n()) %>%
  ungroup() %>%
  arrange(desc(count))

countries <- unique(ordered$pais_empreg)
print(countries)

# graph of mean salary for each country
salaryCountries <- data %>%
  group_by(pais_empreg) %>%
  summarise(meanSalary = mean(salario_USD)) %>%
  arrange(desc(meanSalary))

par(mar = c(7.0, 7.0, 2.0, 2.0), mgp = c(5, 1, 0))
barplot(salaryCountries$meanSalary, names.arg = salaryCountries$pais_empreg,
        las = 2, col = "blue", xlab = "Country", ylab = "Mean Salary (USD)",
        main = "Mean Salary by Country")
readline()

# while loop
while (TRUE) {
    catln("Enter a country: ")
    country <- readline()
    if (country == "exit") {
        break
    }
    salaryCountry <- data[data$pais_empreg == country, ]
    plotDNorm(salaryCountry)
}
