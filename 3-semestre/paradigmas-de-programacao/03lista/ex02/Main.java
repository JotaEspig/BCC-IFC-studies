import java.util.*;

class Password {
    Scanner in = new Scanner(System.in);
    String password = "";
    public int attempts = 0;
    public boolean blocked = false;

    public Password(String password) {
        this.password = password;
    }

    public boolean entraSenha() {
        if (blocked) {
            System.out.println("Password blocked!");
            return false;
        }

        boolean correct = inputPassword(in);
        if (correct) {
            attempts = 0;
            return true;
        } else {
            attempts++;
            block();
            if (!blocked)
                System.out.println("Wrong password");
        }

        return entraSenha();
    }

    public void trocarSenha() {
        if (!entraSenha()){
            return;
        }

        System.out.println("Type your new password");
        System.out.print("> ");
        String newPassword = in.nextLine();
        password = newPassword;
    }

    boolean inputPassword(Scanner in) {
        System.out.println("Type your password");
        System.out.print("> ");
        String password = in.nextLine();
        return this.password.equals(password);
    }

    void block() {
        if (attempts >= 3) {
            blocked = true;
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Password s = new Password("UEPA1234");
        s.trocarSenha();
        System.out.println(s.entraSenha());
    }
}
