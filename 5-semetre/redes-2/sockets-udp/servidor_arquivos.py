import socket
import os
import time
import sys

# Configurações do servidor
HOST = '0.0.0.0'
PORT = 9600
BUFFER_SIZE = 1024
DIRETORIO_ARQUIVOS = './arquivos_recebidos/'

# Criar diretório para salvar arquivos se não existir
os.makedirs(DIRETORIO_ARQUIVOS, exist_ok=True)

# Criar socket UDP
try:
    servidor = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    servidor.bind((HOST, PORT))
    print(f"Servidor UDP iniciado em {HOST}:{PORT}")
except socket.error as e:
    print(f"Erro ao criar socket: {e}")
    sys.exit(1)

# Função para receber arquivo


def receber_arquivo(nome_arquivo, endereco_cliente):
    caminho_arquivo = os.path.join(DIRETORIO_ARQUIVOS, nome_arquivo)
    arquivo = open(caminho_arquivo, 'wb')

    esperado = 0
    tamanho_total = 0

    tempo_inicio = time.time()

    while True:
        dados, _ = servidor.recvfrom(BUFFER_SIZE)

        if dados == b'fim':
            tempo_fim = time.time()
            print(f"Arquivo {nome_arquivo} recebido.")
            break

        num_seq = int.from_bytes(dados[:2], byteorder='big')
        fragmento = dados[2:]

        if num_seq == esperado:
            arquivo.write(fragmento)
            tamanho_total += len(fragmento)
            esperado += 1
            servidor.sendto(f"ack:{num_seq}".encode('utf-8'), endereco_cliente)
        else:
            servidor.sendto(
                f"ack:{esperado-1}".encode('utf-8'), endereco_cliente)

    arquivo.close()

    tempo_total = tempo_fim - tempo_inicio
    kibs = (tamanho_total / 1024) / tempo_total if tempo_total > 0 else 0

    print(f"Tamanho: {tamanho_total} bytes")
    print(f"Tempo: {tempo_total:.2f} segundos")
    print(f"Tamanho/Tempo: {kibs:.2f} KiB/s")


# Loop principal do servidor
try:
    print("Aguardando conexões...")
    while True:
        try:
            # Receber solicitação inicial
            dados, endereco = servidor.recvfrom(BUFFER_SIZE)
            mensagem = dados.decode('utf-8')

            # Se for uma solicitação de envio de arquivo
            if mensagem.startswith('ENVIAR:'):
                nome_arquivo = mensagem.split(':')[1]
                print(f"Nova conexão: {endereco}")

                # Enviar confirmação de pronto para receber
                servidor.sendto("PRONTO".encode('utf-8'), endereco)

                # Receber o arquivo
                receber_arquivo(nome_arquivo, endereco)

                print(f"Conexão fechada: {endereco}\n")

        except Exception as e:
            print(f"Erro: {e}")
except KeyboardInterrupt:
    print("\nServidor encerrado pelo usuário.")
finally:
    servidor.close()
    print("Socket do servidor fechado.")
