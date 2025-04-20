import socket
import time
import threading
import sys

# Configurações do cliente
HOST = '127.0.0.1'
PORT = 65433
BUFFER_SIZE = 1024
TIMEOUT = 10

# Flag de encerramento
running = True


def receive_messages(sock):
    """Função para receber mensagens do servidor em uma thread separada"""
    global running
    while running:
        try:
            data = sock.recv(BUFFER_SIZE)
            if not data:
                print("\nConexão encerrada pelo servidor.")
                running = False
                break
            print(data.decode('utf-8'), end='')
        except socket.timeout:
            print("\nErro: tempo limite de leitura atingido.")
            running = False
            break
        except ConnectionResetError:
            print("\nErro: O servidor foi encerrado inesperadamente.")
            running = False
            break
        except Exception as e:
            print(f"\nErro ao receber mensagem: {e}")
            running = False
            break


def encerrar(sock):
    """Encerramento gracioso da aplicação"""
    global running
    running = False
    try:
        sock.send('/quit'.encode('utf-8'))
    except:
        pass
    try:
        sock.shutdown(socket.SHUT_RDWR)
    except:
        pass
    finally:
        sock.close()
    print("\nDesconectado do servidor. Até logo!")


def main():
    global running
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(TIMEOUT)

        while True:
            try:
                s.connect((HOST, PORT))
                # Definindo timeout para operações de leitura
                s.settimeout(TIMEOUT)
                break
            except socket.timeout:
                print("Erro: tempo limite ao tentar conectar ao servidor.")
                time.sleep(5)
            except ConnectionRefusedError:
                print("Servidor não disponível. Tentando novamente em 5 segundos...")
                time.sleep(5)

        print(f"Conectado ao servidor de chat em {HOST}:{PORT}")

        # Inicia thread para receber mensagens
        receive_thread = threading.Thread(target=receive_messages, args=(s,))
        receive_thread.daemon = True
        receive_thread.start()

        # Loop principal para envio de mensagens
        while running:
            try:
                message = input()
                if not running:
                    break
                s.send(message.encode('utf-8'))
                if message == '/quit':
                    break
            except KeyboardInterrupt:
                print("\nEncerrando por interrupção do usuário (Ctrl+C)...")
                break
            except socket.timeout:
                print("Erro: tempo limite de envio de mensagem.")
                break
            except ConnectionResetError:
                print("Erro: O servidor encerrou a conexão.")
                break
            except Exception as e:
                print(f"Erro ao enviar mensagem: {e}")
                break

        encerrar(s)

    except Exception as e:
        print(f"Erro inesperado: {e}")


if __name__ == "__main__":
    main()
