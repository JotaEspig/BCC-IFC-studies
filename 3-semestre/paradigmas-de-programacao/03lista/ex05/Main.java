
class Calculadora {
    public float somar(float a, float b) {
        return a + b;
    }
    public float subtrair(float a, float b) {
        return a - b;
    }
    public float dividir(float a, float b) {
        return a / b;
    }
    public float multiplicar(float a, float b) {
        return a * b;
    }
}


class CalculadoraCientifica extends Calculadora {
    public float potencia(float a, float b) {
        return (float) Math.pow(a, b);
    }
}

class TestaCalculadoras {
    public void testaCalculadoraNormal() {
        Calculadora calculadora = new Calculadora();
        float resultado = calculadora.somar(1.0f, 2.0f);
        System.out.println("O resultado da soma de 1.0 e 2.0 e: " + resultado);
        assert resultado == 3.0f;
        resultado = calculadora.subtrair(1.0f, 2.0f);
        System.out.println("O resultado da subtração de 1.0 e 2.0 e: " + resultado);
        assert resultado == -1.0f;
        resultado = calculadora.dividir(1.0f, 2.0f);
        System.out.println("O resultado da divisão de 1.0 e 2.0 e: " + resultado);
        assert resultado == 0.5f;
        resultado = calculadora.multiplicar(1.0f, 2.0f);
        System.out.println("O resultado da multiplicação de 1.0 e 2.0 e: " + resultado);
        assert resultado == 2.0f;
    }

    public void testaCalculadoraCientifica() {
        CalculadoraCientifica calculadora = new CalculadoraCientifica();
        float resultado = calculadora.potencia(2.0f, 3.0f);
        System.out.println("O resultado da potência e: " + resultado);
        assert resultado == 8.0f;
    }
}

public class Main {
    public static void main(String[] args) {
        TestaCalculadoras test = new TestaCalculadoras();
        test.testaCalculadoraNormal();
        test.testaCalculadoraCientifica();
    }
}
