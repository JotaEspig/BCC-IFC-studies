import socketserver
import threading

# Shared memory register
X = 0
X_mutex = threading.Lock()


class ThreadedTCPRequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        global X
        client_socket = self.request
        client_ip = self.client_address[0]
        print(f"[?] Handling request from {client_ip}")

        # Critical section guarded by mutex
        with X_mutex:
            client_socket.sendall(str(X).encode())
            resp = client_socket.recv(1024).decode().strip()
            X = int(resp)
            print(f"[✔] New X={X}")


class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    daemon_threads = True
    allow_reuse_address = True


if __name__ == "__main__":
    HOST, PORT = "0.0.0.0", 9000
    with ThreadedTCPServer((HOST, PORT), ThreadedTCPRequestHandler) as server:
        print(f"[*] Central server running with memory X=0 on {HOST}:{PORT}")
        server.serve_forever()
