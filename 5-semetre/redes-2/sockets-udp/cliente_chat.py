import socket
import threading
import sys

# Configurações do cliente
SERVIDOR_HOST = 'localhost'  # Endereço do servidor
SERVIDOR_PORT = 9500  # Porta do servidor
BUFFER_SIZE = 1024

# Criar socket UDP
try:
    cliente = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except socket.error as e:
    print(f"Erro ao criar socket: {e}")
    sys.exit(1)


# Função para receber mensagens.
def receber_mensagens():
    while True:
        try:
            dados, _ = cliente.recvfrom(BUFFER_SIZE)
            mensagem = dados.decode('utf-8')
            print(mensagem)
        except socket.error as e:
            print(f"Erro ao receber mensagem: {e}")
            break
        except KeyboardInterrupt:
            break


# Registrar usuário no servidor
def registrar_usuario(nome):
    mensagem_registro = f"/registro:{nome}"
    try:
        cliente.sendto(mensagem_registro.encode('utf-8'),
                       (SERVIDOR_HOST, SERVIDOR_PORT))
    except socket.error as e:
        print(f"Erro ao enviar mensagem: {e}")

# Função principal


def main():
    if len(sys.argv) != 2:
        print("Uso: python cliente_chat.py <seu_nome>")
        sys.exit(1)

    nome_usuario = sys.argv[1]

    try:
        # Registrar no servidor
        registrar_usuario(nome_usuario)

        # Iniciar thread para receber mensagens
        thread = threading.Thread(target=receber_mensagens)
        thread.daemon = True
        thread.start()

        print(f"Conectado ao servidor. Digite '/sair' para encerrar.")

        # Loop principal para enviar mensagens
        while True:
            mensagem = input()
            if mensagem.lower() == '/sair':
                msg = '/sair'
                try:
                    cliente.sendto(msg.encode(
                        'utf-8'), (SERVIDOR_HOST, SERVIDOR_PORT))
                except socket.error as e:
                    print(f"Erro ao enviar comando de saída: {e}")
                break
            else:
                try:
                    mensagem_completa = mensagem.encode('utf-8')
                    cliente.sendto(mensagem_completa,
                                   (SERVIDOR_HOST, SERVIDOR_PORT))
                except socket.error as e:
                    print(f"Erro ao enviar mensagem: {e}")
    except KeyboardInterrupt:
        print("\nCliente encerrado pelo usuário.")
    finally:
        cliente.close()
        print("Socket do cliente fechado.")


if __name__ == "__main__":
    main()
