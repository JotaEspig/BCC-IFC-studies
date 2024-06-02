import java.time.LocalDate;

class Data {
    int dia;
    int mes;
    int ano;

    public Data() {
        LocalDate data = LocalDate.now();
        this.dia = data.getDayOfMonth();
        this.mes = data.getMonthValue();
        this.ano = data.getYear();
    }

    public Data(int dia, int mes, int ano) {
        this.dia = dia;
        this.mes = mes;
        this.ano = ano;
        if (!isValid()) {
            throw new IllegalArgumentException("Data inválida");
        }
    }

    public boolean isValid() {
        try {
            LocalDate.of(this.ano, this.mes, this.dia);
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    public void proximoDia() {
        LocalDate data = LocalDate.of(this.ano, this.mes, this.dia);
        data = data.plusDays(1);
        this.dia = data.getDayOfMonth();
        this.mes = data.getMonthValue();
        this.ano = data.getYear();
    }

    public String toString() {
        return this.dia + "/" + this.mes + "/" + this.ano;
    }

    public void imprime() {
        System.out.println(this.toString());
    }
}

public class Main {
    public static void main(String[] args) {
        Data data = new Data();
        for (int i = 0; i < 10; i++) {
            data.proximoDia();
            data.imprime();
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // Teste de data inválida
        // Data dataErrada = new Data(30, 2, 2024);
        // dataErrada.imprime();
    }
}
