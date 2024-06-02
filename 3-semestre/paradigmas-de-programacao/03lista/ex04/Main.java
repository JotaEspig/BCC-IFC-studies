class Port {
    private boolean isOpen;
    public String color;
    public Float posX;
    public Float posY;
    public Float posZ;

    public Port(String color, Float posX, Float posY, Float posZ) {
        this.isOpen = true;
        this.color = color;
        this.posX = posX;
        this.posY = posY;
        this.posZ = posZ;
    }

    public void open() {
        this.isOpen = true;
    }

    public void close() {
        this.isOpen = false;
    }

    public void paint(String color) {
        this.color = color;
    }

    public boolean isOpen() {
        return this.isOpen;
    }
}

class House {
    Port port1;
    Port port2;
    Port port3;
    String color;

    public House() {
        port1 = new Port("", 0.0f, 0.0f, 0.0f);
        port2 = new Port("", 0.0f, 0.0f, 0.0f);
        port3 = new Port("", 0.0f, 0.0f, 0.0f);
        color = "";
    }

    public void paint(String color) {
        this.color = color;
    }

    public String getColor() {
        return this.color;
    }

    public int getAmountOfOpenPorts() {
        int amount = 0;
        if (port1.isOpen()) {
            amount++;
        }
        if (port2.isOpen()) {
            amount++;
        }
        if (port3.isOpen()) {
            amount++;
        }
        return amount;
    }

    public Port getPort1() {
        return port1;
    }

    public Port getPort2() {
        return port2;
    }

    public Port getPort3() {
        return port3;
    }
}

class TestHouse {
    House house;

    public TestHouse() {
        house = new House();
    }

    public void testHouse() {
        house.paint("red");
        house.getPort1().open();
        house.getPort2().open();
        house.getPort3().open();
        System.out.println(house.getAmountOfOpenPorts());
        System.out.println(house.getColor());
        assert house.getAmountOfOpenPorts() == 3 : "A casa deve ter 3 portas abertas";
        assert house.getColor().equals("red") : "A casa deve ter a cor vermelha";
    }
}

public class Main {
    public static void main(String[] args) {
        TestHouse testHouse = new TestHouse();
        testHouse.testHouse();
    }
}
