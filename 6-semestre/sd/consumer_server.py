import socket

SERVER_HOST = "127.0.0.1"
SERVER_PORT = 9000

X = 0


def consumer(op, operand):
    """Send operation to central server and wait for result."""
    global X

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((SERVER_HOST, SERVER_PORT))
        resp = sock.recv(1024).decode()
        x = int(resp.strip())
        res = 0
        if op == "ADD":
            res = x + operand
        elif op == "SUB":
            res = x - operand
        elif op == "MUL":
            res = x * operand
        elif op == "DIV":
            res = x // operand

        sock.sendall(str(res).encode())
        print(f"[Consumer] {op} {operand} -> {res}")
        X = res


if __name__ == "__main__":
    print("[*] Consumer started")
    print("ADD")
    consumer("ADD", 10)
    print("MUL")
    consumer("MUL", 2)
    print("SUB")
    consumer("SUB", 4)
    print("DIV")
    consumer("DIV", 2)
    print(X)
