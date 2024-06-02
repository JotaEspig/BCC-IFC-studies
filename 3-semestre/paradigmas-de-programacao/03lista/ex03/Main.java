class Port {
    private boolean isOpen;
    public String color;
    public Float posX;
    public Float posY;
    public Float posZ;

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

public class Main {
    public static void main(String[] args) {
        Port port = new Port();
        port.open();
        port.paint("red");
        System.out.println(port.isOpen());
    }
}
