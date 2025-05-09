import socket
import os
import sys
import time

# Configurações do cliente
SERVIDOR_HOST = 'localhost'
SERVIDOR_PORT = 9600
BUFFER_SIZE = 1024
TAMANHO_FRAGMENTO = 1000
TIMEOUT = 1.0
MAX_TENTATIVAS = 10

# Criar socket UDP
try:
    cliente = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except socket.error as e:
    print(f"Erro ao criar socket: {e}")
    sys.exit(1)

# Função para enviar arquivo


def enviar_arquivo(caminho_arquivo):
    try:
        with open(caminho_arquivo, 'rb') as arquivo:
            data = arquivo.read()

        frag_num_total = (
            len(data) + TAMANHO_FRAGMENTO - 1) // TAMANHO_FRAGMENTO
        num_seq = 0

        cliente.settimeout(TIMEOUT)

        while num_seq < frag_num_total:
            start = num_seq * TAMANHO_FRAGMENTO
            end = start + TAMANHO_FRAGMENTO
            fragment = data[start:end]

            pacote = num_seq.to_bytes(2, byteorder='big') + fragment

            tentativas = 0
            enviado = False

            # tenta enviar o pacote até receber um ACK ou atingir o número máximo de tentativas
            while not enviado:
                if tentativas >= MAX_TENTATIVAS:
                    break

                try:
                    cliente.sendto(pacote, (SERVIDOR_HOST, SERVIDOR_PORT))
                    resposta, _ = cliente.recvfrom(BUFFER_SIZE)
                    resposta = resposta.decode('utf-8')

                    if resposta.startswith('ack:'):
                        ack_num = int(resposta.split(':')[1])
                        if ack_num == num_seq:
                            print(
                                f"\rProgresso {num_seq}/{frag_num_total}.", end="")
                            enviado = True
                            num_seq += 1

                except socket.timeout:
                    tentativas += 1

            if not enviado:
                print(
                    f"Falha ao enviar fragmento {num_seq} após {MAX_TENTATIVAS} tentativas.")
                return

        cliente.sendto(b'fim', (SERVIDOR_HOST, SERVIDOR_PORT))
        print("\nArquivo enviado!")

    except Exception as e:
        print(f"Erro ao enviar arquivo: {e}")


def main():
    if len(sys.argv) != 2:
        print("Uso: python cliente_arquivos.py <caminho_do_arquivo>")
        sys.exit(1)

    caminho_arquivo = sys.argv[1]

    # Verificar se o arquivo existe
    if not os.path.isfile(caminho_arquivo):
        print(f"Erro: O arquivo '{caminho_arquivo}' não existe.")
        sys.exit(1)

    try:
        # Enviar solicitação inicial ao servidor
        nome_arquivo = os.path.basename(caminho_arquivo)
        solicitacao = f"ENVIAR:{nome_arquivo}"
        print(f"Solicitando envio de '{nome_arquivo}' para o servidor...")
        cliente.sendto(solicitacao.encode('utf-8'),
                       (SERVIDOR_HOST, SERVIDOR_PORT))

        # Esperar confirmação do servidor
        cliente.settimeout(5.0)  # 5 segundos para timeout inicial
        try:
            resposta, _ = cliente.recvfrom(BUFFER_SIZE)
            if resposta.decode('utf-8') == "PRONTO":
                print("Servidor pronto para receber. Iniciando envio...")
                enviar_arquivo(caminho_arquivo)
            else:
                print(
                    f"Resposta inesperada do servidor: {resposta.decode('utf-8')}")
        except socket.timeout:
            print("Timeout: O servidor não respondeu à solicitação inicial.")
            sys.exit(1)

    except KeyboardInterrupt:
        print("\nCliente encerrado pelo usuário.")
    finally:
        cliente.close()
        print("Socket do cliente fechado.")


if __name__ == "__main__":
    main()
