package src;

interface IVehicle {
    void move();
}

class Airplane implements IVehicle {
    @Override
    public void move() {
        System.out.println("Zooom");
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println("Hello World");
        Airplane c = new Airplane();
        c.move();
    }
}
