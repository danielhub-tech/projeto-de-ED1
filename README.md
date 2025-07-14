# projeto-de-ED1
# Sistema de Gerenciamento - Açaiteria Bom Sabor

Este projeto é um Sistema de Gerenciamento de Pedidos para uma Açaíteria desenvolvido em C. O sistema utiliza manipulação de arquivos de texto para persistência de dados e programação estruturada para implementar operações básicas (Registrar, Listar, Editar, Excluir) e relatórios diversos.

## Funcionalidades

### Sistema de Login
-   **Autenticação de Usuário:** Login baseado em usuário e senha pré-definidos.
-   **Validação de E-mail:** Solicita um e-mail no login, garantindo que ele contenha o caractere `'@'` e que seja único (não tenha sido utilizado em logins anteriores).

### Operações básicas de Pedidos de Açaí
-   **Registrar :** Cadastra novos pedidos, incluindo nome do cliente, tamanho do copo (300ml, 500ml, 700ml) e número de adicionais.
-   **Listar :** Exibe todos os pedidos registrados na base de dados.
-   **Editar :** Modifica o tamanho ou o número de adicionais de um pedido existente, buscando pelo nome do cliente.
-   **Excluir :** Remove um pedido específico da base de dados.

### Cálculo de Preço
-   O sistema calcula automaticamente o preço do pedido com base no tamanho escolhido e adicionando R$ 1.50 por cada adicional selecionado.

### Persistência de Dados
-   **Pedidos:** Todas as informações dos pedidos são salvas no arquivo `pedidos_acai.txt`.
-   **E-mails de Login:** Os e-mails utilizados nos logins são salvos em `emails_usados.txt` para controle de unicidade.

### Operações e Relatórios Específicos
-   **Calcular Faturamento Total:** Soma o valor de todos os pedidos registrados e informa o total arrecadado.
-   **Busca por Cliente:** Localiza e lista todos os pedidos feitos por um cliente específico.
-   **Listagem por Tamanho:** Filtra e exibe pedidos de um tamanho específico (ex: 500ml).
-   **Listagem por Adicionais:** Lista todos os pedidos que possuem mais do que 'N' adicionais (onde 'N' é definido pelo usuário).
-   **Listagem por Valor:** Filtra pedidos que custaram acima de um determinado valor em reais.
