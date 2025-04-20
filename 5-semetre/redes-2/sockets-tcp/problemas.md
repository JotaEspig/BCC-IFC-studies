# Problemas

1. ** Falha de gerenciamento de recursos **
  -- Não existe uma limitação relacionada a quantidade de conexões (sockets) abertas, caso muitos cliente queiram conectar, o servidor pode ficar sem recursos para atender a todos. Deveria ser implementado um limite de conexões simultâneas.

2. ** Vulnerabilidade a ataques **
  -- Esse problema é relacionado com o problema anterior. Um agente malicioso, sabendo disso, pode fazer um DoS (Denial of Service) no servidor, onde o atacante abre várias conexões e não fecha, fazendo com que o servidor fique sem recursos para atender a outros clientes.

3. ** Falta de validação de entrada **
  -- Não existe um filtro para validar os dados de entrada.
