import socket
import sys

# Configurações do servidor
HOST = '0.0.0.0'  # Aceita conexões de qualquer IP
PORT = 9500  # Porta para o servidor escutar
BUFFER_SIZE = 1024
# Dicionário para armazenar os clientes conectados (endereço: nome)
clientes = {}


# Criar socket UDP
try:
    servidor = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    servidor.bind((HOST, PORT))
    print(f"Servidor iniciado em {HOST}: {PORT}")
except socket.error as e:
    print(f"Erro ao criar socket: {e}")
    sys.exit(1)


# Função para enviar mensagem para todos os clientes
def broadcast(mensagem, endereco_origem=None):
    for addr, nome in clientes.items():
        if addr != endereco_origem:
            try:
                servidor.sendto(mensagem.encode('utf-8'), addr)
            except Exception as e:
                print(f"Erro enviando mensagem para {nome}{addr} -> {e}")


def main():
    # Loop principal do servidor
    try:
        print("Aguardando mensagens...")
        while True:
            try:
                # Receber mensagem e endereço do cliente
                dados, addr = servidor.recvfrom(BUFFER_SIZE)
                mensagem = dados.decode('utf-8')

                # Processar a mensagem recebida
                if mensagem.startswith('/registro:'):
                    nome = mensagem.split(':')[1].strip()
                    clientes[addr] = nome
                    print(f"Novo cliente registrado: {nome}{addr}")
                    broadcast(f"Novo cliente: {nome}{addr}")

                elif mensagem.startswith('/sair'):
                    if addr in clientes:
                        nome = clientes.pop(addr)
                        print(f"Cliente {nome} {addr} saiu.")
                        # Informa aos outros clientes sobre a saída
                        mensagem_saida = f"{nome} saiu."
                        broadcast(mensagem_saida, addr)
                    else:
                        print(
                            f"Erro: /sair de um cliente não registrado: {addr}")
                else:
                    if addr in clientes:
                        nome = clientes[addr]
                        msg_e_nome = f"{nome}: {mensagem}"
                        print(
                            f"BROADCAST {nome} {addr}: {mensagem}")
                        broadcast(msg_e_nome, addr)
                    else:
                        print(
                            f"Mensagem de um cliente não registrado {addr}: {mensagem}")
                        para_enviar = "Use /registro:<seu_nome> para enviar mensagens."
                        try:
                            servidor.sendto(
                                para_enviar.encode('utf-8'), addr)
                        except Exception as e:
                            print(
                                f"Erro ao enviar mensagem para se registrar para {addr}: {e}")
            except Exception as e:
                print(f"Erro no processamento da mensagem: {e}")
    except KeyboardInterrupt:
        print("\nServidor encerrado pelo usuário.")
    finally:
        servidor.close()
        print("Socket do servidor fechado.")


if __name__ == '__main__':
    main()
